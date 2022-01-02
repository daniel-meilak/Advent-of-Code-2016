#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

bool ABBA(std::vector<std::string> &sequences);
bool ABA(std::vector<std::string> &hyper, std::vector<std::string> &non_hyper);
bool BAB(std::vector<std::string> &hyper, std::string bab);

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input_07", "");

    // valid ip adresses for part 1 and 2
    int count1 = 0;
    int count2 = 0;

    // work through ip addresses
    for (const std::string &ip : input){

        std::vector<std::string> hyper, non_hyper;

        std::string line = ip;
        while (line.find('[') != std::string::npos){
            int pos1 = line.find('[');
            int pos2 = line.find(']');

            non_hyper.push_back(line.substr(0,pos1));
            hyper.push_back(line.substr(pos1+1,pos2-(1+pos1)));

            line = line.substr(pos2+1);
        }
        non_hyper.push_back(line);

        // TLS requirements
        if (ABBA(non_hyper) && !ABBA(hyper)){
            count1++;
        }

        // SSL requirements
        if (ABA(hyper, non_hyper)){
            count2++;
        }
    }


    std::cout << "Answer (part 1): " << count1 << std::endl;
    std::cout << "Answer (part 2): " << count2 << std::endl;

    return 0;
}

// checks if vector of strings contain ABBA sequence
bool ABBA(std::vector<std::string> &sequences){

    for (std::string seq : sequences){

        // sequence must be at least 4 characters long
        if (seq.size()<4){ continue; }

        int size = seq.size()-3;
        for (int i=0; i<size; i++){

            // look for abba 
            if (seq[i] == seq[i+3] && seq[i+1] == seq[i+2] && seq[i] != seq[i+1]){ return true; }
        }
    }

    // no abba found
    return false;
}

// checks if ip contains ABA and BAB
bool ABA(std::vector<std::string> &hyper, std::vector<std::string> &non_hyper){

    for ( std::string seq : non_hyper ){

        // sequence must be at least 3 characters long
        if (seq.size()<3){ continue; }

        int size = seq.size()-2;
        for (int i=0; i<size; i++){

            // look for ABA
            if (seq[i] == seq[i+2] && seq[i] != seq[i+1]){

                // BAB sequence
                std::string bab = {seq[i+1], seq[i], seq[i+1]};

                // look for BAB
                if (BAB(hyper, bab)){ return true; }
            }
        }
    }

    // no aba found
    return false;
}

// search for BAB sequence in vector of strings
bool BAB(std::vector<std::string> &hyper, std::string bab){

    for ( std::string seq : hyper){

        // seach for BAB in each sequence
        if (seq.find(bab) != std::string::npos){ return true; }
    }

    return false;
}
