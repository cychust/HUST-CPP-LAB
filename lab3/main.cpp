#include <iostream>
#include <cstring>

class STACK {
    int *const elems;    //申请内存用于存放栈的元素
    const int max;    //栈能存放的最大元素个数
    int pos;            //栈实际已有元素个数，栈空时pos=0;
public:
    STACK(int m);        //初始化栈：最多m个元素
    STACK(const STACK &s);            //用栈s拷贝初始化栈
    virtual int size() const;            //返回栈的最大元素个数max
    virtual operator int() const;            //返回栈的实际元素个数pos
    virtual int operator[](int x) const;    //取下标x处的栈元素
    virtual STACK &operator<<(int e);    //将e入栈,并返回栈
    virtual STACK &operator>>(int &e);    //出栈到e,并返回栈
    virtual STACK &operator=(const STACK &s); //赋s给栈,并返回被赋值的栈
    virtual void print() const;            //打印栈
    virtual ~STACK();                    //销毁栈
};

STACK::STACK(int m) : max(m), elems(new int[m]) {
    pos = 0;
}

STACK::STACK(const STACK &s) : max(s.max), elems(new int[s.max]) {
    pos = s.pos;
    *this = s;
}

int STACK::size() const {
    return this->max;
}

//int STACK::operator int() const {
//    return this->pos;
//}

STACK::operator int() const {
    return this->pos;
}

int STACK::operator[](int x) const {
    if (x >= pos) {
        printf("E  ");
        return 0;
    }
    return this->elems[x - 1];
}

STACK &STACK::operator<<(int e) {
    if (pos == max) {
        std::cout << "E  ";
        return *this;
    }
    this->elems[pos] = e;
    pos++;
    return *this;
}

STACK &STACK::operator>>(int &e) {
    if (pos == 0) {
        std::cout << "E  ";
        return *this;
    }
    e = this->elems[pos - 1];
    pos--;
    return *this;
}

STACK &STACK::operator=(const STACK &s) {
    int i;
    for (i = 0; i < s.pos && i < max; ++i) {
        this->elems[i] = s.elems[i];
    }
    pos = i;
    return *this;
}

void STACK::print() const {
    for (int i = 0; i < pos; ++i) {
        std::cout << elems[i] << "  ";
    }
}

STACK::~STACK() {
    delete elems;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        STACK *sStack;
        STACK *pStack;
        int operate = 1;  //操作序号 在0-12之间
        int isInitial = 0; //判断栈是否存在
        int maxNum;
        int e;
        int temp;
        int input;
        while (operate) {
            system("cls");
            printf("\n\n");
            printf("    欢  迎  使  用  顺  序  线  性  表  菜  单 \n");
            printf("-------------------------------------------------\n");
            printf("    	  1. 初始化栈P            7. 将一个数出栈到e\n");
            printf("    	  2. 从栈S初始化栈P       8. 赋s给p指向的栈\n");
            printf("    	  3. 栈元素的最大个数     9. 打印p指向的栈 \n");
            printf("    	  4. 栈中实际元素个数     10. 销毁p指向的栈\n");
            printf("    	  5. 取下标为x的栈元素                   \n");
            printf("    	  6. 输入一个数并入栈    0. 退出        \n");
            printf("-------------------------------------------------\n");
            printf("    请选择你的操作[0~11]:");
            scanf("%d", &operate);
            switch (operate) {
                case 1:
                    //InitStack
                    if (isInitial == 0) {
                        printf("\n\t请输入栈的大小:");
                        scanf("%d", &maxNum);
                        sStack = new STACK(maxNum);
                        isInitial = 1;
                        printf("\n\t新建栈成功，栈的大小为%d\n", maxNum);
                    } else {
                        printf("\n\t栈已经被创建\n");
                    }

                    getchar();
                    printf("\n\t\t（按任意键继续……）\n");
                    getchar();
                    break;
                case 2:
                    //initSTACK：S-P
                    if (isInitial)printf("\n\t栈p已经初始化！");
                    else {
                        pStack = new STACK(*sStack);
                        printf("\n\t成功从栈s新建栈p");
                    }
                    getchar();
                    printf("\n\t\t（按任意键继续……）\n");
                    getchar();
                    break;
                case 3:
                    //sizeNum
                    if (!isInitial)printf("\n\t栈p不存在！");
                    else {
                        temp = sStack->size();
                        printf("\n\t该栈的最大容量是%d", temp);
                    }
                    getchar();
                    printf("\n\t\t（按任意键继续……）\n");
                    getchar();
                    break;
                case 4:
                    //howMany
                    if (!isInitial)printf("\n\t栈p不存在！");
                    else {
                        temp = *sStack;
                        printf("\n\t该栈中目前有%d个元素", temp);
                    }
                    getchar();
                    printf("\n\t\t（按任意键继续……）\n");
                    getchar();
                    break;
                case 5:
                    //getelem
                    if (!isInitial)printf("\n\t栈p不存在！");
                    else {
                        printf("\n\t请输入你要查找的数据下标:\n");
                        scanf("%d", &temp);
                        if (temp <= *sStack) {
                            temp = sStack[temp];
                            printf("\n\t你要查找的数据为%d\n", temp);
                        } else {
                            printf("\n\t超出范围！\n");
                        }

                    }
                    getchar();
                    printf("\n\t\t（按任意键继续……）\n");
                    getchar();
                    break;
                case 6:
                    //push
                    if (!isInitial)printf("\n\t栈p不存在！");
                    else {
                        printf("\n\t请输入你需要入栈的元素:");
                        scanf("%d", &e);
                        *sStack >> e;
                        printf("\n\t成功入栈！\n");
                    }
                    getchar();
                    printf("\n\t\t（按任意键继续……）\n");
                    getchar();
                    break;
                case 7:
                    //LocateElem
                    if (!isInitial)printf("\n\t栈p不存在！");
                    else {
                        *sStack << e;
                        printf("\n\t出栈的数据为%d", e);
                    }
                    getchar();
                    printf("\n\t\t（按任意键继续……）\n");
                    getchar();
                    break;
                case 8:
                    //PriorElem
                    if (!isInitial)printf("\n\t栈p不存在！");
                    else {
                        *sStack = *pStack;
                    }
                    getchar();
                    printf("\n\t\t（按任意键继续……）\n");
                    getchar();
                    break;
                case 9:
                    //NextElem
                    if (!isInitial)printf("\n\t栈p不存在！");
                    else {
                        printf("\n\t该栈的内容为：\n");
                        sStack->print();
                    }
                    getchar();
                    printf("\n\t\t（按任意键继续……）\n");
                    getchar();
                    break;
                case 10:

                    if (!isInitial)printf("\n\t栈p不存在！");
                    else {
                        delete sStack;
                        printf("\n\t成功销毁该栈！\n");
                    }
                    getchar();
                    printf("\n\t\t（按任意键继续……）\n");
                    getchar();
                    break;

                case 0:
                    break;
            }//end of switch
        }//end of while
        printf("欢迎下次再使用本系统！\n");
        return 0;
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
        STACK *pStack;
        STACK *sStack;
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
                    pStack = new STACK(tmp);
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
                    int stackLength = *pStack;
                    int stackMax = pStack->size();
                    if (stackLength == stackMax) {
                        printf("E  ");
                        fprintf(fp, "E  ");
                        flag = 1;
                        break;
                    }
                    *pStack << tmp;
                }
                if (flag == 0) {
                    pStack->print();
                    if (err == 0)
                        for (int j = 0; j < *pStack; ++j) {
                            fprintf(fp, "%d  ", (*pStack)[j]);
                        }
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
                    if (tmp > *pStack) {
                        printf("E");
                        fprintf(fp, "E  ");
                        break;
                    }
                    for (int j = 0; j < tmp; ++j) {
                        *pStack >> tmp2;
                    }
                    pStack->print();
                    if (err == 0)
                        for (int j = 0; j < *pStack; ++j) {
                            fprintf(fp, "%d  ", (*pStack)[j]);
                        }
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
                    sStack = new STACK(tmp);
                    *sStack = *pStack;
                    sStack->print();
                    if (err == 0)
                        for (int j = 0; j < *sStack; ++j) {
                            fprintf(fp, "%d  ", (*sStack)[j]);
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
                sStack = new STACK(*pStack);
                sStack->print();
                if (err == 0)
                    for (int j = 0; j < *sStack; ++j) {
                        fprintf(fp, "%d  ", (*sStack)[j]);
                    }
            }
            if (!strcmp(argv[i], "-N")) {
                printf("N  ");
                fprintf(fp, "N  ");
                int n = *pStack;
                fprintf(fp, "%d  ", n);
                printf("%d", n);
            }
            if (!strcmp(argv[i], "-G")) {
                printf("G  ");
                fprintf(fp, "G  ");
                if (i + 1 < argc && argv[i + 1][0] >= '0' && argv[i + 1][0] <= '9') {
                    tmp = atoi(argv[i + 1]);
                    if (tmp >= *pStack) {
                        printf("E  ");
                        fprintf(fp, "E  ");
                        break;
                    } else {
                        tmp2 = (*pStack)[tmp];
                        printf("%d  ", tmp2);
                        fprintf(fp, "%d  ", tmp2);
                    }
                }
            }

        }
    }

    return 0;
}