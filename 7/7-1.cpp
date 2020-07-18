#include <iostream>

/*
 描述:creatIregularArray(T **p,int *p);
    本函数是用来产生一个不规则的二维数组的，其中第一个参数表示的是这个数组的一个二维指针
    第二个参数是用来表示每一行的大小的
 */
template<typename T>void creatIregularArray(T **p,int *length,int numberOfRows){
    for(int i = 0;i != numberOfRows;++i){
        p[i] = new T[length[i]];
    }
}
int main()
{
    int numberOfRows = 5;
    int length[5] = {6,3,4,2,7};
    int **p = new int*[numberOfRows];//指针数组，用来存放指针的，所以得用个二维指针来指向
    creatIregularArray(p,length,numberOfRows);

    p[2][3] = 5;
    p[4][6] = p[2][3] + 2;
    p[1][1] = 3;

    std::cout<<p[2][3]<<std::endl;
    std::cout<<p[4][6]<<std::endl;
    std::cout<<p[1][1]<<std::endl;

    return 0;
}

