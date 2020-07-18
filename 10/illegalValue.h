#pragma once
#ifndef __ILLEGALVALUE__H
#define __ILLEGALVALUE__H

#include <exception>
#include <string>
#include <iostream>

class illegalValue : public std::invalid_argument
{
public:
    explicit illegalValue(const std::string s):std::invalid_argument(s){}
};

#endif
