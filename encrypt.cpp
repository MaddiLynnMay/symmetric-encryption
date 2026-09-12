#include "encrypt.h"

std::vector<int> Encrypt::encryptData(){
    std::vector<int> dataOut;

    keyHandler.generateKeys();

    //start by doing the initial permutation of the data
    dataOut = firstPermutation(ogData);

    std::cout<<"initial perm: ";
    doLogic.printVector(dataOut);

    std::vector<int> left;
    std::vector<int> right;

    std::vector<int> leftFinal;

    int leftEnd = 32;
    int rightBegin = 32;
    int rightEnd = 64;

    //this will loop 16 times, using each generated key
    for (int i = 0; i < 16; i++){
        //clear and repartion left and right halves
        left.clear();
        leftFinal.clear();
        right.clear();
        left.insert(left.begin(), dataOut.begin(), dataOut.begin() + leftEnd);
        right.insert(right.begin(), dataOut.begin() + rightBegin, dataOut.begin() + rightEnd);

        //the final left bits are just the right initial half
        leftFinal = right;

        //encode right half
        transformRight(right);

        //use encoded right half to make left half


        //create the new dataOut from combining the new halves 
        dataOut.clear();
        dataOut = leftFinal;

        dataOut.insert(dataOut.begin()+rightBegin, left.begin(), left.end());
        std::cout<< "\n\n Output Data "<< i+1 << ": ";
        doLogic.printVector(dataOut);
    }

    return dataOut;
}

void Encrypt::transformRight(std::vector<int>& right){
    std::vector<int> expR = expandRight(right);
    std::cout<<"\n Expanded Right Side: ";
    doLogic.printVector(expR);

}


std::vector<int> Encrypt::expandRight(std::vector<int>& right){
    std::vector<int> EBitTable = {
        32,     1,    2,     3,     4,    5,
         4,     5,    6,     7,     8,    9,
         8,     9,   10,    11,    12,   13,
        12,    13,   14,    15,    16,   17,
        16,    17,   18,    19,    20,   21,
        20,    21,   22,    23,    24,   25,
        24,    25,   26,    27,    28,   29,
        28,    29,   30,    31,    32,    1
    };
    
    std::vector<int> permOut;

    for(int index : EBitTable){
        //adds the ogKey from the index in the table -1 to correct for 1 based table
        permOut.push_back(right[index-1]);
    }
    return permOut;
}


/*
    Intital Permutation. Rearranges the ogData in order listed in IP table.
*/
std::vector<int> Encrypt::firstPermutation(std::vector<int> data){
    const std::vector<int> IP = {
        58,    50,   42,    34,    26,   18,    10,    2,
        60,    52,   44,    36,    28,   20,    12,    4,
        62,    54,   46,    38,    30,   22,    14,    6,
        64,    56,   48,    40,    32,   24,    16,    8,
        57,    49,   41,    33,    25,   17,     9,    1,
        59,    51,   43,    35,    27,   19,    11,    3,
        61,    53,   45,    37,    29,   21,    13,    5,
        63,    55,   47,    39,    31,   23,    15,    7
    };

    std::vector<int> permOut;

    for(int index : IP){
        //adds the ogKey from the index in the table -1 to correct for 1 based table
        permOut.push_back(data[index-1]);
    }

    return permOut;
}




/*
    used throughout encryption to xor bits, used a common XOR method
*/
std::vector<int> Encrypt::xorVectors(const std::vector<int>& a, const std::vector<int>& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("vectors must be same length to XOR");
    }
    std::vector<int> result(a.size());
    for (size_t i = 0; i < a.size(); i++) {
        result[i] = a[i] ^ b[i];
    }
    return result;
}