#include "arrayStack.h"



int main()
{
    int n,      //n表示一共有多少个数
        r;      //r表示一共有多少个关系对
    std::cout<<"Enter number of elemnts\n";
    std::cin>>n;
    if(n < 2){
        std::cout<<"Too few elements\n";
        return 1;
    }
    std::cout<<"Enter the number of relation\n";
    std::cin>>r;
    if(r < 1){
        std::cout<<"Too few relations\n";
        return 1;
    }
    //建立空栈组成的数组，stack[0]不使用
    arrayStack<int> *list = new arrayStack<int>[n+1];


    int a,b;//用来存放关系对的两个元素
    //存放关系对
    for(int i = 1; i <= r;++i){
        std::cout<<"Enter next relation/pair\n";
        std::cin>>a>>b;
        list[a].push(b);
        list[b].push(a);
    }
    //初始化以输出等价类
    arrayStack<int> unprocessedList;
    bool *out = new bool[n+1];
    for(int i = 1;i <= n; ++i)
        out[i] = false;

    //输出等价类
    for(int i = 1; i <= n;++i){
        if(!out[i]){//如果这个数没有被输出的话，那就输出
            std::cout<<"Next class is: "<<i<<" ";
            out[i] = true;//表示这个数已经被输出了
            unprocessedList.push(i);//把输出的数放到栈里边
            while(!unprocessedList.empty()){//如果这个栈不是空的话，
            //那么就需要把所有栈里边与unprocessedList的数据pop出来
                int j = unprocessedList.top();
                unprocessedList.pop();
                while(!list[j].empty()){//输出这个数据的所有的等价类
                    int q = list[j].top();
                    list[j].pop();
                    if(!out[q]){//如果这个数还没输出的话
                        std::cout<<q<<" ";
                        out[q] = true;
                        unprocessedList.push(q);
                    }
                }
            }
        }
        std::cout<<std::endl;
    }
    std::cout<<"End of list of equivalence classes "<<std::endl;
    return 0;
}

