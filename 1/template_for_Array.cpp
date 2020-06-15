#include <iostream>
using namespace std;

template<typename T> bool make2Aarry(T ** &x,int numberOfRows,int numberOfColumns){
    try{
        x = new T * [numberOfRows];//首先这个是一个数组，然后数组里放的是
                                   //T类型的指针。
        for(int i=0;i!=numberOfRows;++i)
            x[i] = new int[numberOfColumns];
        return true;
    }catch(bad_alloc){
        return false;
    }
}
int main()
{
    
    return 0;
}

