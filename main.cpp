#include <iostream>
#include <string>
#include <vector>
#include "key.h"
#include "logic.h"
#include "encrypt.h"


int main (){
    std::string data = "0123456789ABCDEF";
    std::string key = "133457799BBCDFF1";

    Encrypt doEncrypt(data, key);
    Logic doLogic;
    std::vector<int> encryptedData = doEncrypt.encryptData();

    std::string finalOut = doLogic.convertToHex(encryptedData);
    std::cout<<"\nFinal Encrypted Hex Message: "+ finalOut;

    return 0;
}
