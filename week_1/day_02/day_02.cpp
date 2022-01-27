#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_map>
#include<cstdlib>
#include"utils.h"

// Forward functino declarations
std::string passcode(const std::vector<std::string> &keypad, const std::vector<std::string> &input);

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input_02");

    // square keypads
    std::vector<std::string> keypad1 = {"123","456","789"};
    std::vector<std::string> keypad2 = {"  1  "," 234 ","56789"," ABC ","  D  "};

    std::cout << "Answer (part 1): " << passcode(keypad1, input) << std::endl;
    std::cout << "Answer (part 2): " << passcode(keypad2, input) << std::endl;

    return 0;
}

// creates maps of keypad neighbour relations and follows input directions
std::string passcode(const std::vector<std::string> &keypad, const std::vector<std::string> &input){
    
    // map of key relations
    std::unordered_map<char, std::unordered_map<char,char>> keys;

    int max_size = keypad.size(); 

    // construct key relations
    for (int x=0; x<max_size; x++){
        for (int y=0; y<max_size; y++){
            std::unordered_map<char,char> dir;
            
            // Up
            if (y==0 || keypad[y-1][x]==' '){dir['U']=keypad[y][x];}
            else {dir['U']=keypad[y-1][x];}

            // Down
            if (y==max_size-1 || keypad[y+1][x]==' '){dir['D']=keypad[y][x];}
            else {dir['D']=keypad[y+1][x];}

            // Left
            if (x==0 || keypad[y][x-1]==' '){dir['L']=keypad[y][x];}
            else {dir['L']=keypad[y][x-1];}

            // right
            if (x==max_size-1 || keypad[y][x+1]==' '){dir['R']=keypad[y][x];}
            else {dir['R']=keypad[y][x+1];}

            keys[keypad[y][x]] = dir;
        }
    }

    // current key
    char key = '5';

    // hold password
    std::string password;

    // work through input
    for (std::string line : input){

        // work through movements
        for (char c : line){
            key = keys[key][c];
        }

        password.push_back(key);
    }

    return password;
}