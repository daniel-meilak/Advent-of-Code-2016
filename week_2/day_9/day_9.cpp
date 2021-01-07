#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

// forward function declarations
int decompress1(std::string input);

int main(){

    // read input into vector of strings.
    std::vector<std::string> full_input = read_input("input_test", "");
    std::string input = full_input[0];

    std::cout << "Answer (part 1): " << decompress1(input) << std::endl;

    return 0;
}

// compression for part 1
// actually creates string
int decompress1(std::string input){
    
    size_t pos1 = input.find('(');

    while (pos1 != std::string::npos){

        size_t pos2 = input.find('x',pos1);
        size_t pos3 = input.find(')',pos1);

        // a is num of following char to capture
        // b is num of times to repeate those char
        int a = std::stoi(input.substr(pos1+1, pos2-(pos1+1)));
        int b = std::stoi(input.substr(pos2+1, pos3-(pos2+1)));

        std::string repeat = input.substr(pos3+1,a);
        std::string unwrap = "";

        // create repeated string
        for (int i=0; i<b; i++){
            unwrap += repeat;
        }

        // replace marker
        input.replace(pos1,pos3+a+1-pos1,unwrap);

        // find next marker
        pos1 = input.find('(',pos1+unwrap.size());
    }

    return input.size();
}

