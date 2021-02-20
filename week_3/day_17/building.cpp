#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"building.h"
#include"md5.h"

//===================================================================================
// Struct Constructors
//===================================================================================

// point parametrised constructor
point::point(int x, int y, std::string path){
    this->x    = x;
    this->y    = y;
    this->path = path;
}

// point default constructor
point::point(){
    x=0;
    y=0;
    path = "";
}

//===================================================================================
// Struct operators
//===================================================================================

bool operator==(const point& lhs, const point& rhs){
    return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.path == rhs.path);
}

//===================================================================================
// Struct public functions
//===================================================================================

// verify point is in positive quadrand 
// and not wall
bool point::is_valid(){
    return (x >= 0) && (x < 4) && (y >= 0) && (y < 4);
}

//===================================================================================
// Other functions
//===================================================================================

// find all the neighbours of the current point
std::vector<point> neighbours(const point &pos){

    // take current path from pos and find hash
    std::string hash = MD5(pos.path).hexdigest();

    // vector of next positions
    std::vector<point> open;

    if (char_check(hash,0)){
        point next(pos.x,pos.y-1,pos.path+"U");
        next.steps = pos.steps+1;
        if (next.is_valid()){ open.push_back(next); }
    }    
    if (char_check(hash,1)){
        point next(pos.x,pos.y+1,pos.path+"D");
        next.steps = pos.steps+1;
        if (next.is_valid()){ open.push_back(next); }
    }
    if (char_check(hash,2)){
        point next(pos.x-1,pos.y,pos.path+"L");
        next.steps = pos.steps+1;
        if (next.is_valid()){ open.push_back(next); }
    }
    if (char_check(hash,3)){
        point next(pos.x+1,pos.y,pos.path+"R");
        next.steps = pos.steps+1;
        if (next.is_valid()){ open.push_back(next); }
    }

    return open;    
}

// check if char n in string is in {b,c,d,e,f}
bool char_check(const std::string &hash, const int &n){
    char c = hash[n];

    if (c=='b' || c=='c' || c=='d' || c=='e' || c=='f'){ return true; }

    return false;
}

// breadth first search algorithm to find the final point
point solve(const point &start, const point &end){

    // stack to work through
    std::list<point> queue = {start};

    while (queue.size() != 0){
        point current = queue.front();
        queue.pop_front();

        // if latest config is the solution, return
        if (current.x == end.x && current.y == end.y){ return current; }

        // find possible next steps from current
        std::vector<point> next_points = neighbours(current);

        // add next steps to queue
        for ( auto p : next_points){
            queue.push_back(p);
        }
    }

    return start;
}

// breadth first search algorithm to find the final point
int longest_path(const point &start, const point &end){

    // stack to work through
    std::list<point> queue = {start};

    // vector of lengths of paths
    std::vector<int> lengths;

    while (queue.size() != 0){
        point current = queue.front();
        queue.pop_front();

        // if latest config is the solution
        if (current.x == end.x && current.y == end.y){
            lengths.push_back(current.steps);
            continue;
        }

        // find possible next steps from current
        std::vector<point> next_points = neighbours(current);

        // add next steps to queue
        for ( auto p : next_points){
            queue.push_back(p);
        }
    }

    return lengths.back();
}