#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<utility>
#include<cstdlib>
#include"utils.h"

// forward function declarations
int part1(const int &input);
int part2(const int &input);

int main(){

    int input = std::stoi(read_line("input_19"));

    std::cout << "Answer (part 1): " << part1(input) << std::endl;
    std::cout << "Answer (part 2): " << part2(input) << std::endl;

    return 0;
}

// simulate the problem
int part1(const int &input){
    
    std::list<std::pair<int,int>> elves(input);

    int i=1;
    for (auto & elf : elves){
        elf.first  = 1;
        elf.second = i;
        i++;
    }

    // start of list
    auto it = elves.begin();

    // play white elephant parties
    while (elves.size() > 1){

        auto next = next_cyclic(it,1,elves);
        (*it).first += (*next).first;
        elves.erase(next);
        advance_cyclic(it,1,elves);
    }

    return elves.front().second;
}

// for part two we move around two linked lists as if moving around
// elves
int part2(const int &input){

    std::list<int> first, second;

    // fill lists with indexes
    for (int i=1; i<=input/2; i++){ first.push_back(i); }
    for (int i=1+(input/2); i<=input; i++){ second.push_back(i); }

    // reduce lists untill left with one elf
    while (first.size()> 1){

        // take the 1st elf from first list
        int current = first.front();
        first.pop_front();

        // if the lists are the same size take from end of first
        if (first.size() == second.size()){ first.pop_back(); }
        // else take from front of second
        else { second.pop_front(); }

        // put the 1st elf from first at the back of second
        second.push_back(current);

        // take the first elf from second and put at the end of first
        int shuffle = second.front();
        second.pop_front();
        first.push_back(shuffle);
    }

    return first.front();
}