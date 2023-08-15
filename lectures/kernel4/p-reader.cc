#include "u-lib.hh"

static size_t nsyscalls = 0;

int readc() {
    unsigned char ch;
    ssize_t r = -1;

    while (r < 0) {
        r = sys_read(&ch, 1);
        ++nsyscalls;
    }

    assert(r == 1);
    return ch;
}

size_t readline(char* buf, size_t bufsiz) {
    size_t pos = 0;
    while (pos < bufsiz && (pos == 0 || buf[pos - 1] != '\n')) {
        int ch = readc();
        if (ch <= 0) {
            panic("ran out of data!\n");
        }
        buf[pos] = ch;
        ++pos;
    }
    if (pos == bufsiz) {
        --pos;
    }
    buf[pos] = '\0';
    return pos;
}

void process_main() {
    char buf[200];

    while (true) {
        // Read a message
        size_t n = readline(buf, sizeof(buf));

        // Print the message that was read
        console_printf(0x0E00, "%zu syscalls: read %.*s",
                       nsyscalls, n, buf);
    }
}
