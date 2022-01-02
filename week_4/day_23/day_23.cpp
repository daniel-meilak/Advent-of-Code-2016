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
void tgl(const unsigned int &i, const std::string &x, std::vector<std::vector<std::string>> &input, std::unordered_map<std::string, int> &reg);
void mul(const std::string &b, const std::string &d, const std::string &a, std::unordered_map<std::string, int> &reg);
int computer(const std::vector<int> &registers, std::vector<std::vector<std::string>> input);

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" "};
    std::vector<std::vector<std::string>> input = read_input_2D("input_23", delimiters);

    std::vector<int> reg1 = {7,0,0,0};
    std::vector<int> reg2 = {12,0,0,0};

    std::cout << "Answer (part 1): " << computer(reg1,input) << std::endl;
    std::cout << "Answer (part 2): " << computer(reg2,input) << std::endl;

    return 0;
}

int computer(const std::vector<int> &registers, std::vector<std::vector<std::string>> input){
    
    // map of reg
    std::unordered_map<std::string, int> reg;
    reg["a"] = registers[0];
    reg["b"] = registers[1];
    reg["c"] = registers[2];
    reg["d"] = registers[3];

    // work through instructions
    for (unsigned int i=0; i<input.size(); i++){

        std::vector<std::string> &line = input[i];

        if (line[0] == "cpy"){ copy(line[1], line[2], reg); }
        else if (line[0] == "jnz"){ jnz(i, line[1], line[2], reg); }
        else if (line[0] == "inc"){ inc(line[1], reg); }
        else if (line[0] == "dec"){ dec(line[1], reg); }
        else if (line[0] == "tgl"){ tgl(i, line[1], input, reg); }
        else if (line[0] == "mul"){ mul(line[1], line[2], line[3], reg); }
        else {
            std::cout << "Invalid function in memory." << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    return reg["a"];
}

void tgl(const unsigned int &i, const std::string &x, std::vector<std::vector<std::string>> &input, std::unordered_map<std::string, int> &reg){

    int pos;

    // if taking pos from register
    if (x=="a" || x=="b" || x=="c" || x=="d"){ pos = reg[x]; }
    // otherwise pos is value
    else { pos = std::stoi(x); }

    // toggle according to register at i+pos
    // if i+pos is out of range continue
    if ( (i+pos) >= input.size() ){ return; }

    std::string &instr = input[i+pos][0];
    if (instr == "inc"){ instr = "dec"; }
    else if (instr == "dec"){ instr = "inc"; }
    else if (instr == "jnz"){ instr = "cpy"; }
    else if (instr == "cpy"){ instr = "jnz"; }
    else if (instr == "tgl"){ instr = "inc"; }
    else { std::cout << "There is a problem" << std::endl; }
}

void mul(const std::string &b, const std::string &d, const std::string &a, std::unordered_map<std::string, int> &reg){
    reg[a] += reg[b] * reg[d];
}

void copy(const std::string &x, const std::string &y, std::unordered_map<std::string, int> &reg){

    // check for invalid instruction (skip if invalid)
    std::string r = "abcd";
    if (r.find(y) == std::string::npos){ return; }

    // if copying from register
    if (x=="a" || x=="b" || x=="c" || x=="d"){ reg[y] = reg[x]; }
    // otherwise copy from value
    else { reg[y] = std::stoi(x); }
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
        if (reg[x]==0){ return; }
    }
    // if x is a value
    else if (std::stoi(x)==0){ return; }

    // if y is a register
    if (y=="a" || y=="b" || y=="c" || y=="d"){ i += reg[y]-1; }
    // if y is a value
    else { i += std::stoi(y)-1; }
}