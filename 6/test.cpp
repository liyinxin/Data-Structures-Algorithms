#include <iostream>
/*
//class A;
class B;
//void printElement(const B& a);
//template<typename T>
class A {//没有乱码
//基类的友元函数是可以通过派生类的对象去访问派生类中的基类的友元函数的!!!!
//friend  void printElement(const B &a);

public:
    A(int theElement):element(theElement){}
    void print(){std::cout<<element<<std::endl;}
protected:
    int element;
};

class B : public A{
//测试2，派生类的友元函数可以访问从基类中继承过来的成员!!!!!
friend void printElement(const B &a);
public:
    B(int theElement):A(theElement){}
    void print(){
        A::print();
    }
};
//基类的友元函数可以通过派生类的对象去访问基类的成员函数的!!!
*
void printElement(const B &a){
    std::cout<<a.element;
}*
void printElement(const B &a){
    std::cout<<a.element;
}
*/

template<typename T>
class A {//没有乱码
public:
    A(int theElement):element(theElement){}
    void print(){std::cout<<element<<std::endl;}
protected:
    int element;
};
template<typename T>
class B : public A<T>{
template<typename C> friend void printElement(const B<C> &a);
template<typename E> friend bool operator==(const B<E> &left,const B<E> &right);
public:
    B(int theElement):A<T>(theElement){}
    void print(){
        A<T>::print();
    }
};
template<typename T> void printElement(const B<T> &a){
    std::cout<<a.A<T>::element;
}
template<typename T> bool operator==(const B<T> &left,const B<T> &right){
    std::cout<<"left is "<<left.A<T>::element;
    std::cout<<"\nright is "<<right.A<T>::element;
    return 1;
}
int main()
{
    B<int> b(100),b1(200);
    b.print();
    //A a(1000);
    std::cout<< "Hello world" << std::endl;
    std::cout<<"\n";
    b==b1;
    return 0;
}

