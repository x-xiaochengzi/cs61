#include "timedwait.hh"
bool quiet = false;
double exit_delay = 0.5;
double timeout = 0.75;

void signal_handler(int signal) {
    (void) signal;
}

int main(int argc, char** argv) {
    parse_arguments(argc, argv);

    // Demand that SIGCHLD interrupt system calls
    int r = set_signal_handler(SIGCHLD, signal_handler);
    assert(r >= 0);

    double start_time = timestamp();

    // Start child
    pid_t p1 = timedwait_make_child(exit_delay);

    // Wait for the timeout or child exit.
    // `dsleep` will either succeed, returning 0 after `timeout` sec,
    // or be interrupted by SIGCHLD, returning -1. (Maybe.)
    r = dsleep(timeout);
    (void) r;

    // Print results
    int status;
    pid_t exited_pid = waitpid(p1, &status, WNOHANG);
    timedwait_print_results(exited_pid, status, timestamp() - start_time);
}
