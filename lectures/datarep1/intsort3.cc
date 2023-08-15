#include <cstdio>
#include <cassert>
#include <map>
#include "hexdump.hh"

int main() {
    std::map<int, bool> ls;

    // read integers from stdin, storing them in sorted order
    int val;
    while (fscanf(stdin, "%d", &val) == 1) {
        ls.insert({val, true});
    }

    // print integers in sorted order
    for (auto kv : ls) {
        // NB Elements of `std::map` are key-value pairs. We want the key.
        fprintf(stdout, "%d\n", kv.first);
    }
}
