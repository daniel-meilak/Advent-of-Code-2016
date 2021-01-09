## Day 4

Not particularly happy for my implementation in part 1. I create a map of letter frequencies to validate the checksum. This map is only sorted alphabetically, not in the frequency of those letters. 

Hence, various checks have to be done to verify the correctness of the checksum:
- check that first value in checksum has the highest frequency in the name
- check that checksum contains no letters of 0 frequency
- check that checksum is ordered in terms of frequency
- check that letters of the same frequency are ordered alphabetically

None of this is done automatically. In addition, I can see a way for checksums to still be false if, for example, there are many letters of the same frequency and some of these are ordered alphabetically in the checksum, however some are omitted (missing the 2nd for example but instead containing the 6th). In this case, the checksum is ordered well but is still not correct.

The best way to remedy this would be to create some kind of container that automatically ordered according to size first, and then alphabetically second.

There is a possible solution:
- create vector of pairs of size 26 (num of letters in alphabet) and initialize all values to zero and the corresponding letter.
- loop through name and convert char to index of vector using the ascii code
- increment values in vector according to ascii code (using the index from previous step, no need to find the letter)
- create a sorting function which sorts according to value first and alphabetical order second

This way filling the vector is faster (no need for hash) and verifying the checksum is also fast as it needs to be the same as the first five values in the vector. Largest slowdown is now sorting the vector of letters, which contains extra letters that do not need sorting. In addition, the checksum must now be correct; the scenario described earlier can no longer happen.

The second method as well as part 2 of Day 4 is implemented in day_4v2.cpp.