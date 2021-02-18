#pragma once

#include<vector>
#include<list>
#include<string>

//===================================================================================
// struct definitions
//===================================================================================

// struct of generator or microchip
struct thing{
    // variables
    std::string ele;
    char type;

    // constructors
    thing(std::string ele, char type);
};

// type of floor, contains generators or microchips
typedef std::vector<thing> floor_t;

// struct of building
struct building{
    // variables
    std::vector<floor_t> floors;
    int elevator;
    int steps = 0;

    // constructors
    building(int elevator, std::vector<floor_t> floors);

    // functions
    bool verify();
    bool is_solved();
};

// struct for unique building representation
struct red_build{
    // variables
    int elevator;
    std::vector<std::vector<int>> floor_tally;
    
    // constructor
    red_build(building build);
};


//===================================================================================
// Forward function declarations
//===================================================================================

// find the microchip complement to a generator or vice-versa
thing complement(thing gen_or_micro);

// moves item(s) from a floor to neighbouring floor. New building must be verified
building move(building current, const int &dir, const std::vector<thing> &items);

// find all the possible building configs from current state (one move)
std::vector<building> next_states(const building &state, std::vector<red_build> &uniques);

// compare building to vector of unique buildings
// if building is also unique, add to vector
bool unique_config(const building &build1, std::vector<red_build> &uniques);

// breadth first search algorithm to find the final state
building solve(const building & start_state);