#include <cstdio>
#include <cstring>

const char* f(int) {
    char* buf = new char[strlen("example")];
    strcpy(buf, "example");
    return buf;
}

int main() {
    const char* s = f(2);
    printf("%s\n", s);
    delete[] s;
}
