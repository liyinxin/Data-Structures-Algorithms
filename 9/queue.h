#pragma once
#ifndef __QUEUE__H
template<typename T>
class queue
{
public:
    virtual bool empty()const =0;   //返回是不是空的
    virtual int size()const =0;     //返回这个队列的大小的
    virtual T &front() =0;          //返回当前队列中的第一个元素
    virtual T &back() =0;           //返回队列的尾元素
    virtual void pop() =0;          //删除首元素
    virtual void push(const T& theElement) =0;//插入到队尾
    virtual ~queue() {}
};

#endif
