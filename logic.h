#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

class Logic {
    public:
        std::vector<int> convertBinary(std::string input);
        void printVector(std::vector<int> v);
        std::string convertToHex(const std::vector<int>& bits);

    private:
        std::vector<int> hexToBinary(char c);
};