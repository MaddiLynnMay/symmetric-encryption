#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "logic.h"
#include <algorithm>

class Key {
    public:
        Key(std::string input){
            ogKey = doLogic.convertBinary(input);
        };

        //std::string getKey();
        void generateKeys();

        std::vector<int> getKey(int keyNum);

    private:
        std::vector<int> ogKey;
        std::vector<std::vector<int>> keys;

        Logic doLogic;

        std::vector<int> ogPermutation();
        void permutation2(std::vector<int>& keys56b);
        void shiftHalf(std::vector<int>& half, int shiftNum);

};