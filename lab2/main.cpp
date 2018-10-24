#include <iostream>

class STACK {
    int *const elems;    //申请内存用于存放栈的元素
    const int max;    //栈能存放的最大元素个数
    int pos;            //栈实际已有元素个数，栈空时pos=0;
public:
    STACK(int m);        //初始化栈：最多m个元素
    STACK(const STACK &s); //用栈s拷贝初始化栈
    int size() const;        //返回栈的最大元素个数max
    int howMany() const;    //返回栈的实际元素个数pos
    int getelem(int x) const;    //取下标x处的栈元素
    STACK &push(int e);    //将e入栈,并返回栈
    STACK &pop(int &e);    //出栈到e,并返回栈
    STACK &assign(const STACK &s); //赋s给栈,并返回被赋值的栈
    void print() const;        //打印栈
    ~STACK();                //销毁栈
};

STACK::STACK(int m) : max(m), elems(new int[m]) {
    this->pos = 0;
}

STACK::STACK(const STACK &s) : max(s.max), elems(new int[s.max]) {
    this->pos = s.pos;
    assign(s);
}

int STACK::size() const {
    return this->max;
}

int STACK::howMany() const {
    return this->pos;
}

int STACK::getelem(int x) const {
    if (x >= pos) {
        printf("error");
        return 0;
    }
    return this->elems[x];
}

STACK &STACK::push(int e) {
    if (pos == max) {
        printf("堆已满");
        return *this;
    }
    this->elems[pos] = e;
    this->pos++;
    return *this;
}

STACK &STACK::pop(int &e) {
    if (pos == 0) {
        printf("E  ");
        return *this;
    }
    e = this->elems[pos - 1];
    this->pos--;
    return *this;
}

STACK &STACK::assign(const STACK &s) {
    int i;
    for (i = 0; i < s.pos && i < this->max; ++i) {
        this->elems[i] = s.elems[i];
    }
    pos = i;
    return *this;
}

void STACK::print() const {
    for (int i = 0; i < pos; ++i) {
        printf("%d  ", this->elems[i]);
    }
}

STACK::~STACK() {
    delete (this->elems);
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}