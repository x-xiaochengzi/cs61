#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <string>
#include <algorithm>
#include <thread>
#include <atomic>
#include <mutex>


struct minipipe {
    char pbuf;
    bool full = false;
    bool read_closed = false;
    bool write_closed = false;
    std::mutex lock;

    ssize_t write(const char* buf, size_t sz);
    void close_write();

    ssize_t read(char* buf, size_t sz);
    void close_read();
};


// minipipe::write(buf, sz)
//    Write up to `sz` bytes from `buf` into the minipipe.
//    Return value `ret` is:
//    * `0 < ret <= sz`: Successfully wrote `ret` bytes.
//    * `ret == -1 && errno == EPIPE`: Read end closed.
//    * `ret == -1 && errno == EAGAIN`: Minipipe full.
//    * `ret == 0`: `sz == 0`.

ssize_t minipipe::write(const char* buf, size_t sz) {
    std::scoped_lock guard(this->lock);
    assert(!this->write_closed);
    if (sz == 0) {
        return 0;
    } else if (this->read_closed) {
        errno = EPIPE;
        return -1;
    } else if (this->full) {
        errno = EAGAIN;
        return -1;
    } else {
        this->pbuf = buf[0];
        this->full = true;
        return 1;
    }
}

// minipipe::close_write
//    Close this minipipe for writing.

void minipipe::close_write() {
    std::scoped_lock guard(this->lock);
    assert(!this->write_closed);
    this->write_closed = true;
}



// minipipe::read(buf, sz)
//    Write up to `sz` bytes from the minipipe into `buf`.
//    Return value `ret` is:
//    * `0 < ret <= sz`: Successfully read `ret` bytes.
//    * `ret == 0`: `sz == 0` or no data left and write end closed.
//    * `ret == -1 && errno == EAGAIN`: Buffer empty.

ssize_t minipipe::read(char* buf, size_t sz) {
    std::scoped_lock guard(this->lock);
    assert(!this->read_closed);
    if (sz == 0) {
        return 0;
    } else if (!this->full) {
        if (this->write_closed) {
            return 0;
        } else {
            errno = EAGAIN;
            return -1;
        }
    } else {
        buf[0] = this->pbuf;
        this->full = false;
        return 1;
    }
}

// minipipe::close_read
//    Close this minipipe for reading.

void minipipe::close_read() {
    std::scoped_lock guard(this->lock);
    assert(!this->read_closed);
    this->read_closed = true;
}


// MAIN PROGRAM

std::atomic<unsigned long> nwrites = 0;
std::atomic<unsigned long> nreads = 0;


void writer_thread(minipipe& minib, const char* msg) {
    size_t pos = 0, len = strlen(msg);
    while (pos != len) {
        ssize_t nw = minib.write(msg + pos, len - pos);
        ++nwrites;

        if (nw > 0) {
            pos += nw;
        } else if (nw == -1 && errno != EAGAIN) {
            fprintf(stderr, "writer_thread: %s\n", strerror(errno));
            break;
        }
    }
    minib.close_write();
}


void reader_thread(minipipe& minib) {
    char buf[BUFSIZ];
    while (true) {
        ssize_t nr = minib.read(buf, BUFSIZ);
        ++nreads;

        if (nr > 0) {
            fwrite(buf, 1, nr, stdout);
            fflush(stdout);
        } else if (nr == 0) {
            break;
        } else if (nr == -1 && errno != EAGAIN) {
            fprintf(stderr, "reader_thread: %s\n", strerror(errno));
            break;
        }
    }
    minib.close_read();
}


int main(int argc, char* argv[]) {
    // collect message
    std::string msg;
    if (argc < 2) {
        msg = "Hello, world!\n";
    } else {
        for (int i = 1; i != argc; ++i) {
            msg += std::string(i == 1 ? "" : " ") + argv[i];
        }
        msg += "\n";
    }

    // start threads
    minipipe minib;
    std::thread reader(reader_thread, std::ref(minib));
    std::thread writer(writer_thread, std::ref(minib), msg.c_str());

    // join threads
    reader.join();
    writer.join();
    fprintf(stderr, "%zu reads, %zu writes\n", nreads.load(), nwrites.load());
}
