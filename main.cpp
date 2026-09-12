#include <iostream>
#include <string>
#include <vector>
#include "key.h"
#include "logic.h"
#include "encrypt.h"


int main (){

    //Inputs given by assignment details
    std::string data = "0123456789ABCDEF";
    std::string key = "133457799BBCDFF1";

    Encrypt doEncrypt(data, key);
    Logic doLogic;

    std::vector<int> encryptedData = doEncrypt.encryptData();

    std::string finalOut = doLogic.convertToHex(encryptedData);

    std::cout<<"For Assignment Set Inputs: ";
    std::cout<<"\nM: "+ data;
    std::cout<<"\nK: "+ key;
    std::cout<<"\nC: "+ finalOut;

    //My chosen Inputs:
    data = "BACE1882FADE1413";
    key = "12344321ABCDA1B2";

    Encrypt doMyEncrypt(data, key);

    encryptedData = doMyEncrypt.encryptData();
    finalOut = doLogic.convertToHex(encryptedData);

    std::cout<<"\n\nFor My Chose Inputs: ";
    std::cout<<"\nM: "+ data;
    std::cout<<"\nK: "+ key;
    std::cout<<"\nC: "+ finalOut;


    return 0;
}
