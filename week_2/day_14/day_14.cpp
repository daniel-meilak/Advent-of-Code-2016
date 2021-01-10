#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<utility>
#include"../../Utils/utils.h"
#include"md5.h"

// forward function declaration
int find_hash(const std::string &input, const bool &part2);
char quintuple(std::string word);
bool first_triple(std::string word, char match);
std::string generate_hash(const std::string &word, const bool &part2);

int main(){

    std::string input = "cuanljph";
    // std::string input = "abc";

    // key stretching for part 2
    bool part1 = false;
    bool part2 = true;

    std::cout << "Answer (part 1): " << find_hash(input,part1) << std::endl;
    std::cout << "Answer (part 2): " << find_hash(input,part2) << std::endl;

    return 0;
}

// find 64th hash index
int find_hash(const std::string &input, const bool &part2){
    
    // vector to store hash indexes
    std::vector<int> indexes;

    // vector of calculated hashes
    std::vector<std::string> hashes;

    // index
    int i = 0;

    // generate at least 70 hashes 
    while (indexes.size() < 70){

        // check if more hashes need to be generated
        int stored_hashes = hashes.size();
        if (i == stored_hashes){

            // generate next 1000 hashes
            int max = stored_hashes+1000;
            for (int k=stored_hashes; k<max; k++){
                std::string hash = input + std::to_string(k);
                hashes.push_back(generate_hash(hash, part2));
            }
        }

        // check ith hash for quintuple
        char match = quintuple(hashes[i]);

        // if match is found
        if ( match != ' '){

            // check previous 1000 hashes for triple
            int j = i-1000;
            if (j < 0){ j=0; };

            while ( j != i ){

                // search for triple and make sure it hasnt already occured
                if ( first_triple(hashes[j], match) && (std::find(indexes.begin(), indexes.end(), j) == indexes.end()) ){
                        indexes.push_back(j);
                }
                j++;
            }
        }

        i++;
    }

    std::sort(indexes.begin(), indexes.end());

    return indexes[63];
}

// generate hash by hashing once or 2017 times
std::string generate_hash(const std::string &word, const bool &part2){
        
        std::string hash = word;

        if (part2){
            for (int k=0; k<2017; k++){
                hash = MD5(hash).hexdigest();
            }
        }
        else {
            hash = MD5(hash).hexdigest();
        }

        return hash;
}

// search for char repeating 5 times consecutively in string
char quintuple(std::string word){

    int max = word.size()-5;

    for (int i=0; i<=max; i++){
        bool check = true;
        char c = word[i];

        for (int j=i+1; j<i+5; j++){
            check *= (c == word[j]);
        }
        if (check){
            return c;
        }
    }

    return ' ';
}

// search for match repeating 3 times consecutively in string
bool first_triple(std::string word, char match){

    int max = word.size()-3;

    for (int i=0; i<=max; i++){
        if (word[i] == word[i+1] && word[i] == word[i+2]){
            if ( word[i] == match ){
                return true;
            }
            else {
                break;
            }
        }
    }

    return false;
}