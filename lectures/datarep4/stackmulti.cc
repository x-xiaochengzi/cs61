#include <cstdio>
#include <cstdlib>
#include "hexdump.hh"

int f1(int f1arg) {
    hexdump_named_object(f1arg);
    return f1arg;
}

int f2(int f2arg) {
    hexdump_named_object(f2arg);
    return f1(rand()) + f2arg;
}

int f3(int f3arg) {
    hexdump_named_object(f3arg);
    return f2(rand()) + f3arg;
}

int f4(int f4arg) {
    hexdump_named_object(f4arg);
    return f3(rand()) + f4arg;
}

int f5(int f5arg) {
    hexdump_named_object(f5arg);
    return f4(rand()) + f5arg;
}

int main() {
    f5(0);
}
