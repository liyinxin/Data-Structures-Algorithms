#include "arrayStack.h"


bool checkBox(int net[],int n){//net表示的是你的网元之间的关系,n表示的是你有多少个数
    arrayStack<int> *s = new arrayStack<int>(n);
    for(int i = 0;i != n;++i){
        if(!s->empty()){//如果非空的话
            if(net[i] == net[s->top()]){//栈顶可以出去了
                s->pop();
            }
            //如果没有相等的话，那么就在栈里边，直到遇到相同的时候出栈
            //如果出现交叉的话，那么就栈就不会是空的 !!!
        }
        else//如果是空的话，那么我们就直接给它入栈
            s->push(net[i]);
    }
    if(s->empty()){//如果是空的话，那么就说明是可以被连线的
        std::cout<<"Switch box is routable\n";
        return true;
    }
    std::cout<<"Switch box is not routable\n";
    return false;
}
int main()
{
    return 0;
}

