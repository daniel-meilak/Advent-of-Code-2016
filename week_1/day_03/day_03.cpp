#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

int part_1(std::vector<std::vector<int>> input);
int part_2(std::vector<std::vector<int>> input);

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" "};
    std::vector<std::vector<int>> input = input_to_int_2D(read_input_2D("input_03", delimiters));

    std::cout << "Answer (part 1): " << part_1(input) << std::endl;
    std::cout << "Answer (part 2): " << part_2(input) << std::endl;

    return 0;
}

int part_1(std::vector<std::vector<int>> input){
    
    // number of valid triangles
    int count = 0;

    // work through input
    for (std::vector<int> &sides : input){

        std::sort(sides.begin(), sides.end());

        if (sides[0]+sides[1] > sides[2]){count++;}
    }

    return count;
}

int part_2(std::vector<std::vector<int>> input){

    // number of valid triangles
    int count = 0;

    // work through input
    for (unsigned int i=0; i<input.size(); i+=3){

        std::vector<std::vector<int>> v(3);

        v[0] = {input[i][0], input[i+1][0], input[i+2][0]};
        v[1] = {input[i][1], input[i+1][1], input[i+2][1]};
        v[2] = {input[i][2], input[i+1][2], input[i+2][2]};

        // use part 1 to check triangles in v
        count += part_1(v);
    }

    return count;
}