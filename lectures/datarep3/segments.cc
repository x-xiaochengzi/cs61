#include <cstdio>
#include "hexdump.hh"

int i1 = 61;
const int i2 = 62;

int main() {
    int i3 = 63;
    int* i4 = new int{64};

    hexdump_named_object(i1);
    hexdump_named_object(i2);
    hexdump_named_object(i3);
    hexdump_named_object(i4);
    hexdump_named_object(*i4);
}
