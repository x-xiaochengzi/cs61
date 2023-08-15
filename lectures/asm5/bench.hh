#ifndef CS61_BENCH_HH
#define CS61_BENCH_HH
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <ctime>

// cputime()
//    Return the amount of CPU time this process has taken so far.
inline double cputime() {
    struct timespec ts;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
    return ts.tv_sec + (double) ts.tv_nsec * 1e-9;
}

#endif
