#include "membench.hh"
#include <random>
#include <vector>
#include "gc.hh"
extern "C" {
extern char** environ;
}

struct node {
    node* next;
    node* prev;
    long value;
};


struct node_arena {
    node* nb_;
    node* freelist_;
    bool* marks_;

    static constexpr size_t buffersize = 16384;

    node_arena()
        : nb_(new node[buffersize]), freelist_(this->nb_), marks_(new bool[buffersize]) {
        for (size_t i = 1; i != buffersize; ++i) {
            this->nb_[i-1].next = &this->nb_[i];
        }
        this->nb_[buffersize-1].next = nullptr;
    }

    ~node_arena() {
        delete[] nb_;
        delete[] marks_;
    }

    node* allocate() {
        if (!this->freelist_) {
            gc_protector();
            this->gc();
        }
        node* fn = this->freelist_;
        this->freelist_ = fn->next;
        fn->next = fn->prev = nullptr;
        fn->value = 0;
        return fn;
    }

    [[gnu::noinline]] void gc() {
        // unmark all nodes
        for (size_t i = 0; i != buffersize; ++i) {
            this->marks_[i] = false;
        }

        // determine lowest & highest addresses in stack
        uintptr_t stackhi = (uintptr_t) environ;
        uintptr_t stacklo = (uintptr_t) &stackhi;

        // scan stack region
        this->gc_scan(stacklo, stackhi);

        // all unmarked nodes are free
        node** tail = &this->freelist_;
        size_t count = 0;
        for (size_t i = 0; i != buffersize; ++i) {
            if (!this->marks_[i]) {
                *tail = &nb_[i];
                tail = &nb_[i].next;
                ++count;
            }
        }
        *tail = nullptr;

        fprintf(stderr, "gced %zu nodes\n", count);
    }

    [[gnu::noinline]] void gc_scan(uintptr_t lo, uintptr_t hi) {
        lo &= ~7UL;
        hi &= ~7UL;
        for (; lo != hi; lo += 8) {
            uintptr_t contents = *(uintptr_t*) lo;
            //fprintf(stderr, " ? %p @%p\n", contents, lo);
            if (contents >= (uintptr_t) &this->nb_[0]
                && contents < (uintptr_t) &this->nb_[buffersize]) {
                size_t index = (contents - (uintptr_t) &this->nb_[0]) / sizeof(node);
                //fprintf(stderr, " ! %p %zu @%p\n", contents, index, lo);
                if (!this->marks_[index]) {
                    this->marks_[index] = true;
                    this->gc_scan((uintptr_t) &this->nb_[index], (uintptr_t) &this->nb_[index + 1]);
                }
            }
        }
    }

    void deallocate(node*) {
    }
};


unsigned long memnode_benchmark(unsigned noperations, int seed) {
    std::minstd_rand randomness(seed);
    std::uniform_int_distribution<int> random_node_index(10, 400);
    node_arena arena;

    // allocate and free a random-length linked list `noperations` times
    long counter = 0;
    node* list = nullptr;
    for (unsigned i = 0; i != noperations; ++i) {
        // delete old list
        while (list) {
            node* next = list->next;
            arena.deallocate(list);
            list = next;
        }

        // allocate new list
        int length = random_node_index(randomness);
        for (; length > 0; --length) {
            node* n = arena.allocate();
            n->next = list;
            n->prev = nullptr;
            if (list) {
                list->prev = n;
            }
            list = n;
            n->value = random_node_index(randomness);
            ++counter;
        }
    }

    // compute a statistic from the remaining nodes and free them
    unsigned long result = 0;
    for (node* n = list; n; n = n->next) {
        result += n->value;
    }
    return result;
}
