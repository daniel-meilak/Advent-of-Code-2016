#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<unordered_map>
#include"../../Utils/utils.h"

void copy(const std::string &x, const std::string &y, std::unordered_map<std::string, int> &reg);
void inc(const std::string &x, std::unordered_map<std::string, int> &reg);
void dec(const std::string &x, std::unordered_map<std::string, int> &reg);
void jnz(unsigned int &i, const std::string &x, const std::string &y, std::unordered_map<std::string, int> &reg);
int computer(const std::vector<int> &registers, const std::vector<std::vector<std::string>> &input);

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" "};
    std::vector<std::vector<std::string>> input = read_input_2D("input", delimiters);

    std::vector<int> reg1 = {0,0,0,0};
    std::vector<int> reg2 = {0,0,1,0};

    std::cout << "Answer (part 1): " << computer(reg1,input) << std::endl;
    std::cout << "Answer (part 2): " << computer(reg2,input) << std::endl;

    return 0;
}

int computer(const std::vector<int> &registers, const std::vector<std::vector<std::string>> &input){
    
    // map of reg
    std::unordered_map<std::string, int> reg;
    reg["a"] = registers[0];
    reg["b"] = registers[1];
    reg["c"] = registers[2];
    reg["d"] = registers[3];

    // work through instructions
    for (unsigned int i=0; i<input.size(); i++){

        std::vector<std::string> line = input[i];

        if (line[0] == "cpy"){ copy(line[1], line[2], reg); }
        else if (line[0] == "jnz"){ jnz(i, line[1], line[2], reg); }
        else if (line[0] == "inc"){ inc(line[1], reg); }
        else if (line[0] == "dec"){ dec(line[1], reg); }
        else {std::cout << "Invalid fnc" << std::endl;}
    }

    return reg["a"];
}

void copy(const std::string &x, const std::string &y, std::unordered_map<std::string, int> &reg){

    // if copying from register
    if (x=="a" || x=="b" || x=="c" || x=="d"){
        reg[y] = reg[x];
    }
    // otherwise copy from value
    else {
        reg[y] = std::stoi(x);
    }
}

void inc(const std::string &x, std::unordered_map<std::string, int> &reg){
    reg[x]++;
}

void dec(const std::string &x, std::unordered_map<std::string, int> &reg){
    reg[x]--;
}

void jnz(unsigned int &i, const std::string &x, const std::string &y, std::unordered_map<std::string, int> &reg){

    // if x is a register
    if (x=="a" || x=="b" || x=="c" || x=="d"){
        if (reg[x]==0){return;}
    }
    // if x is a value
    else {
        if (std::stoi(x)==0){return;}
    }

    i += std::stoi(y)-1;
}
