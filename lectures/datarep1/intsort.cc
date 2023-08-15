#include <cstdio>
#include <cassert>
#include <list>
#include <vector>
#include "hexdump.hh"

int main() {
    std::list<int> ls;

    // read integers from stdin, storing them in sorted order
    int val;
    while (fscanf(stdin, "%d", &val) == 1) {
        auto it = ls.begin();
        while (it != ls.end() && *it < val) {
            ++it;
        }
        ls.insert(it, val);
    }

    // print integers in sorted order
    for (auto v : ls) {
        fprintf(stdout, "%d\n", v);
    }
}
