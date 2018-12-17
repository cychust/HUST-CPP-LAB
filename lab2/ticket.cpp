//
// Created by cyc on 18-12-10.
//
#include "iomanip"
#include <iostream>

#include <pthread.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <zconf.h>

#define N 5
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

struct thread_para {
//    int a;
    int id;         //线程id
    int semId;
};

int sell = 0;
int total = 100;

void V(int semId, int semNum) {
    struct sembuf sem;
    sem.sem_num = semNum;
    sem.sem_op = 1;
    sem.sem_flg = 0;
    semop(semId, &sem, 1);
    return;
}

//int semId;

void *sellHandle(void *a) {
    struct thread_para *t = (struct thread_para *) a;
    while (sell < total) {
        P(t->semId, 0);
        if (sell >= total) {
            V(t->semId, 0);
            break;
        }
        sell++;
        std::cout << "线程 " << std::right << std::setw(2)
                  << t->id << " 售票:"
                  << "一共已卖 " << std::right << std::setw(3) << sell << std::endl;
        V(t->semId, 0);
        srand((unsigned) time(NULL));
        usleep(rand() % 100);
    }

}


int main() {
//    std::cout << "Hello, World!" << std::endl;
    union semun arg;
    int semId;
    int key;
    int ret;
    int a = 0;
    struct thread_para para[N];                     //子线程参数
    pthread_t thread[N];
    void *a1[N];
    key = ftok("/tmp", 0x66);
    if (key < 0) {
        perror("ftok key error");
        return -1;
    }
    semId = semget(key, 1, IPC_CREAT | 0666);       //semId信号组id
    if (semId == -1) {
        perror("create semget error");
        return -1;
    }
    arg.val = 1;                                  //信号灯 1　初值为1;
    ret = semctl(semId, 0, SETVAL, arg);
    if (ret < 0) {
        perror("ctl sem error");
        semctl(semId, 0, IPC_RMID, arg);
        return -1;
    }
    for (int i = 0; i < N; ++i) {
        para[i].semId = semId;
        para[i].id = i + 1;
        pthread_create(&thread[i], NULL, sellHandle, &para[i]);
    }
    for (int j = 0; j < N; ++j) {
        pthread_join(thread[j], &a1[j]);
        std::cout << "线程" << j + 1 << "退出" << std::endl;
    }
    std::cout << "main" << std::endl;
    return 0;
}