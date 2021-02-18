#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"
#include"building.h"

int count_set_bits(int n);

int main(){

    point start(1,1);
    point end(31,39);

    // vector containing all unique squares found until end
    std::vector<point> uniques;

    std::cout << "Answer (part 1): " << solve(start, end, uniques).steps << std::endl;

    // count all unique points with less than 50 steps
    int count = 0;
    for (point p : uniques){
        if (p.steps<=50){ count++; }
    }

    std::cout << "Answer (part 2): " << count << std::endl;

    return 0;
}

