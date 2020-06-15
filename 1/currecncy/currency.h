#pragma once
#ifndef __CURRENCY__H
#define __CURRENCY__H
#include <iostream>
enum class signType{plus,minus};
class currency
{
public:
    currency(signType theSign = signType::plus,
             unsigned long theDollars = 0,
             unsigned int theCents = 0);
    void setValue(signType,unsigned long,unsigned int);
    void setValue(double);
    signType getSign()const {
        return sign;
    }
    unsigned long getDollars()const{
        return dolloars;
    }
    unsigned int getCents()const{
        return cents;
    }
    currency add(const currency &)const;
    currency &increment(const currency&);
    void output()const;
    ~currency() {}
    
private:
    signType sign;           //对象的符号
    unsigned long dolloars; //美元的数量
    unsigned int cents;     //美分的数量
};
#endif
