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
    doEncrypt.encryptData();
    

    return 0;
}
