#include <iostream>

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
    this = s;
}

int STACK::size() const {
    return this->max;
}

int STACK::operator int() const {
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

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}