CS 61: Data representation 1
============================

This lecture is our teaser lecture, and our introduction to data
representation. Its aims to open doors—to introduce interesting directions—not
necessarily to explain the outcomes. We’ll be investigating the consequences
of these experiments for the rest of the class.

Type `make` to build the programs in this directory.


`testaccess`
------------

The `testaccess` program tests how long it takes to access all elements in an
array of 4-byte integers. The inner timing loop of each run accesses exactly
the same amount of data; the only difference between these runs is the access
order. Try:

```sh
$ ./testaccess -u 100000     # accesses 100,000 integers in “up” order:
                             # index 0, then index 1, then index 2, etc.
$ ./testaccess -d 100000     # accesses 100,000 integers in “down” order:
                             # index 99,999, then index 99,998, etc.
$ ./testaccess -r 100000     # accesses 100,000 integers in random order
$ ./testaccess -m 100000     # accesses 100,000 integers in “magic” order
                             # (bouncing between the ends of the array)
```


`testinsertN`
-------------

The `testinsert0` and `testinsert1` programs test how long it takes to create
a sorted sequence of integers through repeated insertion. `testinsert0` stores
the sequence in a linked list, while `testinsert1` stores the sequence in an
array.

To insert an integer _X_, the test programs:

1. Find the insertion position—the greatest position in the sequence where all
   previous elements are smaller than _X_. These programs find that position
   by checking the elements in order.

2. Insert _X_ at that position.

Step 1 (finding the insertion position) has worst-case computational
complexity $O(N)$, where $N$ is the length of the sequence, for both data
structures.

> **On computational complexity.** “O notation” like this is an incredibly
> useful shorthand for discussing the performance characteristics of different
> algorithms. “Worst-case computational complexity $O(N)$” means that, for a
> sequence with $N$ elements, the find-insertion-position operation may take
> up to $N$ distinct steps (or a constant factor of $N$ distinct steps). In
> particular, if _X_ is greater than all current elements of the sequence,
> then find-insertion-position will examine all $N$ sequence elements before
> stopping.

Step 2 (inserting _X_) has $O(1)$ complexity for linked lists, but $O(N)$
worst-case complexity for arrays. (Inserting an element at the beginning of an
array requires moving all the existing elements.)

Which data structure do you think will be faster, and on what order? Why?

```sh
$ ./testaccess0 -u 100000
$ ./testaccess1 -u 100000
```

As a bonus, `testaccess2` performs the same job, using an array data
structure, but with a faster algorithm: _binary search_. In binary search,
step 1 (finding the insertion position) has worst-case computational
complexity $O(\log N)$. This should be faster than `testaccess1`! Try it.


Quicksort
---------

We investigated a number of different quicksort implementations as
systems programs.

Quicksort on Wikipedia: https://en.wikipedia.org/wiki/Quicksort

* `qs.ml`: An OCaml quicksort function.

* `qs0.c` through `qs3.c`: List-based quicksorts (like OCaml).
  * `ilist.h`: A little library for handling singly-linked lists of
    integers.
  * `testqs-list.c`: The test driver.

* `qs4.c` through `qs6.c`: Array-based quicksorts.
  * `testqs-array.c`: The test driver.

* `qs7.c`: Standard library quicksort (array-based).

Type `make` to build programs `testqs0` through `testqs7`. Options for
these programs are:

* `./testqsX -r [N]`: The array contains `N` random ints. Default `N`
  is 6.
* `./testqsX -u [N]`: The array is initially sorted.
* `./testqsX -d [N]`: The array is initially reverse-sorted.
* `./testqsX -m [N]`: The array contains the numbers 1,...,`N` in a
  magic evil order.

Executions to try:

* `./testqs0 -r 10`
* `./testqs0 -r 10000000`
* `make SANITIZE=1; ./testqs0 -r 10`
* `./testqs5 -m 100000`

Try `time ./testqsX` to see how long an execution takes.

Further reading: "Implementing Quicksort Programs", Robert Sedgewick,
Communications of the ACM 21(10), October 1978;
http://www.csie.ntu.edu.tw/~b93076/p847-sedgewick.pdf

"Engineering a Sort Function", Jon L. Bentley and M. Douglas McIlroy,
Software---Practice and Experience 23(11), November 1993;
http://www.skidmore.edu/~meckmann/2009Spring/cs206/papers/spe862jb.pdf


`add` and `addin`
-----------------

Run `./add 2 2` to add 2 and 2.

The `add` function’s definition is located in `addf.c`. Check out
`addf-examples.c` for some alternate definitions that work too
(amazingly).

Run `./addin FILE OFFSET A B` to add `A` and `B`, using the “add function”
located in `FILE` at byte `OFFSET`. For instance, try `./addin addf.o 64 2 2`.

Use `objdump -S addf.o` to look at the instructions in `addf.o`.


`addin`
-------
covid: 0x2400/9216
