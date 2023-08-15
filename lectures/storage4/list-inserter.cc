#include "hexdump.hh"
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <list>

int main(int argc, char* argv[]) {
    constexpr size_t size = 50000;

    // check for insertion style argument
    int style = 'u';
    int opt;
    while ((opt = getopt(argc, argv, "rdu")) != -1) {
        if (opt == 'r' || opt == 'd' || opt == 'u') {
            style = opt;
        }
    }

    // initialize a large list of integers
    std::list<int> l;
    double t0 = cputime();

    // create a sorted list of integers in up, down, or random order
    unsigned long index_sum = 0;
    unsigned long rand_sum = 0;

    for (size_t i = 0; i != size; ++i) {
        int r = rand() % size;

        int value = 0;
        if (style == 'u') {
            value = i;
        } else if (style == 'd') {
            value = size - i - 1;
        } else if (style == 'r') {
            value = r;
        }

        int idx = 0;
        auto it = l.begin();
        while (it != l.end() && *it < value) {
            ++it;
            ++idx;
        }
        l.insert(it, value);
        index_sum += idx;
        rand_sum += r;
    }

    double t1 = cputime();

    printf("inserted %zu integers, order %c, in %.09f sec\n", size, style, t1 - t0);
    printf("index_sum: %lu, rand_sum: %lu\n", index_sum, rand_sum);
}
