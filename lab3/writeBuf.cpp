//
// Created by cyc on 18-12-18.
//

#include <iostream>
#include <fstream>
#include "common.h"

//using namespace std;

int main() {
    int outPointer = 0;
    int result;
    FILE *pFile;
    int size;
    pFile = fopen("./my", "rb");
    if (pFile == NULL) {
        perror("Error when open file");
        exit(-1);
    }
    while (1) {
        p1(outPointer);
        result = fwrite(buf[inPointer], sizeof(char), sizeof(buf[outPointer]), pFile);
        v1(outPointer);
        outPointer = (outPointer + 1) % N;
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