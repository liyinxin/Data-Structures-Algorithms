#pragma once
#ifndef __LISTMAP_H
#define __LISTMAP_H
#include <iostream>
#include <string>
//自定义一个错误报错的类，继承自length_error
class illeagleParameter : public std::length_error{
public:
    explicit illeagleParameter(const std::string &s):length_error(s){}
};

//自定义一个listMap用来存放n个线性表
template<typename T> class listMap
{
public:
    listMap(int listSize=1000,int elementSize=1000):front(new T[listSize+2]),last(new T[listSize+2]),
    length(listSize * elementSize),element(new T[length]){
        front[0] = last[0] = -1;
        front[listSize+1] = last[listSize+1] = length - 1;
        //放两个边界主要是为了好处理，左右内存空间还有没有空的问题，
        //如果你不放一个边界的话，那么在查找左边或右边有没有空的时候
        //就不容易找到终止条件，所以你在最后一个位置放一个边界，如果
        //极限情况下，全满的时候，你的std-1的last和std的front就是
        //相等的。
        for(int i = 1; i <= listSize;++i){
            front[i] = last[i] = -1+elementSize*(i-1);
        }
    }
    void insert(int i,int index,const T &theElement);//在第i个表的index处插入元素theEleme
    T get(int i,int index)const;
    int capacity()const;
    int getFront(int i)const;
    int getLast(int i)const;
    ~listMap() {}

private:
    T *front;//front和last中存放的值是每个列表中第一个元素的前边位置，以及
    T *last;//最后一个元素的位置
    T *element;//存放所有元素的指针，每个数组中存放的大小是lastSize大小的
    int length;
};

#endif
