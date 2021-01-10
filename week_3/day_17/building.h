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
    std::string path;

    point(int x, int y, std::string path);
    point();

    bool is_valid();
};

//===================================================================================
// Forward function declarations
//===================================================================================

// find all the neighbours of the current point
std::vector<point> neighbours(const point &pos);

// breadth first search algorithm to find the final point
point solve(const point &start, const point &end);

// check if char n in string is in {b,c,d,e,f}
bool char_check(const std::string &hash, const int &n);

// find longest path length from start to end
int longest_path(const point &start, const point &end);

#endif /* BUILDING_H */