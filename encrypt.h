#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "logic.h"
#include "key.h"
#include <algorithm>

class Encrypt {
    public:
        Encrypt(std::string data, std::string key) : keyHandler(key) {
            ogData = doLogic.convertBinary(data);
        }

        //this will do all of the encryption and return output
        std::vector<int> encryptData();
        


    private:
        Logic doLogic;
        Key keyHandler;

        std::vector<int> ogData;

        std::vector<int> firstPermutation(std::vector<int> data);
        void transformRight(std::vector<int>& right);
        void transformLeft(std::vector<int>& left, std::vector<int>& right);
        
        //methods used by transformRight
        std::vector<int> expandRight(std::vector<int>& right);
        

        std::vector<int> xorVectors(const std::vector<int>& a, const std::vector<int>& b);

};  