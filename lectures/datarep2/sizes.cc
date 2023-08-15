#include <cstdio>
#include "hexdump.hh"

int main() {
    char c1 = 61;
    int i1 = 61;
    float f1 = 61;
    int* p1 = &i1;

    printf("c1: %d\n", c1);
    printf("i1: %d\n", i1);
    printf("f1: %g\n", f1);
    printf("p1: %p\n", p1);

    hexdump_object(c1);
    hexdump_object(i1);
    hexdump_object(f1);
    hexdump_object(p1);
}
