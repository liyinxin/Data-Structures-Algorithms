#include "matrix.h"

int main()
{
    matrix<int> a(2,2),b(2,4),c(2,2);
    for(int i = 1;i<=2;i++)
        for(int j=1;j<=2;++j){
            a(i,j)=j;
        }
    for(int i = 1;i<=2;i++)
        for(int j=1;j<=4;++j){
            b(i,j)=j;
        }
    for(int i = 1;i <= 2;++i){
        for(int j = 1;j <= 2;++j){
            std::cout<<a(i,j)<<" ";
        }
        std::cout<<"\n";
     }    
    std::cout<<std::endl;
    for(int i = 1;i <= 2;++i){
        for(int j = 1;j <= 4;++j){
            std::cout<<b(i,j)<<" ";
        }
        std::cout<<"\n";
    }    
    c = (a*b);
    std::cout<<"\n";
    for(int i = 1;i <= 2;++i){
        for(int j = 1;j <= 4;++j){
            std::cout<<c(i,j)<<" ";
        }
        std::cout<<"\n";
    }
    return 0;
}

