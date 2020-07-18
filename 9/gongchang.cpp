#include "arrayQueue.h"
#include <vector>

struct task;        //用来表示工序的
struct job;         //用来表示任务的
struct machine;     //用来表示机器的
class eventList;

int numMachines,     //用来表示机器一共有多少个的
    numJobs,        //用来表示任务一共有多少个
    timeNow,        //用来表示当前的时间是多少
    largeTime=1000; //在这个时间之前所有机器都已完成工序
machine *mArray;    //用来存放机器的数组
eventList *eList;   //事件表的指针

//工序的定义
struct task{
    int machine,    //表示该道工序对应的机器
        time;       //表示该道工序需要的时间
    task(int theMachine = 0,int theTime = 0):machine(theMachine),time(theTime){}
};

//任务的定义
struct job{
    arrayQueue<task> taskQ;
    int length;         //表示这个任务执行完以后，总的等待时间是多少
    int arrivalTime;    //表示任务到达的时间
    int id;             //表示这个任务是第几个任务，也就是任务的编号

    job(int theId = 0):id(theId),length(0),arrivalTime(0){}
    //增加一个工序的方法
    void addTask(int theMachine,int theTime){
        //这里不需要加一个判断theMachine跟theTime的条件，当调用这个的时候，前边已经会自动判断传入的参数
        //是不是合法的
        task theTask(theMachine,theTime);
        taskQ.push(theTask);
    }
    //移除一个工序的方法
    int removeNextTask(){
        int theTime = taskQ.front().time;
        taskQ.pop();//出队列
        length += theTime;
        return theTime;
    }
};

//机器的定义
struct machine{
    arrayQueue<job *> jobQ;//用来存放在这个机器的任务的
    int changeTime;     //用来存放这个机器转换的时间
    job *activeJob;     //用来表示机器当前正在处理的任务
    int totalWait;      //用来表示机器总的等待时间
    int numTasks;        //本机器处理的工序数量

    machine():totalWait(0),numTasks(0),activeJob(NULL)/*表示没有正在处理的任务*/{}
};

//类EvenList
//主要是用来机器完成的时间存储在一个事件表
class eventList{
public:
    eventList(int theNumMachines,int theLargeTime){
        //为m台机器，初始化其完成时间
        if(theNumMachines < 1)
            throw illegalParameterValue("number of machine must be >= 1");
        numMachines= theNumMachines;
        finishTime = new int [numMachines+1];

        //所有机器都空闲，用大的完成时间初始化
        for(int i = 1;i <= numMachines;++i)
            finishTime[i] = theLargeTime;
    }

    int nextEventMachine(){
        //返回值是处理下一项工作的机器
        //寻找完成时间最早的机器
        int p = 1;
        int t = finishTime[1];
        for(int i = 2; i <= numMachines;++i){
            if(finishTime[i] < t){//机器i完成时间更早
                p = i;
                t = finishTime[i];
            }
        }
        return p;
    }
    //返回下一个工序完成或者是状态转换完成的时间
    int nextEventTime(int theMachine){
        return finishTime[theMachine];
    }
    //设置下一个工序结束或者是状态转换完成的时间
    void setFinishTime(int theMachine,int theTime){
        finishTime[theMachine] = theTime;
    }
private:
    int *finishTime;
    int numMachines;
};


void inputData(){
    std::cout<<"Enter the number of the machines and jobs\n";
    std::cin>>numMachines>>numJobs;
    //判断输入的machine的数量和job的数量是不是有效的
    if(numMachines < 1 || numJobs < 1)
        throw illegalParameterValue("number of machine and jobs must be >= 1");
    //创建相应的机器
    eList  = new eventList(numMachines,largeTime);
    mArray = new machine[numMachines+1];//数组的第一个位置不使用
    //接下来我们初始化每个machine的changeTime
    int ct;
    for(int i = 1;i <= numMachines;++i){
        std::cout<<"Enter the change-over time for machine "<<i<<std::endl;
        std::cin>>ct;
        if(ct < 0)
            throw illegalParameterValue("the change-over time must be > 0");
        //如果合法的话，我们就将其赋予mArray[i]
        mArray[i].changeTime = ct;
    }
    //接下来就是添加任务
    
    job *theJob;
    int numTasks,       //一共有多少道工序
        firstMachine,   //第一道工序对应的机器
        theMachine,     //每一道工序对应的机器
        theTaskTime;    //每一道工序对应的时间
    for(int i = 1; i <= numJobs;++i){
        std::cout<<"Enter the numTask of the Job "<<i<<std::endl;
        std::cin>>numTasks;
        //判断输入的数据是否合法
        firstMachine = 0;
        if(numTasks < 1)
            throw illegalParameterValue("the numTasks must be > 1");
        //如果合法了
        theJob = new job(i);
        for(int j = 1;j <= numTasks;++j){
            std::cout<<"Enter the (machine,time) in process order \n";
            std::cin>>theMachine>>theTaskTime;
            if(theMachine < 1 || theMachine > numMachines || theTaskTime < 0)
                throw illegalParameterValue("bad machine number or task time");

            if(j == 1)
                firstMachine = theMachine;//用来保存第一道工序对应的机器的
            theJob->addTask(theMachine,theTaskTime);
        }
        mArray[firstMachine].jobQ.push(theJob);//将这个任务放到其第一道工序对应的机器中
    }
}

//改变每一个机器的状态的函数
/*  Function:   job *changeState(int theMachine);
 *  Describe:   此函数是用来改变一个机器的状态的
 *  详细步骤:
 *      (1):首先判断下，该机器中有没有激活的任务，也就是说activeJob是不是NULL(如果不是NULL的话，activeJob指向一个任务)
 *如果没有指向一个任务的话，那么先去看看该机器中有没有任务了。如果没有任务了，直接把当前的机器的time设置为largeTime，表示空闲了
 *如果有任务在排队的话，那么就把这个任务给激活，注意激活的时候，然后把当前队列的task给
 *抛出一个来，然后把numTasks++(也就是把处理的工序加一)；然后记录一下当前机器等待的总时间，这个总时间是用timeNow - 
 */
job *changeState(int theMachine){
    job *lastJob;
    if(mArray[theMachine].activeJob == NULL){//如果这个机器是空闲的或转换状态
        lastJob = NULL;
        //等待，准备处理新的工序
        if(mArray[theMachine].jobQ.empty())//如果这个机器中没有别的任务了
            eList->setFinishTime(theMachine,largeTime);
        else{//如果这个机器还有别的工序，那么继续处理
            mArray[theMachine].activeJob = mArray[theMachine].jobQ.front();//将当前的任务状态转换成队列中的第一个工序
            mArray[theMachine].jobQ.pop();//将这个工序出队列
            mArray[theMachine].totalWait += timeNow - mArray[theMachine].activeJob->arrivalTime;//加上处理完这个工序等待的时间
            mArray[theMachine].numTasks++;//记录一共处理了多少个工序了
            int t = mArray[theMachine].activeJob->removeNextTask();//把相应的工序移出来
            eList->setFinishTime(theMachine,timeNow+t);
        }
    }
    else{//在机器theMachine上刚刚完成一道工序
        //设置转换时间
        lastJob = mArray[theMachine].activeJob;
        mArray[theMachine].activeJob = NULL;
        eList->setFinishTime(theMachine,timeNow + mArray[theMachine].changeTime);
    }
    return lastJob;
}

//将每一个任务的第一道工序放到机器中开始运行
//startShop其实就是将machine对应的activeJob变成激活状态就好了
void startShop(){
    for(int p = 1; p <= numMachines;++p)
        changeState(p);
}

/*Function:
 *          moveToNextMachine
 *describe:
 *  是用来将一个任务从一个机器中移动到另一个机器上
 *具体步骤:
 *  (1)首先查看下当前的任务还有没有相应的工序，如果没有相应的工序了，那么就说明此任务已经完成了
 *      就打印下相应的数据，就好了
 *  (2)如果此任务还有工序的话，那么根据此任务的工序对应的机器去把这个任务添加到对应的机器中去。
 *      这个时候移动到相应的机器中的时候要注意：改变下此工序的arrivalTime，还要判断下，当前的
 *      那个机器是不是处于空闲的，如果处于空闲的话，我们就直接改变下这个机器的状态。
 */

bool moveToNextMachine(job *theJob){
    //调度任务theJob到执行其下一道工序的机器
    //如果任务已经完成，则返回false
    if(theJob->taskQ.empty()){
        std::cout<<"Job "<<theJob->id<<" has completed at "
        <<timeNow<<" Total wait was "<<(timeNow - theJob->length)<<std::endl;
        return false;
    }else{
        //任务theJob有一道工序
        //确定执行下一道工序的机器
        int p = theJob->taskQ.front().machine;
        //把任务插入机器p的等待任务队列
        mArray[p].jobQ.push(theJob);
        theJob->arrivalTime = timeNow;
        //如果机器p空闲，则改变它的状态
        if(eList->nextEventTime(p) == largeTime)
            //机器空闲
            changeState(p);
        return true;
    }
}

/*  Function: simulate
 *  Describe: 用来仿真工厂的机器操作
 *  操作步骤:
 *  (1):首先去找到下一个要结束的工序
 *  (2):设置下一个工序结束的时间
 *  (3):激活当前的任务
 *  (4):判断下有没有任务结束，如果有的话，那么就numOfJobs--
 */
void simulate(){
    //处理所有未处理的任务
    while(numJobs > 0){//至少有一个任务未处理
        //找到一个目前最快要处理完一道工序的机器
        int nextToFinish = eList->nextEventMachine();
        //记录下当前的时间
        timeNow = eList->nextEventTime(nextToFinish);
        //改变机器nextToFinish上的任务
        //返回的是上一次完成工序的任务，
        job * theJob = changeState(nextToFinish);
        //把任务theJob调度到下一台机器
        //把任务theJob完成，则减少任务
        //如果某一个任务结束了，那么就numJobs--;
        if(theJob != NULL && !moveToNextMachine(theJob))
            numJobs--;
    }
}

void outputStatistics(){
    std::cout<<"Finish time = "<<timeNow<<std::endl;
    for(int p = 1; p <= numMachines;p++){
        std::cout<<"Machine "<<p<<" completed "<<mArray[p].numTasks<<" tasks\n";
        std::cout<<"The total wait time was "<<mArray[p].totalWait<<std::endl;
        std::cout<<std::endl;
    }
}
int main()
{
    inputData();
    startShop();
    simulate();
    outputStatistics();
    return 0;
}

