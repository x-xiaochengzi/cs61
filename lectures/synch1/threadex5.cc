#include <cstdio>
#include <cstring>
#include <thread>
#include <ctime>
#include <unistd.h>
#include "hexdump.hh"

void print(int id,
           const char* readonly_str,
           char* caller_local_str,
           char* heap_str) {
    char my_local_str[100];
    snprintf(my_local_str, sizeof(my_local_str),
             "T%d local", id);

    char my_id[10];
    snprintf(my_id, sizeof(my_id), "T%d", id);

    fhexdump(stdout, readonly_str, strlen(readonly_str), my_id);
    fhexdump(stdout, caller_local_str, strlen(caller_local_str), my_id);
    fhexdump(stdout, heap_str, strlen(heap_str), my_id);
    fhexdump(stdout, my_local_str, strlen(my_local_str), my_id);

    caller_local_str[id] = 'X';
}

int main() {
    char main_local_str[100];
    strcpy(main_local_str, "main local");

    char* heap_str = new char[100];
    strcpy(heap_str, "heap");

    std::thread t1(print, 1, "readonly", main_local_str, heap_str);
    std::thread t2(print, 2, "readonly", main_local_str, heap_str);
    t1.join();
    t2.join();

    fhexdump(stdout, main_local_str, strlen(main_local_str), "MAIN");
}
