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


#define PATHNAME "/tmp"
#define PROJID1  0X1
#define PROJID2  0X2
#define PROJID3  0X3
#define SIZE 1024*4    //4k
#define N 4

key_t key;
key_t key1;
key_t key2;
int semId1;
int semId2;
int shmid[N];

union semun {
    int val; /* value for SETVAL */
    struct semid_ds *buf; /* buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /* array for GETALL, SETALL */
    struct seminfo *__buf; /* buffer for IPC_INFO */
};

char *buf[N];

//int commonMem(int flags);
//
//int createMem();
//
//int createMutex();
//
//int getMem();
//
//int destroyMem(int shmid);
//
//int destroyMutex(int semId);
//
//void p1(int semnum);
//
//void p2(int semnum);
//
//void v1(int semnum);
//
//void v2(int semnum);


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
    key = ftok(PATHNAME, PROJID1);
    if (key < 0) {
        perror("ftok error");
        exit(-1);
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
        shmid[i] = shmget(key, SIZE * sizeof(char), flags);
        if (shmid[i] < 0) {
            std::cout<<"end"<<std::endl;
            perror("shmget error");
            std::cout<<"end"<<std::endl;
            exit(-1);
        }
        printf("shmid is %d", shmid[i]);
        buf[i] = (char *) shmat(shmid[i], 0, 0);
    }

    return 0;
}

void p1(int semnum) {
    P(semId1, semnum);
    std::cout << "p1 " << semnum << std::endl;
}

void p2(int semnum) {
    std::cout << "p2 " << semnum << std::endl;
    P(semId2, semnum);
}

void v1(int semnum) {
    std::cout << "v1 " << semnum << std::endl;
    V(semId2, semnum);
}

void v2(int semnum) {
    std::cout << "v2 " << semnum << std::endl;
    V(semId1, semnum);
}

int createMutex() {
    union semun arg1[N];
    union semun arg2[N];
    int ret;
    semId1 = semget(key1, N, IPC_CREAT | 0666);   //写信号灯组
    semId2 = semget(key2, N, IPC_CREAT | 0666);   //读信号灯组
    if (semId1 == -1 || semId2 == -1) {
        perror("create semget error");
        exit(-1);
    }
    for (int i = 0; i < N; ++i) {                   //对写信号灯组进行初始化
        arg1[i].val = 1;                                  //信号灯 　初值为1;
        ret = semctl(semId1, i, SETVAL, arg1[i]);
        if (ret < 0) {
            perror("ctl sem error");
            semctl(semId1, i, IPC_RMID, arg1[i]);
            exit(-1);
        }
    }
    for (int j = 0; j < N; ++j) {                   //对读信号灯组初始化
        arg2[j].val = 0;                                  //信号灯 　初值为0;
        ret = semctl(semId2, j, SETVAL, arg2[j]);
        if (ret < 0) {
            perror("ctl sem error");
            semctl(semId2, j, IPC_RMID, arg2[j]);
            exit(-1);
        }
    }
}


int createMem() {
    return commonMem(IPC_CREAT | IPC_EXCL | 0666);
}


int destroyMem(int *shmid) {
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

#endif //LAB3_COMMON_H
