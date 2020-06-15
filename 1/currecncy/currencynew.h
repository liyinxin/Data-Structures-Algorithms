#pragma once
#ifndef __CURRENCYNEW_H
#define __CURRENCYNEW_H
#include <ostream>
enum signType{plus,minus};
class currencynew
{
friend std::ostream &operator<<(std::ostream &,const currencynew &);
public:
    currencynew(signType theSign = plus,
                 unsigned long theDollars = 0,
                 unsigned int theCents = 0);
    void setValue(signType,unsigned long,unsigned int);
    void setValue(double);
    signType getSign()const{
        if(amount < 0)
            return minus;
        else
            return plus;
    }
    unsigned long getDollar()const{
       if(amount < 0) {
           return (-amount)/100;
       }
       else
           return amount/100;
    }
    unsigned int getCents()const{
        if(amount < 0){
            return ((-amount)-getDollar()*100);
        }
        else
            return (amount - getDollar()*100);
    }
    currencynew add(const currencynew &)const;
    currencynew &increment(const currencynew &);
    currencynew operator+(const currencynew &)const;
    currencynew &operator+=(const currencynew &);
    currencynew input();
    currencynew subtract(const currencynew &x);
    currencynew percent(double x)const;
    currencynew muliply(double x)const;
    currencynew divide(double x)const;
    void output(std::ostream &)const;
    currencynew operator-(const currencynew &rhs)const;
    currencynew operator%(double x)const;
    currencynew operator*(double x)const;
    currencynew operator/(double x)const;
    ~currencynew() {}

private:
    long amount;
};
//重载<<
std::ostream &operator<<(std::ostream &,const currencynew &);
//注意上面的operator<<重载一定要声明，要不然在main函数调用
//的时候，编译器默认使用的是内置的ostream的<<运算符
#endif
