#include <cstdio>
#include "hexdump.hh"

int main() {
    int a[2] = {61, 62};
    hexdump_object(a);

    struct {
        int a;
        int b;
        char c;
        char d;
    } s = {61, 62, 63, 64};
    hexdump_object(s);
}
