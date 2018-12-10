#include <iostream>
#include <zconf.h>
#include <wait.h>
#include <cstring>

#define MAXLINE 1000

int pid[2];
int fd[2];
void handle(int signum) {
    if (signum == SIGINT) {
        kill(pid[0], SIGUSR1);
        kill(pid[1], SIGUSR2);
    }
}

void handle1(int signum) {
    if (signum == SIGUSR1) {
        std::string line = "Child Process 1 is Killed by Parent!\n";
        write(STDOUT_FILENO, line.data(), strlen(line.data()));
        close(fd[1]);
        exit(0);
    }
}

void handle2(int signum) {
    if (signum == SIGUSR2) {
        std::string line = "Child Process 2 is Killed by Parent!\n";
        write(STDOUT_FILENO, line.data(), strlen(line.data()));
        close(fd[0]);
        exit(0);
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    int n;
//    int fd[2];
    pid_t pid1;
    pid_t pid2;
    int x = 1;
    char line[MAXLINE];
    std::string message1 = "I send you ";
    std::string message2 = " times\n";
    std::string message;
    std::string x_str;
    signal(SIGINT, handle);
    pipe(fd);                     //创建管道
    if ((pid1 = fork()) == -1) {   //子进程
        exit(1);
    }
    if (pid1 == 0) {
        signal(SIGINT, SIG_IGN);
        if (signal(SIGUSR1, handle1) == SIG_ERR) {
            printf("cant catch SIGINT");
        }
        while (1) {
            x_str = std::to_string(x);
            message = message1 + x_str + message2;
            close(fd[0]);               //关闭读
            write(fd[1], message.data(), message.size());
            x++;
            sleep(1);
        }
    }
    pid[0] = pid1;
    if ((pid2 = fork()) == -1) {   //子进程2
        exit(1);
    }

    if (pid2 == 0) {
        signal(SIGINT, SIG_IGN);
        if (signal(SIGUSR2, handle2) == SIG_ERR) {
            printf("cant catch SIGINT");
        }
        while (1) {
            close(fd[1]);
            n = read(fd[0], line, MAXLINE);
            write(STDOUT_FILENO, line, n);
        }
    }
    pid[1] = pid2;
    std::cout << pid[0] << " " << pid[1] << std::endl;
    waitpid(pid[0], NULL, 0);
    waitpid(pid[1], NULL, 0);
    close(fd[0]);
    close(fd[1]);
    std::cout << "Parent Process is killed" << std::endl;
    return 0;
}