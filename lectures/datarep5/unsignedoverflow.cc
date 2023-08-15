#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "hexdump.hh"

void test_overflow() {
    unsigned char n = 255;   // range representable in `n` is [0,255]
    n = n + 1;               // `n` should be 256, but can’t be represented

    unsigned u = 1'000'000;  // range representable in `u` is [0,4'294'967'295]
    u = u * 10'000'000;      // `n` should be 10'000'000'000'000,
                             // but can’t be represented

    printf("n=%u, u=%u\n", (unsigned) n, u);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        test_overflow();
    } else {
        unsigned long x = strtoul(argv[1], nullptr, 0);
        printf("%lu + 1 == %lu\n", x, x + 1);
    }
}
