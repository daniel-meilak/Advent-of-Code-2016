#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<unordered_map>
#include"utils.h"

struct carrier{
    // is the connection to
    std::string low_to;
    std::string high_to;

    // compaires low and high microchips
    int low_val;
    int high_val;

    // microchip storage
    int store;

    // num of held microchips
    int num_micro = 0;
};

// forward function declarations
void flow(std::unordered_map<std::string, carrier> &tree, const int &value, const std::string &name);

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {"goes to", "gives low to", "and high to", " "};
    std::vector<std::vector<std::string>> input = read_input_2D("input_10", delimiters);

    // map of bots and outputs
    std::unordered_map<std::string, carrier> tree;

    // create tree of bots
    for (auto line : input){

        if (line[0] == "bot"){

            // connections to
            tree[line[0]+line[1]].low_to  = line[2]+line[3];
            tree[line[0]+line[1]].high_to = line[4]+line[5];
        }
    }

    // pass values into tree
    for (auto line : input){

        if (line[0] == "value"){
            
            std::string name = line[2]+line[3];
            int value = std::stoi(line[1]);

            // propagate value through tree
            flow(tree, value, name);            
        }
    }

    // look for 61,17 bot
    for (auto pair : tree){
        if (pair.second.high_val == 61 && pair.second.low_val == 17){
            std::cout << "Answer (part 1): " << pair.first << std::endl;
            break;
        }
    }

    // multiply values of output 0,1 and 2
    int part2 = tree["output0"].store * tree["output1"].store * tree["output2"].store;

    std::cout << "Answer (part 2): " << part2 << std::endl;

    return 0;
}

// allows values to flow through tree of bots
void flow(std::unordered_map<std::string, carrier> &tree, const int &value, const std::string &name){

    carrier &bot = tree[name];

    // if recieving bot holds no microchips
    if (bot.num_micro == 0){
        
        bot.store = value;
        bot.num_micro++;
    }
    // else bot already holds a chip, pass to next bots or output
    else {
        int new_val = value;

        // new val goes to high output, stored value to low
        if (new_val > bot.store){
            bot.high_val = new_val;
            bot.low_val = bot.store;

            flow(tree,new_val,bot.high_to);
            flow(tree,bot.store,bot.low_to);
        }
        // new val goes to low output, stored value to high
        else {
            bot.high_val = bot.store;
            bot.low_val = new_val;

            flow(tree,new_val,bot.low_to);
            flow(tree,bot.store,bot.high_to);
        }
    }
}
