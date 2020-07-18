#pragma once
#ifndef __SPARSEMATRIX__H

#include <iostream>
#include <vector>
#include "illegalNumber.h"

template<typename T>
class matrixTerm{
public:
    int row,        //行号
        col;        //列号
    T value;        //对应的值
};

template<typename T>
class sparseMatrix{
template<typename C>friend  std::ostream &operator<<(std::ostream &out,sparseMatrix<C> &x);//这个可以输入随便类型的sparseMatrix
template<typename C>friend  std::istream &operator>>(std::istream &in,sparseMatrix<C>  &x);
public:
    sparseMatrix() {}
    void transpose(sparseMatrix<T> &b);
    void add(sparseMatrix<T> &b,sparseMatrix<T> &c);
    ~sparseMatrix() {}
private:
    int rows,//         矩阵的行数
        cols;//         矩阵的列数
    std::vector<matrixTerm<T>> terms;
};

//重载<<，其作为模板类sparseMatrix的友元函数
template<typename T> std::ostream &operator<<(std::ostream &out,sparseMatrix<T> &x){
    out<<"rows = "<<x.rows<<" columns = "<<x.cols<<std::endl;
    out<<"nozero terms = "<<(x.terms).size()<<std::endl;

    //输出矩阵项，一行一个
    for(auto it = x.terms.begin();it != x.terms.end();++it){
        out<<"a("<<it->row<<","<<it->col<<") = "<<it->value<<std::endl;
    }
    return out;
}

//重载>>，其作为模板类sparseMatrix的友元函数
template<typename T> std::istream &operator>>(std::istream &in,sparseMatrix<T> &x){//输入一个稀疏矩阵
    //输入矩阵的特征
    int numberOfTerms;
    std::cout<<"Enter number of rows,columns,and #terms"<<std::endl;

    in>>x.rows>>x.cols>>numberOfTerms;
    //判断输入的数据是不是有效的
    if(x.rows<1 || x.cols < 1 )
        throw illegalNumber("the rows and cols must be > 0");
    if(numberOfTerms < 1 || numberOfTerms > x.rows * x.cols)
        throw illegalNumber("the numberOfTerms must > 0 and <= rows * cols");
    //如果输入有效的话，
    matrixTerm<T> mTerm;
    for(int i = 0; i != numberOfTerms;++i){
        std::cout<<"Enter row,column,and value of term "<<(i+1)<<std::endl;
        in>>mTerm.row>>mTerm.col>>mTerm.value;
        //检查下输入的行号和列号有没有问题
        if(mTerm.row < 1 || mTerm.col < 1 || mTerm.row > x.rows || mTerm.col > x.cols)
            throw illegalNumber("the row and col must be >0");
        x.terms.push_back(mTerm);
    }
    return in;
}


template<typename T> void sparseMatrix<T>::transpose(sparseMatrix<T> &b){
    //先把矩阵b的行列数表示一下
    b.cols = rows;
    b.rows = cols;
    //不论以前有没有数据，都要被格式化下
    b.terms.clear();
    b.terms(this->terms.size());

    //
    
}
#endif
