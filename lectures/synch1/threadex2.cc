#include <cstdio>
#include <thread>

void printn(int n) {
    printf("Hello from thread %d\n", n);
}

int main() {
    std::thread t1(printn, 1);
    std::thread t2(printn, 2);
    t1.join();
    t2.join();
}
