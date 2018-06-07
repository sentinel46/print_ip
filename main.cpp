#include "print_ip.h"

int main()
{
    char c = -1;
    my::print_ip(c);  // 255

    short s = 0;
    my::print_ip(s);  // 0.0

    int i = 2130706433;
    my::print_ip(i);  // 127.0.0.1

    long l = 8875824491850138409;
    my::print_ip(l);  // 123.45.67.89.101.112.131.41

    std::string str = "192.168.0.1";
    my::print_ip(str);

//    std::vector<int> v = {10, 20, 0, 1};
//    my::print_ip(v);

    return 0;
}
