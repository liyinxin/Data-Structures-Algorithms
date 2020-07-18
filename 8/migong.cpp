#include "arrayStack.h"
#include <vector>
class position{
public:
    int row,    //表示这个位置对应的行号
        col;    //表示这个位置对应的列号
};

bool findPath(std::vector<std::vector<int>> maze,int size){
    auto path = new arrayStack<position>;
    //offset是用来表示每次是先向哪个方向移动
    //C++数据结构的顺序是先右，后下，再左，再上，本程序也采用此顺序
    position offset[4];
    offset[0].row = 0; offset[0].col = 1;    //先右
    offset[1].row = 1; offset[1].col = 0;    //后下
    offset[2].row = 0; offset[2].col = -1;   //后左
    offset[3].row = -1;offset[3].col = 0;    //后上
    
    //初始化迷宫外围的障碍物
    
    for(int i = 0; i <=size;++i){
        maze[0][i] = maze[size+1][i] = 1;//最开始的一行和最后一行设置为1，障碍
        maze[i][0] = maze[i][size+1] = 1;//第一列和最后一列置为1
    }
    position here;
    here.row = 1;
    here.col = 1;//起始位置(1,1)
    maze[1][1] = 1;//堵住，防止重复过来
    int option = 0;     //下一步
    int lastOption = 3; //
    
    while(here.row != size || here.col != size){//如果还没有超出边界的话
        int r,c;
        while(option <= lastOption){//从当前的位置开始查找下一个空闲的位置
            r = here.row + offset[option].row;
            c = here.col + offset[option].col;
            if(maze[r][c] == 0){//如果下一个位置是空的话，我就直接退出去，找到该点了
                break;
            }else//如果按照顺时针方向找的位置被堵住了
                option++;//那就换下一个位置进行继续查找
        }
        if(option <= lastOption){//如果找到了一个空闲的位置，那么我就把当前点移动到这个位置来
            here.row = r;
            here.col = c;//把当前点移动到这个空闲位置
            path->push(here);//入栈保存这个位置，以便后面要返回到这个位置，然后从别的方向继续查找
            maze[r][c] = 1;//把这个位置也堵住;
            option = 0;//然后从这个位置也可以继续按照从右往下到左再到上的顺时针方向继续查找
        }else{//如果没有找到这个点的话，
            if(path->empty())//如果当前没有位置可以返回，那么就说明死路了，回不去了
                return false;
            position nextPostion = path->top();//这个是要返回到上一个的位置
            path->pop();//把上一个位置出栈
            //因为在进入到一个空位置的时候已经把该空位置堵上了，所以不需要自己再去堵了
            if(nextPostion.row == here.row)//如果两个点是同一行的话，那么下一个位置要么是1要么是3
                option = 2 + nextPostion.col - here.col;//如果here在nextPosition的右边的话，那么就是减去1，下一个位置的postion是1
                                                        //如果是左边的话，就是+1
            else//如果在同一列的话，那么下一个位置要么是2要是是0
                option = 3 + nextPostion.row - here.row;//如果here在nextPosition的下边的话，那么下一个位置就是2了，也就是here是
            //nextPostion的1这个offset得到的
            //注意，上面的那个3+nextPostion.row - here.row
            //如果当nextPosition是在here的下方的话，那么表示here是nextPosition最后一个offset(也就是3)的查找的过程，这个时候如果没
            //有找到的话，那么就不会找到出口了，这个时候，栈内肯定为空的了，因为上下左右都查找了一遍，没有找到
            here = nextPostion;
        }   
    }
    while(!path->empty()){
        std::cout<<"("<<path->top().row<<","<<path->top().col<<")"<<" ";
        path->pop();
    }
    std::cout<<"\n";
    return true;
}

int main()
{
    std::vector<std::vector<int>> migong(12,std::vector<int>(12,0)); 
    int number[12][12] = {  
                            {1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,0,1,1,1,1,1,0,0,0,0,1},
                            {1,0,0,0,0,0,1,0,1,0,0,1},
                            {1,0,0,0,1,0,1,0,0,0,0,1},
                            {1,0,1,0,1,0,1,0,1,1,0,1},
                            {1,0,1,0,1,0,1,0,1,0,0,1},
                            {1,0,1,1,1,0,1,0,1,0,1,1},
                            {1,0,1,0,0,0,1,0,1,0,1,1},
                            {1,0,1,0,1,1,1,0,1,0,0,1},
                            {1,1,0,0,0,0,0,0,1,0,0,1},
                            {1,0,0,0,0,1,1,1,1,0,0,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1}
                        };
    for(int i = 0;i <12;++i)
        for(int j = 0;j <12;++j)
            migong[i][j] = number[i][j];
    for(int i = 0;i <12;++i){
        for(int j = 0;j <12;++j)
            std::cout<<migong[i][j]<<",";
        std::cout<<"\n";
    }
    std::cout<<"it's ok ? "<<findPath(migong,10);
    return 0;
}

