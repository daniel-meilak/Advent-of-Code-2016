#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"
#include"building.h"
#include"md5.h"

int main(){

    //std::string input = "kglvqrro";
    std::string input = "pslxynzg";

    // start and end points
    point start(0,0,input);
    point end(3,3,"");

    std::cout << "Answer (part 1): " << solve(start,end).path.substr(8) << std::endl;
    std::cout << "Answer (part 2): " << longest_path(start,end)         << std::endl;

    return 0;
}
