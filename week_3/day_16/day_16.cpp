#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

// forward function declarations
std::string reduce(const std::string &data);
std::string calc_checksum(const std::string &input, const int &size);

int main(){

    std::string input = "10111100110001111";

    // required size of data
    int size1 = 272;
    int size2 = 35651584;

    std::cout << "Answer (part 1): " << calc_checksum(input,size1) << std::endl;
    std::cout << "Answer (part 2): " << calc_checksum(input,size2) <<std::endl;

    return 0;
}

std::string calc_checksum(const std::string &input, const int &size){

    std::string data = input;

    while ( (int)data.size() < size ){
        std::string b = data;
        std::reverse(b.begin(), b.end());

        // change 1s to a temporarily, then 0->1 and a->0
        std::replace(b.begin(), b.end(), '1', 'a');
        std::replace(b.begin(), b.end(), '0', '1');
        std::replace(b.begin(), b.end(), 'a', '0');

        data += "0" + b;        
    }

    // reduce data to required size
    std::string required_data = data.substr(0,size);

    // calculate checksum of data
    std::string checksum = reduce(required_data);

    // calculate checksum of checksum untill size is odd
    while ( checksum.size() % 2 == 0 ){
        checksum = reduce(checksum);
    }

    return checksum;
}

// creates checksum of data string
std::string reduce(const std::string &data){

    std::string checksum;

    int max = data.size();

    // for every pair of values
    for (int i=0; i<max; i+=2){

        // if the same ("11" or "00")
        if (data[i] == data[i+1]){ checksum.push_back('1'); }
        // if different ("01" or "10")
        else { checksum.push_back('0'); }
    }

    return checksum;
}


