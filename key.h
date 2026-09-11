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

    private:
        std::vector<int> ogKey;
        std::vector<std::vector<int>> keys;
        int keyNum = 0;

        Logic doLogic;

        std::vector<int> ogPermutation();
        void permutation2(std::vector<int>& keys56b);
        void shiftHalf(std::vector<int>& half, int shiftNum);


        /*
            Tables used by the key methods to make the keys
        */

        // //used to shift the halves in shiftHalf() method
        // const std::vector<int> shiftDist = {
        //         1,  1,  2,  2,  
        //         2,  2,  2,  2,  
        //         1,  2,  2,  2,  
        //         2,  2,  2,  1
        // };


        




};