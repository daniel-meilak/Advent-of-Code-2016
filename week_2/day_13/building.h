#ifndef BUILDING_H
#define BUILDING_H

#include<vector>
#include<list>
#include<string>

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

#endif /* BUILDING_H */