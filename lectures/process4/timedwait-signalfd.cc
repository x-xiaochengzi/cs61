#include "timedwait.hh"
#if __linux__
#include <sys/signalfd.h>
#endif
bool quiet = false;
double exit_delay = 0.5;
double timeout = 0.75;

int main(int argc, char** argv) {
    parse_arguments(argc, argv);

#if __linux__
    // Create a signalfd
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);
    int r = sigprocmask(SIG_BLOCK, &mask, nullptr);
    assert(r == 0);
    int sigfd = signalfd(-1, &mask, SFD_CLOEXEC);
    assert(sigfd >= 0);

    double start_time = timestamp();

    // Start child
    pid_t p1 = timedwait_make_child(exit_delay);

    // Wait for `timeout` sec, or until something is written to `sigfd`,
    // whichever happens first
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(sigfd, &fds);
    struct timeval timeout_timeval = make_timeval(timeout);
    r = select(sigfd + 1, &fds, nullptr, nullptr, &timeout_timeval);

    int status;
    pid_t exited_pid = waitpid(p1, &status, WNOHANG);
    assert(exited_pid == 0 || exited_pid == p1);

    // Print results
    timedwait_print_results(exited_pid, status, timestamp() - start_time);

#else
    fprintf(stderr, "%s: This program only works on Linux.\n",
            argv[0]);
    exit(1);
#endif
}
