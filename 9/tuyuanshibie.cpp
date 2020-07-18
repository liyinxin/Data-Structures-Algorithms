#include "arrayQueue.h"
#include <vector>

#define  size 7
std::vector<std::vector<int>> grid(size+2,std::vector<int>(size+2));
class position{
public:
    int row,
        col;
};
position *path,here;

void labelComponents(){
    position offSet[4];
    int numOfNbrs = 4;
    //设置围墙
    for(int i =0; i <= size+1;++i){
        grid[0][i] = grid[size+1][i] = 0;//现在用0表示的是墙了
        grid[i][0] = grid[i][size+1] = 0;
    }
    //设置移动的方向
    offSet[0].row = 0;offSet[0].col = 1;    //右边
    offSet[1].row = 1;offSet[1].col = 0;    //下边
    offSet[2].row = 0;offSet[2].col = -1;   //左边
    offSet[3].row = -1;offSet[3].col = 0;   //上边
    //扫描所有像素，标记图元
    arrayQueue<position> q;//队列，要插入的
    position nbr;   //临时的一个位置
    int id = 1;     //id表示的是每一个等价类的不同的id
    /*
     *这个算法的思想其实也很简单，就是首先遍历每一行，如果找到这一行中有标记为1的像素点，那么就把这个点变为2或者3...(其实就是id，也就是不同
     等价类的id)。找到这么一个点以后，我们就去拿这个点去寻找它的附近，看看有没有标记为1的像素点。这样一直递归遍历完所有的点。记住，在查找一个
     点的附近的时候，需要把所有的点都加入到队列中，以便，下一次查找的时候，可以直接从队列中取出来，继续去查找。其实这个就是用队列/栈
     去将递归写成了这种形式的for循环而已！！！！
     1.首先去遍历每一行，然后如果找到相应像素值为1的点，然后去寻找它的附近所有相邻的点为1的点，然后将其grid变为相应的id
     2.在查找的时候，如果q为空了，那么就是说与最开始的点相邻的点已经没有了。如果还存在的话，那么就出队列，然后拿着这个点去寻找与它相邻的点
     */
    for(int r = 1; r <= size;++r){
        for(int c = 1;c <= size;++c){
            if(grid[r][c] == 1){//如果是像素点为1的话
                grid[r][c] = ++id;//让其变为相应的id
                here.row = r;here.col=c;//去寻找相应等价类
                do{
                    for(int i = 0;i < numOfNbrs;++i){
                        nbr.row = here.row + offSet[i].row;
                        nbr.col = here.col + offSet[i].col;
                        if(grid[nbr.row][nbr.col] == 1){//如果有也是相应的图元素的话
                            grid[nbr.row][nbr.col] = id;//跟它最开始的点是同一个id的
                            q.push(nbr);//把这个点push到队列中去，以便后边继续查找相应的点
                        }
                    }
                    if(q.empty())//如果当前的队列空了，那么就说明这个点的所有等价类都没有了
                        break;
                    //如果队列还有，我们继续查找
                    here = q.front();
                    q.pop();
                }while(true); 
            }
        }
    }
}
int main()
{
    int input[7][7] = {{0,0,1,0,0,0,0},
                       {0,0,1,1,0,0,0},
                       {0,0,0,0,1,0,0},
                       {0,0,0,1,1,0,0},
                       {0,1,0,0,1,0,1},
                       {1,1,1,0,0,0,1},
                       {1,1,1,0,0,1,1}
    };
    for(int i = 1; i <=size;i++)
        for(int j=1;j<=size;j++)
            grid[i][j] = input[i-1][j-1];
    labelComponents();
    for(int i =0;i<=size+1;i++){
        for(int j=0;j<=size+1;j++)
            std::cout<<grid[i][j]<<" ";
        std::cout<<"\n";
    }
    return 0;
}

