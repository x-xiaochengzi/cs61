#include <cstdio>
#include "hexdump.hh"
// Compile with CXX=clang++

int main() {
    char c1 = 61;
    int i1 = 61;
    char c2 = 61;
    float f1 = 61;
    char c3 = 61;
    int* p1 = &i1;
    char c4 = 61;

    printf("c1:\n");
    hexdump_object(c1);
    printf("c2:\n");
    hexdump_object(c2);
    printf("c3:\n");
    hexdump_object(c3);
    printf("c4:\n");
    hexdump_object(c4);
    printf("i1:\n");
    hexdump_object(i1);
    printf("f1:\n");
    hexdump_object(f1);
    printf("p1:\n");
    hexdump_object(p1);
}
