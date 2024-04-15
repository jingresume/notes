#ifndef __QUESTION_UTILS_LOG_H
#define __QUESTION_UTILS_LOG_H

#include<iostream>

template <typename T>
void printVector(std::vector<T> v, const std::string& str = "")
{
    std::cout << str << " : ";
    for (auto t : v) std::cout << t;
    std::cout << std::endl;
}

#endif