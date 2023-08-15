#include "hexdump.hh"
#include <cstring>
#include <cstdio>

long triangular_number(long i) {
    if (i > 1) {
        return i + triangular_number(i - 1);
    } else {
        return i;
    }
}

int main(int argc, char* argv[]) {
    long n = 1;
    if (argc >= 2) {
        n = strtol(argv[1], nullptr, 0);
    }

    printf("%ldth triangular number = %ld\n", n, triangular_number(n));
}
