#ifndef TIMEDWAIT_HH
#define TIMEDWAIT_HH
#include <unistd.h>
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <csignal>
#include <ctime>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sched.h>
#include <errno.h>
#include "hexdump.hh"


// timedwait_make_child(t)
//    Create a child process that exits after `delay` seconds. If `loud`
//    is true, the process prints a message before exiting. Returns the
//    child process’s pid.

inline pid_t timedwait_make_child(double delay, bool loud = false) {
    pid_t p = fork();
    assert(p >= 0);

    if (p == 0) {
        if (delay > 0) {
            dsleep(delay);
        }
        if (loud) {
            fprintf(stderr, "%d: child exiting\n", getpid());
        }
        exit(0);
    }

    return p;
}


inline void timedwait_print_results(pid_t waitresult, int status, double lifetime) {
    extern bool quiet;
    extern double exit_delay;
    if (waitresult == -1) {
        fprintf(stderr, "%d: parent interrupted by %s after %g sec\n",
                getpid(), strerror(errno), lifetime);
    } else if (waitresult == 0) {
        fprintf(stderr, "%d: child timed out after %g sec\n",
                getpid(), lifetime);
    } else if (WIFEXITED(status)) {
        if (!quiet || lifetime > exit_delay + 0.1) {
            fprintf(stderr, "%d: child %d exited with status %d after %g sec\n",
                    getpid(), waitresult, WEXITSTATUS(status), lifetime);
        }
    } else {
        fprintf(stderr, "%d: child %d exited abnormally [%x]\n",
                getpid(), waitresult, status);
    }
}


// make_timeval(t)
//    Return `t` as a `struct timeval`.

inline struct timeval make_timeval(double d) {
    double intpart;
    double fracpart = modf(d, &intpart);
    struct timeval tv = {
        (long) intpart, (int) (fracpart * 1'000'000)
    };
    return tv;
}


// set_signal_handler(signo, handler)
//    Install `handler` as the signal handler for `signo`.
//    The `handler` is automatically re-installed after signal delivery.
//    Has the same interface as `signal()` (`man 2 signal`), but is portable.

inline int set_signal_handler(int signo, void (*handler)(int)) {
    struct sigaction sa;
    sa.sa_handler = handler;    // call `handler` on signal
    sigemptyset(&sa.sa_mask);   // don't block other signals in handler
    sa.sa_flags = 0;            // don't restart system calls
    return sigaction(signo, &sa, nullptr);
}


// parse_arguments(argc, argv)
//    Parse arguments for `-q`, `-e DELAY`, `-t DELAY`.

inline void parse_arguments(int argc, char* argv[]) {
    extern bool quiet;
    extern double exit_delay, timeout;
    int ch;
    while ((ch = getopt(argc, argv, "qe:t:")) != -1) {
        double* ptr = nullptr;
        if (ch == 'e') {
            ptr = &exit_delay;
        } else if (ch == 't') {
            ptr = &timeout;
        } else if (ch == 'q') {
            quiet = true;
        }
        if (ptr) {
            char* endptr;
            double val = strtod(optarg, &endptr);
            if (*endptr == '\0') {
                *ptr = val;
            }
        }
    }
}

#endif
