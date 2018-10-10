#include <iostream>
#include "stack.h"

int main() {
//    std::cout << "Hello, World!" << std::endl;
    STACK *s;
    STACK *p1;
    int tmp;
    initSTACK(s, 5);
    printf("%d\n", s->max);
    push(s, 3);
    print(s);
    push(s, 2);
    pop(s, tmp);
    printf("%d\n", tmp);
    print(s);
    initSTACK(p1,*s);
    print(p1);
    return 0;
}