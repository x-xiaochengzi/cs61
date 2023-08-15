#include <cstdio>
#include "hexdump.hh"

int main() {
    char c1 = 61;
    short s1 = 61;
    int i1 = 61;
    long l1 = 61;
    long long ll1 = 61;
    float f1 = 61;
    double d1 = 61;
    int* p1 = &i1;

    printf("c1: %d (%zu)\n", c1, sizeof(c1));
    printf("s1: %d (%zu)\n", s1, sizeof(s1));
    printf("i1: %d (%zu)\n", i1, sizeof(i1));
    printf("l1: %ld (%zu)\n", l1, sizeof(l1));
    printf("ll1: %lld (%zu)\n", ll1, sizeof(ll1));
    printf("f1: %g (%zu)\n", f1, sizeof(f1));
    printf("d1: %g (%zu)\n", d1, sizeof(d1));
    printf("p1: %p (%zu)\n", p1, sizeof(p1));

    hexdump_object(c1);
    hexdump_object(s1);
    hexdump_object(i1);
    hexdump_object(l1);
    hexdump_object(ll1);
    hexdump_object(f1);
    hexdump_object(d1);
    hexdump_object(p1);
}
