//#include "linkedStack.h"
#include "arrayStack.h"

arrayStack<int> tower[4];
/*
 * bool parenthesisMatching(const std::string s,linkedStack<char> &parenthesis){
    for(auto it = s.begin();it != s.end();++it){
        if(*it=='(')//如果是左括号，那么就入栈
            parenthesis.push(*it);
        else if(*it == ')')//如果是右括号那么就出栈
        {
            if(parenthesis.empty())
                return false;
            parenthesis.pop();
        }
    }
    //注意，如果左括号多的话，那么需要判断下
    if(parenthesis.empty())
        return true;
    else
        return false;
}
*/
/*
 *这个放塔的其实可以这样想:
 *首先我们要把n-1个元素借助第二个桶放到第三个柱子上。
 *放完以后，其实就变成了，n-1个塔在第三个柱子上，然后
 *将其借助第一个柱子，然后放到第二个柱子上。所以一直递归就好了。
 */
void towersOfHanoi(int n,int x,int y,int z){
    if(n>0){
        towersOfHanoi(n-1,x,z,y);//n-1个塔借助第二个柱子放到第三个上去
        std::cout<<"Move top disk from tower "<<x<<" to top of tower "
                 <<y<<std::endl;
        towersOfHanoi(n-1,z,y,x);//排放完最后一个塔以后，可以理解为n-1个塔
        //都放在第三个柱子上了，然后这个时候其实就是通过第三个柱子，借助第一个柱子
        //将其放到第二个柱子上。所以是n-1,z,y,x
    }
}


void showStable(){
    for(int i = 1;i <=3;++i){
        for(int j = 0;j <= (tower[i].size()-1);++j){
            std::cout<<tower[i].get(j)<<" ";
        }
        std::cout<<"\n";
    }
    std::cout<<"**********************\n";
}

void moveAndShow(int n,int x,int y,int z){
    if(n>0){
        moveAndShow(n-1,x,z,y);
        int d = tower[x].top();
        tower[y].push(d);
        tower[x].pop();
        showStable();
        moveAndShow(n-1,z,y,x);
    }
}

void towersOfHanoi(int n){//重载
    for(int i = 1;i <= 3;++i)
        tower[i].clear();
    for(int d = n;d>0;--d)
        tower[1].push(d);//因为是栈，而且数组的右端是栈顶

    //所以大的在下面
    moveAndShow(n,1,2,3);
}
int main()
{ 
    /*
    std::string s;
    std::cout<<"please input the string\n";
    while(std::cin>>s){
        linkedStack<char> parenthesis;
        std::cout<<"the string "<<s<<" is "<<parenthesisMatching(s,parenthesis);
    }
    std::cout<<"\n";
    */
    int n;
    std::cout<<"please input the number of the disk\n";
    while(std::cin>>n){
        towersOfHanoi(n);
        std::cout<<"please input the number of the disk\n";
    }   
    return 0;
}

