#include "logic.h"

/*
    Converts hex string data into a bit vector to use in the encryption process
*/
std::vector<int> Logic::convertBinary(std::string input){
    std::vector<int> bits;

    //makes upper case so can ignore lower case logic
    std::transform(input.begin(), input.end(), input.begin(), ::toupper);

    //converts from hex chars to 4 bits using common bit logic
    for (char c : input){
        int value;

        if (c >= '0' && c <= '9') {
            value = c - '0';
        } else if (c >= 'A' && c <= 'F') {
            value = c - 'A' + 10;
        } else {
            throw std::invalid_argument("non hex char in string");
        }

        for (int shift = 3; shift >= 0; shift--) {
            bits.push_back((value >> shift) & 1);
        }
    }

    return bits;
}

/*
    Simply prints vector for debugging and visuals
*/
void Logic::printVector(std::vector<int> v){
    int spacer = 0;

    std::cout<<std::endl;
    for (const auto& element : v) {
        //includes spaces to make more readable
        if(spacer%4 == 0){
            std::cout<<" ";
        }
        std::cout << element;
        spacer++;
    }
}
