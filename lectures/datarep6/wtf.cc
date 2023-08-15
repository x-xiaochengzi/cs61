#include <cstdio>
#include <cstdint>
#include <sstream>
#include "hexdump.hh"

template <typename T>
std::string to_binary(T x) {
    std::ostringstream str;
    str << "0b";
    for (T u = T(1) << (sizeof(T) * 8 - 1); u; u >>= 1) {
        str << (x & u ? '1' : '0');
    }
    return str.str();
}

unsigned long wtf(unsigned long x) {
    unsigned long y = x & -x;
    unsigned long c = x + y;
    return (((x ^ c) >> 2) / y) | c;
}

int main() {
    unsigned long x = 7;

    for (int n = 0; n < 20; ++n) {
        printf("%s\n", to_binary(x).c_str());
        x = wtf(x);
    }
}
