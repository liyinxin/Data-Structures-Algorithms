#include <iostream>
#include <iterator>
class Base{
public:
    Base(){}
    virtual int fcn(){
        std::cout<<"this is the Base's virtual fcn()"<<std::endl;
    }
//    int a;
};
class Derived : public Base{
public:
    Derived(){}
    int fcn(int){
        std::cout<<"this is the Derived's fcn(int)"<<std::endl;
    }
    virtual void f2(){
        std::cout<<"this is the Derived's virtual f2()"<<std::endl;
    }
//private:
    //int c;

};
class D2 : public Derived{
public:
    int fcn(int){
        std::cout<<"this is the D2's fcn(int)"<<std::endl;
    }
    int fcn(){
        std::cout<<"this is the same of the Base's virtual"<<std::endl;
    }
    void f2(){
        std::cout<<"this is overried the Derived's virtual f2()"<<std::endl;
    }

};
template<typename T> void changeLength2D(T** &a,int oldRows,int newRows,int newColumns,int copyRows,int copyColumns){
    if(copyRows > newRows || copyRows > newColumns)
        std::cout<<"error with the size"<<std::endl;
    else{
        T **temp = new T* [newRows];//创建一个指针数组，然后每一个指针指向一个一维数组。这样就构成了一个二维数组
        for(int i = 0; i != newRows;++i)
            temp[i] = new T[newColumns];//这个表示每个指针指向的数组的大小是多少的
        for(int i = 0; i != copyRows;++i){
            std::copy(a[i],a[i]+copyColumns,temp[i]);
            std::copy(a[i],a[i]+copyColumns,std::ostream_iterator<T>(std::cout,","));
            std::cout<<std::endl;
            std::copy(temp[i],temp[i]+4,std::ostream_iterator<T>(std::cout,"-"));
            std::cout<<std::endl;
            delete []a[i];
        }//这一步已经拷贝完了
        //删除剩下的
        for(int i = copyRows;i != oldRows;++i)
            delete [] a[i];
        //delete []a;
        a = temp;
    }
}
void test_for_pointer(int **a){
    int *p = new int[10];
    for(int i = 0;i != 10;i++)
        p[i] = i * 10;
    *a = p;
}
//下面的例子简单的说明了生成的拷贝函数/赋值操作函数都支持相应的类对象的派生类
//向基类转换。
int main()
{
    //Derived a(10,20);
    //Base b(a);
    //std::cout<<b.a<<std::endl;
    /*
    Base bobj;Derived d1obj;D2 d2obj;

    Base *bp1 = &bobj,*bp2 = &d1obj,*bp3 = &d2obj;

    bp1->fcn();
    bp2->fcn();
    bp3->fcn();

    Derived *p1 = &d1obj;D2 *p2 = &d2obj;

    p1->fcn();//报错
    p1->fcn(42);
    p2->fcn(42);
    return 0;
    */
    int a[4][4] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    int **b = new int *[4];
    for(int i = 0;i != 4;++i){
        b[i] = new int [4];
        std::copy(a[i],a[i]+4,b[i]);
    }
    int (*pi)[4] = a;
    int *pi1 = a[0];    
    for(int i = 0;i != 4;++i){
        for(int j = 0; j != 4;++j)
            std::cout<<b[i][j]<<"-";
        std::cout<<std::endl;
    }
    std::cout<<"this is the new :"<<std::endl;
    /*
    for(int i = 0;i != 4; ++i)
        std::cout<<*(pi1+i)<<",";
    */
    int **temp = new int*[5];
    for(int i = 0; i != 4;++i){
        temp[i] = a[i];
    }
    changeLength2D(b,4,8,8,4,4);
    for(int i = 0;i != 8;++i){
        for(int j = 0; j != 8;++j)
            std::cout<<b[i][j]<<"-";
        std::cout<<std::endl;
    }
    int *p;
    test_for_pointer(&p);
    std::cout<<std::endl;
    for(int i = 0; i != 10;++i)
        std::cout<<p[i]<<"...";
}


