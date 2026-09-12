#include "logic.h"


/*
    This is a helper class that processes data 
*/

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
    Covenverts from Binary to Hexidecimal
*/
std::string Logic::convertToHex(const std::vector<int>& bits){
    if (bits.size() % 4 != 0) {
        throw std::invalid_argument("bit vector length must be a multiple of 4");
    }

    const std::string hexDigits = "0123456789ABCDEF";
    std::string result;

    for (size_t i = 0; i < bits.size(); i += 4) {
        int value = (bits[i] << 3) | (bits[i+1] << 2) | (bits[i+2] << 1) | bits[i+3];
        result += hexDigits[value];
    }

    return result;
}

/*
    Simply prints vector for debugging and visuals
*/
void Logic::printVector(std::vector<int> v){
    int spacer = 0;
    int bitSize = v.size();

    std::cout << std::endl;
    for (const auto& element : v) {
        // includes spaces to make more readable
        if(bitSize == 48 && spacer%6 == 0){
            std::cout << " ";
        }
        if(spacer%4 == 0){
            std::cout << " ";
        }
        std::cout << element;
        spacer++;
    }
}


