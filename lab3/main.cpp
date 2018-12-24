#include <iostream>
#include <zconf.h>
#include <wait.h>

#include "common.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    createKey();
    createMem();
    createMutex(IPC_CREAT | 0666);
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
    std::cout << "fork 1 return" << std::endl;
    waitpid(pid2, NULL, 0);
    std::cout << "fork 2 return" << std::endl;
//    system("ipcs -m");
    destroy();
    return 0;
}