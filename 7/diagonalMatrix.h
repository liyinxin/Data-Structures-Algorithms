#pragma once
#ifndef __DIAGNONALMATRIX__H
#define __DIAGNONALMATRIX__H

#include <iostream>
#include "illegalNumber.h"


template<typename T>
class diagonalMatrix
{
public:
    diagonalMatrix(int theN = 10);
    ~diagonalMatrix(){delete []element;}
    
    T get(int,int)const;
    void set(int,int,const T&);

private:
    int n;
    T *element;

};

template<typename T>  diagonalMatrix<T>::diagonalMatrix(int theN){//注意，默认参数，在类外就不需要再写上了
    if(theN < 1)
       throw illegalNumber("Matrix size must be > 0");
    n = theN;
    element = new T[n];
}
//返回(i,j)对应的值
template<typename T> T diagonalMatrix<T>::get(int i,int j)const{
    if(i < 1 || i > n || j < 1 || j > n)
        throw illegalNumber("the i,j must be right\n");
    if(i != j)
        return 0;
    else
        return element[i-1];
}
//set方法
template<typename T> void diagonalMatrix<T>::set(int i,int j,const T &value){
    if(i < 1 || i > n || j < 1 || j > n)
        throw illegalNumber("the i,j must be right\n");
    if(i == j)
        element[i-1] = value;
    else{//非对角元素的值必须是0，
        if(value != 0)
            throw illegalNumber("the value must be zero");
    }
}
#endif

