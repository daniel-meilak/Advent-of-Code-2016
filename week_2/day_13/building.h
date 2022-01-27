#pragma once

#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"utils.h"

const int input = std::stoi(read_line("input_13"));

//===================================================================================
// struct definitions
//===================================================================================

// struct of point
struct point{
    int x;
    int y;
    int steps = 0;

    point(int x, int y);
    point();

    bool is_valid();
};

//===================================================================================
// Forward function declarations
//===================================================================================

// find all the neighbours of the current point
std::vector<point> neighbours(const point &pos, std::vector<point> &uniques);

// breadth first search algorithm to find the final point
point solve(const point &start, const point &end, std::vector<point> &uniques);

// Function to get no of set bits in binary 
// representation of positive integer n 
int count_set_bits(int n);

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

bool operator==(const point& lhs, const point& rhs){
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
bool point::is_valid(){

    int temp = x*x + 3*x + 2*x*y + y + y*y;
    temp += input;

    return (count_set_bits(temp) % 2 == 0) && (x >= 0 ) && (y >= 0);
}

//===================================================================================
// Other functions
//===================================================================================

// find all the neighbours of the current point
std::vector<point> neighbours(const point &pos, std::vector<point> &uniques){

    // vector of next building configs
    std::vector<point> neighbours(4);
    std::vector<point> output;

    neighbours[0] = pos + point( 0, 1);
    neighbours[1] = pos + point( 1, 0);
    neighbours[2] = pos + point( 0,-1);
    neighbours[3] = pos + point(-1, 0);

    for (auto it=neighbours.begin(); it != neighbours.end(); it++){
        point &p = *it;

        if (p.is_valid() && (std::find(uniques.begin(), uniques.end(), p) == uniques.end())){
            p.steps = pos.steps+1;
            uniques.push_back(p);
            output.push_back(p);
        }
    }

    return output;    
}

// breadth first search algorithm to find the final point
point solve(const point &start, const point &end, std::vector<point> &uniques){

    // stack to work through
    std::list<point> queue = {start};

    while (queue.size() != 0){
        point current = queue.front();
        queue.pop_front();

        // if latest config is the solution, return
        if (current == end){ return current; }

        // find possible next steps from current
        std::vector<point> next_points = neighbours(current, uniques);

        // add next steps to queue
        for ( auto p : next_points){
            queue.push_back(p);
        }
    }

    return start;
}

// Function to get no of set bits in binary 
// representation of positive integer n 
int count_set_bits(int n){

    int count = 0; 
    while (n){ 
        count += n & 1; 
        n >>= 1; 
    } 
    return count; 
}   
