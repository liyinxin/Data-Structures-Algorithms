#pragma once

#include <string>
#include <stdexcept>

class illegalParameterValue : public std::invalid_argument{
public:
    explicit illegalParameterValue(std::string s) : invalid_argument(s){}
};

