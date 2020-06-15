#include "recursive.h"
#include "tgmath.h"
#include "algorithm"
std::size_t recursive::factorial(std::size_t n)const{
    if(n <= 1)
        return 1;
    else
        return n*factorial(n-1);
}
template<class T> T recursive::sum(T a[],int n)const{
    if(n <= 0)
        return 0;
    else
        return a[n-1] +sum(a,n-1);
}
template<typename T> void recursive::permutations(T list[],int k,int m)const{
    if(k==m){
        std::copy(list,list+m+1,std::ostreambuf_iterator<T>(std::cout));
        std::cout<<std::endl;
    }
    else{
        for(int i = k;i <= m;++i){
            std::swap(list[k],list[i]);//这个是把一个元素，拿出来，然后，剩下的组成一个集合
            permutations(list,k+1,m);//剩下的数据组成的集合
            //std::swap(list[k],list[i]);//处理完第一个位置的元素以后，再换回来，恢复原样   
        }
    }
}
std::size_t recursive::fibonacci(std::size_t n)const{
    if(n==0)
        return 0;
    else if(n==1)
        return 1;
    else
        return fibonacci(n-1)+fibonacci(n-2);
}
std::size_t fibonacciNoRecursive(std::size_t n){
    int fl = 0,fr = 1,fn = 0;
    if(n == 0)
        return 0;
    else if(n==1)
        return 1;
    else{
        for(int i = 2; i <= n;i++){
            fn = fl + fr;
            fl = fr;
            fr = fn;
         }
    }
    return fn;
}
std::size_t recursive::algorithm21(std::size_t n)const{
    if(n % 2 == 0)
        return n/2;
    else
        return algorithm21(3*n + 1);
}
std::size_t recursive::AckermannFunction(std::size_t i,std::size_t j)const{
    if(i == 1 && j >= 1)
        return std::pow(2,j);
    else if(i >= 2 && j ==1)
        return AckermannFunction(i-1,2);
    else if(i >= 2 && j >= 2)
        return AckermannFunction(i-1,AckermannFunction(i,j-1));
}
std::size_t recursive::gcd(std::size_t x,std::size_t y)const{
    if(y == 0)
        return x;
    else
        return gcd(y,x % y);
}

template<typename T> void recursive::subsetGeneration(T list[],int array[],int index,int len)const{
    if(index == len){
        for(int i = 0;i<len;i++)
            std::cout<<array[i];
        std::cout<<" {";
        for(int i = 0;i<len;++i)
            if(array[i])
                std::cout<<list[i];
        std::cout<<"}"<<std::endl;
    }else{
        for(int i = 0;i != 2;++i){
            array[index] = i;
            subsetGeneration(list,array,index+1,len);
        }
    }
}
template<typename T,unsigned int N> void recursive::grayCodeGeneration(T (*list)[N],std::size_t size)const{
    if(size==1){//最后需要翻转输出
        list[0][size-1]=0;
        list[1][size-1]=1;
    }
    else{
        grayCodeGeneration(list,size-1);
        //下面做的是对称翻转
        for(int i= std::pow(2,size-1),j=std::pow(2,size)-1;i < std::pow(2,size);++i)
            for(int k = 0;k<N;k++)
                list[i][k] = list[j-i][k];//对应的逆序的行进行保存，这个时候用到的是
                                        //需要逆序保存的两个行之和是pow(2,size)-1;
        //这一步做的是前一部分加0，后一步分加1
        for(int i = 0;i < std::pow(2,size);i++){
            if(i <= (std::pow(2,size)/2-1))
                list[i][size-1]=0;
            else
                list[i][size-1]=1;
        }
    }
}
int main()
{
    int number[10]={1,2,3,4,5,6,7,8,9,10};
    int grayCode[16][4];
    char zimu[4]={'a','b','c','d'};
    recursive g;
    int shuzi[4];
    std::cout<<zimu<<std::endl;
    std::cout<<g.factorial(5)<<std::endl;
    std::cout<<g.sum(number,10)<<std::endl;
    g.permutations(zimu,0,2);
    std::cout<<"fibonacci 10 is "<<g.fibonacci(10)<<std::endl;
    std::cout<<"use no recursive fibonacci 10 is "<<fibonacciNoRecursive(10)<<std::endl;
    std::cout<<"数据结构C++回顾课后21题f(35) is "<<g.algorithm21(35)<<std::endl;
    std::cout<<"Ackermann's Function A(1,2) is "<<g.AckermannFunction(1,2)<<std::endl;
    std::cout<<"Ackermann's Function A(2,1) is "<<g.AckermannFunction(2,1)<<std::endl;
    std::cout<<"Ackermann's Function A(2,2) is "<<g.AckermannFunction(2,2)<<std::endl;
    std::cout<<"Eculid's Algorithm gcd(20,30) is "<<g.gcd(20,30)<<std::endl;
    g.subsetGeneration(zimu,shuzi,0,4);
    g.grayCodeGeneration(grayCode,4);
    for(int i =0;i<16;++i){
        for(int j=3;j>=0;--j){
            std::cout<<grayCode[i][j];
        }
        std::cout<<std::endl;
    }
    return 0;
}

