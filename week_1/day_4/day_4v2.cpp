#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<utility>
#include<regex>
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

    // user regex to parse name, id and checksum
    std::regex r_name(R"(^[a-z\-]+)");
    std::regex r_id(R"([0-9]+)");
    std::regex r_checksum(R"([a-z]+(?=\]))");

    // sum of sector id's
    int sum = 0;

    // id of north-pole-objects
    int id_north_pole;

    // work through input
    for (const std::string & line : input){

        std::smatch s1,s2,s3;
        std::regex_search(line,s1,r_name);
        std::regex_search(line,s2,r_id);
        std::regex_search(line,s3,r_checksum);

        std::string name = s1.str();
        int id = std::stoi(s2.str());
        std::string checksum = s3.str();

        // vector of pair for each letter and its frequency
        std::vector<std::pair<char,int>> freq(26);

        // initialize freq, uses char ascii codes
        for (int i=0; i<26; i++){
            freq[i] = {i+97,0};
        }

        // fill freq using name
        for (const char & letter : name){
            if (letter == '-'){continue;}
            freq[letter-97].second++;
        }

        // sort freq first by number, then alphabetically
        std::sort(freq.begin(), freq.end(), greater_freq);

        // check that checksum is the first five values in freq
        bool valid_checksum = true;
        for (int i=0; i<5; i++){
            if (checksum[i] != freq[i].first){
                valid_checksum = false;
                break;
            }
        }

        if (!valid_checksum){continue;}
        
        // add to sum of id's
        sum+=id;
        
        // look for "north-pole-objects"
        for (char & letter : name){
            if (letter == '-'){continue;}
            int c  = ((letter-97)+id) % 26;
            letter = c+97; 
        }
        
        
        if (name.find("north") != std::string::npos){
            id_north_pole = id;
        }
    }


    std::cout << "Answer (part 1): " << sum           << std::endl;
    std::cout << "Answer (part 2): " << id_north_pole << std::endl;

    return 0;
}

