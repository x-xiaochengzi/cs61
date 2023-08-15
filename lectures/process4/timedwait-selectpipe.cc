#include "timedwait.hh"
bool quiet = false;
double exit_delay = 0.5;
double timeout = 0.75;
int signalpipe[2];

void signal_handler(int signal) {
    (void) signal;
    ssize_t r = write(signalpipe[1], "E", 1);
    assert(r == 1);
}

int main(int argc, char** argv) {
    parse_arguments(argc, argv);

    // Create the signal pipe
    int r = pipe(signalpipe);
    assert(r >= 0);

    // SIGCHLD writes `E` to the pipe
    r = set_signal_handler(SIGCHLD, signal_handler);
    assert(r >= 0);

    double start_time = timestamp();

    // Start child
    pid_t p1 = timedwait_make_child(exit_delay);

    // Wait for `timeout` sec, or until a byte is written to `signalpipe`,
    // whichever happens first
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(signalpipe[0], &fds);
    struct timeval timeout_timeval = make_timeval(timeout);
    r = select(signalpipe[0] + 1, &fds, nullptr, nullptr, &timeout_timeval);

    // Check if child exited
    int status;
    pid_t exited_pid = waitpid(p1, &status, WNOHANG);
    assert(exited_pid == 0 || exited_pid == p1);

    // Print results
    timedwait_print_results(exited_pid, status, timestamp() - start_time);
}
