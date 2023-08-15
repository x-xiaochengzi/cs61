#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <unistd.h>
#include <sys/fcntl.h>

#define TESTFILE "consistency-test.txt"

// Overwrite the contents of `TESTFILE` with the string `contents`.
void overwrite(const char* contents) {
    FILE* f = fopen(TESTFILE, "w");
    fputs(contents, f);
    fclose(f);
}

size_t read_using_stdio(char buf[BUFSIZ]) {
    overwrite("CS 61 is terrible!\n");
    // Contents of `TESTFILE` is now "CS 61 is terrible!\n"

        // Open `TESTFILE` and read first 9 bytes
        FILE* f = fopen(TESTFILE, "r");
        size_t nr = fread(buf, 1, 9, f);
        assert(nr == 9);

        fflush(f);

    overwrite("CS 61 is awesome!!\n");
    // Contents of `TESTFILE` is now "CS 61 is awesome!!\n"

        // Read remaining bytes of already-open `TESTFILE`
        nr += fread(buf + nr, 1, BUFSIZ - nr, f);
        fclose(f);
        return nr;
}

size_t read_using_syscalls(char buf[BUFSIZ]) {
    overwrite("CS 61 is terrible!\n");
    // Contents of `TESTFILE` is now "CS 61 is terrible!\n"

        // Open `TESTFILE` and read first 9 bytes
        int fd = open(TESTFILE, O_RDONLY);
        ssize_t nr = read(fd, buf, 9);
        assert(nr == 9);

    overwrite("CS 61 is awesome!!\n");
    // Contents of `TESTFILE` is now "CS 61 is awesome!!\n"

        // Read remaining bytes of already-open `TESTFILE`
        nr += read(fd, buf + nr, BUFSIZ - nr);
        close(fd);
        assert(nr >= 9);
        return nr;
}

int main() {
    char buf[BUFSIZ];

    printf("Reading using stdio:\n");
    size_t n = read_using_stdio(buf);
    fwrite(buf, 1, n, stdout);

    printf("\nReading using system calls:\n");
    n = read_using_syscalls(buf);
    fwrite(buf, 1, n, stdout);
}
