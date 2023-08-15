#include <cstdio>
#include <vector>
#include <random>
#include "bench.hh"


[[gnu::noinline]]
void multiply_all(float* ptr, size_t n, float multiplier) {
    float* end = ptr + n;
    while (ptr != end) {
        *ptr = *ptr * multiplier;
        ++ptr;
    }
}


typedef float vsf __attribute__((vector_size (16)));


[[gnu::noinline]]
void vectorized_multiply_all(float* ptr, size_t n, float multiplier) {
    assert(n % (sizeof(vsf) / sizeof(float)) == 0);
    vsf* vptr = (vsf*) ptr;
    vsf* vend = (vsf*) (ptr + n);
    while (vptr != vend) {
        *vptr = *vptr * multiplier;
        ++vptr;
    }
}


int main() {
    size_t n = 1000000;
    float max = 1.0;

    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_real_distribution<float> distribution(0, max);
    float multiplier = distribution(engine);

    // Initialize `src` as vector of random floats
    std::vector<float> src;
    while (src.size() < n) {
        src.push_back(distribution(engine));
    }

    // `dst1` and `dst2` start as copies of `src`
    std::vector<float> dst1(src);
    std::vector<float> dstm(src);

    // Multiply all elements of `dst1` and `dstm` by `multiplier`
    auto time0 = cputime();
    multiply_all(dst1.data(), dst1.size(), multiplier);
    auto time1 = cputime();
    vectorized_multiply_all(dstm.data(), dstm.size(), multiplier);
    auto time2 = cputime();

    // The data should be the same
    assert(memcmp(dst1.data(), dstm.data(), dst1.size() * sizeof(float)) == 0);
    printf("Single float instructions took %.06f sec\n", time1 - time0);
    printf("Vectorized float instructions took %.06f sec\n", time2 - time1);
}
