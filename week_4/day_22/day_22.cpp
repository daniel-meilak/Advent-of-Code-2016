#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

struct node{
    int size;
    int used;
    int avail;
    int percent;
    bool full = false;
};

int main(){
    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {"/dev/grid/node", "-", " ", "x", "y", "T", "%"};
    std::vector<std::vector<int>> input = input_to_int_2D(read_input_2D("input", delimiters));

    // width height with padding
    const int height = 34 + 2;
    const int width  = 30 + 2;

    // grid of nodes
    std::vector<std::vector<node>> grid(height, std::vector<node>(width));

    // digest input
    for ( const auto &line : input ){
        node &current = grid[line[0]+1][line[1]+1];

        current.size    = line[2];
        current.used    = line[3];
        current.avail   = line[4];
        current.percent = line[5];
    }

    // work thrrough grid and look for valid pairs
    int pairs = 0;
    int xmax = height-1, ymax = width-1;
    for (int x1=1; x1<xmax; x1++){
        for (int y1=1; y1<ymax; y1++){

            // if current not is empty -> invalid
            if (grid[x1][y1].used == 0){ continue; }

            // mark and skip the large nodes
            if (grid[x1][y1].size > 200){
                grid[x1][y1].full = true;
                continue;
            }

            // now we consider every other grid point
            for (int x2=1; x2<xmax; x2++){
                for (int y2=1; y2<ymax; y2++){

                    // node 1 and 2 cant be the same
                    if (x1==x2 && y1==y2){ continue; }

                    // check if data fits
                    if (grid[x2][y2].avail >= grid[x1][y1].used){
                        pairs++;
                    }
                }
            }
        }
    }

    std::cout << "Answer (part 1): " << pairs << std::endl << std::endl;

    std::cout << "Printout of nodes:" << std::endl;
    for (int x=1; x<xmax; x++){
        for (int y=1; y<ymax; y++){

            // destination
            if (x==1 && y==1){
                std::cout << 'S';
            }
            // goal data
            else if (x==34 && y==1){
                std::cout << 'G';
            }
            // unusable nodes
            else if (grid[x][y].full){
                std::cout << '#';
            }
            // empty node starting pos
            else if (grid[x][y].used == 0){
                std::cout << '_';
            }
            // moveable data
            else {
                std::cout << '.';
            }
        }
        std::cout << std::endl;
    }
    // can now easily solve by hand

    std::cout << std::endl << "Answer (part 2): " << 220 << std::endl;

    return 0;
}
