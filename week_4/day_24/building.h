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

    bool is_valid(const char &c);
};

//===================================================================================
// Forward function declarations
//===================================================================================

// find all the neighbours of the current point
std::vector<point> neighbours(const point &pos, std::vector<point> &uniques, const std::vector<std::string> &input);

// breadth first search algorithm to find the final point
int solve(const point &start, const point &end, const std::vector<std::string> &input);

#endif /* BUILDING_H */