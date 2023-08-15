#include <unistd.h>
#include <cstdio>
#include <cassert>

int main() {
    printf("Hello from initial process, pid %d\n", getpid());

    pid_t p1 = fork();
    assert(p1 >= 0);

    pid_t p2 = fork();
    assert(p2 >= 0);

    printf("Goodbye from pid %d (parent pid %d)\n", getpid(), getppid());

    usleep(250000);
}
