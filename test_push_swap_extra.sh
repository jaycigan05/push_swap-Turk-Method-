#!/bin/bash

# ============================================================
#  push_swap — extra edge case tests
#  covers tricky cases evaluators use to catch people
# ============================================================

PUSH_SWAP="./push_swap"
CHECKER="./checker_OS"
PASS="\033[0;32m[PASS]\033[0m"
FAIL="\033[0;31m[FAIL]\033[0m"
INFO="\033[0;34m[INFO]\033[0m"

TOTAL_PASS=0
TOTAL_FAIL=0

# generate N unique random numbers in range 0-MAX
gen_nums() {
    local n=$1
    local max=$2
    shuf -i 0-$max -n $n | tr '\n' ' '
}

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

check_ok() {
    local desc="$1"
    local ARG="$2"
    local MAX_OPS="$3"
    local OPS RESULT
    OPS=$(./push_swap $ARG | wc -l)
    RESULT=$(./push_swap $ARG | $CHECKER $ARG 2>/dev/null)
    if [ "$RESULT" = "OK" ] && [ "$OPS" -le "$MAX_OPS" ]; then
        echo -e "$PASS $desc → $OPS ops OK"
        TOTAL_PASS=$((TOTAL_PASS + 1))
    else
        echo -e "$FAIL $desc → $OPS ops $RESULT"
        TOTAL_FAIL=$((TOTAL_FAIL + 1))
    fi
}

# ============================================================
# SECTION A — sneaky error cases
# ============================================================
echo ""
echo "============================================"
echo " SECTION A — Sneaky Error Cases"
echo "============================================"

check_error "sign only '+'"              "./push_swap +"
check_error "sign only '-'"              "./push_swap -"
check_error "double plus '++42'"         "./push_swap ++42"
check_error "empty string '\"\"'"        "./push_swap \"\""
check_error "space only '\" \"'"         "./push_swap \" \""
check_error "valid then invalid"         "./push_swap 1 2 abc"
check_error "invalid then valid"         "./push_swap abc 1 2"
check_error "float number"              "./push_swap 1.5 2 3"
check_error "comma separated"           "./push_swap 1,2,3"
check_error "special chars"             "./push_swap 1 @ 3"
check_error "INT_MAX + 1"               "./push_swap 2147483648"
check_error "INT_MIN - 1"               "./push_swap -2147483649"
check_error "very large number"         "./push_swap 99999999999"
check_error "very large negative"       "./push_swap -99999999999"
check_error "duplicate zeros"           "./push_swap 0 0"
check_error "duplicate negatives"       "./push_swap -1 -1 2"
check_error "duplicate with leading zeros" "./push_swap 01 1"

# ============================================================
# SECTION B — identity edge cases
# ============================================================
echo ""
echo "============================================"
echo " SECTION B — Identity Edge Cases"
echo "============================================"

check_empty "single number"             "./push_swap 42"
check_empty "single negative"           "./push_swap -42"
check_empty "INT_MAX"                   "./push_swap 2147483647"
check_empty "INT_MIN"                   "./push_swap -2147483648"
check_empty "two sorted"               "./push_swap 1 2"
check_empty "two sorted negatives"     "./push_swap -5 -3"
check_empty "sorted with negatives"    "./push_swap -5 -3 0 1 4"
check_empty "sorted leading zero"      "./push_swap 0001 2 3"
check_empty "sorted +/- signs"        "./push_swap +1 +2 +3"
check_empty "large sorted"             "./push_swap 0 1 2 3 4 5 6 7 8 9"
check_empty "INT_MIN to INT_MAX"       "./push_swap -2147483648 0 2147483647"

# ============================================================
# SECTION C — sorting correctness stress
# ============================================================
echo ""
echo "============================================"
echo " SECTION C — Sorting Correctness Stress"
echo "============================================"

# 2 numbers
echo -e "$INFO testing 2 numbers (10 random cases)..."
FAILS=0
for i in {1..10}; do
    ARG=$(gen_nums 2 1000)
    OPS=$(./push_swap $ARG | wc -l)
    RESULT=$(./push_swap $ARG | $CHECKER $ARG 2>/dev/null)
    if [ "$RESULT" != "OK" ] || [ "$OPS" -gt 1 ]; then
        echo -e "$FAIL 2 numbers '$ARG' → $OPS ops $RESULT"
        FAILS=$((FAILS + 1))
        TOTAL_FAIL=$((TOTAL_FAIL + 1))
    fi
done
if [ "$FAILS" -eq 0 ]; then
    echo -e "$PASS all 2-number tests passed"
    TOTAL_PASS=$((TOTAL_PASS + 1))
fi

# 3 numbers
echo -e "$INFO testing 3 numbers (20 random cases)..."
FAILS=0
for i in {1..20}; do
    ARG=$(gen_nums 3 1000)
    OPS=$(./push_swap $ARG | wc -l)
    RESULT=$(./push_swap $ARG | $CHECKER $ARG 2>/dev/null)
    if [ "$RESULT" != "OK" ] || [ "$OPS" -gt 3 ]; then
        echo -e "$FAIL 3 numbers '$ARG' → $OPS ops $RESULT"
        FAILS=$((FAILS + 1))
        TOTAL_FAIL=$((TOTAL_FAIL + 1))
    fi
done
if [ "$FAILS" -eq 0 ]; then
    echo -e "$PASS all 3-number tests passed"
    TOTAL_PASS=$((TOTAL_PASS + 1))
fi

# 5 numbers
echo -e "$INFO testing 5 numbers (20 random cases)..."
FAILS=0
for i in {1..20}; do
    ARG=$(gen_nums 5 1000)
    OPS=$(./push_swap $ARG | wc -l)
    RESULT=$(./push_swap $ARG | $CHECKER $ARG 2>/dev/null)
    if [ "$RESULT" != "OK" ] || [ "$OPS" -gt 12 ]; then
        echo -e "$FAIL 5 numbers '$ARG' → $OPS ops $RESULT"
        FAILS=$((FAILS + 1))
        TOTAL_FAIL=$((TOTAL_FAIL + 1))
    fi
done
if [ "$FAILS" -eq 0 ]; then
    echo -e "$PASS all 5-number tests passed"
    TOTAL_PASS=$((TOTAL_PASS + 1))
fi

# negative numbers (simulate with offset)
echo -e "$INFO testing with negative numbers (10 random cases, 10 numbers)..."
FAILS=0
for i in {1..10}; do
    ARG=$(gen_nums 10 1000 | tr ' ' '\n' | awk '{print $1 - 500}' | tr '\n' ' ')
    RESULT=$(./push_swap $ARG | $CHECKER $ARG 2>/dev/null)
    if [ "$RESULT" != "OK" ]; then
        echo -e "$FAIL negatives '$ARG' → $RESULT"
        FAILS=$((FAILS + 1))
        TOTAL_FAIL=$((TOTAL_FAIL + 1))
    fi
done
if [ "$FAILS" -eq 0 ]; then
    echo -e "$PASS all negative number tests passed"
    TOTAL_PASS=$((TOTAL_PASS + 1))
fi

# 20 numbers stress
echo -e "$INFO testing 20 numbers (10 random cases)..."
FAILS=0
for i in {1..10}; do
    ARG=$(gen_nums 20 10000)
    RESULT=$(./push_swap $ARG | $CHECKER $ARG 2>/dev/null)
    if [ "$RESULT" != "OK" ]; then
        echo -e "$FAIL 20 numbers '$ARG' → $RESULT"
        FAILS=$((FAILS + 1))
        TOTAL_FAIL=$((TOTAL_FAIL + 1))
    fi
done
if [ "$FAILS" -eq 0 ]; then
    echo -e "$PASS all 20-number tests passed"
    TOTAL_PASS=$((TOTAL_PASS + 1))
fi

# 50 numbers stress
echo -e "$INFO testing 50 numbers (10 random cases)..."
FAILS=0
for i in {1..10}; do
    ARG=$(gen_nums 50 10000)
    RESULT=$(./push_swap $ARG | $CHECKER $ARG 2>/dev/null)
    if [ "$RESULT" != "OK" ]; then
        echo -e "$FAIL 50 numbers → $RESULT"
        FAILS=$((FAILS + 1))
        TOTAL_FAIL=$((TOTAL_FAIL + 1))
    fi
done
if [ "$FAILS" -eq 0 ]; then
    echo -e "$PASS all 50-number tests passed"
    TOTAL_PASS=$((TOTAL_PASS + 1))
fi

# ============================================================
# SECTION D — exact eval sheet tests
# ============================================================
echo ""
echo "============================================"
echo " SECTION D — Exact Eval Sheet Tests"
echo "============================================"

check_ok "eval: '2 1 0' ≤3 ops"      "2 1 0"     3
check_ok "eval: '1 5 2 4 3' ≤12 ops" "1 5 2 4 3" 12

ARG="0 9 1 8 2"
OPS_LIST=$(printf "pb\nra\npb\nra\nsa\nra\npa\npa")
RESULT=$(echo "$OPS_LIST" | ./checker_OS $ARG 2>/dev/null)
if [ "$RESULT" = "OK" ]; then
    echo -e "$PASS checker '0 9 1 8 2' [pb ra pb ra sa ra pa pa] → OK"
    TOTAL_PASS=$((TOTAL_PASS + 1))
else
    echo -e "$FAIL checker '0 9 1 8 2' → $RESULT"
    TOTAL_FAIL=$((TOTAL_FAIL + 1))
fi

# ============================================================
# SECTION E — makefile no relinking
# ============================================================
echo ""
echo "============================================"
echo " SECTION E — Makefile No Relinking"
echo "============================================"

RELINK=$(make 2>&1)
if echo "$RELINK" | grep -q "Nothing to be done\|is up to date"; then
    echo -e "$PASS no relinking on second make"
    TOTAL_PASS=$((TOTAL_PASS + 1))
elif [ -z "$RELINK" ]; then
    echo -e "$PASS no relinking on second make"
    TOTAL_PASS=$((TOTAL_PASS + 1))
else
    echo -e "$FAIL relinking detected"
    echo "$RELINK"
    TOTAL_FAIL=$((TOTAL_FAIL + 1))
fi

# ============================================================
# SECTION F — stderr vs stdout
# ============================================================
echo ""
echo "============================================"
echo " SECTION F — stderr vs stdout"
echo "============================================"

STDOUT=$(./push_swap 1 a 3 2>/dev/null)
STDERR=$(./push_swap 1 a 3 2>&1 >/dev/null)
if [ -z "$STDOUT" ] && [ "$STDERR" = "Error" ]; then
    echo -e "$PASS Error → stderr only"
    TOTAL_PASS=$((TOTAL_PASS + 1))
else
    echo -e "$FAIL Error stream wrong — stdout:'$STDOUT' stderr:'$STDERR'"
    TOTAL_FAIL=$((TOTAL_FAIL + 1))
fi

STDOUT=$(./push_swap 2 1 2>/dev/null)
if [ "$STDOUT" = "sa" ]; then
    echo -e "$PASS operations → stdout"
    TOTAL_PASS=$((TOTAL_PASS + 1))
else
    echo -e "$FAIL operations not on stdout → '$STDOUT'"
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
if [ "$TOTAL_FAIL" -eq 0 ]; then
    echo -e "\033[0;32m ALL TESTS PASSED — ready for evaluation!\033[0m"
else
    echo -e "\033[0;31m $TOTAL_FAIL tests failed — fix before evaluation!\033[0m"
fi
echo ""