#include "membench.hh"
#include <random>
#include <vector>

struct node {
    long value;
};


struct node_arena {
    union fnode {
        node n;
        fnode* next;
    };

    fnode* freelist_ = nullptr;
    std::vector<fnode*> groups_;

    node* allocate() {
        if (!this->freelist_) {
            refresh();
        }
        fnode* fn = this->freelist_;
        this->freelist_ = fn->next;
        return &fn->n;
    }

    [[gnu::noinline]] void refresh() {
        constexpr int groupsize = 10000;
        fnode* fn = new fnode[groupsize];
        groups_.push_back(fn);
        for (int i = 0; i != groupsize; ++i) {
            fn[i].next = this->freelist_;
            this->freelist_ = &fn[i];
        }
    }

    void deallocate(node* n) {
        fnode* fn = (fnode*) n;
        fn->next = this->freelist_;
        this->freelist_ = fn;
    }

    ~node_arena() {
        for (auto fn : this->groups_) {
            delete[] fn;
        }
    }
};


unsigned long memnode_benchmark(unsigned noperations, int seed) {
    const int nnodes = 8192;
    node* n[nnodes];
    for (int i = 0; i != nnodes; ++i) {
        n[i] = nullptr;
    }

    std::minstd_rand randomness(seed);
    std::uniform_int_distribution<int> random_node_index(0, nnodes - 1);
    node_arena arena;

    // allocate and free nodes `noperations` times
    long counter = 0;
    for (unsigned i = 0; i != noperations; ++i) {
        int pos = random_node_index(randomness);
        if (n[pos] == nullptr) {
            n[pos] = arena.allocate();
            n[pos]->value = counter;
            ++counter;
        } else {
            arena.deallocate(n[pos]);
            n[pos] = nullptr;
        }
    }

    // compute a statistic from the remaining nodes and free them
    unsigned long result = 0;
    for (int i = 0; i != nnodes; ++i) {
        if (n[i]) {
            result += n[i]->value;
            arena.deallocate(n[i]);
        }
    }
    return result;
}
