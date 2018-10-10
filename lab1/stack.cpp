//
// Created by cyc on 18-10-10.
//

#include <malloc.h>
#include "stack.h"

//static char *errorMessages = "error";

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
    p->pos = s.max;
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

    if (p->pos > 1) {
        e = p->elems[p->pos - 1];
        p->pos--;
    }

    return p;
}

STACK *const assign(STACK *const p, const STACK &s) {
    int i;
    for (int i = 0; i < s.pos && i < p->max; i++) {
        p->elems[i] = s.elems[i];
    }
    p->pos = i;
    return p;
}

void print(const STACK *const p) {

    if (p->pos == 0) {
        printf("none of p");
    } else {
        for (int i = 0; i < p->pos; ++i) {
            printf("%d ", (*p).elems[i]);
        }
        printf("\n");
    }

}

void destroySTACK(STACK *const p) {

    free(p->elems);
    if (p != NULL)
        free(p);
//    }
}
