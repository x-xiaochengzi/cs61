//! -O1 -Wno-unused

struct small {
    char m1, m2;
};

struct medium {
    long m1, m2;
};

struct large {
    long m1, m2, m3, m4, m5, m6, m7, m8;
};

int f(small a1) {
    return a1.m1;
}
