#include "key.h"

/*
    This method is ran once to generate all of the keys in the vector keys.

    It runs the ogPermutation method to get initial 56 bit key

    splits the key in half, shifting each half by the designated amount from
    shiftDist, and then merges the halves to create each key. this happens 16 times

*/
void Key::generateKeys(){
    
    //std::cout << "check og key bits: ";
    //doLogic.printVector(ogKey);

    //std::cout << "\ncheck 56 bit key: ";
    std::vector<int> shortKey = ogPermutation();
    //doLogic.printVector(shortKey);

    // Key holder, holds all the keys before perm2
    std::vector<std::vector<int>> keysPrePerm2;
    keysPrePerm2.push_back(shortKey);

    int leftEnd = 28;
    int rightBegin = 28;
    int rightEnd = 56;

    std::vector<int> left;
    std::vector<int> right;
    std::vector<int> createdKey;

    //used to shift the halves in shiftHalf() method
    const std::vector<int> shiftDist = {
            1,  1,  2,  2,  
            2,  2,  2,  2,  
            1,  2,  2,  2,  
            2,  2,  2,  1
        };

    //creates all of the keys before perm2
    for (int num = 1; num <= 16; num++){
        createdKey.clear();

        //splits the intial key into left and right halves to be shifted
        if (num == 1){
            left.insert(left.begin(), keysPrePerm2[0].begin(), keysPrePerm2[0].begin() + leftEnd);
            right.insert(right.begin(), keysPrePerm2[0].begin() + rightBegin, keysPrePerm2[0].begin() + rightEnd);
        }

        //shifts the left and right
        shiftHalf(left, shiftDist[num-1]);
        shiftHalf(right, shiftDist[num-1]);

        //merges the two halves to add to the key list
        createdKey.insert(createdKey.begin(), left.begin(), left.end());
        createdKey.insert(createdKey.end(), right.begin(), right.end());
        keysPrePerm2.push_back(createdKey);

        //std::cout<<"\n\n56 bit key "<< num <<": ";
        //doLogic.printVector(keysPrePerm2[num]);

        permutation2(createdKey);
    }

}

std::vector<int> Key::getKey(int keyNum){
    return keys[keyNum];
}


//          PRIVATE 

/*
    First permuation, converting from 64 bits to a 56 bit key
*/
std::vector<int> Key::ogPermutation(){
    //create shortened vector using key and pc1 table
    std::vector<int> reducedKey;

    const std::vector<int> pc1 = { 
            57,   49,    41,   33,    25,    17,    9,
            1,    58,    50,   42,    34,    26,   18,
            10,    2,    59,   51,    43,    35,   27,
            19,   11,     3,   60,    52,    44,   36,
            63,   55,    47,   39,    31,    23,   15,
            7,    62,    54,   46,    38,    30,   22,
            14,    6,    61,   53,    45,    37,   29,
            21,   13,     5,   28,    20,    12,    4
            
        };

    for (int index : pc1){

        //adds from ogKey at index from table-1 (have to correct for base 0 index)
        reducedKey.push_back(ogKey[index-1]);
    }

    return reducedKey;
}

/*
    Second Permutation used by generateKeys takes 56 bit keys
    and uses pc2 to reduce to 48 bit Keys
*/
void Key::permutation2(std::vector<int>& keys56b){
    //create shortened vector using key and pc2 table
    std::vector<int> reducedKey;
    const std::vector<int> pc2 = { 
            14,    17,   11,    24,     1,    5,
             3,    28,   15,     6,    21,   10,
            23,    19,   12,     4,    26,    8,
            16,     7,   27,    20,    13,    2,
            41,    52,   31,    37,    47,   55,
            30,    40,   51,    45,    33,   48,
            44,    49,   39,    56,    34,   53,
            46,    42,   50,    36,    29,   32
        };

    for (int index : pc2){
        //adds from ogKey at index from table-1 (have to correct for base 0 index)
        reducedKey.push_back(keys56b[index-1]);
    }

    //std::cout<<"\n48 bit key : ";
    //doLogic.printVector(reducedKey);
    keys.push_back(reducedKey);
    
}


/*
    Takes in a reference to the half vectors, and shifts them
*/
void Key::shiftHalf(std::vector<int>& half, int roundNum){
    //int amount = shiftDist[roundNum - 1]; // -1 because roundNum is 1-indexed, vector is 0-indexed
    std::rotate(half.begin(), half.begin() + roundNum, half.end());
}