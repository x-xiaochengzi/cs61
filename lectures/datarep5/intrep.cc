#include <cstdio>
#include <cstdint>
#include "hexdump.hh"

int main() {
    int i = 258;
    unsigned u = 1;

    hexdump_object(i);
    hexdump_object(u);
}
