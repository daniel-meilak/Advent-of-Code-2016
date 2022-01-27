#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<sstream>
#include<iomanip>
#include<openssl/md5.h>
#include"utils.h"

std::string get_md5(const std::string& input){
    
    unsigned char result[MD5_DIGEST_LENGTH];
    MD5(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), result);

    std::ostringstream sout;
    sout << std::hex << std::setfill('0');
    for(long long c: result){ sout << std::setw(2) << (long long)c; }

    return sout.str();
}

int main(){

    std::string input = read_line("input_05");

    // index
    int index = 4000000;

    // passwords and hash
    std::string password1(8,'x');
    std::string password2(8,'x');
    std::string hash = "hash";

    // index for part 1
    int idx = 0;

    // vector of bool for filled password slots (part 2)
    std::vector<bool> filled(8,false);

    // loop while filled still has false entries
    while (std::find(filled.begin(), filled.end(), false) != filled.end()){

        hash = input+std::to_string(index);
        hash = get_md5(hash);

        while (hash.substr(0,5)!="00000"){
            index++;
            hash = input + std::to_string(index);
            hash = get_md5(hash);
        }

        // part 1
        if (idx < 8){
            password1[idx] = hash[5];
            idx++;
        }

        // part 2
        int pos = hash[5]-'0';
        if (pos >= 0 && pos < 8 && !filled[pos]){
            password2[pos] = hash[6];
            filled[pos] = true;
        }

        index++;
    }

    std::cout << "Answer (part 1): " << password1 << std::endl;
    std::cout << "Answer (part 2): " << password2 << std::endl;

    return 0;
}
