//
// Created by cyc on 18-12-18.
//

#include <iostream>
#include <stdio.h>
#include "common.h"

//using namespace std;

int main() {
    int inPointer = 0;
    int result;
    FILE *pFile;

//    char *buf[N];
    int size;
    createKey();
    createMutex(IPC_CREAT | 0666);
    commonMem(0);
    sleep(1);
    pFile = fopen("yichao.jpeg", "rb");
    std::cout << "readBuf" << std::endl;
    if (pFile == NULL) {
        perror("Error when open file");
        exit(-1);
    }

    while (1) {
        p1(inPointer);
        result = fread(buf[inPointer]->buf, 1, SIZE, pFile);
        buf[inPointer]->length = result;
        v1(inPointer);
        inPointer = (inPointer + 1) % N;
        if (result != SIZE) {
            if (ferror(pFile)) {
                perror("error when read file");
                fclose(pFile);
                destroy();
                exit(-1);
            } else {
                fclose(pFile);
                break;
            }

        }
    }


}