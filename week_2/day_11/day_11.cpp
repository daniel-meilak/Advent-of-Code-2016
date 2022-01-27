#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<unordered_map>
#include"utils.h"
#include"building.h"

const std::unordered_map<std::string,std::string> elem = {{"thulium","Th"},{"plutonium","Pl"},{"strontium","St"},{"promethium","Pr"},{"ruthenium","Ru"}};
const std::unordered_map<std::string,char> GM = {{"generator",'G'},{"microchip",'M'}};

floor_t fill_floor(const std::vector<std::string>& objects);

int main(){

    // read input
    std::vector<std::string> delimiters = {"The"," ",",","first","second","third","fourth","floor contains","-compatible","and","a ","nothing relevant","."};
    std::vector<std::vector<std::string>> input = read_input_2D("input_11",delimiters);

    // vector of reactor types
    std::vector<std::string> {"Th", "Pl", "St", "Pr", "Ru"};

    // floor_t floor1 = {thing("Th",'G'), thing("Th",'M'), thing("Pl",'G'), thing("St",'G')};
    floor_t floor1 = fill_floor(input[0]);
    floor_t floor2 = fill_floor(input[1]);
    floor_t floor3 = fill_floor(input[2]);
    floor_t floor4 = fill_floor(input[3]);

    building easter_building(0,{floor1, floor2, floor3, floor4});


    std::cout << "Answer (part 1): " << solve(easter_building).steps << std::endl;

    // floor 1 for part 2
    floor1.push_back(thing("El",'G'));
    floor1.push_back(thing("El",'M'));
    floor1.push_back(thing("Di",'G'));
    floor1.push_back(thing("Di",'M'));

    easter_building.floors[0] = floor1;

    std::cout << "Answer (part 2): " << solve(easter_building).steps << std::endl;

    return 0;
}

floor_t fill_floor(const std::vector<std::string>& objects){

    floor_t floor;

    for (size_t i=0; i<objects.size(); i+=2){
        floor.push_back(thing(elem.at(objects[i]),GM.at(objects[i+1])));
    }

    return floor;
}
