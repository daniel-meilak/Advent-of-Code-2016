#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"building.h"

//===================================================================================
// Struct Constructors
//===================================================================================

// point parametrised constructor
point::point(int x, int y){
    this->x = x;
    this->y = y;
}

// point default constructor
point::point(){
    x=0;
    y=0;
}

//===================================================================================
// Struct operators
//===================================================================================

bool operator==(const point& lhs, const point& rhs)
{
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

point operator+(const point& lhs, const point& rhs){

    return {lhs.x+rhs.x, lhs.y+rhs.y};
}


//===================================================================================
// Struct public functions
//===================================================================================

// verify point is in positive quadrand 
// and not wall
bool point::is_valid(const char &c){

    return (c != '#') && (x >= 0 ) && (y >= 0) && (x < 185) && (y < 41);
}

//===================================================================================
// Other functions
//===================================================================================

// find all the neighbours of the current point
std::vector<point> neighbours(const point &pos, std::vector<point> &uniques, const std::vector<std::string> &input){

    // vector of next building configs
    std::vector<point> neighbours(4);
    std::vector<point> output;

    neighbours[0] = pos + point( 0, 1);
    neighbours[1] = pos + point( 1, 0);
    neighbours[2] = pos + point( 0,-1);
    neighbours[3] = pos + point(-1, 0);

    for (auto it=neighbours.begin(); it != neighbours.end(); it++){
        point &p = *it;

        if (p.is_valid(input[p.y][p.x]) && (std::find(uniques.begin(), uniques.end(), p) == uniques.end())){
            p.steps = pos.steps+1;
            uniques.push_back(p);
            output.push_back(p);
        }
    }

    return output;    
}

// breadth first search algorithm to find the final point
int solve(const point &start, const point &end, const std::vector<std::string> &input){

    // stack to work through
    std::list<point> queue = {start};

    // vector of uniques
    std::vector<point> uniques = {start};

    while (queue.size() != 0){
        point current = queue.front();
        queue.pop_front();

        // if latest config is the solution, return
        if (current == end){ return current.steps; }

        // find possible next steps from current
        std::vector<point> next_points = neighbours(current, uniques, input);

        // add next steps to queue
        for ( auto p : next_points){
            queue.push_back(p);
        }
    }

    return start.steps;
}