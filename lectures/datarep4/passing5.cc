#include <cstdio>
#include "hexdump.hh"

void f(int arg[]) {
    // printf("sizeof(arg) = %zu\n", sizeof(arg));
    arg[0] = -1;
}

int main() {
    int l[9] = {2, 0, 0, 0, 0, 0, 0, 0, 0};
    // printf("sizeof(l) = %zu\n", sizeof(l));
    f(l);
    printf("l[0] is %d\n", l[0]);
}
