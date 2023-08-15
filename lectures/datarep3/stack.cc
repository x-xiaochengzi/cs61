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

    hexdump_named_object(c1);
    hexdump_named_object(c2);
    hexdump_named_object(c3);
    hexdump_named_object(c4);
    hexdump_named_object(i1);
    hexdump_named_object(f1);
    hexdump_named_object(p1);
}
