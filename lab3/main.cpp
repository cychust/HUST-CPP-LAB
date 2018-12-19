#include <iostream>
#include <zconf.h>
#include <wait.h>

#include "common.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    createMem();
    pid_t pid1, pid2;
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork error");
        exit(-1);
    } else if (pid1 == 0) {
        execv("./readBuf", NULL);
    }
    pid2 = fork();
    if (pid2 == -1) {
        perror("fork error");
        exit(-1);
    } else if (pid2 == 0) {
        execv("./writeBuf", NULL);
    }
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    destroyMutex(semId1);                  //删除写信号灯组
    destroyMutex(semId2);                  //删除读信号灯组
    destroyMem(shmid);
    return 0;
}