#include <iostream>
/*
 *
 * 
    template<class T> class task;
    template<class T> task<T>* preempt(task<T>*);

    template<class T> class task {
    friend void next_time();
    friend void process(task<T>*);
    friend task<T>* preempt<T>(task<T>*);
    template<class C> friend int func(C);
    friend class task<int>;
    template<class P> friend class frd;
    };

 *其实理解，类模板的友元函数，首先得明白如何声明友元函数，以及类模板如何被实例化的。
 *首先说下类模板是如何被实例化的，类模板要想被实例化，就必须得借助模板参数列表提供的
 *参数类型，比方说我下面的base类模板，我就必须得到base<int> a;的时候才会产生相应的类
 *这个时候要注意，只有模板类被实例化的时候，这个类才是被真正的实现的，以前没实例化的
 *时候，只是一些声明而已；所以实例化以后我们才可以看到什么类型的友元被声明了。拿上面
 *的例子来说的话，在模板类task中定义了好几种不同的友元。
 *第一个友元next_time()是一个普通的函数，所以，当我们实例化不同的类型的task实例的时候，
 *都会在各自的实例中声明该函数为友元函数，所以在所有的task实例中我们的next_time()都被
 *声明成了一个友元函数。但是请注意这个申请为友元函数的过程，其实是在task的各自实例化
 *过程中声明的，而不是一次就声明的，也就是说我的每一个task实例对应声明一个next_time()
 *友元函数而已；接着看第二个友元，这个友元的形参是一个模板类task的指针。那它是怎么一
 *回事呢？当我们实例化一个task<int>时（就拿int来说)。那么我的process的形参就被实例化成
 *task<int> *的类型了。所以也就是说，我的process是一对一的友元函数类型。即，我的task<int>
 *声明的是process(task<int> *)这个函数为友元。所以你的process(task<T> *)就得定义很多实际
 *类型的函数。这个时候你只能使用重载函数的方式去定义各个类型process的函数。不能使用
 *模板去实现这个重载的过程，因为这个process函数是一个普通的函数；接着看第三个友元。
 *task<T>* preempt<T>(task<T> *);这个是一个模板函数作为一个友元。注意这个时候友元没有那个
 *template<typename T>因为在这个类作用域内已经有了T了。所以不用定义并且，如果你使用
 *template<T>的话也会报错，因为不能在同一个作用域内定义两个相同名的类型参数。好了，继续看
 *第三个友元。当我们实例化一个task类时，我们也顺便实例话了一个preempt相同类型的函数。也就
 *是说，第三个友元类表示的是我们实例化一个类型的task的时候，我们顺便实例化了一个相同类型的
 *模板函数，该实例化的模板函数被声明成该类型的task的友元类。那这个与第二个有什么区别呢？
 *因为第二个是一个普通的函数，所以你得重载相应类型的函数才可以去匹配相应类型的task类。但是
 *第三个因为是一个模板函数。所以你可以定义这个模板，当定义一个int类型的task实例的时候，你只需要
 *实例化你的preempt<int>为int类型的就可以了。这样就可以去访问你的int类型的task实例了。但是
 *请注意，因为你的int类型的task只声明了int类型的preempt为友元，所以你只能使用int类型的preempt
 *去访问int类型的task。如果使用不同类型的preempt，那么就不可以，会报找不到匹配的友元函数的。
 *接着看第四个友元。这个友元表示的是一个模板函数，不过这个模板函数的模板参数列表是与类的模板参数
 *列表不一样的。所以这个时候。当你实例化一个int类型的task的时候，它声明一个模板函数（这个模板的
 *参数列表是与类的参数列表不一样）func为友元。所以这个友元函数表示的范围更大了。也就是说，
 *当我们实例化一个int类型的task的时候，我们的模板func函数被声明成了一个友元。所以只要我实例化一个
 *func，就可以去访问一个int类型的task。不管我的func被实例化成什么类型，即使是double(与int不一样的类型)
 *类型实例化的func也可以去访问int类型实例化的task。所以第四个表示的是，我们只要实例化一个类型的task，
 *那么我的所有实例化的func都可以访问被实例化的task(但是只有被实例化task的对象才可以)。接着看第五个
 *友元。第五个class task<int>表示的是一个友元模板类，不过这个模板类已经被实例化了。所以，当我们实例化
 *一个double类型的task时，我们的task<int>类就被声明成一个友元类了。所以只要实例化一个类型的task，那么
 *我的task<int>模板类就被声明成相应的友元函数了。也就是说我的task<int>模板类可以是任意被实例化的task
 *的友元类；但是注意，只有task<int>是别的被实例化的task累的友元，其他类型的就不是了。接着看第六个友元。
 *template<class P> friend class frd；这个也是一个模板类。但是注意，这个模板类的模板参数列表和类task
 *的模板参数列表不一样。也就是当我们实例化一个int类型的task时，我们的frd模板类被声明成了一个友元类。这个
 *跟不同参数列表的模板函数是一样的。所以我的任意类型的frd实例是任意被实例化task的友元类了。这也就是多对多的
 *关系了。
 *
 */

template<typename> class task;
template<typename> class percent;
template<typename T> void preempt(const task<T> &);
template<typename T> class frd;


template<typename T>class task{
friend void next_time();//普通函数，形参与task无关
friend void process(const task<T> &);//普通函数，形参与task有关
friend void preempt<T>(const task<T> &);//模板函数，形参与task有关
template<typename C> friend void func(C);//模板函数，模板参数列表不一样
friend class percent<int>;
template<typename P> friend class frd;
public:
    task(T a):number(a){}
    void print(){
        std::cout<<"this is the base "<<number<<std::endl;
    }
private:
    T number;
};


//next_time ,这个函数可以访问任何被实例化的task，也就是所有被实例化的task都将next_time
void next_time(){
    task<int>a(10);
    task<double>b(20.4);
    task<char>c('h');
    std::cout<<"this is the function "<<__FUNCTION__<<" and this is the a.number "<<a.number<<std::endl;
    std::cout<<"this is the function "<<__FUNCTION__<<" and this is the b.number "<<b.number<<std::endl;
    std::cout<<"this is the function "<<__FUNCTION__<<" and this is the c.number "<<c.number<<std::endl;
}

//void process(const task<T> &);
//下面的这些必须我们去手动重载的
void process(const task<int> &a){
    std::cout<<"this is the funcion "<<__FUNCTION__<<" and this is the a.number "<<a.number<<std::endl;
}
void process(const task<double> &a){
    std::cout<<"this is the funcion "<<__FUNCTION__<<" and this is the a.number "<<a.number<<std::endl;
}
void process(const task<char> &a){
    std::cout<<"this is the funcion "<<__FUNCTION__<<" and this is the a.number "<<a.number<<std::endl;
}

//第三个友元的实现
//template<typename T> void preempt(const task<T> &)
template<typename T> void preempt(const task<T> &a){
    std::cout<<"this is the funcion "<<__FUNCTION__<<" and this is the a.number "<<a.number<<std::endl;
}

//第四个友元的实现
//template<typename C> friend void func();
//其实这个友元和第一个友元是异曲同工的做法，这里不在演示了
template<typename C> void func(C number){
    task<int>a(10);
    task<double>b(20.4);
    task<char>c('h');
    std::cout<<"this is the function "<<__FUNCTION__<<" and this is the a.number "<<a.number<<std::endl;
    std::cout<<"this is the function "<<__FUNCTION__<<" and this is the b.number "<<b.number<<std::endl;
    std::cout<<"this is the function "<<__FUNCTION__<<" and this is the c.number "<<c.number<<std::endl;
    std::cout<<"this is the numebr  "<<number<<std::endl;
}

//第五个友元的实现
//friend class percent<int>
template<typename T> class percent{
public:
    percent(T numbers):number(numbers){}
    void print(){
        task<int>a(10);
        task<double>b(20.4);
        task<char>c('h');
        std::cout<<"this is the function "<<__FUNCTION__<<" of the class of percent and this is the a.number "<<a.number<<std::endl;
        std::cout<<"this is the function "<<__FUNCTION__<<" of the class of percent and this is the b.number "<<b.number<<std::endl;
        std::cout<<"this is the function "<<__FUNCTION__<<" of the class of percent and this is the c.number "<<c.number<<std::endl;
    }
private:
    T number;
};

//第六个友元实现
//template<typename P> friend class frd;
template<typename P> class frd{
public:
    frd()=default;
    void print(){
        task<int>a(10);
        task<double>b(20.4);
        task<char>c('h');
        std::cout<<"this is the function "<<__FUNCTION__<<" of the class frd and this is the a.number "<<a.number<<std::endl;
        std::cout<<"this is the function "<<__FUNCTION__<<" of the class frd and this is the b.number "<<b.number<<std::endl;
        std::cout<<"this is the function "<<__FUNCTION__<<" of the class frd and this is the c.number "<<c.number<<std::endl;
    }
};
int main()
{ 
    task<int>a(10);
    task<double>b(20.4);
    task<char>c('h');
    //利用第一个友元函数
    next_time();
    std::cout<<std::endl;

    //利用第二个友元函数
    process(a);
    process(b);
    process(c);
    std::cout<<std::endl;

    //利用第三个友元函数来访问task<T>
    preempt<int>(a);
    //preemt<int>(b);这样的话是错误的，因为你的b也就是task<double>类型的实例被初始化的时候，只声明了
    //preempt<double>是其友元函数，所以你现在使用preempt<int>去访问task<double>是不行的，因为没有声明
    //preempt<int>是task<double>的友元函数
    preempt<double>(b);
    preempt<char>(c);
    std::cout<<std::endl;
    
    //利用第四个友元去访问task<T>
    func<int>(10);
    std::cout<<std::endl;
    func<double>(20.5);
    std::cout<<std::endl;

    //第五个友元的使用
    percent<int> e(10);
    e.print();
    std::cout<<std::endl;
    /*
     * percent<double>f(20.4);//这样做是错误的，因为percent<int>被声明成友元的，所以你只能是用percent<int>
     * f.print();//去访问task<T>中的私有成员，但是不能使用percent<double>去访问task<T>的私有成员
     */

    //第六种利用
    frd<int> g;
    frd<double> h;
    g.print();
    std::cout<<std::endl;
    h.print();
    return 0;
}

