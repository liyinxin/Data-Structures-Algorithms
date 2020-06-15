#include <iostream>

void print(int *a){
    for(int i = 0; i != 10;++i){
        std::cout<<a[i]<<std::endl;
    }
}
void printfshuzu(int a[10]){
    for(int i = 0; i != 10;++i)
        std::cout<<a[i]<<std::endl;     
}
void printfzhizhen(int (&a)[10]){
    for(int i = 0;i != 10;++i)
        std::cout<<a[i]<<std::endl;
}
int main()
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    int b[20] = {1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10};
    print(a);
    print(b);
    std::cout<<"printf the shuzu "<<std::endl;
    printfshuzu(a);
    printfshuzu(b);
    std::cout<<"printfzhizhen"<<std::endl;
    printfzhizhen(a);
    printfzhizhen(b);
    return 0;
}

