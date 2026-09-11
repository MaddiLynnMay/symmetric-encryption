#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "logic.h"
#include "key.h"

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

};  