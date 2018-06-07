/*!
 * \file
 * \brief Основной файл программы
 */

/*! \mainpage print_ip
 * Учебный проект по курсу OTUS C++
 * Задание 4
 */

#include <vector>
#include <list>

#include "print_ip.h"

int main()
{
    char c = -1;  // 255
    my::print_ip(c);

    short s = 0;  // 0.0
    my::print_ip(s);

    int i = 2130706433;  // 127.0.0.1
    my::print_ip(i);

    long l = 8875824491850138409;  // 123.45.67.89.101.112.131.41
    my::print_ip(l);

    std::string str = "192.168.0.1";
    my::print_ip(str);

    std::vector<int> vector = {10, 20, 0, 1};
    my::print_ip(vector);

    std::list<int> list = {10, 20, 0, 4};
    my::print_ip(list);

    return 0;
}
