//
// Created by cyc on 18-12-18.
//

#include <iostream>
#include <fstream>
#include "common.h"

//using namespace std;

int main() {
    int inPointer = 0;
    int result;
    FILE *pFile;
    int size;
    pFile = fopen("in.txt", "rb");
    if (pFile == NULL) {
        perror("Error when open file");
        exit(-1);
    }
    while (1) {
        p1(inPointer);
        result = fread(buf[inPointer], 1, SIZE, pFile);
        std::cout << "read" << result << std::endl;
        v1(inPointer);
        inPointer = (inPointer + 1) % N;
        if (result != SIZE) {
            if (ferror(pFile)) {
                perror("error when read file");
                exit(-1);
            } else {
                break;
            }

        }
    }


}