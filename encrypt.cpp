#include "encrypt.h"


/*
    Main encryption function. The only one that can be ran outside of
    the class.
*/
std::vector<int> Encrypt::encryptData(){
    std::vector<int> dataOut;

    keyHandler.generateKeys();

    //start by doing the initial permutation of the data
    dataOut = firstPermutation(ogData);

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
        transformRight(right, i);

        //use encoded right half to make left half
        left = xorVectors(left, right);

        //create the new dataOut from combining the new halves 
        dataOut.clear();

        if (i == 15) {
            // final round: skip the swap, so put left first instead of leftFinal first
            dataOut = left;
            dataOut.insert(dataOut.end(), leftFinal.begin(), leftFinal.end());
        } else {
            dataOut = leftFinal;
            dataOut.insert(dataOut.end(), left.begin(), left.end());
        }
    }

    finalPermutation(dataOut);

    return dataOut;
}


/*
   Final encryption Permutation
*/
void Encrypt::finalPermutation(std::vector<int>& data){
    const std::vector<int> P = {
        40,     8,   48,    16,    56,   24,    64,   32,
        39,     7,   47,    15,    55,   23,    63,   31,
        38,     6,   46,    14,    54,   22,    62,   30,
        37,     5,   45,    13,    53,   21,    61,   29,
        36,     4,   44,    12,    52,   20,    60,   28,
        35,     3,   43,    11,    51,   19,    59,   27,
        34,     2,   42,    10,    50,   18,    58,   26,
        33,     1,   41,     9,    49,   17,    57,   25
    };

    std::vector<int> permOut;

    for(int index : P){
        //adds the ogKey from the index in the table -1 to correct for 1 based table
        permOut.push_back(data[index-1]);
    }

    data.clear();
    data = permOut;
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



//  THE REST OF THIS CODE IS FOR THE TRANSFOR RIGHT METHOD

/*
    Takes the original right half, expands it and XOR's it with a key
    then takes the bits and sends them through the s table and permutates
    the output to get the rearranged value.
*/
void Encrypt::transformRight(std::vector<int>& right, int num){
    std::vector<int> expR = expandRight(right);
    std::vector<int> key = keyHandler.getKey(num);

    std::vector<int> rightXORkey = xorVectors(expR, key);

    std::vector<std::vector<int>> sTables = {s1, s2, s3, s4, s5, s6, s7, s8};

    std::vector<int> bitBlock;
    std::vector<int> sValueBits;
    std::vector<int> sResult;

    for (int i = 0; i < 8; i++){
        int blockIndx = i * 6;

        bitBlock.clear();
        bitBlock.insert(bitBlock.begin(), rightXORkey.begin()+blockIndx, rightXORkey.begin()+blockIndx+6);

        int searchIndex = getSBoxIndex(bitBlock);
        int sValue = sTables.at(i).at(searchIndex);
        sValueBits = toBits(sValue);

        sResult.insert(sResult.end(), sValueBits.begin(), sValueBits.end());
    }

    right = pPermutation(sResult); 
}


/*
    Last Permutation for Transform Right Function
*/
std::vector<int> Encrypt::pPermutation(std::vector<int> keyedRight){
    const std::vector<int> P = {
        16,   7,  20,  21,
        29,  12,  28,  17,
         1,  15,  23,  26,
         5,  18,  31,  10,
         2,   8,  24,  14,
        32,  27,   3,   9,
        19,  13,  30,   6,
        22,  11,   4,  25
    };

    std::vector<int> permOut;

    for(int index : P){
        //adds the ogKey from the index in the table -1 to correct for 1 based table
        permOut.push_back(keyedRight[index-1]);
    }

    return permOut;
}

/*
    Used by Tranform right method
    uses the EBit table to expand from 32 bits to 48 bits
*/
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
    Converts the bit block into an index that can be used to pull the right 
    value from the table
*/
int Encrypt::getSBoxIndex(const std::vector<int>& sixBits) {
    int row = (sixBits[0] << 1) | sixBits[5];
    int col = (sixBits[1] << 3) | (sixBits[2] << 2) | (sixBits[3] << 1) | sixBits[4];
    return (row * 16) + col;
}


/*
    converts s table result to bits
*/
std::vector<int> Encrypt::toBits(int value) {
    std::vector<int> bits;
    for (int shift = 3; shift >= 0; shift--) {
        bits.push_back((value >> shift) & 1);
    }
    return bits;
}


