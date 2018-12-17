#include <iostream>

#include <pthread.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <zconf.h>
#include <iomanip>

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
    int a;
    int semId;
    int flag;
};

void V(int semId, int semNum) {
    struct sembuf sem;
    sem.sem_num = semNum;
    sem.sem_op = 1;
    sem.sem_flg = 0;
    semop(semId, &sem, 1);
    return;
}

void *handle1(void *a) {
    int i = 1;
    struct thread_para *t = (struct thread_para *) a;
    while (i <= 100) {
        P(t->semId, 0);
        std::cout << "线程１计算，加" << i << std::endl;
        t->a += i;
        i++;
        V(t->semId, 1);
    }
    t->flag = 1;

}

void *handle2(void *a) {
    int i = 1;
    struct thread_para *t = (struct thread_para *) a;
    while (!t->flag) {
        P(t->semId, 1);
        std::cout << "和为" << std::right << std::setw(5) << t->a << std::endl;
        V(t->semId, 0);
    }
}

int main() {
    union semun arg;
    int semId;
    key_t key;
    int ret;
    int a = 0;
    struct thread_para para;                     //子线程参数
    pthread_t thread1;
    pthread_t thread2;
    void *a1, *a2;
//    key = IPC_PRIVATE;
    key = ftok("/tmp", 0x1);                 //生成IPC键值
    if (key < 0) {
        perror("ftok key error");
        return -1;
    }
    semId = semget(key, 2, IPC_CREAT | 0666);       //semId信号组id
    if (semId == -1) {
        perror("create semget error");
        return -1;
    }
    arg.val = 1;                                  //信号灯 1　初值为1;
    ret = semctl(semId, 0, SETVAL, arg);
    std::cout << "out" << std::endl;
    if (ret < 0) {
        perror("ctl sem error");
        semctl(semId, 0, IPC_RMID, arg);
        return -1;
    }
    arg.val = 0;                                 //信号灯 2　初值为0;
    ret = semctl(semId, 1, SETVAL, arg);
    if (ret < 0) {
        perror("ctl sem error");
        semctl(semId, 0, IPC_RMID, arg);
        return -1;
    }
    para.semId = semId;
    para.a = a;
    para.flag = 0;
    pthread_create(&thread1, NULL, handle1, &para);
    pthread_create(&thread2, NULL, handle2, &para);

    pthread_join(thread1, &a1);
    std::cout << "线程 1 退出" << std::endl;
    pthread_join(thread2, &a2);
    std::cout << "线程 2 退出" << std::endl;
    semctl(semId, 2, IPC_RMID);
    std::cout << "主线程退出" << std::endl;
    return 0;
}