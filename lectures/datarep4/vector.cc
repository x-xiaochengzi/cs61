#include <cstdio>
#include <vector>
#include "hexdump.hh"

int main() {
    std::vector<int> v = {61, 62, 63, 64, 65, 66, 67, 68, 69};
    printf("sizeof(v) = %zu\n", sizeof(v));
    printf("v.size() = %zu\n", v.size());
}
