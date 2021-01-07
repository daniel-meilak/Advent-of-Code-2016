#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

// forward function declarations
long decompress(std::string input, bool part2);

int main(){

    // read input into vector of strings.
    std::vector<std::string> full_input = read_input("input", "");
    std::string input = full_input[0];

    // vector of weights initialized to 1
    std::vector<long> weights(input.size(), 1L);

    // total length
    long length = 0L;

    // work through input
    for (unsigned int i=0; i<input.size(); i++){

        // if char is not marker, add weight to total
        if ( input[i] != '(' ){
            length += weights[i];
        }
        // else when we reach a marker exctract values
        else {
            size_t pos1, pos2, pos3;
            pos1 = i;
            pos2 = input.find('x',pos1);
            pos3 = input.find(')',pos1);

            int a = std::stoi(input.substr(pos1+1, pos2-(pos1+1)));
            int b = std::stoi(input.substr(pos2+1, pos3-(pos2+1)));

            // adjust weights according to marker
            for (unsigned int j=pos3+1; j<pos3+1+a; j++){
                weights[j] *= b;
            }

            // skip marker
            i = pos3;
        }
    }

    std::cout << "Answer (part 2): " << length << std::endl;

    return 0;
}

