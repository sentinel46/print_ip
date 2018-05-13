#include "print_ip.h"

int main()
{
    char c = -1;
    print_ip(c);  // 255

    short s = 0;
    print_ip(s);  // 0.0

    int i = 2130706433;
    print_ip(i);  // 127.0.0.1

    long l = 8875824491850138409;
    print_ip(l);  // 123.45.67.89.101.112.131.41

    return 0;
}
