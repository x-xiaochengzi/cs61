#include <cstdio>

void f(int arg) {
    arg = -1;
    (void) arg; // quiet warning
}

int main() {
    int x = 2;
    f(x);
    printf("x is %d\n", x);
}
