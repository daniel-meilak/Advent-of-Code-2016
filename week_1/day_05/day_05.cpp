#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"
#include"md5.h"

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
        hash = MD5(hash).hexdigest();

        while (hash.substr(0,5)!="00000"){
            index++;
            hash = input + std::to_string(index);
            hash = MD5(hash).hexdigest();
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
