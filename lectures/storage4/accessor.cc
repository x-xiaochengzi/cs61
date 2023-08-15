#include "hexdump.hh"
#include <cstdlib>
#include <cstring>
#include <unistd.h>

int main(int argc, char* argv[]) {
    constexpr size_t size = 100'000'000;

    // check for access style argument
    int style = 'u';
    int opt;
    while ((opt = getopt(argc, argv, "rdu")) != -1) {
        if (opt == 'r' || opt == 'd' || opt == 'u') {
            style = opt;
        }
    }

    // initialize a very large array of integers
    int* v = new int[size];
    for (size_t i = 0; i != size; ++i) {
        v[i] = rand();
    }

    double t0 = cputime();

    // access 10M integers in up, down, or random order
    unsigned long sum = 0;
    unsigned long rand_sum = 0;

    for (size_t i = 0; i != size; ++i) {
        int r = rand() % size;

        int idx = 0;
        if (style == 'u') {
            idx = i;
        } else if (style == 'd') {
            idx = size - i - 1;
        } else if (style == 'r') {
            idx = r;
        }

        sum += v[idx];
        rand_sum += r;
    }

    double t1 = cputime();

    printf("accessed %zu integers, order %c, in %.09f sec\n", size, style, t1 - t0);
    printf("sum: %lu, rand_sum: %lu\n", sum, rand_sum);
}
