#include <iostream>

int nsum = 0;
int totalPaper(int totalNumber){
    nsum++;
    int maxNumber = 1;
    while(maxNumber < totalNumber){//如果目前的数小于总额的话
        maxNumber *= 5;
    }
    if(maxNumber == totalNumber)
        return 1;
    else{
        if((maxNumber - totalNumber) > (totalNumber - maxNumber/5))//就是这个总额跟谁比较接近
            return totalPaper(totalNumber-maxNumber/5)+1;
        else
            return totalPaper(maxNumber - totalNumber)+1; 
    }
}


int main()
{
    int totalNUmber,maxNumber=1;
    std::cout << "please input the total money\n";
    //std::cin>>totalNUmber;
    //重量一样，表示需要找到最小的张数
    while(std::cin>>totalNUmber){
        std::cout<<"totalPaper is "<<totalPaper(totalNUmber)<<"\n";
        std::cout<<"nsum is "<<nsum<<std::endl;
        nsum = 0;
    }
    return 0;
}

