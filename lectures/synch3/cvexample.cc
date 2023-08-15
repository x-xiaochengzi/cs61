#include "helpers.hh"
#include <mutex>
#include <condition_variable>
#include <thread>
#include <ctime>

double start_time;
std::mutex m;
std::condition_variable_any cv;
bool go = false;

void waiting_thread() {
    fprintf(stderr, "%.06f: waiting_thread enters\n", elapsed_time());
    m.lock();
    fprintf(stderr, "%.06f: waiting_thread acquires m\n", elapsed_time());
    while (!go) {
        fprintf(stderr, "%.06f: waiting_thread waits\n", elapsed_time());
        cv.wait(m);
        fprintf(stderr, "%.06f: waiting_thread wakes\n", elapsed_time());
    }
    m.unlock();
    fprintf(stderr, "%.06f: waiting_thread exits\n", elapsed_time());
}

void silent_waiting_thread() {
    m.lock();
    while (!go) {
        cv.wait(m);
    }
    m.unlock();
}

int main() {
    fhexdump(stderr, &m, sizeof(m), "m initial");
    fhexdump(stderr, &cv, sizeof(cv), "cv initial");

    m.lock();
    fprintf(stderr, "%.06f: main thread enters\n", elapsed_time());
    fprintf(stderr, "mutex at %p, cv at %p\n", &m, &cv);
    std::thread th(waiting_thread);
    fprintf(stderr, "%.06f: main thread starts waiting_thread\n", elapsed_time());
    fhexdump(stderr, &m, sizeof(m), "m locked in main");
    m.unlock();

    sleep(1);

    fprintf(stderr, "%.06f: main thread wakes\n", elapsed_time());
    fhexdump(stderr, &cv, sizeof(cv), "cv waiting");
    m.lock();
    go = true;
    cv.notify_all();
    m.unlock();

    th.join();
    fhexdump(stderr, &cv, sizeof(cv), "cv waited");

    m.lock();
    go = false;
    std::thread th2(silent_waiting_thread);
    m.unlock();

    sleep(1);

    fhexdump(stderr, &cv, sizeof(cv), "cv waiting 2nd time");
    m.lock();
    go = true;
    cv.notify_all();
    m.unlock();

    th2.join();
    fhexdump(stderr, &cv, sizeof(cv), "cv waited 2nd time");
}
