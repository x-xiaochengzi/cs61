#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "hexdump.hh"

int main(int argc, char** argv) {
    int x;
    if (argc >= 2) {
        x = strtol(argv[1], nullptr, 0);
    } else {
        fprintf(stderr, "Usage: %s NUMBER\n", argv[0]);
        exit(1);
    }

    int x_incr = x + 1;
    assert(x_incr > x);
    printf("assertion passed, so %d > %d\n", x_incr, x);
}
