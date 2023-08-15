#include "hexdump.hh"
// Compile me with different compilers and optimization levels!

int main() {
    char c1 = 61;
    int i1 = 62;
    char c2 = 63;
    short s1 = 64;

    hexdump_named_object(c1);
    hexdump_named_object(c2);
    hexdump_named_object(s1);
    hexdump_named_object(i1);
}
