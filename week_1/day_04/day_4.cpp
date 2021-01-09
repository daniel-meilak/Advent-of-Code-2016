#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<map>
#include<regex>
#include"../../Utils/utils.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input_test", "");

    // user regex to parse name, id and checksum
    std::regex r_name(R"(^[a-z\-]+)");
    std::regex r_id(R"([0-9]+)");
    std::regex r_checksum(R"([a-z]+(?=\]))");

    // sum of sector id's
    int sum = 0;

    // work through input
    for (const std::string & line : input){

        std::smatch s1,s2,s3;
        std::regex_search(line,s1,r_name);
        std::regex_search(line,s2,r_id);
        std::regex_search(line,s3,r_checksum);

        std::string name = s1.str();
        int id = std::stoi(s2.str());
        std::string checksum = s3.str();

        std::map<char,int> freq;

        for (char letter : name){
            if (letter == '-'){continue;}
            freq[letter]++;
        }

        // check checksum
        int value = freq[checksum[0]];

        // first check the first checksum value has the highest freq
        bool valid_checksum = true;
        for (auto const & pair : freq){
            if (pair.second > value){
                valid_checksum = false;
                break;
            }
        }
        if (!valid_checksum){continue;}

        // go through rest of checksum
        for (unsigned int i=1; i<checksum.size(); i++){
            int next = freq[checksum[i]];
            // if freq is 0 checksum is invalid
            if (next==0){
                valid_checksum = false;
                break;
            }
            
            // check if numbers go from large->small
            if (value > next){
                value = next;
            }
            // check that letters with same occurence are ordered well
            else if (value == next && checksum[i] > checksum[i-1]){
                value = next;
            }
            // otherwise invalid
            else {
                valid_checksum = false;
                break;
            }
        }
        
        if (valid_checksum){ sum+=id; }
    }


    std::cout << "Answer (part 1): " << sum << std::endl;
    std::cout << "Answer (part 2): " << std::endl;

    return 0;
}
