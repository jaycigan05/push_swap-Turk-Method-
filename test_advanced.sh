#!/bin/bash

# ============================================================
#  push_swap — advanced / evil test cases
#  designed to catch edge cases evaluators use
# ============================================================

PASS="\033[0;32m[PASS]\033[0m"
FAIL="\033[0;31m[FAIL]\033[0m"
INFO="\033[0;34m[INFO]\033[0m"
WARN="\033[0;33m[WARN]\033[0m"

TOTAL_PASS=0
TOTAL_FAIL=0

CHECKER="./checker_OS"

check_error() {
    local desc="$1"
    local cmd="$2"
    local OUT
    OUT=$(eval "$cmd" 2>&1)
    if [ "$OUT" = "Error" ]; then
        echo -e "$PASS $desc"
        TOTAL_PASS=$((TOTAL_PASS + 1))
    else
        echo -e "$FAIL $desc → got: '$OUT'"
        TOTAL_FAIL=$((TOTAL_FAIL + 1))
    fi
}

check_empty() {
    local desc="$1"
    local cmd="$2"
    local OUT
    OUT=$(eval "$cmd" 2>&1)
    if [ -z "$OUT" ]; then
        echo -e "$PASS $desc"
        TOTAL_PASS=$((TOTAL_PASS + 1))
    else
        echo -e "$FAIL $desc → got: '$OUT'"
        TOTAL_FAIL=$((TOTAL_FAIL + 1))
    fi
}

check_sort() {
    local desc="$1"
    local ARG="$2"
    local MAX_OPS="$3"
    local OPS RESULT
    OPS=$(./push_swap $ARG 2>/dev/null | wc -l)
    RESULT=$(./push_swap $ARG 2>/dev/null | $CHECKER $ARG 2>/dev/null)
    if [ "$RESULT" = "OK" ]; then
        if [ -n "$MAX_OPS" ] && [ "$OPS" -gt "$MAX_OPS" ]; then
            echo -e "$FAIL $desc → $OPS ops (max $MAX_OPS) $RESULT"
            TOTAL_FAIL=$((TOTAL_FAIL + 1))
        else
            echo -e "$PASS $desc → $OPS ops OK"
            TOTAL_PASS=$((TOTAL_PASS + 1))
        fi
    else
        echo -e "$FAIL $desc → $OPS ops $RESULT"
        TOTAL_FAIL=$((TOTAL_FAIL + 1))
    fi
}

# ============================================================
# SECTION 1 — evil parser inputs
# ============================================================
echo ""
echo "============================================"
echo " SECTION 1 — Evil Parser Inputs"
echo "============================================"
echo -e "$INFO these are the inputs evaluators love to try"
echo ""

# whitespace tricks
check_error "newline in arg"          "printf '1\n2\n3' | xargs ./push_swap 2>&1 | head -1"
check_error "multiple spaces arg"     "./push_swap '1  2  3'"
check_error "leading space in arg"    "./push_swap ' 1 2 3'"
check_error "trailing space in arg"   "./push_swap '1 2 3 '"

# sign tricks
check_error "plus minus combined"     "./push_swap +-1"
check_error "minus plus combined"     "./push_swap -+1"
check_error "multiple minuses"        "./push_swap ---1"
check_error "multiple pluses"         "./push_swap +++1"
check_error "sign no digit"           "./push_swap - 1 2"
check_error "space after sign"        "./push_swap '- 1' 2 3"

# number tricks
check_error "hex number"              "./push_swap 0x1 2 3"
check_error "octal number"            "./push_swap 010 2 3 2>/dev/null || ./push_swap 010 2 3"
check_error "scientific notation"     "./push_swap 1e5 2 3"
check_error "null byte arg"           "./push_swap '' 1 2"

# overflow edge cases
check_error "exactly INT_MAX + 1"     "./push_swap 2147483648"
check_error "exactly INT_MIN - 1"     "./push_swap -2147483649"
check_error "INT_MAX * 2"             "./push_swap 4294967294"
check_error "INT_MIN * 2"             "./push_swap -4294967296"
check_empty "exactly INT_MAX valid"   "./push_swap 2147483647"
check_empty "exactly INT_MIN valid"   "./push_swap -2147483648"
check_empty "INT_MAX sorted"          "./push_swap -2147483648 0 2147483647"

# ============================================================
# SECTION 2 — worst case arrangements
# ============================================================
echo ""
echo "============================================"
echo " SECTION 2 — Worst Case Arrangements"
echo "============================================"
echo -e "$INFO these arrangements are hardest to sort"
echo ""

# perfectly reverse sorted
check_sort "reverse 3"    "3 2 1"                    3
check_sort "reverse 5"    "5 4 3 2 1"               12
check_sort "reverse 10"   "10 9 8 7 6 5 4 3 2 1"    ""
check_sort "reverse 20"   "20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1" ""

# already sorted (should be 0 ops)
check_sort "sorted 3"     "1 2 3"                    0
check_sort "sorted 5"     "1 2 3 4 5"                0
check_sort "sorted 10"    "1 2 3 4 5 6 7 8 9 10"    0

# rotation needed only
check_sort "rotate needed 3"    "2 3 1"    3
check_sort "rotate needed 5"    "2 3 4 5 1"  12
check_sort "rrotate needed 3"   "3 1 2"    3
check_sort "rrotate needed 5"   "5 1 2 3 4"  12

# single swap needed
check_sort "one swap 3"   "2 1 3"   1
check_sort "one swap 5"   "1 2 4 3 5"  ""

# INT boundary values
check_sort "INT boundaries"  "2147483647 0 -2147483648"  ""
check_sort "INT_MIN first"   "-2147483648 2147483647 0"  ""
check_sort "INT_MAX first"   "2147483647 -2147483648 0"  ""

# ============================================================
# SECTION 3 — specific size stress tests
# ============================================================
echo ""
echo "============================================"
echo " SECTION 3 — Size-Specific Stress Tests"
echo "============================================"

stress_test() {
    local size=$1
    local count=$2
    local max_ops=$3
    local desc=$4
    local fails=0
    local total_ops=0

    echo -e "$INFO $desc ($count runs)..."
    for i in $(seq 1 $count); do
        ARG=$(shuf -i 0-10000 -n $size | tr '\n' ' ')
        OPS=$(./push_swap $ARG 2>/dev/null | wc -l)
        RESULT=$(./push_swap $ARG 2>/dev/null | $CHECKER $ARG 2>/dev/null)
        total_ops=$((total_ops + OPS))
        if [ "$RESULT" != "OK" ]; then
            echo -e "$FAIL size $size: '$ARG' → $RESULT"
            fails=$((fails + 1))
        elif [ -n "$max_ops" ] && [ "$OPS" -gt "$max_ops" ]; then
            echo -e "$FAIL size $size: $OPS ops exceeds $max_ops"
            fails=$((fails + 1))
        fi
    done
    local avg=$((total_ops / count))
    if [ "$fails" -eq 0 ]; then
        echo -e "$PASS $desc — avg $avg ops"
        TOTAL_PASS=$((TOTAL_PASS + 1))
    else
        echo -e "$FAIL $desc — $fails/$count failed"
        TOTAL_FAIL=$((TOTAL_FAIL + 1))
    fi
}

stress_test 2   20  1    "2 numbers (max 1 op)"
stress_test 3   20  3    "3 numbers (max 3 ops)"
stress_test 4   20  ""   "4 numbers"
stress_test 5   20  12   "5 numbers (max 12 ops)"
stress_test 10  20  ""   "10 numbers"
stress_test 20  10  ""   "20 numbers"
stress_test 50  10  ""   "50 numbers"
stress_test 100 10  700  "100 numbers (max 700)"
stress_test 500 5   5500 "500 numbers (max 5500)"

# ============================================================
# SECTION 4 — stability test (same input, same output)
# ============================================================
echo ""
echo "============================================"
echo " SECTION 4 — Stability Test"
echo "============================================"
echo -e "$INFO same input should always produce correct output"
echo ""

ARG="42 7 13 99 1 55 23 77 8 31"
echo -e "$INFO testing '$ARG' 10 times..."
FAILS=0
for i in {1..10}; do
    RESULT=$(./push_swap $ARG 2>/dev/null | $CHECKER $ARG 2>/dev/null)
    if [ "$RESULT" != "OK" ]; then
        echo -e "$FAIL run $i → $RESULT"
        FAILS=$((FAILS + 1))
    fi
done
if [ "$FAILS" -eq 0 ]; then
    echo -e "$PASS stable — all 10 runs correct"
    TOTAL_PASS=$((TOTAL_PASS + 1))
else
    echo -e "$FAIL unstable — $FAILS/10 runs wrong"
    TOTAL_FAIL=$((TOTAL_FAIL + 1))
fi

# ============================================================
# SECTION 5 — negative number combinations
# ============================================================
echo ""
echo "============================================"
echo " SECTION 5 — Negative Number Tests"
echo "============================================"

check_sort "all negatives 3"    "-1 -3 -2"           3
check_sort "all negatives 5"    "-5 -1 -4 -2 -3"    12
check_sort "neg and zero"       "-3 0 -1 -2"         ""
check_sort "neg pos mix 5"      "-2 3 -1 2 0"        12
check_sort "neg pos mix 10"     "-5 3 -1 7 0 -3 4 -2 6 1" ""
check_sort "all neg reverse 5"  "-1 -2 -3 -4 -5"    12

# ============================================================
# SECTION 6 — operation count verification
# ============================================================
echo ""
echo "============================================"
echo " SECTION 6 — Operation Count Benchmarks"
echo "============================================"

echo -e "$INFO running 20 tests for 100 numbers..."
ABOVE_700=0
ABOVE_1500=0
for i in {1..20}; do
    ARG=$(shuf -i 0-1000 -n 100 | tr '\n' ' ')
    OPS=$(./push_swap $ARG 2>/dev/null | wc -l)
    RESULT=$(./push_swap $ARG 2>/dev/null | $CHECKER $ARG 2>/dev/null)
    if [ "$RESULT" != "OK" ]; then
        echo -e "$FAIL run $i → KO ($OPS ops)"
        TOTAL_FAIL=$((TOTAL_FAIL + 1))
    fi
    [ "$OPS" -gt 700 ]  && ABOVE_700=$((ABOVE_700 + 1))
    [ "$OPS" -gt 1500 ] && ABOVE_1500=$((ABOVE_1500 + 1))
done
echo -e "$INFO runs above 700 ops: $ABOVE_700/20"
echo -e "$INFO runs above 1500 ops: $ABOVE_1500/20"
if [ "$ABOVE_1500" -eq 0 ]; then
    echo -e "$PASS always under 1500 ops"
    TOTAL_PASS=$((TOTAL_PASS + 1))
else
    echo -e "$FAIL $ABOVE_1500 runs exceeded 1500 ops"
    TOTAL_FAIL=$((TOTAL_FAIL + 1))
fi

echo ""
echo -e "$INFO running 10 tests for 500 numbers..."
ABOVE_5500=0
ABOVE_11500=0
for i in {1..10}; do
    ARG=$(shuf -i 0-10000 -n 500 | tr '\n' ' ')
    OPS=$(./push_swap $ARG 2>/dev/null | wc -l)
    RESULT=$(./push_swap $ARG 2>/dev/null | $CHECKER $ARG 2>/dev/null)
    if [ "$RESULT" != "OK" ]; then
        echo -e "$FAIL run $i → KO ($OPS ops)"
        TOTAL_FAIL=$((TOTAL_FAIL + 1))
    fi
    [ "$OPS" -gt 5500 ]  && ABOVE_5500=$((ABOVE_5500 + 1))
    [ "$OPS" -gt 11500 ] && ABOVE_11500=$((ABOVE_11500 + 1))
done
echo -e "$INFO runs above 5500 ops: $ABOVE_5500/10"
echo -e "$INFO runs above 11500 ops: $ABOVE_11500/10"
if [ "$ABOVE_11500" -eq 0 ]; then
    echo -e "$PASS always under 11500 ops"
    TOTAL_PASS=$((TOTAL_PASS + 1))
else
    echo -e "$FAIL $ABOVE_11500 runs exceeded 11500 ops"
    TOTAL_FAIL=$((TOTAL_FAIL + 1))
fi

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
    echo -e "\033[0;32m ALL TESTS PASSED — excellent!\033[0m"
else
    echo -e "\033[0;31m $TOTAL_FAIL tests failed — fix before evaluation!\033[0m"
fi
echo ""