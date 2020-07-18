#include "arrayQueue.h"

arrayQueue<int> *track;
int numberOfCars;
int numberOfTracks;
int smallestNumber;
int itsTrack;

bool putInHoldingTrack(int c){
    //将一个新元素入队列的时候，需要将其放在队列中最小的那个中去
    int bestBack  = -1;//假设现在这个数是最大的，
    int bestQueue = numberOfTracks;//这个表示有没有找到最合适的队列
    for(int i = 0; i < numberOfTracks;++i){
        if(!track[i].empty()){//一个一个找，找最大的一个队列，将其放进去
            int theLast = track[i].back();
            if(theLast > bestBack && c > theLast){
                bestBack = theLast;
                bestQueue = i;break;
            }
        }else{//如果前边没有空的，且没有找到c>d的条件的话
            //那么到了这边有一个空的队列，我就直接入队列了
            bestQueue = i;break;
        }
    }//找到最好的一个队列
    if(bestQueue == numberOfTracks){//如果遇到这种情况，那么就是说
        //这是刚开始，或者所有的队列都是空的，那么我就直接插入到第一个队列中
        std::cout<<"no stack to hold car\n";
        return false;
    }
    //插入进去了
    track[bestQueue].push(c);//将这个数据插入到最好的一个队列中
    std::cout<<"Move car "<<c<<" from input track to holding track "<<bestQueue<<std::endl;
    if(c < smallestNumber){//如果需要更改最小的话
        smallestNumber = c;
        itsTrack = bestQueue;
    }
    return true;
}

void outputFromHoldingTrack(){
    track[itsTrack].pop();
    std::cout<<"Move car "<<smallestNumber<<" from holding track "<<itsTrack<<std::endl;
    smallestNumber = numberOfCars+2;
    for(int i = 0; i < numberOfTracks;++i){
        if(!track[i].empty()){//如果这个队列不为空
            if(track[i].front() < smallestNumber){
                smallestNumber = track[i].front();
                itsTrack = i;
            }
        }
    }
}

bool railroad(int inputOrder[],int theNumberOfCars,int theNumberOfTracks){
    numberOfCars   = theNumberOfCars;
    numberOfTracks = theNumberOfTracks-1;
    track  = new arrayQueue<int>[theNumberOfTracks+1];


    smallestNumber = theNumberOfCars+1;//假设当前是最大的
    int nextCarToOutput = 1;
    for(int i = theNumberOfCars-1; i >= 0; --i){
        if(inputOrder[i] == nextCarToOutput){//如果当前输入序列中
            //元素是要输出的话，那么就直接输出
            std::cout<<"Move car "<<inputOrder[i]<<" from input track to output track\n";
            nextCarToOutput++;//下一个要输出的
            //这个时候需要查找下，队列里边有没有要输出的
            while(smallestNumber == nextCarToOutput){//如果当前队列中的
            //最小的元素是等于要输出的话，那我们就调用从队列里输出的函数去输出它
                outputFromHoldingTrack();
                nextCarToOutput++;
            }
        }else{//如果不相等的话，那么就入队列
            if(!putInHoldingTrack(inputOrder[i]))
                return false;
        }
    }
    return true;
}
int main()
{
    int input[9] = {5,8,1,7,4,2,9,6,3};
    std::cout<<"the output is "<<railroad(input,9,3);
    return 0;
}

