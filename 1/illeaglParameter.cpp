#include <iostream>
class illegalParameterValue{
public:
    illegalParameterValue():message("Illegal parameter value"){}
    illegalParameterValue(const char *theMessage):message(theMessage){}
    void outputMessage(){
        std::cout<<message<<std::endl;
    }
private:
    std::string message;
};
int abc(int a,int b,int c){
    if(a <= 0 || b <= 0 || c <= 0)
        throw illegalParameterValue("All parameters should be > 0");
    return a + b * c;
}
int main()
{
    try{
        std::cout<<abc(2,0,4)<<std::endl;
    }catch(illegalParameterValue e){
        std::cout<<"The parameters to abc were 2,0,4"<<std::endl;
        std::cout<<"illegalParameterValue exception thrown"<<std::endl;
        e.outputMessage();
        return 1;
    }
    return 0;

}

