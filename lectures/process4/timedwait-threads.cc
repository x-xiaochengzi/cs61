#include "timedwait.hh"
#include <thread>
#include <condition_variable>
#include <mutex>
bool quiet = false;
double exit_delay = 0.5;
double timeout = 0.75;
std::mutex m;
std::condition_variable_any alert;
pid_t waitresult = -2;
int waitstatus;


static void child_threadfunc(pid_t p1) {
    int status;
    pid_t p = waitpid(p1, &status, 0);
    assert(p == p1);

    std::unique_lock<std::mutex> guard(m);
    if (waitresult == -2) {
        waitresult = p;
        waitstatus = status;
    }
    alert.notify_all();
}

static void timeout_threadfunc() {
    dsleep(timeout);

    std::unique_lock<std::mutex> guard(m);
    if (waitresult == -2) {
        waitresult = 0;
    }
    alert.notify_all();
}

int main(int argc, char** argv) {
    parse_arguments(argc, argv);

    double start_time = timestamp();

    pid_t p1 = timedwait_make_child(exit_delay);

    // We must lock the mutex BEFORE creating threads! (Why?)
    std::unique_lock<std::mutex> guard(m);

    std::thread child_thread(child_threadfunc, p1);
    child_thread.detach();
    std::thread delay_thread(timeout_threadfunc);
    delay_thread.detach();

    alert.wait(guard);

    timedwait_print_results(waitresult, waitstatus, timestamp() - start_time);
}
