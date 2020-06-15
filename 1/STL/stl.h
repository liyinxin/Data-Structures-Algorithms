#pragma once
#ifndef __STL__H
#define __STL__H

class stl
{
public:
    stl() {}
    template<typename input_type,typename output_type>
        output_type accumulate(input_type start,input_type end,output_type initialValue)const;
    template<typename input_type,typename output_type,typename functionType>
        output_type accumulate(input_type start,input_type end,output_type initialValue,functionType compare)const;
    template<typename inputType,typename outputType> outputType copy(inputType start,inputType end,outputType outstart)const;
    template<typename T> void permutations(T start,T end)const;
    template<typename T> void anotherPermutations(T start,T end)const;
    ~stl() {}

private:

};
#endif
