#include <iostream>
#include "IPPrint.h"
#include <tuple>

using namespace std;

int main()
{
    print_ip<char>(-1);
    print_ip<short>(0);
    print_ip<int>(2130706433);
    print_ip<long long>(8875824491850138409);
    print_ip("1.2.3.4"s);
    print_ip(vector<int>{192,168,1,1});
    print_ip(list<int>{89,34,56,21});
    print_ip(make_tuple(1,2,3,4));

    return 0;
}
