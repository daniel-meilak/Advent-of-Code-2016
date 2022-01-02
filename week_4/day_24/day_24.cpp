#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<cctype>
#include<map>
#include<utility>
#include"../../Utils/utils.h"
#include"building.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input_24", "");

    // find numbered positions
    std::vector<std::vector<int>> pos;

    const int size_y = input.size();
    const int size_x = input[0].size(); 
    for (int y=0; y<size_y; y++){
        for (int x=0; x<size_x; x++){
            if (std::isdigit(input[y][x])){ pos.push_back({input[y][x]-'0',y,x}); }
        }
    }

    // map of distances from each point to other points
    std::map<std::string, int> distances;

    // use BFS to find distances between each point
    for (auto p1 : pos){
        for (auto p2 : pos){
            // ignore distance from point to itself
            if (p1 == p2){ continue; }
            
            distances[std::to_string(p1[0])+std::to_string(p2[0])] = solve(point{p1[2],p1[1]}, point{p2[2],p2[1]}, input);
        }
    }

    std::vector<int> route = {1,2,3,4,5,6,7};

    int min_dist1 = 100000;
    int min_dist2 = 100000;

    // brute force the lowest total distance between points
    do {
        int start = 0;
        int total = 0;
        for (int num : route){
            total += distances[std::to_string(start)+std::to_string(num)];
            start = num;
        }
        if (total < min_dist1){ min_dist1 = total; }

        total += distances[std::to_string(start)+std::to_string(0)];
        if (total < min_dist2){ min_dist2 = total; }

    } while (std::next_permutation(route.begin(), route.end()));
    
    std::cout << "Answer (part 1): " << min_dist1 << std::endl;
    std::cout << "Answer (part 2): " << min_dist2 << std::endl;

    return 0;
}
