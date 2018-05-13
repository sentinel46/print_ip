#pragma once

#include <type_traits>
#include <iostream>

namespace my
{
    template<class T, bool = std::is_integral<T>::value>
    struct helper { };

    template<class T>
    struct helper<T, true>
    {
        static void print_ip(const T& t)
        {
            auto x = 0;
            for (auto i = 0; i < sizeof(t); ++i)
            {
                if (i != 0)
                    std::cout << ".";
                //x = ((unsigned int)t >> (i << 3)) & 0xff;
                x = (unsigned char*)&t[i];
                std::cout << x;
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
}

template<class T>
void print_ip(const T& t)
{
    my::helper<T>::print_ip(t);
}
