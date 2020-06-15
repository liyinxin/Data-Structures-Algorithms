#include <iostream>
#include <time.h>
template<typename T> void insert(T a[],int n,T x){
    int i = 0;
    for(i = n-1;i >= 0 && x < a[i];--i)//i>=0是为了可以插入i+1=0
        a[i+1] = a[i];//如果没有大于的话，那么就给该x元素腾出一个空的位置来
    a[i+1] = x;
}
template<typename T> void insertSort(T a[],int n){
    //利用插入排序，其实就是首先取出一个元素作为开始的一个数组
    //然后，以这个元素为有序数组，开始插入元素，这样就得到一个
    //完整的有序数组了
    for(int i = 1;i < n;++i){
        insert(a,i,a[i]);//这个开始从第位置开始插入到数组中
        //其中第一个参数表示的是你要插入到的数组，第二个参数是
        //数组目前有值的长度，第三个表示的是要插入的元素。
    }
}
int main()
{
    int a[1000],step = 10;
    //注意这个CLOCKS_PER_SEC表示的是一秒中多少个us，它其实是根据滴答定时器来算的
    //CLOCKS_PER_SEC 的大小是1000 000表示10的6次方个us
    double clockPerMillis = double(CLOCKS_PER_SEC)/1000;
    std::cout<<"The worst-case time,in milliseconds,are "<<std::endl;
    std::cout<<"n\tRepetitions\tTotal Ticks\tTime per Sort"<<std::endl;
    //std::cout<<"CLOCKS_PER_SEC is "<<CLOCKS_PER_SEC<<std::endl;
    //次数n = 0,10,20,....1000
    for(int n = 0;n <= 1000; n += step){
        //用最坏的测试数据初始化
        /*
        for(int i = 0;i != n;++i)
            a[i] = n-i;
        clock_t startTime = clock();//clock()函数返回从这个时刻开始滴答计时器累计了多少个数了
        //clock_t 的大小最起码是一个long的大小
        insertSort(a,n);
        float elapasedMillis = (float(clock()-startTime))/CLOCKS_PER_SEC;
        std::cout<<n<<"\t"<<elapasedMillis<<std::endl;
        if(n==100)
           step = 100;
        */
        long numberOfRepetitions = 0;
        clock_t startTime = clock();
        do{
            numberOfRepetitions++;
            for(int i = 0;i<n;++i)
                a[i] = n-i;
            insertSort(a,n);
        }while(clock()-startTime<1000000);//注意1秒内有1000 000个us
        double elapsedMills = (clock()-startTime)/clockPerMillis;//代表的是ms
        std::cout<<n<<"\t"<<numberOfRepetitions<<"\t"<<elapsedMills<<"\t"
            <<elapsedMills/numberOfRepetitions<<std::endl;
        if(n==100)
            step = 100;
    }
    return 0;
}
 
