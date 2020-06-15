#include <iostream>
template<typename T> T Horner(T coeff[],std::size_t n,std::size_t length,const T &x){
    if(n==1)
        return coeff[length-1];//到最底层的话返回的是Cn
    else
        return Horner(coeff,n-1,length,x)*x+coeff[length-n];//递归返回的是Cn*x+Cn-1
    //注意:length - n表示的是当前是第几次了，比如说最开始的时候length-n=0表示的是加的一个C0也就是最后一次
    //然后第二次的是length-n=1了也就是加的是C1
}
//这个函数是用来表示函数的名词顺序的
template<typename T> void rank(T a[],int n,int r[]){
    for(int i = 0;i != n ;++i)
        r[i]=0;
    for(int i = 1; i != n;++i)
        for(int j = 0; j != i;++j){
            if(a[j] <= a[i])//这个算法表示的是首先拿第一个数去跟第二个数比较。比较
                            //完以后记录下大小关系。然后让右边的数移动，然后继续让左边的
                            //数去跟新的右边的数去比较。这种算法思想的。
                            //简而言之就是右边的数移动，然后让所有左边的数去跟右边的数比较
                r[i]++;
            else
                r[j]++;
        }
}
//这个比较的方法的比较次数是(n-1)n/2而转移次数是2n这个方法在n>3的时候是比我下面写的冒泡好的，但
//不一定比别的冒泡法好。
template<typename T> void sortAarryByRank(T a[],int n,int r[])//注意这个函数使用的时候，传入的
    //r[]是表示的各个元素在原先数组中的名次顺序的一个数组。也就是经过上面那个函数得到的数组r[]
{
    T *u = new T [n];//创建一个临时动态数组去保存数据
    for(int i = 0;i != n; ++i)
        u[r[i]]=a[i];//这样做不会更改a中的元素
    for(int i = 0;i != n;++i)
        a[i]=u[i];
    delete []u;
}
template<typename T> int indexOfMax(T a[],int n){
    int index = 0;
    for(int i = 1;i != n;++i){
        if(a[index] < a[i])
            index = i;
    }
    return index;
}
//注意，这个冒泡法的比较次数是n-1+(n-2)+...+1=(n-1)n/2;而转移的次数是3(n-1)，因为swap操作会产生一个
//临时变量然后总共三次
template<typename T> void selectionSort(T a[],int n){
    /*注意下面的这种方式有一个缺点就是，无论你的数组是否是有序的，这个
     * 程序都会去给你交换相应的数组的元素的，所以可以有改进的方法，就是一旦
     * 发现这个数组是有序的，那么我们就可以不需要进行交换了。
    for(int i = n;i > 1;--i){
        swap(a[indexOfMax(a,n)],a[n-1]);//把得到的最大的结果和最后本次比较的数据范围的最后一位进行
        //转换，也就是把最大的往后移动
    }
    */
    int size=0,indexOfMax=0;
    bool issorted=0;
    for(size = n;issorted && size>=1;size--){//如果这个序列是无序的才进入
        issorted = true;//默认是有序的，然后通过比较查看是否
        //是有序的，如果不是有序的，则交换，如果是有序的，则退出
        for(int i = 1; i < size ;++i){//比较一下这个数组是不是有序的，如果是有序的
            //则issorted=true，所以直接跳出了第一个for循环，如果是无序的，那么进行交换
            if(a[indexOfMax] <= a[i])indexOfMax = i;//挨个比较，把最大的依次往后排
            else
                issorted = false;
        }
        swap(a[indexOfMax],a[size-1]);
    }
}
template<typename T>void bubble(T a[],int n){//一次冒泡排序得到的结果
    for(int i = 0; i != n-1; ++i){
        if(a[i]<a[i+1])
            swap(a[i],a[i+1]);
    }
}
template<typename T>void bubbleSort(T a[],int n){
    for(int i = n;i > 0;--i){
        bubble(a,i);
    }
}
template<typename T>void rearrange(T a[],int n,int r[]){
    for(int i = 0;i < n;++i){
        if(r[i]!=i){//如果名次排名和我当前的下标不一样的话，那么说明该位置
            //存放的不是正确的位置。我们可以把该位置的数据放到它对应的位置处
            //比如说我现在第二个位置的数据的名次是4这个时候，我就利用swap函数
            //把这个位置的数据和第四个位置的数据进行交换，那么就可以把第四个位置
            //的数据放对位置了。但是注意，这个时候放对以后，你还需要把名次对应的
            //顺序进行交换一下，因为名次也是它们本身自带的属性（如果不换的话，那么
            //到到达第四个位置的时候,r[4]!=4了。所以必须得换，其实这个原地的算法
            //可以用很多人拿了不同的号码排队一样，每个人首先站一个顺序，但是这个顺序
            //有可能跟你手中的拿到的位置不一样，这个时候你就需要两两交换得到正确的位
            std::swap(a[r[i]],a[i]);//把这个不相等的位置的数据交换到正确的位置处
            //比如r[i]表示4，i当前为2;那么就是把当前第3个数据和第五个数据交换
            std::swap(r[r[i]],r[i]);
            //交换完数据以后，我们需要交换对应的下标，这个时候我们需要把第五个位置
            //名词跟当前位置的名次进行交换。r[r[i]],r[i]就是这个意思。
        }
    //这个算法可以理解为站队。首先每个人先按着某一个顺序排队，然后让这些人去抽一些
    //顺序拿在自己的手里。然后我们开始从第一个人开始。首先让第一个人查看自己的手里
    //拿的位置与自己站的位置对不对。如果不对，好。那么我去跟我手里拿的位置的人去交换位置
    //这样我自己是换成功了。然后我是在自己对应的位置了。同理，让第二个人继续这样操作
    //那么从头一直到结尾肯定就可以交换完了。并且都是正确的位置。对应程序的时候。
    //我们一方面要交换数值，另一方面还需要交换对应的名次。这样才会做到在相应的
    //位置有相应的数据。
    }
}
template<typename T> bool bubble_for_sort(T a[],int n){
   bool swapped = false;//有没有交换
   for(int i = 0;i != n;++i){
       if(a[i]>a[i+1]){//谁大把谁交换到右边去
           swap(a[i],a[i+1]);
           swapped = true;
        }
   }
   return swapped;//如果要是一次也没交换，那么这个顺序本来就是从小到大的。
}
template<typename T> void bubbleSortByEnd(T a[],int n){//这个函数主要是对冒泡法的一个改进，就是如果顺序是对的
    //那么就不用冒泡排序了，直接退出去。
    for(int i = n; i > 1 && bubble_for_sort(a,i);--i);
    
}
template<typename T> void insert(T a[],int n,const T &data){
    //插入有序数组的数据
    /*这是我自己写的插入到有序的数组的程序
    bool issmall = 1;
    for(int i = 0; i != n && issmall;++i){
        if(data <= a[i]){
            for(int j = n;j != i; --j)//把a[i]后面的数据全都往后移一位
                a[j]=a[j-1];
            a[i+1] = a[i];//把该位置插入到a[i]后面的位置
            issmall = 0;
        }
    }
    */
    int i = 0;
    //这是算法书上的写法，这个算法就很简洁
    for(int i = n-1; i >= 0 && data < a[i]; --i)
        a[i+1] = a[i];//从最大的位置开始比较，如果要插入的数据比当前的数据小，那么就把
                    //原先位置的数据往后移动一个位置，
    a[i+1] = data;//把当前空的位置添加上x的数据。

}
template<typename T>void inserSort(T a[],int n){
    T tmp[] = a;
    for(int i = 1; i != n;i++){//从第二个位置开始插入到数组temp中去
        insert(a,i,a[i]);//之所以在a上直接就插入的原因是因为，我们对序列的插入的大小进行了限定了
                        //每次插入的序列的大小都是i。所以不会影响i后面的元素的。
    }
}
template<typename T> void transpose(T **a,int rows){
    for(int i = 0;i != rows;++i)//这个是用来控制行的
        for(int j = i+1;j != rows;++j){
            std::swap(a[i][j],a[j][i]);//沿着主对角线将边上的元素进行交换
        }
}
int main()
{
    int a[6]={1,2,3,4,5};
    std::cout<<Horner(a,5,5,2)<<std::endl;
    insert(a,5,3);
    for(int i=0;i<6;i++)
        std::cout<<a[i]<<" ";
    return 0;
}

