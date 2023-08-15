#include <cstdio>
#include <cstdlib>
#include "hexdump.hh"

extern "C" {
int add(int a, int b);
}

int main(int argc, char* argv[]) {
    if (argc <= 2) {
        fprintf(stderr, "Usage: add A B\n\
    Prints A + B.\n");
        exit(1);
    }

    int a = strtol(argv[1], nullptr, 0);
    int b = strtol(argv[2], nullptr, 0);
    printf("%d + %d = %d\n", a, b, add(a, b));
}
