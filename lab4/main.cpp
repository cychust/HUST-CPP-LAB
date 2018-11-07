#include <iostream>
#include "STACK.h"


class QUEUE : public STACK {

    STACK s2;
public:
    QUEUE(int m); //每个栈最多m个元素，要求实现的队列最多能入2m个元素
    QUEUE(const QUEUE &s);            //用队列s拷贝初始化队列
    virtual operator int() const;            //返回队列的实际元素个数
    virtual int full() const;               //返回队列是否已满，满返回1，否则返回0
    virtual int operator[](int x) const;   //取下标为x的元素，第1个元素下标为0
    virtual QUEUE &operator<<(int e);  //将e入队列,并返回队列
    virtual QUEUE &operator>>(int &e);    //出队列到e,并返回队列
    virtual QUEUE &operator=(const QUEUE &s); //赋s给队列,并返回被赋值的队列
    virtual void print() const;            //打印队列
    virtual ~QUEUE();                    //销毁队列
};

QUEUE::QUEUE(int m) : STACK(m), s2(m) {
}

QUEUE::QUEUE(const QUEUE &s) : STACK(s.STACK::size()), s2(s.STACK::size()) {
    *this = s;
}

QUEUE::operator int() const {
    return STACK::operator int() + s2;
}

int QUEUE::full() const {
    if (s2 == s2.size() && STACK::size() == STACK::operator int()) {
        return 1;
    }
    return 0;
}

int QUEUE::operator[](int x) const {
    if (x > int()) {
        std::cout << "error" << std::endl;
        return -1;
    }
    if (s2 == 0) {
        return STACK::operator[](x);
    }
    if (s2 > x) {
        return s2[s2 - x + 1];
    } else {
        STACK::operator[](x - s2);
    }
}

QUEUE &QUEUE::operator<<(int e) {
    int k;
    if (full()) {
        return *this;
    }
    if (STACK::operator int() < STACK::size()) {
        STACK::operator<<(e);
    } else {
        while (STACK::operator int() != 0) {
            STACK::operator>>(k);
            s2 << k;
        }
        STACK::operator<<(e);
    }
    return *this;
}

QUEUE &QUEUE::operator>>(int &e) {
    if (s2 == 0 && STACK::operator int() == 0)return *this;
    if (s2 != 0) {
        s2 >> e;
    } else {
        int k;
        while (STACK::operator int() != 0) {
            STACK::operator>>(k);
            s2 << k;
        }
        s2 >> (e);
    }
    return *this;
}

QUEUE &QUEUE::operator=(const QUEUE &s) {
    if (s.s2 != 0)
        s2 = s.s2;
    if (s.STACK::operator int() != 0)
        STACK::operator=(s);
    return *this;
}

void QUEUE::print() const {
    if (s2 != 0) {
////        s2.print();
        for (int i = s2-1; i >= 0; --i) {
            std::cout << s2[i] << "  ";
        }
    }
    if (STACK::operator int() != 0) {
//        for (int i = 0; i < STACK::operator int(); ++i) {
//            int tmp=STACK::operator[](i);
//            printf("%d  ", STACK::operator[](i));
//        }
        STACK::print();
    }
}

QUEUE::~QUEUE() {}

int main(int argc, char *argv[]) {

    if (argc == 1) {

    } else {
        FILE *fp;
        int err;
        char filename[20] = {'\0'};
        strcat(filename, "cyc");
        strcat(filename, ".txt");
        std::cout << filename << " " << std::endl;
        if ((fp = fopen(filename, "w")) == NULL) {
//            printf("Cannot open file strike any key exit!");
            err = 1;
            getchar();
        } else {
//            printf("%s\n",filename);
            err = 0;
        }
        QUEUE *pQueue;
        QUEUE *qQueue;
        int tmp;
        int isInitial = 0;
        int tmp2;
        int flag = 0;
        for (int i = 1; i < argc; ++i) {
            if (!strcmp(argv[i], "-S")) {
                printf("S  ");
                fputs("S  ", fp);

                if (isInitial == 1) {   //多次
                    fprintf(fp, "E  ");
                    printf("E  ");
                    break;
                }
                if (i + 1 < argc && argv[i + 1][0] >= '0' && argv[i + 1][0] <= '9') {
                    tmp = atoi(argv[i + 1]);
                    pQueue = new QUEUE(tmp);
                    fprintf(fp, "%d  ", tmp);
                    printf("%d  ", tmp);
                    isInitial = 1;
                } else {
                    fprintf(fp, "E  ");
                    printf("E  ");
                }
            }
            if (!strcmp(argv[i], "-I")) {
                fprintf(fp, "I  ");
                printf("I  ");
                flag = 0;
                if (isInitial == 0) {
                    fprintf(fp, "E  ");
                    printf("E  ");
                    break;
                }

                i++;
                for (; (i < argc) && (argv[i][0] >= '0' && argv[i][0] <= '9'); ++i) {
                    tmp = atoi(argv[i]);
//                    int stackLength = *pQueue;
//                    int stackMax = pQueue->size();
                    if (pQueue->full()) {
                        printf("E  ");
                        fprintf(fp, "E  ");
                        flag = 1;
                        break;
                    }
                    *pQueue << tmp;
                }
                if (flag == 0) {
                    pQueue->print();
//                    if (err == 0)
//                        for (int j = 0; j < *pQueue; ++j) {
//                            fprintf(fp, "%d  ", (*pQueue)[j]);
//                        }
                } else
                    break;
                i--;
            }

            if (!strcmp(argv[i], "-O")) {
                fprintf(fp, "O  ");
                printf("O  ");
                if (isInitial == 0) {
                    fprintf(fp, "E  ");
                    printf("E  ");
                    break;
                }
                if (i + 1 < argc && argv[i + 1][0] >= '0' && argv[i + 1][0] <= '9') {
                    tmp = atoi(argv[i + 1]);
                    if (tmp > *pQueue) {
                        printf("E");
                        fprintf(fp, "E  ");
                        break;
                    }
                    for (int j = 0; j < tmp; ++j) {
                        *pQueue >> tmp2;
                    }
                    pQueue->print();
//                    if (err == 0)
//                        for (int j = 0; j < *pQueue; ++j) {
////                            fprintf(fp, "%d  ", (*pQueue)[j]);
//                        }
                } else {
                    printf("E  ");
                    fprintf(fp, "E  ");
                    break;
                }
            }
            if (!strcmp(argv[i], "-A")) {
                fprintf(fp, "A  ");
                printf("A  ");
                if (i + 1 < argc && argv[i + 1][0] >= '0' && argv[i + 1][0] <= '9') {
                    tmp = atoi(argv[i + 1]);
                    qQueue = new QUEUE(tmp);
                    *qQueue = *pQueue;
                    qQueue->print();
                    if (err == 0)
                        for (int j = 0; j < *qQueue; ++j) {
                            fprintf(fp, "%d  ", (*qQueue)[j]);
                        }
                } else {
                    printf("E  ");
                    fprintf(fp, "E  ");
                    break;
                }
            }
            if (!strcmp(argv[i], "-C")) {
                printf("C  ");
                fprintf(fp, "C  ");
                qQueue = new QUEUE(*pQueue);
                qQueue->print();
                if (err == 0)
                    for (int j = 0; j < *qQueue; ++j) {
                        fprintf(fp, "%d  ", (*qQueue)[j]);
                    }
            }
            if (!strcmp(argv[i], "-N")) {
                printf("N  ");
                fprintf(fp, "N  ");
                int n = *pQueue;
                fprintf(fp, "%d  ", n);
                printf("%d", n);
            }
            if (!strcmp(argv[i], "-G")) {
                printf("G  ");
                fprintf(fp, "G  ");
                if (i + 1 < argc && argv[i + 1][0] >= '0' && argv[i + 1][0] <= '9') {
                    tmp = atoi(argv[i + 1]);
                    if (tmp >= *pQueue) {
                        printf("E  ");
                        fprintf(fp, "E  ");
                        break;
                    } else {
                        tmp2 = (*pQueue)[tmp];
                        printf("%d  ", tmp2);
                        fprintf(fp, "%d  ", tmp2);
                    }
                }
            }

        }
    }

//    std::cout << "Hello, World!" << std::endl;
    return 0;
}