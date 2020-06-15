#include <iostream>
#include "currency.h"
currency::currency(signType theSign,unsigned long theDollars,unsigned int theCents){
        setValue(theSign,theDollars,theCents);
}
void currency::setValue(signType theSign,unsigned long theDollars,unsigned int theCents){
    //给调用对象的数据成员赋值
    if(theCents > 99)
        throw std::invalid_argument("the Cents must <= 99");
    sign = theSign;
    dolloars = theDollars;
    cents = theCents;
}
void currency::setValue(double theAmount){
    //给调用对象的数据成员赋值
    if(theAmount < 0){
        sign = signType::minus;
        theAmount = -theAmount;
    }
    else
        sign = signType::plus;
    dolloars = (unsigned long)theAmount;//double数据转换成unsigned long
    cents = (unsigned int)((theAmount + 0.001 - dolloars) * 100);
    //上述的cents的计算的时候，因为cents的小数部分在计算机的表示的时候
    //是有偏差的，所以加上0.001表示与实际值不少于0.001，不多于
    //0.009
    
}
currency currency::add(const currency &rhs)const{
    long a1,a2,a3;
    currency result;
    a1 = dolloars * 100 + cents;
    if(sign == signType::minus)
        a1 = -a1;
    //把rhs的美元转换成整数
    a2 = rhs.dolloars * 100 + rhs.cents;
    if(rhs.sign == signType::minus)
        a2 = -a2;

    a3 = a1 + a2;
    if(a3 < 0){
        result.sign = signType::minus;
        a3 = -a3;
    }
    else
        result.sign = signType::plus;
    result.dolloars = (unsigned long)(a3/100);
    result.cents = a3 - result.dolloars*100;
    return result;
}
currency &currency::increment(const currency &rhs){
    //增加x
    *this = add(rhs);
    return *this;
}
void currency::output()const{
    if(sign == signType::minus)
        std::cout<<'-';
    std::cout<<'$'<<dolloars<<".";
    if(cents<10)
        std::cout<<'0';
    std::cout<<cents;
}
