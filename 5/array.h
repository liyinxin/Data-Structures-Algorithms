#pragma once
#ifndef __ARRAY_H__
#define __ARRAY_H__
#include <iostream>
#include <sstream>//注意:ostringstream是在sstream中的
#include <iterator>
#include <typeinfo>
#include <cxxabi.h>
#include <string>
#include <algorithm>

//这是一个抽象基类
/*
   抽象数据类型linearList{
    实例:
        有限个元素的有序集合
    操作:
        empty();若表空，返回true了；否则返回false
        size():返回线性表的大小（表的元素个数）
        get(index):返回线性表中索引为index的元素
        indexOf(x):返回线性表中第一次出现的x的索引。若x不存在，则返回-1
        erase(index):删除索引为index的元素，索引大于index的元素其索引减一
        insert(index,x):将x插入线性表中索引为index的位置上，索引大于index的元素其索引加一
        output(cout):从左到右输出表元素
   }
 */
extern const std::string getClearName(const char  *name);
template<typename T> class linearList{
public:
    virtual ~linearList(){}
    virtual bool empty()const =0;
    virtual int size()const =0;
    virtual T& get(int theIndex)const =0;
    virtual int indexOf(const T& theElement)const =0;
    virtual void erase(int theIndex) =0;
    virtual void insert(int theIndex,const T& theElement)=0;
    virtual void output(std::ostream &out)const =0;

};
template<typename T>class arrayList : public linearList<T>{
public:
    //构造函数，拷贝构造函数和析构函数
    arrayList(int initialCapacity = 10);
    arrayList(const arrayList<T> &);

    ~arrayList(){}

    //ADT的纯虚函数方法
    bool empty()const override{return listSize == 0;}
    int size()const{return listSize;}
    T &get(int theIndex)const;
    int indexOf(const T& theElement)const override;
    void erase(int theIndex);
    void insert(int theIndex,const T &theElement);
    void output(std::ostream &out)const;

    //新增的方法
    int capacity()const{
        return arrayLength;
    }
    /*
     首先说明一下，在类(A)中嵌套类(B)的定义。两个类都是相互独立的。类A
     和类B是相互独立的。类A是不能访问类B的，同理类B也是不能访问类A的。
     所以两者之间的桥梁就是将类A的成员传递给类B，然后类B使用类A
     传进来的成员进行二次的开发使用。
     接下来就能看到类arrayList<T>是如何被iterator访问的。我们发现在类
     arrayList<T>中定义了两个成员函数begin()和end()。但是注意这两个成员
     的返回类型是iterator也就是类的对象。所以我们可以继续使用这个对象的
     方法去进行一些操作。比如说*(array3.begin())就是表示的是array3[0]
     *
     *
     *
     */
    class iterator{
    public:
        //用C++的typedef语句实现双向迭代器
        //typedef type anothername
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;

        //构造函数
        iterator(T *thePosition = 0):position(thePosition){}

        //解引用操作符
        T &operator*()const{return *position;}
        T *operator->()const{return &*position;}

        //迭代器的值增加
        iterator &operator++(){//前增加
            ++position;
            return *this;
        }
        iterator &operator++(int){//后加
            iterator old = *this;
            ++position;
            return old;
        }
        //迭代器的减少
        iterator &operator--(){//前减
            --position;
            return *this;
        }
        iterator &operator--(int){//后减
            iterator old = *this;
            --position;
            return old;//其实后加/减都增加或至少了迭代器，只不过返回的结果是
                      //原先的对象而已，
        }
        //测试是否相等
        bool operator!=(const iterator &right)const{
            return position != right.position;
        }
        bool operator==(const iterator &right)const{
            return position == right.position;
        }
    protected:
        T *position;
    };
    iterator begin(){
        return iterator(element);
    }
    iterator end(){
        return iterator(element + listSize);
    }

    //习题新增加的功能
    void trimToSize();//将arrayLength - listSize之间的空间给删掉
    void setSize(int newLength);
    T &operator[](int index);
    const T &operator[](int index)const;//常量对象的返回的是常量的变量
    void push_back(const T &theElement);//在线性表右端插入一个元素
    void pop_back();//输出最后一个元素
    void swap(arrayList<T> &theList);//跟theList进行交换
    //void changArrayLength(int newArrayLength);
    //void changListSize(int newListSize);
    //T *&getElement();
    T set(int theIndex,const T &theElement);//用元素theElement替换索引为theIndex的元素
    void reserve(int theCapacity);//把数组的容量改变为当前容量和theCapacity中
    //较大者
    void clear();//清楚element指向的元素空间也被删除了
    void removeRange(int start,int end);//将start--end这个序列从element指向的序列中删除
    int lastIndexOf(const T &theElement)const;//返回theElement在该序列中的最后一个位置，如果不存在则返回-1
    void reverse();//原地倒序翻转
    void leftShift(int index);//仅仅是把左边部分给移除去
    void circularShift(int index);//循环移位，
    void half();//将线性表的元素隔一个删除一个
    void meld(const arrayList<T> &a,const arrayList<T> &b);
    void merge(const arrayList<T> &a,const arrayList<T> &b);
    void split(arrayList<T> &a,arrayList<T> &b);

private:
    int listSize;//线性表的元素个数
    int arrayLength;//一维数组的容量
    void checkIndex(int theIndex)const;//如果索引无效的话，则抛出异常
    T *element;//存储线性表示元素的一维数组

};

#endif
