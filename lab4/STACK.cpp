//
// Created by cyc on 18-11-7.
//

#include "STACK.h"

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
    return this->elems[x];
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