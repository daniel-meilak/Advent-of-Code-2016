#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

// sorting function for vec of vec of llint
bool sortcol( const std::vector<long long> &lhs, const std::vector<long long> &rhs){
    return lhs[0] < rhs[0];
}

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {"-"};
    std::vector<std::vector<long long>> input = input_to_llint_2D(read_input_2D("input_20", delimiters));

    // sort input according to first column
    std::sort(input.begin(), input.end(), sortcol);

    // number of free ips
    int allowed = 0;

    // first free ip
    long long ip = 0LL;

    // keep track of max ip 
    long long max = 0;

    const int size = input.size();
    for (int i=0; i<size; i++){

        const long long &low  = input[i][0];
        const long long &high = input[i][1];

        // if range is connect, increase max to next high
        if ( low <= max+1LL && high > max){ max = high; }
        // if range is disconnected, add gap to allowed
        else if ( low > max+1LL){
            if (ip==0LL){ ip = max+1LL; }
            allowed += low-(max+1LL);
            max = high;
        }

        // ranges within max are ignored

    }

    std::cout << "Answer (part 1): " << ip      << std::endl;
    std::cout << "Answer (part 2): " << allowed << std::endl;

    return 0;
}
