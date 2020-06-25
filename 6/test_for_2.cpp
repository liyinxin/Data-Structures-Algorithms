#include <iostream>
//class A;
class B;
//void printElement(const B& a);
//template<typename T>
class A {//没有乱码
//基类的友元函数是可以通过派生类的对象去访问派生类中的基类的友元函数的!!!!
friend  void printElement(const A &a);

public:
    A(int theElement):element(theElement){}
    void print(){std::cout<<element<<std::endl;}
protected:
    int element;
};

class B : public A{
//测试2，派生类的友元函数可以访问从基类中继承过来的成员!!!!!
//friend void printElement(const B &a);
public:
    B(int theElement):A(theElement),number(10){}
    void print(){
        A::print();
    }
protected:
    int number;
};
//基类的友元函数可以通过派生类的对象去访问基类的成员函数的!!!
/*
void printElement(const B &a){
    std::cout<<a.element;
}*/
void printElement(const A &a){
    std::cout<<a.element;
}
int main()
{
    B b(100);
    b.print();
    //A a(1000);
    std::cout<< "Hello world" << std::endl;
    std::cout<<"\n";
    printElement(b);
    return 0;
}

