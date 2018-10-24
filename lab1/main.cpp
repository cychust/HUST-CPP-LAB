#include <iostream>
#include <string.h>
#include "stdio.h"
#include <malloc.h>
#include <stdlib.h>

struct STACK {
    int *elems;
    int max;
    int pos;
};
typedef struct STACK STACK;

void initSTACK(STACK *const p, int m);    //初始化p指向的栈：最多m个元素
void initSTACK(STACK *const p, const STACK &s); //用栈s初始化p指向的栈
int size(const STACK *const p);        //返回p指向的栈的最大元素个数max
int howMany(const STACK *const p);    //返回p指向的栈的实际元素个数pos
int getelem(const STACK *const p, int x);    //取下标x处的栈元素
STACK *const push(STACK *const p, int e);    //将e入栈，并返回p
STACK *const pop(STACK *const p, int &e);    //出栈到e，并返回p
STACK *const assign(STACK *const p, const STACK &s); //赋s给p指的栈,并返回p
void print(const STACK *const p);            //打印p指向的栈
void destroySTACK(STACK *const p);        //销毁p指向的栈


FILE *fp;


int main(int argc, char *argv[]) {

    if (argc == 1) {
        STACK *pStack = (struct STACK *) malloc(sizeof(STACK));
        STACK *sStack = (struct STACK *) malloc(sizeof(STACK));
        initSTACK(sStack, 5);
        push(sStack, 4);
        push(sStack, 7);
        push(sStack, 6);
        push(sStack, 1);
        push(sStack, 3);
        push(sStack, 4);

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
                        initSTACK(pStack, maxNum);
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
                        initSTACK(pStack, *sStack);
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
                        temp = size(pStack);
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
                        temp = howMany(pStack);
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
                        if (temp <= howMany(pStack)) {
                            temp = getelem(pStack, temp);
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
                        push(pStack, e);
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
                        pop(pStack, e);
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
                        assign(pStack, *sStack);
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
                        print(pStack);
                    }
                    getchar();
                    printf("\n\t\t（按任意键继续……）\n");
                    getchar();
                    break;
                case 10:

                    if (!isInitial)printf("\n\t栈p不存在！");
                    else {
                        destroySTACK(pStack);
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
        int err;
        char filename[20];
        strcat(filename, argv[0]);
        strcat(filename, ".txt");
        if ((fp = fopen(filename, "w")) == NULL) {
//            printf("Cannot open file strike any key exit!");
            err=1;
            getchar();
        } else{
//            printf("%s\n",filename);
            err=0;
        }
        STACK *pStack = (STACK *) malloc(sizeof(STACK));
        STACK *sStack = (STACK *) malloc(sizeof(STACK));
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
                if (argv[i + 1][0] >= '0' && argv[i + 1][0] <= '9') {
                    tmp = atoi(argv[i + 1]);
                    initSTACK(pStack, tmp);
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
                    int stackLength = howMany(pStack);
                    int stackMax = size(pStack);
                    if (stackLength == stackMax) {
                        printf("E  ");
                        fprintf(fp, "E  ");
                        flag = 1;
                        break;
                    }
                    push(pStack, tmp);
                }
                if (flag == 0) {
                    print(pStack);
                    if (err == 0)
                        for (int j = 0; j < pStack->pos; ++j) {
                            fprintf(fp, "%d  ", pStack->elems[j]);
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
                if (argv[i + 1][0] >= '0' && argv[i + 1][0] <= '9') {
                    tmp = atoi(argv[i + 1]);
                    if (tmp > howMany(pStack)) {
                        printf("E");
                        fprintf(fp, "E  ");
                        break;
                    }
                    for (int j = 0; j < tmp; ++j) {
                        pop(pStack, tmp2);
                    }
                    print(pStack);
                    if (err == 0)
                        for (int j = 0; j < sStack->pos; ++j) {
                            fprintf(fp, "%d  ", sStack->elems[j]);
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
                if (argv[i + 1][0] >= '0' && argv[i + 1][0] <= '9') {
                    tmp = atoi(argv[i + 1]);
                    initSTACK(sStack, tmp);
                    assign(sStack, (*pStack));
                    print(sStack);
                    if (err == 0)
                        for (int j = 0; j < sStack->pos; ++j) {
                            fprintf(fp, "%d  ", sStack->elems[j]);
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
                initSTACK(sStack, *pStack);
                print(sStack);
                if (err == 0)
                    for (int j = 0; j < sStack->pos; ++j) {
                        fprintf(fp, "%d  ", sStack->elems[j]);
                    }
            }
            if (!strcmp(argv[i], "-N")) {
                printf("N  ");
                fprintf(fp, "N  ");
                int n = howMany(pStack);
                fprintf(fp, "%d  ", n);
                printf("%d", n);
            }
            if (!strcmp(argv[i], "-G")) {
                printf("G  ");
                fprintf(fp, "G  ");
                if (argv[i + 1][0] >= '0' && argv[i + 1][0] <= '9') {
                    tmp = atoi(argv[i + 1]);
                    if (tmp >= howMany(pStack)) {
                        printf("E  ");
                        fprintf(fp, "E  ");
                        break;
                    } else {
                        tmp2 = getelem(pStack, tmp);
                        printf("%d  ", tmp2);
                        fprintf(fp, "%d  ", tmp2);
                    }
                }
            }

        }
    }

    return 0;

}


void initSTACK(STACK *const p, int m) {
    p->elems = (int *) malloc(sizeof(int) * m);
    p->max = m;
    p->pos = 0;
//    else
//        print("%s",errorMessages);
}

void initSTACK(STACK *const p, const STACK &s) {
    initSTACK(p, s.max);
//    p->elems = s.elems;
    p->max = s.max;
    p->pos = 0;
    assign(p, s);

}

int size(const STACK *const p) {
    if (p != NULL)
        return p->max;
    return -1;
}

int howMany(const STACK *const p) {
    if (p != NULL)
        return p->pos;
    return -1;
}

int getelem(const STACK *const p, int x) {
    if (p != NULL) {
        if (x >= 0 && x < p->pos) {
            return p->elems[x];
        }
    }
}

STACK *const push(STACK *const p, int e) {
    if (p->max > p->pos) {
        (*p).elems[p->pos] = e;
        p->pos++;
    }
    return p;
}

STACK *const pop(STACK *const p, int &e) {

    if (p->pos >= 1) {
        e = p->elems[p->pos - 1];
        p->pos--;
    }

    return p;
}

STACK *const assign(STACK *const p, const STACK &s) {
    int i;
    for (i = 0; i < s.pos; i++) {
        p->elems[i] = s.elems[i];
    }
    p->pos = i;
    return p;
}

void print(const STACK *const p) {

    for (int i = 0; i < p->pos; ++i) {
        printf("%d  ", p->elems[i]);
    }


}

void destroySTACK(STACK *const p) {

    free(p->elems);
//    if (p != NULL)
//        free(p);
//    }
}