#pragma once
#ifndef __TRIDIAGONALMATRIX__H
#include <iostream>
#include "illegalNumber.h"

//首先它是一个方阵
//然后它是一个三对角矩阵

template<typename T>
class tridiagonalMatrix
{
public:
    tridiagonalMatrix(int theN = 10);
    ~tridiagonalMatrix() {delete []element;}
    T get(int,int)const;
    void set(int,int,const T &value);
private:
    int n;
    T *element;
};
//构造函数
template<typename T> tridiagonalMatrix<T>::tridiagonalMatrix(int theN){
    if(theN < 1)
        throw illegalNumber("the theN must be > 0\n");
    n = theN;
    element = new T[n];
}
//get函数这是利用对角线的方式去存储的
template<typename T> T tridiagonalMatrix<T>::get(int i,int j)const{
    if(i<1 || j<1 || i>n || j>n)
        throw illegalNumber("the i,j must be in the range of the tridiagonalMatrix");
    switch(i-j){
        case 1:
            return element[i-2];//低对角线
        case 0:
            return element[n-2+i];//中间线
        case -1:
            return element[n-2+n+i];//高对角线
        default:
            return 0;
    }
    //这个是按照对角线来存放的
    //    2 1 0 0
    //    3 1 3 0
    //    0 5 2 7
    //    0 0 9 0
    //也就是说数组存放的结果是3,5,9,2,1,2,0,1,3,7
    /*也就是说如果是n*n的话，那么低对角线有n-1个元素，中间对角线有n个元素，高对角线有n-1个元素
     *也就是说，第一个元素是(2,1)，那么其对应的是数组的下标是0,而第二个元素是(3,2)也就是说对应的下标是
     *1，也就是i-2(此时i=3) = 1，也就低对角线对应的是i-2下标；那么中间的就是i-2+n-1+1为什么这么算呢，因为
     *低对角线和其对应的同行的中间线之间差了n-1个元素。然后还要再加上中间线本身的1，所以就是i-2+n-1+1=n+i-2
     *同理高对角线比其同行的隔了n-1个元素n-1+1+i+n-2=2*n+i-2
     *
     */
}
//按照行存储
/*
template<typename T> T tridiagonalMatrix<T>::get(int i,int j)const{
    if(i<1 || j<1 || i>n || j>n)
        throw illegalNumber("the i,j must be in the range of the tridiagonalMatrix");
        switch(i-j){
            case 1://低对角线
                return element[(i-1)*3 - 1];
            case 0://中间的线
                return element[(i-1) * 3];
            case -1:
                return element[(i-1)*3 + 1];
            default:
                return 0;
        }
}
*/
//按照列存储的话
/*
template<typename T> T tridiagonalMatrix<T>::get(int i,int j)const{
    if(i<1 || j<1 || i>n || j>n)
        throw illegalNumber("the i,j must be in the range of the tridiagonalMatrix");
        switch(i-j){
            case 1://低对角线
                return element[(i-2)*3 +1];
            case 0://中间的线
                return element[(i-1) * 3];
            case -1:
                return element[(i-1)*3 + 2];
            default:
                return 0;
        }
}
*/

//set方法
template<typename T> void tridiagonalMatrix<T>::set(int i,int j,const T &value){
    if(i<1 || j<1 || i>n || j>n)
        throw illegalNumber("the i,j must be in the range");
    switch(i-j){
        case 1:
            element[i-2]     = value;break;
        case 0:
            element[n+i-2]   = value;break;
        case -1:
            element[2*n+i-2] = value;break;
        default:
            if(value != 0)
                throw illegalNumber("the value must be zero");
    }
}
#endif

