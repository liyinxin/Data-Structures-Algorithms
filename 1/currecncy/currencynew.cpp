#include <iostream>
#include "currencynew.h"

currencynew::currencynew(signType theSign,unsigned long theDollar,unsigned int theCents){
    setValue(theSign,theDollar,theCents);
}
currencynew currencynew::add(const currencynew &rhs)const{
    currencynew result;
    result.amount = this->amount + rhs.amount;
    return result;
}
currencynew &currencynew::increment(const currencynew&rhs){
    //注意，this是指向本对象的指针
    *this = this->add(rhs);
    return *this;
}
void currencynew::setValue(signType theSign,unsigned long theDoallar,unsigned int theCents){
    if(theCents > 99)
        throw std::invalid_argument("the Cents must < 100");
    this->amount = theDoallar*100 + theCents;
    if(theSign == minus){
        this->amount = -this->amount;
    }
}
void currencynew::setValue(double theAmount){
    if(theAmount < 0)
        amount = (theAmount - 0.001)*100;
    else
        amount = (theAmount + 0.001)*100;
    //注意这个amount是调用该setValue对象的
    //成员
}
void currencynew::output(std::ostream &out)const{
    long theAmount = amount;
    if(theAmount < 0){
        out<<'-';
        theAmount = -theAmount;
    }
    long dollars = theAmount /100;
    int cents = theAmount-dollars*100;
    if(cents < 10)
        cents = 0;
    out<<'$'<<dollars<<'.'<<cents;
}
currencynew currencynew::operator+(const currencynew &rhs)const{
    currencynew result;
    result.amount = amount + rhs.amount;
    return result;
}
currencynew &currencynew::operator+=(const currencynew &rhs){
    *this = *this + rhs;
    return *this;
}
//重载<<运算符
/*
 * std::ostream &operator<<(std::ostream &out,const currencynew &x){
    x.output(out);
}
*/
std::ostream &operator<<(std::ostream &out,const currencynew &x){
    char theSign;
    long dollars;
    int cents;
    long theAmount = x.amount;
    if(theAmount < 0){
        out<<'-';
        theAmount = -theAmount;
    }
    dollars = theAmount/100;
    cents = theAmount - dollars*100;
    out<<'$'<<dollars<<'.'<<cents;
    return out;
}
currencynew currencynew::input(){
    double theAmount=0;//以防用户输错数据
    currencynew temp;
    std::cout<<"Please input the amount of the money,the type must be a right data"<<std::endl;
    if(std::cin>>theAmount){
        temp.setValue(theAmount);
    }
    else
        std::cout<<"you must input the right data"<<std::endl;
    return temp;
}
currencynew currencynew::subtract(const currencynew &x){
    currencynew result;
    result.amount = (*this).amount - x.amount;
    return result;
}
currencynew currencynew::percent(double x)const{
    currencynew result;
    result.amount = long(amount*(x/100));  
    return result;
}
currencynew currencynew::muliply(double x)const{
    currencynew result;
    result.amount = (long)(this->amount * x);
    return result;
}
currencynew currencynew::divide(double x)const{
    currencynew result;
    result.amount = (long)(this->amount / x);
}
currencynew currencynew::operator-(const currencynew &rhs)const{
    currencynew result;
    result.amount = amount - rhs.amount;
    return result;
}
currencynew currencynew::operator%(double x)const{
    currencynew result;
    result.amount = (long)(amount * x /100);
    return result;
}
currencynew currencynew::operator*(double x)const{
    currencynew result;
    result.amount = amount * x;
    return result;
}
currencynew currencynew::operator/(double x)const{
    currencynew result;
    result.amount = (long)(amount / x);
    return result;
}
