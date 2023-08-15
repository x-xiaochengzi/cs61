#include "hexdump.hh"

int main() {
    union {
        int a;
        int b;
        char c;
        char d;
    } u;
    u.a = 61;
    hexdump_object(u);
}
