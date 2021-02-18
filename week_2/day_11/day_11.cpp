#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"
#include"building.h"

int main(){

    // vector of reactor types
    std::vector<std::string> {"Th", "Pl", "St", "Pr", "Ru"};

    floor_t floor1 = {thing("Th",'G'), thing("Th",'M'), thing("Pl",'G'), thing("St",'G')};
    floor_t floor2 = {thing("Pl",'M'), thing("St",'M')};
    floor_t floor3 = {thing("Pr",'G'), thing("Pr",'M'), thing("Ru",'G'), thing("Ru",'M')};
    floor_t floor4 = {};

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

