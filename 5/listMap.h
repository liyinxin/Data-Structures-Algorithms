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
    //类的构造函数初始化顺序:
    //构造函数初始值列表只说明用于初始化成员的值，而不限定初始化的具体执行顺序，成员
    //的初始化顺序与它们在类定义中的出现顺序一致：第一个定义的成员先被初始化，然后第二个
    //以此类推，构造函数初始值列表中初始值的前后位置关系不会影响实际的初始化顺序，
    //所以在下面的初始化的时候，element是先于length，如果你要使用element(new T[length])
    //那么就会出问题，因为length这个时候还没被初始化，所以你的length值不是listSize*elementSize!!!
    //注意，在参数初始化的顺序，如果不清楚，就不要去写element(new T[listSize*element])这种
    //因为如果你不确定length和element谁先被初始化，如果length先被初始化是没问题的，但是
    //如果element先被初始化就完蛋了，因为此时的length是一个不确定的值，所以这个时候要注意
    //为了以防万一，我们就不使用不确定的元素去初始化，直接使用已知的。
    listMap(int listSize=1000,int elementSize=1000):front(new T[listSize+2]),last(new T[listSize+2]),
    length(listSize * elementSize),element(new T[listSize*elementSize]){
        front[0] = last[0] = -1;
        front[listSize+1] = last[listSize+1] = length - 1;
        //放两个边界主要是为了好处理，左右内存空间还有没有空的问题，
        //如果你不放一个边界的话，那么在查找左边或右边有没有空的时候
        //就不容易找到终止条件，所以你在最后一个位置放一个边界，如果
        //极限情况下，全满的时候，你的std-1的last和std的front就是
        //相等的。
        for(int i = 1; i <= listSize;++i){
            front[i] = last[i] = -1+elementSize*(i-1);
        for(int i = 0; i != length; ++i)
            element[i] = 0;
        }
    }
    void insert(int i,int index,const T &theElement);//在第i个表的index处插入元素theEleme
    T get(int i,int index)const;
    int capacity()const;
    int getFront(int i)const;
    int getLast(int i)const;
    void printAllMemeber()const;
    ~listMap() {}

private:
    T *front;//表示每个线性数组的第一个元素的前面的位置(最开始元素的前一个位置)
    T *last;//表示每一个线性数组的最后一个元素的位置(索引)
    T *element;//存放所有元素的指针，每个数组中存放的大小是lastSize大小的
    int length;
};

#endif
