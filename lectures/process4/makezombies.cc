#include "hexdump.hh"
#include <unistd.h>

int main() {
    setvbuf(stdout, nullptr, _IOLBF, 0);
    for (int i = 0; i != 30; ++i) {
        pid_t p = fork();
        assert(p >= 0);
        if (p == 0) {
            exit(0);
        }
        printf("makezombies[%d]: make child %d\n", getpid(), p);
        usleep(10'000);
    }
    sleep(1000);
}
