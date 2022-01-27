#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"utils.h"

// Forward function declarations
void move(int &dir, char &turn, int dist, int &x, int &y, std::vector<std::vector<bool>> &grid, std::vector<int> &visit_dist);

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input_01", {", "});

    // grid of visited locations
    std::vector<std::vector<bool>> grid(1000, std::vector<bool>(1000,false));

    // x and y position on grid
    int x = 0, y = 0;

    // starting direction is north
    int dir = 90;

    // visited distances (part 2)
    std::vector<int> visited_dist;

    // work through input
    for (std::string line : input){

        // perform movements
        move(dir, line[0], std::stoi(line.substr(1)), x, y, grid, visited_dist);
    }

    std::cout << "Answer (part 1): " << std::abs(x)+std::abs(y) << std::endl;
    std::cout << "Answer (part 2): " << visited_dist[0] << std::endl;

    return 0;
}

void move(int &dir, char &turn, int dist, int &x, int &y, std::vector<std::vector<bool>> &grid, std::vector<int> &visit_dist){

    // turn
    if (turn == 'L'){dir = mod(dir+90, 360);}
    else {dir = mod(dir-90, 360);}

    switch (dir){
        case 0:
            // set visited area and check for revisit
            for (int i=1; i<=dist; i++){
                if (grid[y+500][x+i+500]){ visit_dist.push_back(std::abs(x+i)+std::abs(y)); } 
                grid[y+500][x+i+500] = true;
            }
            // move 
            x += dist;
            break;
        case 90:
            // set visited area and check for revisit
            for (int i=1; i<=dist; i++){
                if (grid[y+i+500][x+500]){ visit_dist.push_back(std::abs(x)+std::abs(y+i)); } 
                grid[y+i+500][x+500] = true;
            }
            // move
            y += dist;
            break;
        case 180:
            // set visited area and check for revisit
            for (int i=1; i<=dist; i++){
                if (grid[y+500][x+500-i]){ visit_dist.push_back(std::abs(x-i)+std::abs(y)); } 
                grid[y+500][x+500-i] = true;
            }
            // move
            x -= dist;
            break;
        case 270:
            // set visited area and check for revisit
            for (int i=1; i<=dist; i++){
                if (grid[y+500-i][x+500]){ visit_dist.push_back(std::abs(x)+std::abs(y-i)); } 
                grid[y+500-i][x+500] = true;
            }
            // move
            y -= dist;
            break;
    }
}