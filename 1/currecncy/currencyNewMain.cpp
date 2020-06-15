#include <iostream>
#include "currencynew.h"

int main()
{
    currencynew g,h(plus,3,50),i,j;
    //使用两种形式的setValue来赋值
    g.setValue(minus,2,25);
    i.setValue(-6.45);

    //调用成员函数add和output
    j = h + g;
    
    std::cout<<h<<" + "<<g<<" = "<<j<<std::endl;
    //连续两次调用成员函数add
    j = i+g+h;
    std::cout<<i<<" + "<<g<<" + "<<h<<" = "<<j<<std::endl;

    //调用成员函数increment和add
    std::cout<<"Increment "<<i<<" by "<<g<<" and then "
            " add "<<h<<std::endl;

    j = (i += g)+h;
    std::cout<<"Result is "<<j<<std::endl;
    std::cout<<"Incremented object is "<<i<<std::endl;
    std::cout<<j.input()<<std::endl;
    std::cout<<"j is :"<<j<<std::endl;
    //测试加减乘除
    std::cout<<"j = "<<j<<" h= "<<h<<" j-h "<<j-h<<std::endl;
    std::cout<<"j = "<<j<<" x= 0.5"<<" j %50 = "<<j%50<<std::endl;
    //测试异常
    std::cout<<"Attempting to initialized with cents = 152"<<std::endl;

    try{
        i.setValue(plus,3,152);
    }catch(std::invalid_argument e){
        std::cout<<"cought throw exception "<<std::endl;
        std::cout<<e.what()<<std::endl;
    }
    return 0;
}

