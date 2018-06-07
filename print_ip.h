#pragma once

#include <type_traits>
#include <iostream>
#include <vector>

namespace my
{
namespace h
{
template<class T, bool = std::is_integral<T>::value>
struct helper { };

template<class T>
struct helper<T, true>
{
    static void print_ip(const T& t)
    {
        std::cout << "t = " << t << std::endl;
        auto x = 0;
        for (auto i = 0; i < sizeof(t); ++i) {
            if (i != 0)
                std::cout << ".";
            x = ((unsigned int)t >> (8 * i)) & 0XFF;
            std::cout << x;
        }
        std::cout << std::endl;

        union bytes
        {
            unsigned char b[sizeof(t)];
            T val;
        } bi;
        bi.val = t;
        for (auto i = 1; i <= sizeof(t); ++i) {
            if (i != 1)
                std::cout << ".";
            std::cout << (int)bi.b[sizeof(t) - i];
        }
        std::cout << std::endl;
    }
};

template<class T>
struct helper<T, false>
{
    static void print_ip(const T& t)
    {
        std::cout << t << std::endl;
    }
};

}   // namespace h

template<class T>
void print_ip(const T& t)
{
    h::helper<T>::print_ip(t);
}

}   // namespace my
