#include "timedwait.hh"
bool quiet = false;
double exit_delay = 0.5;
double timeout = 0.75;
static volatile sig_atomic_t got_signal;

void signal_handler(int signal) {
    (void) signal;
    got_signal = 1;
}

int main(int argc, char** argv) {
    parse_arguments(argc, argv);

    // Demand that SIGCHLD interrupt system calls
    int r = set_signal_handler(SIGCHLD, signal_handler);
    assert(r >= 0);

    double start_time = timestamp();

    // Start child
    pid_t p1 = timedwait_make_child(exit_delay);

    // Wait for the timeout or child exit, if child hasn’t exited yet.
    // `dsleep` will either succeed, returning 0 after `timeout` sec,
    // or be interrupted by SIGCHLD, returning -1. (Or will it?)
    if (!got_signal) {
        r = dsleep(timeout);
    }

    // Check if child exited
    int status;
    pid_t exited_pid = waitpid(p1, &status, WNOHANG);
    assert(exited_pid == 0 || exited_pid == p1);

    // Print results
    timedwait_print_results(exited_pid, status, timestamp() - start_time);
}
