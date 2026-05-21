*This project has been created as part of the 42 curriculum by jagan.*

# push_swap

> Sort a stack of integers using the minimum number of operations.

---

## Table of Contents

1. [Description](#1-description)
2. [Algorithm](#2-algorithm)
3. [File Structure](#3-file-structure)
4. [Instructions](#4-instructions)
5. [Usage Examples](#5-usage-examples)
6. [Operations Reference](#6-operations-reference)
7. [Benchmarks](#7-benchmarks)
8. [Resources](#8-resources)

---

## 1. Description

push_swap is a sorting algorithm project from the 42 curriculum. Given a stack of unique integers, the program calculates and outputs the shortest possible sequence of operations to sort the stack in ascending order (smallest at top).

The program works with two stacks — `a` and `b` — and a fixed set of 11 operations to manipulate them.

**Core capabilities:**
- Parses and validates integer arguments (detects non-integers, duplicates, and overflow)
- Handles both separate arguments (`3 1 2`) and quoted string arguments (`"3 1 2"`)
- Normalizes values to indexes for efficient algorithm computation
- Selects the optimal algorithm based on input size (2, 3, 4, 5, or large)
- Implements the Turk algorithm for inputs larger than 5 elements
- Outputs the minimum sequence of operations to stdout, one per line
- Prints `Error` to stderr for any invalid input

---

## 2. Algorithm

### Small inputs (≤ 5 elements)

| Size | Strategy | Max ops |
|------|----------|---------|
| 2 | Direct swap if needed | 1 |
| 3 | Hardcoded 6-case sort | 2 |
| 4 | Push min to B, sort 3, push back | ~5 |
| 5 | Push 2 smallest to B, sort 3, push back | ~12 |

### Large inputs — Turk Algorithm

The Turk algorithm sorts stacks larger than 5 elements in the fewest operations:

```
1. Push all elements from A to B (keep 3 in A)
2. Sort the 3 remaining elements in A using sort_3
3. For each element in B:
   a. Find its correct insertion position in A (successor node)
   b. Calculate cost to bring that B element to top of B
   c. Calculate cost to bring target position to top of A
   d. Pick the cheapest element in B
   e. Rotate A and B simultaneously (use rr/rrr to save moves)
   f. Push B element to A
4. Rotate A so the minimum is at the top
```

**Cost optimisation:**
- Same direction rotations → use `rr` or `rrr` → pay only `max(cost_a, cost_b)`
- Different direction rotations → pay `|cost_a| + |cost_b|`

**Index normalisation:**
Values are converted to ranks (0 = smallest, n-1 = largest) before sorting. This simplifies comparisons and avoids edge cases with large negative/positive values.

**Successor-based insertion:**
When inserting a B element into A, the algorithm rotates A until the successor (smallest element in A larger than the B element) is at the top, then pushes. This maintains A in correct sorted order throughout.

---

## 3. File Structure

```
push_swap/
├── Makefile                  ← build rules: all, clean, fclean, re
├── push_swap.h               ← structs, prototypes, includes
└── src/
    ├── main.c                ← entry point, argument handling, algorithm dispatch
    ├── stack_init.c          ← parse args, build stack A, assign indexes
    ├── stack_utils.c         ← new node, add top, size, last, free
    ├── utils.c               ← atol, is_valid_arg, has_duplicate, is_sorted
    ├── ft_split.c            ← split string by spaces, handle quoted args
    ├── ops_swap.c            ← sa, sb, ss
    ├── ops_push.c            ← pa, pb
    ├── ops_rotate.c          ← ra, rb, rr
    ├── ops_reverse_rotate.c  ← rra, rrb, rrr
    ├── sort_small.c          ← sort_2, sort_3, sort_4, sort_5
    ├── sort_big.c            ← sort_big, do_move, rotate_min_top
    ├── sb_find_target.c      ← find_target, ft_abs
    └── sb_calc_cost.c        ← cost_to_top, calc_cost, find_cheapest
```

---

## 4. Instructions

### Requirements

| Tool | Version | Check |
|------|---------|-------|
| cc (gcc/clang) | any | `cc --version` |
| make | any | `make --version` |
| 42 norminette | any | `norminette --version` |

### Compilation

```bash
# clone the repository
git clone <your-repo-url>
cd push_swap-Turk-Method-

# build
make

# clean object files
make clean

# clean everything including binary
make fclean

# full rebuild
make re
```

### Running norminette

```bash
norminette src/*.c push_swap.h
```

---

## 5. Usage Examples

```bash
# sort numbers — separate arguments
./push_swap 3 1 2
# ra

# sort numbers — quoted string argument
./push_swap "3 1 2"
# ra

# mixed: quoted and separate
./push_swap "3 1" 2
# ra

# count operations
ARG="4 67 3 87 23"
./push_swap $ARG | wc -l
# 9

# verify correctness with official checker
./push_swap $ARG | ./checker_OS $ARG
# OK

# already sorted — prints nothing
./push_swap 1 2 3 4 5

# single number — prints nothing
./push_swap 42

# error cases — all print "Error" to stderr
./push_swap 1 a 3        # non-integer
./push_swap 1 2 2        # duplicate
./push_swap 2147483648   # exceeds INT_MAX
./push_swap -2147483649  # below INT_MIN
./push_swap ""           # empty string
./push_swap "   "        # whitespace only
./push_swap              # no arguments — prints nothing
```

<!-- ### Automated testing

```bash
# run with provided test scripts
chmod +x test_push_swap.sh test_push_swap_extra.sh test_advanced.sh test_leaks.sh

./test_push_swap.sh        # main evaluation tests
./test_push_swap_extra.sh  # edge case tests
./test_advanced.sh         # stress and benchmark tests
./test_leaks.sh            # valgrind memory leak tests

# stress test 100 numbers (repeat 10 times)
for i in {1..10}; do
    ARG=$(shuf -i 0-1000 -n 100 | tr '\n' ' ')
    ./push_swap $ARG | ./checker_OS $ARG
    ./push_swap $ARG | wc -l
done

# stress test 500 numbers
for i in {1..5}; do
    ARG=$(shuf -i 0-10000 -n 500 | tr '\n' ' ')
    ./push_swap $ARG | ./checker_OS $ARG
    ./push_swap $ARG | wc -l
done
``` -->

---

## 6. Operations Reference

| Operation | Description |
|-----------|-------------|
| `sa` | Swap top 2 elements of stack A |
| `sb` | Swap top 2 elements of stack B |
| `ss` | `sa` and `sb` simultaneously |
| `pa` | Push top of B to top of A |
| `pb` | Push top of A to top of B |
| `ra` | Rotate A up — top goes to bottom |
| `rb` | Rotate B up — top goes to bottom |
| `rr` | `ra` and `rb` simultaneously |
| `rra` | Reverse rotate A — bottom comes to top |
| `rrb` | Reverse rotate B — bottom comes to top |
| `rrr` | `rra` and `rrb` simultaneously |

---

## 7. Benchmarks

Performance achieved by this implementation:

| Input size | Target | Achieved (avg) | Score |
|------------|--------|----------------|-------|
| 100 numbers | < 700 ops | ~583 ops | 5/5 ⭐⭐⭐⭐⭐ |
| 500 numbers | < 5500 ops | ~5197 ops | 5/5 ⭐⭐⭐⭐⭐ |

---

## 8. Resources

### References

| Resource | Description |
|----------|-------------|
| [Turk Algorithm — Medium](https://pure-forest.medium.com/push-swap-turk-algorithm-explained-in-6-steps-4c6650a458c0) | Main reference for the Turk algorithm — explains the 6-step approach with visuals |
| [42 Cursus Guide — push_swap](https://42-cursus.gitbook.io/guide/2-rank-02/push_swap) | 42 community guide covering project structure, algorithm choices, and tips |
| YouTube | Used to understand linked list operations and stack manipulation concepts before implementation |

### How AI was used

AI (Claude by Anthropic) was used throughout this project in the following ways:

| Task | How AI helped |
|------|--------------|
| **Concept explanation** | Explained C concepts such as `*` vs `**` pointers, dangling pointers, `argv` structure, `static` keyword, and when NULL checks are necessary |
| **Error clarification** | Helped interpret compiler errors and segfault traces from AddressSanitizer output |
| **Debugging** | Identified bugs such as missing `&& stack->next` guard in `is_sorted`, wrong `find_target` logic (predecessor vs successor), stale `.o` files causing crashes, and `sort_4` missing from `main.c` |
| **Test generation** | Generated shell test scripts (`test_push_swap.sh`, `test_push_swap_extra.sh`, `test_advanced.sh`, `test_leaks.sh`) covering error handling, identity tests, benchmarks, and memory leaks |
| **Code review** | Reviewed function logic and pointed out norminette issues such as missing semicolons, wrong variable names, and 25-line function limit violations |
| **String parsing** | Helped design `ft_split_space` to handle quoted string arguments like `"3 1 2"` in addition to separate arguments |

All code was written, reviewed, and understood by the student. AI was used as a learning and debugging tool — not as a code generator. Every function in this project can be explained and justified by the author.