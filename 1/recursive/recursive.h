#ifndef __RECURSIVE_H
#define __RECURSIVE_H
#include <iostream>
class recursive
{
public:
    recursive() {}
    std::size_t factorial(std::size_t n)const;//n!算法
    template<class T> T sum(T a[], int n)const;//n的求和
    template<typename T> void permutations(T list[],int k,int m)const;//n元素的排列组合
    std::size_t fibonacci(std::size_t n)const;//非递归的斐波那契算法
    std::size_t algorithm21(std::size_t n)const;
    std::size_t AckermannFunction(std::size_t i,std::size_t j)const;
    std::size_t gcd(std::size_t x,std::size_t y)const;//求最大公约数的算法，是
    //欧几里得算法
    template<typename T>void subsetGeneration(T [],int [],int,int)const;
    template<typename T,unsigned int N>void grayCodeGeneration(T (*)[N],std::size_t)const;
};
std::size_t fibonacciNoRecursive(std::size_t n);
#endif
