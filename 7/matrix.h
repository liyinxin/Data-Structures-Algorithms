#pragma once
#ifndef __MATRIX__H
#define __MATRIX__H
#include <iostream>
#include "illegalNumber.h"

template<typename T>
class matrix{
friend std::ostream &operator<<(std::ostream &out,const matrix<T> &);
public:
    matrix(int theRows = 0,int theColumns = 0);
    matrix(const matrix<T> &);
    ~matrix() {delete []element;}
    
    int rows() const {return theRows;}
    int columns() const {return theColumns;}

    T &operator()(int i,int j);
    matrix<T> &operator=(const matrix<T> &);
    matrix<T> operator+()const;
    matrix<T> operator+(const matrix<T> &)const;
    matrix<T> operator-()const;
    matrix<T> operator-(const matrix<T> &)const;
    matrix<T> operator*(const matrix<T> &)const;
    matrix<T> operator+=(const matrix<T> &);

private:
    int theRows,theColumns;//矩阵的行数和列数
    //theRows       代表的是行
    //theColumns    代表的是列
    T *element;
};
//构造函数
template<typename T> matrix<T>::matrix(int theRows,int theColumns){
    if(theRows < 0 || theColumns < 0)
        illegalNumber("the input theRows or theColumns must be > 0");
    if((theColumns == 0 || theRows == 0 )&& (theRows != 0 || theColumns != 0))//这个是用来判断到底是不是两个都是0的，只要一个
        //是0那么另外一个也必须是0
        illegalNumber("Either both or neither rows and columns should be zero");
    //如果上面的没问题了，就开始创建矩阵
    this->theRows    = theRows;
    this->theColumns = theColumns;
    this->element = new T[theRows * theColumns];//用一维数组去表示二维数组，可以省略theColumns个指针
}
//拷贝构造函数
template<typename T> matrix<T>::matrix(const matrix<T> &m){
    this->theRows    = m.theRows;
    this->theColumns = m.theColumns;
    this->element    = new T[this->theRows * this->theColumns];
    std::copy(m.element,m.element+theRows*theColumns,this->element);
}
//赋值运算符重载
template<typename T>matrix<T>  &matrix<T>::operator=(const matrix<T> &m){
    if(this != &m){//如果不是自己的话，
        delete []element;//如果不是自己本身的话，得先把自己的元素给删除掉
        this->theRows    = m.theRows;
        this->theColumns = m.theColumns;
        element          = new T[this->theRows * this->theColumns];
        std::copy(m.element,m.element+this->theRows * this->theColumns,this->element);
    }
    //如果要是本身的话，就不用进行操作了。但是要注意，如果不加if的话，要是传进来的是它本身的话，那么就有可能要
    //处理错误了。
    return *this;
}
//重载()运算符
template<typename T> T &matrix<T>::operator()(int i,int j){
    if(i < 1 || i > theRows || j < 1 || j > theColumns)
        throw illegalNumber("i,j must > 1 and <= (theColumns,theRows)");
    //注意二维数组用一维数组行主排列表示的是对应的映射关系函数map是
    //map(i,j) = i*theRows + theColumns;
    return element[(i-1) * theColumns + j-1];//之所以减一，是因为这个i,j对应的是数学中的
    //起点就是(1,1)，对应的是(0,0)(在数组中的表示方法)
}
//重载运算符+
template<typename T> matrix<T> matrix<T>::operator+(const matrix<T> &m)const{
    if(this->theRows != m.theRows || this->theColumns != m.theColumns)
        return 0;//一会过来改一下这个，这个是抛出一个error
    //生成结果矩阵
    matrix<T> result(this->theRows,this->theColumns);
    for(int i = 0; i != this->theRows * this->theColumns;++i)
        result.element[i] = (this->element[i] + m.element[i]);

    return result;
}
//重载运算符-
template<typename T> matrix<T> matrix<T>::operator-(const matrix<T> &m)const{
    if(this->theRows != m.theRows || this->theColumns != m.theColumns)
        return 0;
    matrix<T> result(this->theRows * this->theColumns);
    for(int i = 0; i != this->theRows * this->theColumns;++i)
        result.element[i] = this->element[i] - m.element[i];
    return result;
}
//重载运算符*
template<typename T> matrix<T> matrix<T>::operator*(const matrix<T> &m)const{
    if(this->theColumns != m.theRows)//如果第一个矩阵的列数不等于第二个矩阵的行号，那么就不能计算
        return 0;
    matrix<T> result(this->theRows,m.theColumns);//新矩阵的大小是this->theRows * m.theColumns;
    for(int i = 0;i < this->theRows;++i){//控制行，这个是第一个矩阵的行
        for(int j = 0; j < m.theColumns;++j)//这个是第二个矩阵的列
        {
            result.element[i*result.theColumns+j] = 0;//确保刚开始的时候是0，类似初始化
            for(int k = 0; k != this->theColumns;++k){
                //注意,result.element中的下标是由result的columns和rows决定的!!!
                result.element[i*result.theColumns+j]+=(this->element[i*(this->theColumns)+k] * m.element[k*m.theColumns+j]);
            }
        }
    }
    return result;
}
#endif

