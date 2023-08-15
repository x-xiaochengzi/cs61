#include <cstdio>
#include "hexdump.hh"

int main() {
    int x = 0;
    hexdump_object(x);

    x = x + 1;
    hexdump_object(x);
}
