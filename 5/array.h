#pragma once
#ifndef __ARRAY_H__
#define __ARRAY_H__
#include <iostream>

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
    bool empty()const{return listSize == 0;}
    int size()const{return listSize;}
    T &get(int theIndex)const;
    int indexOf(const T& theElement)const;
    void erase(int theIndex);
    void insert(int theIndex,const T &theElement);
    void output(std::ostream &out)const;

    //新增的方法
    int capacity()const{return arrayLength;}    
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
    void trimToSize();
    void setSize(int newLength);
    T &operator[](int index);
    const T &operator[](int index)const;//常量对象的返回的是常量的变量
    void push_back(const T &theElement);
    void pop_back();
    void swap(arrayList<T> &theList);
    //void changArrayLength(int newArrayLength);
    //void changListSize(int newListSize);
    //T *&getElement();
    T set(int theIndex,const T &theElement);
    void reserve(int theCapacity);
    void clear();
    void removeRange(int start,int end);



private:
    int listSize;//线性表的元素个数
    int arrayLength;//一维数组的容量
    void checkIndex(int theIndex)const;//如果索引无效的话，则抛出异常
    T *element;//存储线性表示元素的一维数组

};

#endif
