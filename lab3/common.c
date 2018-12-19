//
// Created by cyc on 18-12-18.
//

#include "common.h"


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
    key1 = ftok(PATHNAME, PROJID1);
    if (key1 < 0) {
        perror("ftok error");
        exit(-1);
    }
    key2 = ftok(PATHNAME, PROJID2);
    if (key2 < 0) {
        perror("ftok error");
        exit(-1);
    }

    return 0;
}


int commonMem(int flags) {
    for (int i = 0; i < N; ++i) {
        shmid = shmget(key, SIZE * sizeof(char), flags);
        if (shmid < 0) {
            perror("shmget error");
            exit(-1);
        }
        printf("shmid is %d", shmid);
        buf[i] = (char *) shmat(shmid, 0, 0);
    }

    return 0;
}

void p1(int semnum) {
    P(semId1, semnum);
}

void p2(int semnum) {
    P(semId2, semnum);
}

void v1(int semnum) {
    V(semId2, semnum);
}

void v2(int semnum) {
    V(semId1, semnum);
}

int createMutex() {
    union semun arg;
    int ret;
    semId1 = semget(key1, N, IPC_CREAT | IPC_EXCL | 0666);   //写信号灯组
    semId2 = semget(key2, N, IPC_CREAT | IPC_EXCL | 0666);   //读信号灯组
    if (semId1 == -1 || semId2 == -1) {
        perror("create semget error");
        exit(-1);
    }
    arg.val = 1;                                  //信号灯 　初值为1;
    for (int i = 0; i < N; ++i) {                   //对写信号灯组进行初始化
        ret = semctl(semId, i, SETVAL, arg);
        if (ret < 0) {
            perror("ctl sem error");
            semctl(semId, i, IPC_RMID, arg);
            exit(-1);
        }
    }
    arg.val = 0;                                  //信号灯 　初值为0;
    for (int j = 0; j < N; ++j) {                   //对读信号灯组初始化
        ret = semctl(semId, j, SETVAL, arg);
        if (ret < 0) {
            perror("ctl sem error");
            semctl(semId, j, IPC_RMID, arg);
            exit(-1);
        }
    }
}


int createMem() {
    return commonMem(IPC_CREAT | IPC_EXCL | 0666);
}


int destroyMem(int shmid) {
    if (shmctl(shmid, IPC_RMID, NULL) < 0) {
        perror("destroy error");
        exit(-1);
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