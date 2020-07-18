#include "arrayStack.h"
arrayStack<int> *track;
int numberOfCars;           //表示一共有多少个车厢
int numberOfStacks;         //表示一共有多少个缓冲轨道
int smallestNumber;         //表示缓冲轨道中最小的数
int itsTrack;               //表示最小的数所在的轨道索引

bool putInHoldingTrack(int c){
    int bestTop   = numberOfCars+1;  //用来保存当前大于c并且最接近c的一个数
    int bestStack = numberOfStacks;          //用来保存最好的stack的索引,这里因为我的栈的第一个索引是0，所以我们需要找一个
    //不重复在0---numberOfStacks-1之间的数，用来表示当前没有找到栈去存放这个c
    for(int i = 0; i != numberOfStacks;++i){
        if(!track[i].empty()){//如果非空的话
            int d = track[i].top();//如果当前的
            if(d > c && d < bestTop){
                bestTop = d;//如果满足这种情况的话，那么就要改变bestTop跟itsTrack的值了
                bestStack = i;
            }
        }
        else//如果是空的话，那么如果
            if(bestStack == numberOfStacks){//如果当前还没有找到比c小的栈顶元素的话，那么我们就暂时认为这个空的也可以存放这个元素c
                bestStack = i;
            }
    }
    if(bestStack == numberOfStacks)//也就是说没有找到存放这个c的栈的话，那么就是说栈都被占完了，然后不能放这个元素，所以此时不会将
        //元素重排了
        return false;//那么就返回false
    //如果找到了，那么就存放c到栈中去
    track[bestStack].push(c);
    std::cout<<"Move car "<<c<<" from input track to holding track "<<bestStack<<std::endl;
    //注意，这个时候要检查下，这个c是不是比当前的smallestNumber还要小
    if(c < smallestNumber){
        smallestNumber = c;
        itsTrack = bestStack;
    }
    return true;
}


void outputFromHoldingTrack(){//从栈中输出
    track[itsTrack].pop();//首先把上一次那个最小的pop掉
    std::cout<<"Move car "<<smallestNumber<<" from holding track "<<itsTrack<<" to output track\n";
    smallestNumber = numberOfCars+2;
    for(int i = 0;i != numberOfStacks;++i){
        if(!track[i].empty()/*用来使用top的前提*/ && (track[i].top() < smallestNumber)){
            smallestNumber = track[i].top();//保存最小的数据
            itsTrack = i;//保存最小的数据在栈的索引
        }
    }
}

bool railroad(int inputOrder[],int theNumberOfCars,int theNumberOfTracks){
    numberOfCars   = theNumberOfCars;
    numberOfStacks = theNumberOfTracks;
    track = new arrayStack<int>[numberOfStacks];

    int nextCarToOutput = 1;
    smallestNumber = numberOfCars + 1;  //表示当前所有的栈都是空的
    for(int i = theNumberOfCars-1;i >= 0;--i){
        if(inputOrder[i] == nextCarToOutput){//如果当前的数跟要输出的数是一样的
            std::cout<<"Move car "<<inputOrder[i]<<" from input track to output track\n";//输出数据
            nextCarToOutput++;//把要输出的数据加一;
            while(smallestNumber == nextCarToOutput){//然后去判断栈中最小的元素是不是要输出的数据
                //如果是的话，那么我们就输出
                outputFromHoldingTrack();
                nextCarToOutput++;
            }
        }else{//如果不是要输出的数的话，我们就需要去入栈了
            if(!putInHoldingTrack(inputOrder[i]))
                return false;
        }
    }
    return true;
}
int main()
{
    int input[9]={5,8,1,7,4,2,9,6,3};
    std::cout<<"the output is "<<railroad(input,9,3);
    return 0;
}

