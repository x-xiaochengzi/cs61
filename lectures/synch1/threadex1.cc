#include <cstdio>
#include <thread>

void print1() {
    printf("Hello from thread 1\n");
}

void print2() {
    printf("Hello from thread 2\n");
}

int main() {
    std::thread t1(print1);
    std::thread t2(print2);
    t1.join();
    t2.join();
}
