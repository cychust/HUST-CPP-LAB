//
// Created by cyc on 18-12-18.
//

#ifndef LAB3_COMMON_H
#define LAB3_COMMON_H

#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <zconf.h>
#include <iomanip>
#include <stdlib.h>
#include <string.h>

#define PATHNAME "/tmp"
#define PROJID1  0X1
#define PROJID2  0X2
#define PROJID3  0X3
#define SIZE 1024    //4k
#define N 4

typedef struct ShareBuf{
    char buf[SIZE];
    int length;
}ShareBuf;

key_t key[N];
key_t key1;
key_t key2;
int semId1;
int semId2;
int shmid[N];
ShareBuf *buf[N];

union semun {
    int val; /* value for SETVAL */
    struct semid_ds *buf; /* buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /* array for GETALL, SETALL */
    struct seminfo *__buf; /* buffer for IPC_INFO */
};


void P(int semId, int semNum) {
    struct sembuf sem;
    sem.sem_num = semNum;
    sem.sem_op = -1;
    sem.sem_flg = 0;
    semop(semId, &sem, 1);
    return;
}

void V(int semId, int semNum) {
    struct sembuf sem;
    sem.sem_num = semNum;
    sem.sem_op = 1;
    sem.sem_flg = 0;
    semop(semId, &sem, 1);
    return;
}

int createKey() {
    for (int i = 0; i < N; ++i) {
        key[i] = ftok(PATHNAME, i + 100);
        if (key[i] < 0) {
            perror("ftok error");
            exit(-1);
        }
    }
    key1 = ftok(PATHNAME, PROJID2);
    if (key1 < 0) {
        perror("ftok error");
        exit(-1);
    }
    key2 = ftok(PATHNAME, PROJID3);
    if (key2 < 0) {
        perror("ftok error");
        exit(-1);
    }

    return 0;
}


int commonMem(int flags) {
    for (int i = 0; i < N; ++i) {
        shmid[i] = shmget(key[i], sizeof(ShareBuf), flags);
        if (shmid[i] < 0) {
            std::cout << "end" << std::endl;
            perror("shmget error");
            std::cout << "end" << std::endl;
            exit(-1);
        }
//        printf("shmid is %d", shmid[i]);
        buf[i] = (ShareBuf *) shmat(shmid[i], NULL, 0);
        memset(buf[i], '\0', SIZE);
    }
    return 0;
}


void p1(int semnum) {
    std::cout << "p1 " << semnum << std::endl;
    P(semId1, semnum);
}

void p2(int semnum) {
//    std::cout << "p2 " << semnum << std::endl;
    P(semId2, semnum);
}

void v1(int semnum) {
    V(semId2, semnum);
}

void v2(int semnum) {
    V(semId1, semnum);
}

int createMutex(int flags) {
    union semun arg;
//    union semun arg2[N];
    int ret;
    semId1 = semget(key1, N, flags);   //写信号灯组
    semId2 = semget(key2, N, flags);   //读信号灯组
    if (semId1 == -1 || semId2 == -1) {
        perror("create semget error");
        exit(-1);
    }
    for (int i = 0; i < N; ++i) {                   //对写信号灯组进行初始化
        arg.val = 1;                                  //信号灯 　初值为1;
        ret = semctl(semId1, i, SETVAL, arg);
//        std::cout << "set" << SETVAL << std::endl;
        if (ret < 0) {
            perror("ctl sem error");
            semctl(semId1, i, IPC_RMID, arg);
            exit(-1);
        }
    }
    for (int j = 0; j < N; ++j) {                   //对读信号灯组初始化
        arg.val = 0;                                  //信号灯 　初值为0;
        ret = semctl(semId2, j, SETVAL, arg);
        if (ret < 0) {
            perror("ctl sem error");
            semctl(semId2, j, IPC_RMID, arg);
            exit(-1);
        }
    }
}


int createMem() {
    return commonMem(IPC_CREAT | 0666);
}


int destroyMem() {
    for (int i = 0; i < N; ++i) {
        if (shmctl(shmid[i], IPC_RMID, NULL) < 0) {
            perror("destroy error");
            exit(-1);
        }
    }
    return 0;
}

int destroyMutex(int semId) {
    union semun arg;
    arg.val = 0;
    for (int i = 0; i < N; ++i) {
        semctl(semId, i, IPC_RMID, arg);
    }
}

void destroy() {
    destroyMutex(semId1);
    destroyMutex(semId2);
    destroyMem();
}

#endif //LAB3_COMMON_H
