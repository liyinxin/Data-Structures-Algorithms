#include "arrayQueue.h"
#include <vector>

std::vector<std::vector<int>> grid(9,std::vector<int>(9));
int size,pathLength;

class position{
public:
    int row,
        col;
};

position start,finish;
position *path;

bool findPath(){
    if(start.row == finish.row && start.col == finish.col){//如果起始点跟终点是一样的话，直接返回
        pathLength = 0;
        return true;
    }
    //如果起点跟终点不一样的话，那么就开始首先把所有的点的位置的障碍，然后变成距离
    //首先设置下查找顺序，这个顺序是按照从右，下，然后左再上
    position offSet[4];
    offSet[0].row = 0;offSet[0].col=1;  //往右边
    offSet[1].row = 1;offSet[1].col=0;  //往下边
    offSet[2].row = 0;offSet[2].col=-1; //往左边
    offSet[3].row = -1;offSet[3].col=0; //往上边
    //设置周边的障碍
    for(int i = 0;i <=size+1;++i){
        grid[0][i] = 1;grid[size+1][i] = 1;//加上第一行跟最后一行
        grid[i][0] = 1;grid[i][size+1] = 1;//加上第一列跟最后一列

    }    
    position here = start;//这个点表示的是当前的点
    grid[here.row][here.col] = 2;//用当前的点距离加2，可以防止跟1冲突
    int numOfNbrs = 4;

    arrayQueue<position> q;//设置队列
    position nbr;//nbr为当前位置的上下左右四个位置的点
    do{
        for(int i = 0;i < numOfNbrs;++i){
            nbr.row = here.row + offSet[i].row;
            nbr.col = here.col + offSet[i].col;
            if(grid[nbr.row][nbr.col] == 0){//如果这个点为可以通过的
                grid[nbr.row][nbr.col] = grid[here.row][here.col]+1;//表示这个点比当前点的距离加一
                if(nbr.row == finish.row && nbr.col == finish.col){//如果是这个点是终点了，那么我们就不需要再去标记距离了
                    break;//如果不break的话，那么这个程序会一直遍历完整个二维空间的，所以为了省时间，
                    //我们只要遍历到目的位置就好了
                }//如果不是最后的位置的话，那么我就把这个点入队列
                q.push(nbr);
            }
        }
        if(nbr.row == finish.row && nbr.col == finish.col)//到终点了
            break;
        //如果没有到终点
        if(q.empty())//如果队列里边没有存放数据的话，就说明四周都是堵住的，那么就是死路了
            return false;
        here = q.front();//让它边上的点出队列，然后继续去递归查找距离
        q.pop();
    }while(true);//标记完所有的距离了
    //接下来就是回溯了，去寻找路径了
    pathLength = grid[finish.row][finish.col] - 2;//先把距离找出来
    path = new position[pathLength];//创建一个队列去保存这些位置

    here = finish;
    for(int j = pathLength-1; j >= 0;--j){
        path[j] = here;
        for(int i = 0; i < numOfNbrs; ++i){
            nbr.row = here.row + offSet[i].row;
            nbr.col = here.col + offSet[i].col;
            if(grid[nbr.row][nbr.col] == j+2){//如果距离小的话，那么就break，然后pop出来
                break;//找到位置了
            }
        }
        here = nbr;
    }
    return true;
}
int main()
{
    size = 7;
    start.row  = 3;start.col =  2;
    finish.row = 4;finish.col = 6;
    int Grids[9][9] = {{0,0,0,0,0,0,0,0,0},
                       {0,0,0,1,0,0,0,0,0},
                       {0,0,0,1,1,0,0,0,0},
                       {0,0,0,0,0,1,0,0,0},
                       {0,0,0,0,1,1,0,0,0},
                       {0,1,0,0,0,1,0,0,0},
                       {0,1,1,1,0,0,0,0,0},
                       {0,1,1,1,0,0,0,0,0}
                      };
    for(int i = 0;i <9 ;++i)
        for(int j=0; j < 9;j++)
            grid[i][j] = Grids[i][j];
    std::cout<<"find the path ? "<<findPath()<<"\n";
    for(int i = 0;i <9 ;++i){
        for(int j=0; j < 9;j++)
            std::cout<<grid[i][j]<<" ";
        std::cout<<"\n";
    }

    for(int i = 0;i <pathLength;++i){
        std::cout<<"("<<path[i].row<<","<<path[i].col<<")"<<" ";
    }
    return 0;
}

