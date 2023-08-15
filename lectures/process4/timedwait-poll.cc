#include "timedwait.hh"
bool quiet = false;
double exit_delay = 0.5;
double timeout = 0.75;

int main(int argc, char** argv) {
    parse_arguments(argc, argv);

    double start_time = timestamp();

    // Start child
    pid_t p1 = timedwait_make_child(exit_delay);

    // Wait for timeout or child exit, whichever happens first, by polling
    int status;
    pid_t exited_pid = 0;
    while (timestamp() - start_time < timeout && exited_pid == 0) {
        exited_pid = waitpid(p1, &status, WNOHANG);
        assert(exited_pid == 0 || exited_pid == p1);
    }

    // Print results
    timedwait_print_results(exited_pid, status, timestamp() - start_time);
}
