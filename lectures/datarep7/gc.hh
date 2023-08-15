#ifndef CS61_GC_HH
#define CS61_GC_HH

[[gnu::always_inline]] inline void gc_protector() {
#if __x86_64__
    asm volatile ("" : : : "rbx", "r12", "r13", "r14", "r15");
#endif
}

#endif
