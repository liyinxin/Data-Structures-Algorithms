#pragma once
#ifndef __ILLEGALNUMBER__H
#define __ILLEGALNUMBER__H

#include <string>
#include <exception>
#include <iostream>


class illegalNumber : public std::invalid_argument{
public:
    explicit illegalNumber(const std::string s ):std::invalid_argument(s) {}


};

#endif
