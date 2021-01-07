#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

// forward function declarations
long decompress(std::string input, bool part2);
std::string repeat(std::string word, int n);

int main(){

    // read input into vector of strings.
    std::vector<std::string> full_input = read_input("input", "");
    std::string input = full_input[0];

    std::cout << "Answer (part 1): " << decompress(input,false) << std::endl;
    std::cout << "Answer (part 2): " << decompress(input,true)  << std::endl;

    return 0;
}

long decompress(std::string input, bool part2){

    if (input.find('(') == std::string::npos){
        return input.size();
    }

    // output length
    long length = 0;

    while (input.find('(') != std::string::npos){

        // add any characters before '('
        length += input.find('(');

        // cut off everything before start of marker from input
        input = input.substr(input.find('('));

        // extract a and b
        size_t pos1, pos2, pos3;
        pos1 = input.find('(');
        pos2 = input.find('x');
        pos3 = input.find(')');
        int a = std::stoi(input.substr(pos1+1, pos2-(pos1+1)));
        int b = std::stoi(input.substr(pos2+1, pos3-(pos2+1)));

        // remove marker portion from input
        input = input.substr(pos3+1);

        // add length of substring to total length
        if (part2){
            length += decompress( repeat(input.substr(0,a), b), part2 );
        }
        else {
            length += repeat(input.substr(0,a), b).size();
        }

        // remove substring from input
        input = input.substr(a);
    }

    // add length of left over input
    length += input.size();

    return length;
}

// repeat string n times
std::string repeat(std::string word, int n){
    
    std::string output = "";

    for (int i=0; i<n; i++){
        output += word;
    }

    return output; 
}

