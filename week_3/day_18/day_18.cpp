#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

int safe_trap(const std::string &input, const int &rows);

int main(){

    // read input into string
    std::string input = read_line("input", {});

    const int rows1 = 40;
    const int rows2 = 400000;

    std::cout << "Answer (part 1): " << safe_trap(input,rows1) << std::endl;
    std::cout << "Answer (part 2): " << safe_trap(input,rows2) << std::endl;

    return 0;
}

// construct grid of traps "rows" long using first row from input
int safe_trap(const std::string &input, const int &rows){
    
    // grid of tiles
    std::vector<std::vector<bool>> grid(rows,std::vector<bool>(input.size()+2,true));

    // true = safe, false = trapped
    // build first row from input
    const int size = grid[0].size()-1;
    for (int i=1; i<size; i++){
        grid[0][i] = (input[i-1] == '.');
    }

    // build rest of grid
    const int grid_y = grid.size();
    const int grid_x = grid[0].size()-1;
    for (int y=1; y<grid_y; y++){
        for (int x=1; x<grid_x; x++){

            // left and centre false, right true
            bool cond1 = !grid[y-1][x-1] && !grid[y-1][x] && grid[y-1][x+1];
            // right and centre false, left true
            bool cond2 = !grid[y-1][x+1] && !grid[y-1][x] && grid[y-1][x-1];
            // left false, right and centre true
            bool cond3 = grid[y-1][x+1] && grid[y-1][x] && !grid[y-1][x-1];
            // right false, left and centre true
            bool cond4 = grid[y-1][x-1] && grid[y-1][x] && !grid[y-1][x+1];

            grid[y][x] = !(cond1 || cond2 || cond3 || cond4);
        }
    }

    // count safe tiles
    int safe = 0;
    for (auto row : grid){
        for (auto col : row){
            if (col){ safe++; }
        }
    }

    // remove borders
    safe -= rows*2;

    return safe;
}