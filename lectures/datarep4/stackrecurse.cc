#include <cstdio>
#include "hexdump.hh"

int f(int x) {
    int r = 0;
    if (x % 100 == 0) {
        r += printf("starting f(%d)\n", x);
        hexdump_named_object(x);
    }

    if (x > 0) {
        r += f(x - 1);
    }

    if (x % 100 == 0) {
        r += printf("ending f(%d)\n", x);
    }
    return r;
}

int main() {
    f(100);
}
