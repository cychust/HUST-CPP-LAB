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
//    char *buf[N];
    int size;
    createKey();
    createMutex(IPC_CREAT | 0666);
    commonMem(0);
    pFile = fopen("tmp.jpeg", "wb");
    std::cout << "writeBuf" << std::endl;
    if (pFile == NULL) {
        perror("Error when open file");
        exit(-1);
    }

    while (1) {
        p2(outPointer);
//        buf[outPointer] = (char *) shmat(shmid[outPointer], NULL, 0);
        result = fwrite(buf[outPointer]->buf, 1, buf[outPointer]->length, pFile);
        memset(buf[outPointer], '\0', SIZE);
        v2(outPointer);
        outPointer = (outPointer + 1) % N;
        if (result != SIZE) {
            if (ferror(pFile)) {
                perror("error when write file");
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