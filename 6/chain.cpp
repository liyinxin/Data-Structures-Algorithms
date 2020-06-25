#include "chain.h"
//编程原则，在你编写程序的时候一些常量参数，最好设置成全局的。然后
//不要一个一个写成数字放到函数中。因为这样修改程序的时候只需要修改
//这个常数变量就好了，很方便也不容易出错

template<typename T> void chain<T>::checkIndex(int theIndex)const{
    if(theIndex < 0 || theIndex > listSize){
        std::ostringstream s;
        s<<"index = "<<theIndex<<" size = "<<listSize;
        throw illegalParameterValue(s.str());
    }
}
//注意，你的默认参数在类内声明了以后，在类外定义的时候不需要再去写它的默认值了!!!
template<typename T> chain<T>::chain(int initialCapacity){
    if(initialCapacity < 1){
        std::ostringstream s;
        s<<"Initial capacity = "<<initialCapacity << " must be > 0";
        throw illegalParameterValue(s.str());
    }
    firstNode = NULL;//首节点指向为空
    listSize = 0;
}

template<typename T> chain<T>::chain(const chain<T> &theList){
    //拷贝构造函数/复制构造函数
    listSize = theList.listSize;
    //firstNode = theList.firstNode;//注意这样的做法是错误的，
    //所谓的拷贝是将这些元素都拿出来构造一个副本，不会影响原先的那个样本的。
    //如果如上面的那个操作一样的话，那么我的副本跟我的样本指向的线性表是
    //一样的了，那么我改变副本也会影响样本，所以那样是不对的。
    //所以，我们需要将这些元素重新放到一个副本中，然后再去指向
    if(listSize == 0){//如果链表是空的
        firstNode = NULL;
        return;//直接就返回
    }
    //拷贝的时候，需要注意，我们需要保留头节点，用来寻址的
    //然后再创建两个指针去指向各自对应的头指针。
    chainNode<T> *sourceNode = theList.firstNode;//sourceNode指向源节点的头节点
    firstNode = new chainNode<T>(sourceNode->element);//将第一个节点(也就是head节点)拷贝一下
    sourceNode = sourceNode->next;//转向真正的第一个节点
    auto targetNode = firstNode;//利用targetNode去遍历整个链表
    while(sourceNode != NULL){
        targetNode = new chainNode<T>(sourceNode->element);//
        sourceNode = sourceNode->next;
        targetNode = targetNode->next;
    }
    targetNode->next = NULL;//最后一个尾部元素为NULL
    //记住，操作链表的时候绝不能使用原来的那个firstNode节点本身去操作，
    //要不然的话，会找不到所有的链表了。所以使用另一个指针去指向同一个地点
    //然后通过新的指针去操作，这样原先head指针还是存在的。
}

template<typename T> chain<T>::~chain(){
    //delete chainNode<T>;又是错误的想法，你这样的话，只是删除了首节点，但是
    //剩下的所有节点没有被删除掉,所以我们需要一个一个的删除节点
    while( firstNode != NULL){
        auto nextNode = firstNode->next;//用nextNode去保存first的下一个节点
        delete firstNode;//删除firstNode指向的节点
        firstNode = nextNode;//让firstNode指向firstNode的下一个节点
    }
}

template<typename T> T& chain<T>::get(int theIndex)const{
    //首先要checkIndex;
    checkIndex(theIndex);
    auto currentNode = firstNode;
    //上面那句话等价于chainNode<T> *currentNode = firstNode;
    for(int i = 0;i != theIndex;++i)
        currentNode = currentNode->next;
    return currentNode->element;
}

//这个的index包含了firstNode中的element
template<typename T>  int chain<T>::indexOf(const T& theElement)const{
    int index = 0;
    auto currentNode = firstNode;
    while((currentNode != NULL) && (currentNode->element != theElement)){
        currentNode = currentNode->next;
        index++;
    }
    if(currentNode == NULL)
        return -1;
    else
        return index;
}

//删除的操作
template<typename T> void chain<T>::erase(int theIndex){
    checkIndex(theIndex);//首先要判断索引是不是对的
    chainNode<T> *deleteNode;
    if(theIndex == 0){//如果要删除的节点是头节点
        deleteNode = firstNode;//找到要删除的节点
        firstNode = firstNode->next;//让头结点指向正确的位置
    }
    else{
        auto currentNode = firstNode;
        for(int i = 0; i != theIndex - 1; ++i)
            currentNode = currentNode->next;//找到要删除的节点的前一个节点
        deleteNode = currentNode->next;//找到要删除的节点
        currentNode->next = currentNode->next->next;//然后让要被删除的
        //节点的前一个节点指向要被删除的节点的下一个节点
    }
    delete deleteNode;//删除节点，
    listSize--;//然后长度--
}

template<typename T> void chain<T>::insert(int theIndex,const T& theElement){
    checkIndex(theIndex);//检查下标的索引是否在有效范围内
    //如果没有问题，那么接下来就是插入了
    /*
     注意理解一下指针。
     */
    auto currentNode = firstNode;
    int index = 0;
    if(theIndex==0){//如果要插入的位置是第一个位置的话
        firstNode = new chainNode<T>(theElement,firstNode);
    }
    else{
        while(index++ != theIndex-1){
            currentNode = currentNode->next;
        }//找到要插入的位置的前一个
        currentNode->next = new chainNode<T>(theElement,currentNode->next);
    }
    listSize++;
}

template<typename T> void chain<T>::output(std::ostream &cout)const{
    auto currentNode = firstNode;
    while(currentNode != NULL){
        std::cout<<currentNode->element<<" ";
        currentNode = currentNode->next;
    }
}

template<typename T> std::ostream &operator<<(std::ostream &out,const chain<T> &x){
    x.output(out);
    return out;
}
int main()
{
    chain<std::string> node;
    node.insert(0,"a");
    node.insert(1,"b");
    node.insert(0,"c");
    std::cout<<node<<std::endl<<node.size()<<std::endl;
    node.erase(0);
    std::cout<<node<<std::endl;
    node.insert(0,"e");
    std::cout<<node<<"\nsize is "<<node.size();
    return 0;
}
