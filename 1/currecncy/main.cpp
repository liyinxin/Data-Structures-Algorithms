#include <iostream>
#include "currencynew.h"
int main()
{
    currencynew g,h(signType::plus,3,50),i,j;
    //使用两种形式的setValue来赋值
    g.setValue(signType::minus,2,25);
    i.setValue(-6.45);
    //调用成员函数add和output
    j = h.add(g);
    j.output(std::cout);std::cout<<std::endl;
    //连续调用两次成员函数add
    j = i.add(g).add(h);
    j.output(std::cout);std::cout<<std::endl;
    //调用成员函数increment和add
    j = i.increment(g).add(h);
    j.output(std::cout);std::cout<<std::endl;
    //测试异常
    std::cout<<"Attempting to initialize with cents = 152"<<std::endl;

    try{
        i.setValue(signType::plus,3,152);
    }catch(std::invalid_argument e){
        std::cout<<"Caught throw expression"<<std::endl;
        std::cout<<e.what()<<std::endl;
    }
    return 0;
}

