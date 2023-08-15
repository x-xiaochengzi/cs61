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
    node_arena() {
    }

    ~node_arena() {
    }

    node* allocate() {
        return new node;
    }

    void deallocate(node* n) {
        delete n;
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
    node* n = list;
    while (n) {
        result += n->value;
        node* next = n->next;
        arena.deallocate(n);
        n = next;
    }
    return result;
}
