//
// Created by cyc on 18-12-18.
//

#ifndef LAB3_COMMON_H
#define LAB3_COMMON_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define PATHNAME "/tmp"
#define PROJID1  0X1
#define PROJID2  0X2
#define SIZE 1024*4    //4k
#define N 4
key_t key1;
key_t key2;
int semId1;
int semId2;
int shmid;
union semun {
    int val; /* value for SETVAL */
    struct semid_ds *buf; /* buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /* array for GETALL, SETALL */
    struct seminfo *__buf; /* buffer for IPC_INFO */
};

char *buf[N];

int commonMem(int flags);

int createMem();

int createMutex();

int getMem();

int destroyMem(int shmid);

int destroyMutex(int semId);

void p1(int semnum);

void p2(int semnum);

void v1(int semnum);

void v2(int semnum);


#endif //LAB3_COMMON_H
