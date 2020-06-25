#include "extendedChain.h"



int main()
{   extendedChain<char> L;
    for(int i = 0;i != 5;++i)
        L.insert(i,'a'+i);
    std::cout<<L<<std::endl;
    L.setSize(14);
    std::cout<<"L is "<<L<<" and the size is "<<L.size()<<std::endl;
    L.set(0,'f');
    std::cout<<L<<std::endl;
    //L.removeRange(0,3);
    std::cout<<L.indexOf('f')<<std::endl;
    L.insert(3,'f');
    std::cout<<L<<std::endl;
    std::cout<<L.lastIndexOf('f')<<std::endl;
    L[3] = 'j';
    std::cout<<L<<std::endl;
    extendedChain<char> L1(L);
    std::cout<<"L is\n"<<L;
    L1[5] = 'i';
    //std::cout<<"after the L1[5] the L is\n"<<L;
    std::cout<<"\nthe L1 is\n"<<L1<<std::endl;
    //注意这里，我现在还不清楚为什么在std::cout中，输出的时候进入的==函数中传入的参数左右颠倒了，也就是
    //left绑定的是第二个参数，而right绑定的是第一个参数
    std::cout<<"L is equal to L1 ? "<<(L==L1)<<"\nand the L1 is equal to L ? "<<(L1==L)<<std::endl;

    std::cout<<"L is not equal to L1 ? "<<(L != L1)<<std::endl;
    std::cout<<"this is the test\n";
    std::cout<<"L is < L1 ? "<<(L < L1)<<std::endl;

    //测试swap;
    std::cout<<"the current L is "<<L<<" and the L1 is "<<L1<<std::endl;
    L.swap(L1);
    std::cout<<"after the L.swap(L1) the L is "<<L<<" and the L1 is "<<L1<<std::endl;
    
    //测试L.reverse
    std::cout<<"the current L is "<<L<<std::endl;
    L.reverse();
    std::cout<<"after the L.reverse the L is "<<L<<std::endl;

    reverseNoMember(L);
    std::cout<<"after the reverseNoMember(L) the L is "<<L<<std::endl;

    //测试leftShift
    L.leftShift(2);
    std::cout<<"after the L.leftShit(2) the L is "<<L<<std::endl;
    
    //测试meld
    extendedChain<char> L2;
    meld(L1,L,L2);
    std::cout<<"L is "<<L<<" and L1 is "<<L1<<std::endl;
    std::cout<<"after meld(L1,L,L2) the L2 is "<<L2<<std::endl;
    //测试meld成员函数
    extendedChain<int> L3,L4,L5;
    L3.insert(0,1);L4.insert(0,2);
    L3.insert(1,3);L4.insert(1,4);
    std::cout<<"L3 is "<<L3<<" and L4 is "<<L4;
    L5.meld(L3,L4);
    std::cout<<"after L5.meld(L3,L4) L5 is "<<L5<<std::endl;


    //测试merge非成员函数
    L3.insert(0,10);L4.insert(0,20);
    L3.insert(1,30);L4.insert(1,40);
    merge(L3,L4,L5);
    std::cout<<"after merge L5 is "<<L5<<std::endl;
    L5.merge(L3,L4);
    std::cout<<"after L5.merge the L5 is "<<L5<<std::endl;

    //测试split
    std::cout<<"L3 is "<<L3<<" and the L4 is "<<L4<<" and the L5 is "<<L5<<std::endl;
    split(L4,L3,L5);
    std::cout<<"after the split(L4,L3,L5) the L3 is "<<L3
    <<" and the L4 is "<<L4<<" and the L5 is "<<L5<<std::endl;

    //测试circuShift()
    std::cout<<"the current L2 is "<<L2<<std::endl;
    L2.circularShift(4);
    std::cout<<"after the L2.circularShift(4) the L2 is "<<L2<<std::endl;

    //
    L2.insert(L2.size(),'a');
    std::cout<<"the current L2 is "<<L2<<std::endl;
    //测试插入排序
    //L2.insertSort();
    //测试冒泡排序
    //L2.bubbleSort();
    //测试选择排序
    //L2.selectionSort();
    //测试计数排序
    L2.countingSort();
    std::cout<<"after tne L2.countingSort() the L2 is "<<L2<<std::endl;

    
    
    return 0;
}

