#include "db.hh"

dbmap db;
bool verbose = true;
std::mutex dbmutex[dbmap::bucket_count];

size_t nthreads;
std::mutex thread_mutex;
std::condition_variable_any thread_cv;


void handle_connection(int cfd, std::string remote) {
    FILE* fin = fdopen(cfd, "r");
    FILE* f = fdopen(cfd, "w");

    char buf[BUFSIZ], key[BUFSIZ], key2[BUFSIZ];
    size_t sz;

    while (fgets(buf, BUFSIZ, fin)) {
        if (sscanf(buf, "get %s ", key) == 1) {
            // find item
            auto b = db.bucket(key);
            std::unique_lock<std::mutex> guard(dbmutex[b]);
            auto it = db.bfind(b, key);

            // copy value
            std::string value;
            size_t itemid = 0;
            if (it != db.bend(b)) {
                value = it->value;
                itemid = it->itemid;
            }
            guard.unlock();

            // print value
            if (itemid) {
                fprintf(f, "VALUE %s %zu #%zu\r\n",
                        key, value.length(), itemid);
                fwrite(value.data(), 1, value.length(), f);
                fprintf(f, "\r\n");
            }
            fprintf(f, "END\r\n");
            fflush(f);

        } else if (sscanf(buf, "set %s %zu ", key, &sz) == 2) {
            // read value
            std::string value = std::string(sz, '\0');
            size_t nr = fread(value.data(), 1, sz, fin);
            assert(nr <= sz);

            // find item; insert if missing
            auto b = db.bucket(key);
            std::unique_lock<std::mutex> guard(dbmutex[b]);
            auto it = db.bfind(b, key);
            if (it == db.bend(b)) {
                it = db.binsert(b, key);
            }

            // set value
            it->value.swap(value);
            size_t itemid = it->itemid;
            guard.unlock();

            // print notice
            fprintf(f, "STORED #%zu\r\n", itemid);
            fflush(f);

        } else if (sscanf(buf, "delete %s ", key) == 1) {
            // find item
            auto b = db.bucket(key);
            std::unique_lock<std::mutex> guard(dbmutex[b]);
            auto it = db.bfind(b, key);

            // remove if found
            size_t itemid = 0;
            if (it != db.bend(b)) {
                itemid = it->itemid;
                db.berase(b, it);
            }
            guard.unlock();

            // print message
            if (itemid) {
                fprintf(f, "DELETED #%zu\r\n", itemid);
            } else {
                fprintf(f, "NOT_FOUND\r\n");
            }
            fflush(f);

        } else if (sscanf(buf, "exch %s %s ", key, key2) == 2) {
            // find items
            auto b1 = db.bucket(key);
            auto b2 = db.bucket(key2);
            if (b1 > b2) {
                dbmutex[b2].lock();
                dbmutex[b1].lock();
            } else if (b1 == b2) {
                dbmutex[b1].lock();
            } else {
                dbmutex[b1].lock();
                dbmutex[b2].lock();
            }
            auto it1 = db.bfind(b1, key);
            auto it2 = db.bfind(b2, key2);
            size_t itemid1 = 0, itemid2 = 0;

            // exchange items
            if (it1 != db.bend(b1) && it2 != db.bend(b2)) {
                itemid1 = it1->itemid;
                itemid2 = it2->itemid;
                std::swap(it1->value, it2->value);
            }

            dbmutex[b1].unlock();
            if (b1 != b2) {
                dbmutex[b2].unlock();
            }

            if (itemid1 != 0) {
                fprintf(f, "EXCHANGED #%zu #%zu\r\n", itemid1, itemid2);
            } else {
                fprintf(f, "NOT_FOUND\r\n");
            }
            fflush(f);

        } else if (buf[0] == 'q') {
            break;

        } else if (remove_trailing_whitespace(buf)) {
            fprintf(f, "ERROR\r\n");
            fflush(f);
        }

        if (verbose && remove_trailing_whitespace(buf)) {
            fprintf(stderr, "%s: %s\n", remote.c_str(), buf);
        }
    }

    if (ferror(fin)) {
        perror("read");
    }
    fclose(fin); // also closes `f`'s underlying fd
    (void) fclose(f);

    // mark thread as closed
    std::unique_lock<std::mutex> guard(thread_mutex);
    --nthreads;
    thread_cv.notify_all();
}


int main(int argc, char** argv) {
    // Usage: ./weensydb [PORT]
    int port = 6162;
    if (argc >= 2) {
        port = strtol(argv[1], nullptr, 0);
        assert(port > 0 && port <= 65535);
    }

    // Prepare listening socket
    int fd = open_listen_socket(port);
    assert(fd >= 0);
    fprintf(stderr, "Listening on port %d...\n", port);

    while (true) {
        struct sockaddr addr;
        socklen_t addrlen = sizeof(addr);

        // Accept connection on listening socket
        int cfd = accept(fd, &addr, &addrlen);
        if (cfd < 0) {
            perror("accept");
            exit(1);
        }

        // At most 100 threads at a time
        std::unique_lock<std::mutex> guard(thread_mutex);
        while (nthreads == 100) {
            thread_cv.wait(guard);
        }
        ++nthreads;

        // Handle connection
        std::thread t(handle_connection, cfd, unparse_sockaddr(&addr, addrlen));
        t.detach();
    }
}
