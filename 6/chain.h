#pragma once
#ifndef __CHAIN__H
#define __CHAIN__H
//编程原则，在你编写程序的时候一些常量参数，最好设置成全局的。然后
//不要一个一个写成数字放到函数中。因为这样修改程序的时候只需要修改
//这个常数变量就好了，很方便也不容易出错
#include <iostream>
#include <sstream>


class illegalParameterValue : public std::length_error{
public:
    explicit illegalParameterValue(const std::string &what):length_error(what){}
};
template<typename T> class linearList{
public:
    virtual ~linearList(){}
    virtual bool empty()const =0;//纯虚函数,后面加=0
    virtual int size()const =0;
    virtual T &get(int theIndex)const =0;
    virtual int indexOf(const T &theElement)const =0;
    virtual void erase(int theIndex) =0;
    virtual void insert(int theIndex,const T& theElement) =0;
    virtual void output(std::ostream &out)const =0;
};

template<typename T> class chainNode
{
public:
    T element;//数据元素
    chainNode<T> *next;//链表指针，指向下一个节点
    chainNode() {}
    //这个构造函数是用来通过一个element来创建一个节点的
    chainNode(const T& element):next(NULL){
        this->element = element;
    }
    //这个构造函数，是先创建一个element的节点，然后把这个节点的下一个位置
    //指向传入进来的指针指向的节点的。
    //这个主要是在头结点插入的时候使用的。
    chainNode(const T& element,chainNode<T> *next){
        this->element = element;
        this->next = next;
        //把该chainNode对象的next指向的位置改变成next这个指针指向的内存空间
    }
    ~chainNode() {}
};



//注意一下firstNode作为的索引下标是0！！！不是-1
template<typename T> class chain : public linearList<T>{
public:
    //构造函数，赋值构造函数和析构函数
    chain(int initialCapacity = 10);
    chain(const chain<T> &);//拷贝构造函数
    ~chain();

    //抽象数据类型ADT的方法
    bool empty()const override{return listSize==0;}
    int size()const override{return listSize;}
    T &get(int theIndex)const override;
    int indexOf(const T &theElement)const override;
    void erase(int theIndex)override;
    void insert(int theIndex,const T& theElement)override;
    void output(std::ostream &out)const override;
    //std::ostream &operator<<(std::ostream &cout)const;注意这么做是错误的
    //因为不能把<<作为一个类内的重载的成员函数的
protected:
    void checkIndex(int theIndex)const;
    //firstNode表示的指向的是线性表的第一个节点的指针
    chainNode<T> *firstNode;//通过类chain的对象去访问chainNode类的对象
    //头结点是不需要去保存你的element数据的
    int listSize;//表示节点的个数，也就是线性表的元素的个数
};
#endif

