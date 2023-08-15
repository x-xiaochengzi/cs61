#include "u-lib.hh"

static size_t nsyscalls = 0;

void writec(unsigned char ch) {
    ssize_t r = -1;

    while (r < 0) {
        r = sys_write(&ch, 1);
        ++nsyscalls;
    }

    assert(r == 1);
}

void writeline(const char* buf, size_t len) {
    for (size_t pos = 0; pos != len; ++pos) {
        writec(buf[pos]);
    }
}


const char* messages[] = {
    "You must stay drunk on writing.\n",
    "No surprise in the writer, no surprise in the reader.\n",
    "All semicolons do is show you've been to college.\n",
    "Don't try to make it logical.\n"
};

void process_main() {
    while (true) {
        // Write a message
        const char* message = messages[rand(0, arraysize(messages) - 1)];
        writeline(message, strlen(message));

        // Print the message that was written
        console_printf(0x0F00, "%zu syscalls: wrote %s",
                       nsyscalls, message);

        // Wait 1-3 seconds
        unsigned long wait_until = ticks + rand(HZ, 3 * HZ - 1);
        while (ticks < wait_until) {
            sys_yield();
        }
    }
}
