#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <sys/resource.h>
#include <unistd.h>
#include <string>
#include <algorithm>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#define RUNALIGN

struct RUNALIGN runner {
    bool torch_lit = false;
    std::mutex m;
    std::condition_variable_any cv;
};

constexpr int nrunners = 12;
runner runners[nrunners];
RUNALIGN std::atomic<unsigned long> nhandoffs;
RUNALIGN std::atomic<bool> done;


void runner_thread(runner* self, runner* partner) {
    while (!done) {
        // wait for torch to be lit
        self->m.lock();
        while (!self->torch_lit) {
            self->cv.wait(self->m);
        }
        self->m.unlock();

        // Once `self` has the torch, no other thread will attempt to read
        // `self->torch_lit` until the torch is handed off again!

        // wait for partner’s torch to *not* be lit
        partner->m.lock();
        while (partner->torch_lit) {
            partner->cv.wait(partner->m);
        }

        // handoff
        ++nhandoffs;
        partner->torch_lit = true;
        self->torch_lit = false;
        partner->cv.notify_all();
        partner->m.unlock();

        self->cv.notify_all();
    }
}


int main() {
    runners[0].torch_lit = true;

    std::thread th[nrunners];
    for (int i = 0; i != nrunners; ++i) {
        th[i] = std::thread(runner_thread, &runners[i], &runners[(i + 1) % nrunners]);
    }

    sleep(2);

    done = true;
    for (int i = 0; i != nrunners; ++i) {
        th[i].join();
    }

    struct rusage ru;
    int r = getrusage(RUSAGE_SELF, &ru);
    assert(r >= 0);
    fprintf(stderr, "%lu handoffs with %ld.%06dsec CPU time\n",
            nhandoffs.load(), ru.ru_utime.tv_sec, (int) ru.ru_utime.tv_usec);
}
