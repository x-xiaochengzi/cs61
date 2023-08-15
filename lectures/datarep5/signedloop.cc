#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "hexdump.hh"

[[gnu::noinline]] int f(int x) {
    return x;
}

[[gnu::noinline]] long loop(int n1, int n2) {
    long sum = 0;
    for (int i = n1; i <= n2; ++i) {
        sum += f(i);
    }
    return sum;
}

int main(int argc, char** argv) {
    int n1, n2;
    if (argc >= 3) {
        n1 = strtol(argv[1], nullptr, 0);
        n2 = strtol(argv[2], nullptr, 0);
    } else {
        fprintf(stderr, "Usage: %s LO HI\n", argv[0]);
        exit(1);
    }

    printf("Sum of [%d,%d] is %ld\n", n1, n2, loop(n1, n2));
}
