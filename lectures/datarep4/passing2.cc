#include <cstdio>
#include <vector>

void f(std::vector<int> arg) {
    arg = {-1};
}

int main() {
    std::vector<int> l = {2};
    f(l);
    printf("l[0] is %d\n", l[0]);
}
