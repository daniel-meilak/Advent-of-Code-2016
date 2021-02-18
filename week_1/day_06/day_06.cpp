#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

// sorting function for frequency of letters in string.
// First sorts by freq of letters, then alphabetically
struct{
    bool operator()(const std::pair<char,int> & left, const std::pair<char,int> & right) const{
        if (left.second != right.second){
            return left.second > right.second;
        }
        else {
            return left.first < right.first;
        }
    }
} greater_freq;

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    // vector of strings of input columns
    std::vector<std::string> columns(input[0].size());

    // extract columns
    for (std::string line : input){
        for (size_t i=0; i<line.size(); i++){
            columns[i].push_back(line[i]);
        }
    }

    // error corrected messages
    std::string message1;
    std::string message2;

    // use method from day_4v2 on each column
    for (std::string col : columns){
        // vector of pair for each letter and its frequency
        std::vector<std::pair<char,int>> freq(26);

        // initialize freq, uses char ascii codes
        for (int i=0; i<26; i++){
            freq[i] = {i+97,0};
        }

        // fill freq using name
        for (const char & letter : col){
            if (letter == '-'){continue;}
            freq[letter-97].second++;
        }

        // sort freq first by number, then alphabetically
        std::sort(freq.begin(), freq.end(), greater_freq);

        message1.push_back(freq.front().first);
        message2.push_back(freq.back().first);
    }

    std::cout << "Answer (part 1): " << message1 << std::endl;
    std::cout << "Answer (part 2): " << message2 << std::endl;

    return 0;
}
