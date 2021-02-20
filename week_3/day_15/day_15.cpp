#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

int timing(std::vector<std::vector<std::string>> input, const bool part2);

int main(){
    
    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {"Disc #", "has", "positions; at time=0, it is at position", " ", "."};
    std::vector<std::vector<std::string>> input = read_input_2D("input", delimiters);

    std::cout << "Answer (part 1): " << timing(input,false) << std::endl;
    std::cout << "Answer (part 2): " << timing(input,true)  << std::endl;

    return 0;
}

int timing(std::vector<std::vector<std::string>> input, const bool part2){
    
    // for a correct start time, t, must solve following for all discs:
    // (start pos + disk index + t) mod disk size = 0

    // vector of sizes
    std::vector<int> sizes;

    // vector of starting positions
    std::vector<int> start_pos;

    if (part2){ input.push_back({"7","11","0"}); }

    // fill vectors from input
    for ( auto line : input ){
        sizes.push_back(std::stoi(line[1]));
        start_pos.push_back(std::stoi(line[2]));
    }

    // brute force solution

    int t = 0;
    bool ball_passes = false;
    while (!ball_passes){
        ball_passes = true;
        for (size_t i=0; i<input.size(); i++){
            ball_passes &= ((start_pos[i] + i+1 + t) % sizes[i] == 0);
        }
        if (!ball_passes){ t++; }
    }

    return t;
}