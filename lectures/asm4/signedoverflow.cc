#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include "hexdump.hh"

[[gnu::noinline]]
static int incr(int x) {
    return x + 1;
}

int main(int argc, char** argv) {
    int x;
    if (argc >= 2) {
        x = strtol(argv[1], nullptr, 0);
    } else {
        fprintf(stderr, "Usage: %s NUMBER\n", argv[0]);
        exit(1);
    }

    // print first 8 bytes of `incr` function
    hexdump((void*) incr, 8, "incr");

    int x_incr = incr(x);
    assert(x_incr > x);

    char buf[BUFSIZ];
    size_t n = sprintf(buf, "assertion passed, so %d > %d\n", x_incr, x);
    ssize_t nw = write(STDOUT_FILENO, buf, n);
    assert((size_t) nw == n);
}
