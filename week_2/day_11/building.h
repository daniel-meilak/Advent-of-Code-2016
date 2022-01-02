#pragma once

#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<cstdlib>

//===================================================================================
// struct definitions
//===================================================================================

// struct of generator or microchip
struct thing{
    // variables
    std::string ele;
    char type;

    // thing parametrised constructor
    thing(std::string ele, char type){
        this->ele   = ele;
        this->type  = type;
    }
};

thing complement(thing gen_or_micro);

// type of floor, contains generators or microchips
typedef std::vector<thing> floor_t;

// struct of building
struct building{
    // variables
    std::vector<floor_t> floors;
    int elevator;
    int steps = 0;

    // building parametrised constructor
    building(int elevator, std::vector<floor_t> floors){
        this->elevator = elevator;
        this->floors   = floors;
    }

    // functions
    bool verify();
    bool is_solved();
};

// struct for unique building representation
struct red_build{
    // variables
    int elevator;
    std::vector<std::vector<int>> floor_tally;
    
    // create unique rep of building from building
    red_build(building build){
        elevator = build.elevator;

        // build tally
        for ( auto floor : build.floors ){
            // separate microchips and generators
            std::vector<thing> micros, gens;
            int pairs = 0;
            for (thing item : floor){
                if (item.type == 'M'){ micros.push_back(item); }
                else { gens.push_back(item); }
            }

            // check for pairs
            for (auto micro : micros){
                thing gen = complement(micro);
                if (std::find(gens.begin(), gens.end(), gen) != gens.end()){pairs++;}
            }

            int m = micros.size();
            int g = gens.size();
            floor_tally.push_back({pairs, m, g});
        }
    }
};

//===================================================================================
// Struct operators
//===================================================================================

bool operator==(const red_build& lhs, const red_build& rhs)
{
    if (lhs.elevator == rhs.elevator){
        if (lhs.floor_tally == rhs.floor_tally){
            return true;
        }
    }

    return false;
}

bool operator==(const thing& lhs, const thing& rhs)
{
    if (lhs.ele == rhs.ele){
        if (lhs.type == rhs.type){
            return true;
        }
    }

    return false;
}

//===================================================================================
// Forward function declarations
//===================================================================================

// find the microchip complement to a generator or vice-versa
thing complement(thing gen_or_micro){
    if (gen_or_micro.type == 'M'){
        gen_or_micro.type = 'G';
        return gen_or_micro;
    }
    else if (gen_or_micro.type == 'G'){
        gen_or_micro.type = 'M';
        return gen_or_micro;
    }
    else {
        std::cout << "Error, invalid thing type" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

// moves item(s) from a floor to neighbouring floor. New building must be verified
building move(building current, const int &dir, const std::vector<thing> &items){

    floor_t &source = current.floors[current.elevator];

    // move elevator and check if move is invalid
    current.elevator += dir;
    if (current.elevator < 0 || current.elevator > (int)current.floors.size()-1){return current;}

    floor_t &dest   = current.floors[current.elevator];

    // remove item(s) from source
    for (thing item : items){ source.erase(std::remove(source.begin(), source.end(), item), source.end()); }

    // add item(s) to dest
    for (thing item : items){ dest.push_back(item); }

    // increase steps
    current.steps++;

    return current;
}

// compare building to vector of unique buildings
// if building is also unique, add to vector
bool unique_config(const building &build1, std::vector<red_build> &uniques){

    // first convert build1 to red_build representation
    red_build new_build(build1);

    // if new build is found in uniques, it is not unique
    for ( auto unique : uniques ){
        if (new_build == unique){ return false; }
    }

    // not in uniques, add to uniques
    uniques.push_back(new_build);

    return true;
}

// find all the possible building configs from current state (one move)
std::vector<building> next_states(const building &state, std::vector<red_build> &uniques){

    // vector of next building configs
    std::vector<building> buildings;

    // current floor
    int i = state.elevator;

    // 2 items moves
    size_t floor_size = state.floors[i].size();
    for (size_t j=0; j<floor_size; j++){
        for (size_t k=j+1; k<floor_size; k++){

            building move1 = move(state,  1, {state.floors[i][j], state.floors[i][k]});
            building move2 = move(state, -1, {state.floors[i][j], state.floors[i][k]});

            // if valid, check if unique, then add to lists
            if (move1.verify() && unique_config(move1, uniques)){ buildings.push_back(move1); }

            if (move2.verify() && unique_config(move2, uniques)){ buildings.push_back(move2); }
        }    
    }
    

    // 1 item moves
    for (size_t j=0; j<floor_size; j++){

        // up move and down move
        building move1 = move(state,  1, {state.floors[i][j]});
        building move2 = move(state, -1, {state.floors[i][j]});

        // if valid, check if unique, then add to lists
        if (move1.verify() && unique_config(move1, uniques)){ buildings.push_back(move1); }

        if (move2.verify() && unique_config(move2, uniques)){ buildings.push_back(move2); }    
    }

    return buildings;    
}

// breadth first search algorithm to find the final state
building solve(const building & start_state){

    // stack to work through
    std::list<building> queue = {start_state};

    // unique representation of buildings
    std::vector<red_build> uniques = {red_build(start_state)};

    while (queue.size() != 0){
        building current = queue.front();
        queue.pop_front();

        // if latest config is the solution, return
        if (current.is_solved()){ return current; }

        // find possible next steps from current
        std::vector<building> next_steps = next_states(current, uniques);

        // add next steps to queue
        for ( auto step : next_steps){
            queue.push_back(step);
        }
    }

    return start_state;
}

//===================================================================================
// Struct public functions
//===================================================================================

// verify building contents are valid
bool building::verify(){

    // check elevator position is valid
    int max_floor = floors.size()-1;
    if (elevator < 0 || elevator > max_floor){return false;}

    for ( auto floor : floors ){
        // separate microchips and generators
        std::vector<thing> micros, gens;
        for (thing item : floor){
            if (item.type == 'M'){ micros.push_back(item); }
            else { gens.push_back(item); }
        }

        // if no generators floor is valid
        if (gens.size() == 0){ continue; }

        // check for chips without matching generator
        for (auto chip : micros){

            // complement must be in gens to be valid
            if (std::find(gens.begin(), gens.end(),complement(chip))==gens.end()){ return false; }
        }
    }

    return true;
}

// found solution if floor 4 contains all items
bool building::is_solved(){

    for (size_t i=0; i<floors.size()-1; i++){
        if (floors[i].size()!=0){ return false; }
    }

    return true;
}   