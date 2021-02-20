#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

void swap_letter(std::string &word, const char &c1, const char &c2);
void rotate(std::string &word, const int &n);
void rotate_based(std::string &word, const char &c);
void move(std::string &word, const int &pos1, const int &pos2);
void rotate_based_r(std::string &word, const char &c);
std::string part1(std::string &pass, const std::vector<std::vector<std::string>> &input);
std::string part2(std::string &pass, const std::vector<std::vector<std::string>> &input);


int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" ", "with", "letter", "step", "through", "of", "to"};
    std::vector<std::vector<std::string>> input = read_input_2D("input", delimiters);

    // passwords
    std::string pass1 = "abcdefgh";
    std::string pass2 = "fbgdceah";    

    std::cout << "Answer (part 1): " << part1(pass1,input) << std::endl;
    std::cout << "Answer (part 2): " << part2(pass2,input) << std::endl;

    return 0;
}

std::string part1(std::string &pass, const std::vector<std::vector<std::string>> &input){
    
    // work through input
    for ( auto line : input ){

        if (line[0] == "swap"){
            // swap position
            if (line[1] == "position"){ std::swap( pass[std::stoi(line[2])], pass[std::stoi(line[4])] ); }
            // swap letter
            else { swap_letter(pass,line[1][0],line[2][0]); }
        }
        else if (line[0] == "reverse"){
            //reverse position
            std::reverse(pass.begin()+std::stoi(line[2]), pass.begin()+std::stoi(line[3])+1);
        }
        else if (line[0] == "rotate"){
            // rotate left
            if (line[1] == "left"){ rotate(pass, std::stoi(line[2])); }
            // rotate right
            else if (line[1] == "right"){ rotate(pass, -std::stoi(line[2])); }
            // rotate based on
            else { rotate_based(pass, line[4][0]); }
        }
        else if (line[0] == "move"){ move(pass, std::stoi(line[2]), std::stoi(line[4])); }
    }

    return pass;
}

std::string part2(std::string &pass, const std::vector<std::vector<std::string>> &input){
    
    // work through input
    const int size = input.size()-1;
    for ( int i=size; i>=0; i--){
        const std::vector<std::string> &line = input[i];

        if (line[0] == "swap"){
            // swap position
            if (line[1] == "position"){ std::swap( pass[std::stoi(line[2])], pass[std::stoi(line[4])] ); }
            // swap letter
            else { swap_letter(pass,line[1][0],line[2][0]); }
        }
        else if (line[0] == "reverse"){
            //reverse position
            std::reverse(pass.begin()+std::stoi(line[2]), pass.begin()+std::stoi(line[3])+1);
        }
        else if (line[0] == "rotate"){
            // rotate left
            if (line[1] == "left"){ rotate(pass, -std::stoi(line[2])); }
            // rotate right
            else if (line[1] == "right"){ rotate(pass, std::stoi(line[2])); }
            // rotate based on
            else { rotate_based_r(pass, line[4][0]); }
        }
        else if (line[0] == "move"){ move(pass, std::stoi(line[4]), std::stoi(line[2])); }
    }

    return pass;
}

void swap_letter(std::string &word, const char &c1, const char &c2){

    size_t pos1 = word.find(c1);
    size_t pos2 = word.find(c2);

    word[pos1] = c2;
    word[pos2] = c1;
}

void rotate(std::string &word, const int &n){
    std::string copy = word;

    const int size = word.size(); 
    for (int i=0; i<size; i++){
        word[i] = copy[mod(i+n,size)];
    }
}

void rotate_based(std::string &word, const char &c){

    size_t pos = word.find(c);

    if (pos < 4){ rotate(word, -(1+pos)); }
    else { rotate(word, -(2+pos)); }
}

void rotate_based_r(std::string &word, const char &c){

    size_t pos = word.find(c);

    if      (pos == 0){ rotate(word, 1); }
    else if (pos == 1){ rotate(word, 1); }
    else if (pos == 2){ rotate(word,-2); }
    else if (pos == 3){ rotate(word, 2); }
    else if (pos == 4){ rotate(word,-1); }
    else if (pos == 5){ rotate(word, 3); }
    else if (pos == 7){ rotate(word,-4); }
}

void move(std::string &word, const int &pos1, const int &pos2){

    char c = word[pos1];

    word.erase(word.begin()+pos1);

    if (pos2 == (int)word.size()){ word.push_back(c); }
    else { word.insert(word.begin()+pos2,c); }
}
