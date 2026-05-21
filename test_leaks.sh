#!/bin/bash

# ============================================================
#  push_swap — memory leak tests
#  run with valgrind to catch every possible leak
# ============================================================

PASS="\033[0;32m[PASS]\033[0m"
FAIL="\033[0;31m[FAIL]\033[0m"
INFO="\033[0;34m[INFO]\033[0m"

TOTAL_PASS=0
TOTAL_FAIL=0

# check if valgrind is available
if ! command -v valgrind &> /dev/null; then
    echo "valgrind not found — install with: sudo apt install valgrind"
    exit 1
fi

check_leak() {
    local desc="$1"
    local cmd="$2"
    local OUTPUT
    OUTPUT=$(eval "valgrind --leak-check=full --error-exitcode=42 $cmd" 2>&1)
    local EXIT_CODE=$?
    if [ $EXIT_CODE -eq 42 ]; then
        echo -e "$FAIL $desc — LEAK DETECTED"
        echo "$OUTPUT" | grep "definitely lost\|indirectly lost\|ERROR SUMMARY"
        TOTAL_FAIL=$((TOTAL_FAIL + 1))
    else
        echo -e "$PASS $desc"
        TOTAL_PASS=$((TOTAL_PASS + 1))
    fi
}

# ============================================================
# SECTION 1 — error paths (most common leak source)
# ============================================================
echo ""
echo "============================================"
echo " SECTION 1 — Error Path Leaks"
echo "============================================"
echo -e "$INFO these are where most students leak"
echo ""

check_leak "non numeric arg"          "./push_swap 1 a 3"
check_leak "duplicate"                "./push_swap 1 2 2"
check_leak "INT_MAX overflow"         "./push_swap 2147483648"
check_leak "INT_MIN underflow"        "./push_swap -2147483649"
check_leak "empty string"             "./push_swap \"\""
check_leak "sign only '+'"            "./push_swap +"
check_leak "sign only '-'"            "./push_swap -"
check_leak "float number"             "./push_swap 1.5 2 3"
check_leak "first arg invalid"        "./push_swap abc 1 2 3"
check_leak "last arg invalid"         "./push_swap 1 2 3 abc"
check_leak "middle arg invalid"       "./push_swap 1 2 abc 4 5"
check_leak "duplicate at start"       "./push_swap 1 1 2 3 4"
check_leak "duplicate at end"         "./push_swap 1 2 3 4 4"
check_leak "duplicate in middle"      "./push_swap 1 2 3 2 4"
check_leak "all duplicates"           "./push_swap 5 5 5 5 5"
check_leak "very large number"        "./push_swap 99999999999"
check_leak "very large negative"      "./push_swap -99999999999"

# ============================================================
# SECTION 2 — normal operation paths
# ============================================================
echo ""
echo "============================================"
echo " SECTION 2 — Normal Operation Leaks"
echo "============================================"

check_leak "no args"                  "./push_swap"
check_leak "single number"           "./push_swap 42"
check_leak "already sorted 2"        "./push_swap 1 2"
check_leak "already sorted 3"        "./push_swap 1 2 3"
check_leak "already sorted 5"        "./push_swap 1 2 3 4 5"
check_leak "already sorted 10"       "./push_swap 0 1 2 3 4 5 6 7 8 9"
check_leak "sort 2 numbers"          "./push_swap 2 1"
check_leak "sort 3 numbers"          "./push_swap 3 1 2"
check_leak "sort 3 reverse"          "./push_swap 3 2 1"
check_leak "sort 4 numbers"          "./push_swap 4 3 2 1"
check_leak "sort 5 numbers"          "./push_swap 5 4 3 2 1"
check_leak "sort 5 random"           "./push_swap 1 5 2 4 3"
check_leak "negatives only"          "./push_swap -1 -5 -3 -2 -4"
check_leak "mixed neg and pos"       "./push_swap -3 1 -1 2 0"
check_leak "INT_MIN and INT_MAX"     "./push_swap 2147483647 -2147483648"
check_leak "INT_MIN sorted"          "./push_swap -2147483648 0 2147483647"

# ============================================================
# SECTION 3 — larger inputs
# ============================================================
echo ""
echo "============================================"
echo " SECTION 3 — Larger Input Leaks"
echo "============================================"

check_leak "10 numbers"   "./push_swap $(shuf -i 0-100 -n 10 | tr '\n' ' ')"
check_leak "20 numbers"   "./push_swap $(shuf -i 0-500 -n 20 | tr '\n' ' ')"
check_leak "50 numbers"   "./push_swap $(shuf -i 0-1000 -n 50 | tr '\n' ' ')"
check_leak "100 numbers"  "./push_swap $(shuf -i 0-1000 -n 100 | tr '\n' ' ')"
check_leak "500 numbers"  "./push_swap $(shuf -i 0-10000 -n 500 | tr '\n' ' ')"

# ============================================================
# SECTION 4 — edge cases with signs
# ============================================================
echo ""
echo "============================================"
echo " SECTION 4 — Sign Edge Cases"
echo "============================================"

check_leak "plus sign args"          "./push_swap +3 +1 +2"
check_leak "mixed signs"             "./push_swap +3 -1 +2 -4 0"
check_leak "negative sorted"         "./push_swap -5 -3 -1 0 2"
check_leak "leading zeros"           "./push_swap 0001 002 03"
check_leak "leading zeros dup"       "./push_swap 01 1 2"

# ============================================================
# FINAL SCORE
# ============================================================
echo ""
echo "============================================"
echo " FINAL SCORE"
echo "============================================"
echo -e "$INFO passed: $TOTAL_PASS"
echo -e "$INFO failed: $TOTAL_FAIL"
echo -e "$INFO total:  $((TOTAL_PASS + TOTAL_FAIL))"
if [ "$TOTAL_FAIL" -eq 0 ]; then
    echo -e "\033[0;32m NO LEAKS DETECTED — ready for evaluation!\033[0m"
else
    echo -e "\033[0;31m $TOTAL_FAIL leak(s) found — fix before evaluation!\033[0m"
    echo -e "$INFO run individual test with:"
    echo "  valgrind --leak-check=full ./push_swap <args>"
fi
echo ""