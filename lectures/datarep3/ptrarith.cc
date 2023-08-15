#include <cstdint>
#include <cstdio>
#include "hexdump.hh"

int main() {
    int a[61];
    for (int i = 0; i != 61; ++i) {
        a[i] = 61 + i;
    }

    int* p1 = &a[0];
    int* p2 = &a[1];
    hexdump_named_object(p1);
    hexdump_named_object(p2);

    uintptr_t addr1 = (uintptr_t) p1;
    uintptr_t addr2 = (uintptr_t) p2;
    hexdump_named_object(addr1);
    hexdump_named_object(addr2);

    auto addrdiff1 = addr2 - addr1;
    hexdump_named_object(addrdiff1);
    printf("  = %zu\n", addrdiff1);
}
