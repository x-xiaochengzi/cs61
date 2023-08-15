//! -g -O1 -Wno-unused -fno-stack-protector
#include <cstdio>
#include <cstdlib>
#include <cassert>

[[gnu::noinline]] int identity(int a) {
    return a;
}

[[gnu::noinline]] int f(int x) {
    return identity(x) + identity(x + 1);
}

int main() {
    printf("%d\n", f(61));
}
