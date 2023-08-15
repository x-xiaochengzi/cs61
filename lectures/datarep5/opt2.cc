#include "hexdump.hh"
#include <cstring>
#include <cstdio>

int main(int argc, char* argv[]) {
    long n = 1;
    if (argc >= 2) {
        n = strtol(argv[1], nullptr, 0);
    }

    char* buf = new char[n];
    printf("Allocated an array of %ld bytes\n", n);
    delete[] buf;
}
