#!/bin/bash

# ============================================================
#  push_swap — full evaluation test script
#  based on 42 evaluation sheet
# ============================================================

PUSH_SWAP="./push_swap"
CHECKER="./checker_OS"
PASS="\033[0;32m[PASS]\033[0m"
FAIL="\033[0;31m[FAIL]\033[0m"
INFO="\033[0;34m[INFO]\033[0m"
WARN="\033[0;33m[WARN]\033[0m"

# ============================================================
# SECTION 1 — error management
# ============================================================
echo ""
echo "============================================"
echo " SECTION 1 — Error Management"
echo "============================================"

# non numeric
OUT=$(./push_swap 1 a 3 2>&1)
if [ "$OUT" = "Error" ]; then
    echo -e "$PASS non numeric argument → Error"
else
    echo -e "$FAIL non numeric argument → got: '$OUT'"
fi

# duplicate
OUT=$(./push_swap 1 2 2 2>&1)
if [ "$OUT" = "Error" ]; then
    echo -e "$PASS duplicate → Error"
else
    echo -e "$FAIL duplicate → got: '$OUT'"
fi

# over INT_MAX
OUT=$(./push_swap 2147483648 2>&1)
if [ "$OUT" = "Error" ]; then
    echo -e "$PASS INT_MAX overflow → Error"
else
    echo -e "$FAIL INT_MAX overflow → got: '$OUT'"
fi

# under INT_MIN
OUT=$(./push_swap -- -2147483649 2>&1)
if [ "$OUT" = "Error" ]; then
    echo -e "$PASS INT_MIN underflow → Error"
else
    echo -e "$FAIL INT_MIN underflow → got: '$OUT'"
fi

# no parameters
OUT=$(./push_swap 2>&1)
if [ -z "$OUT" ]; then
    echo -e "$PASS no parameters → nothing printed"
else
    echo -e "$FAIL no parameters → got: '$OUT'"
fi

# empty string
OUT=$(./push_swap "" 2>&1)
if [ "$OUT" = "Error" ]; then
    echo -e "$PASS empty string → Error"
else
    echo -e "$FAIL empty string → got: '$OUT'"
fi

# only sign
OUT=$(./push_swap + 2>&1)
if [ "$OUT" = "Error" ]; then
    echo -e "$PASS sign only '+' → Error"
else
    echo -e "$FAIL sign only '+' → got: '$OUT'"
fi

# duplicate after leading zeros
OUT=$(./push_swap 0001 1 2 2>&1)
if [ "$OUT" = "Error" ]; then
    echo -e "$PASS leading zeros duplicate → Error"
else
    echo -e "$FAIL leading zeros duplicate → got: '$OUT'"
fi

# ============================================================
# SECTION 2 — identity test (already sorted)
# ============================================================
echo ""
echo "============================================"
echo " SECTION 2 — Identity Test (already sorted)"
echo "============================================"

check_sorted() {
    local input="$1"
    local OUT
    OUT=$(./push_swap $input 2>&1)
    if [ -z "$OUT" ]; then
        echo -e "$PASS '$input' → nothing printed"
    else
        echo -e "$FAIL '$input' → got: '$OUT'"
    fi
}

check_sorted "42"
check_sorted "2 3"
check_sorted "0 1 2 3"
check_sorted "0 1 2 3 4 5 6 7 8 9"
check_sorted "-5 -3 0 1 4"
check_sorted "0001 2 3"   # leading zeros, still sorted after parse

# ============================================================
# SECTION 3 — simple version (2-3 numbers)
# ============================================================
echo ""
echo "============================================"
echo " SECTION 3 — Simple Version (2-3 numbers)"
echo "============================================"

# exact test from sheet
ARG="2 1 0"
OPS=$(./push_swap $ARG | wc -l)
RESULT=$(./push_swap $ARG | $CHECKER $ARG)
if [ "$RESULT" = "OK" ] && [ "$OPS" -le 3 ]; then
    echo -e "$PASS '2 1 0' → $OPS ops, OK"
else
    echo -e "$FAIL '2 1 0' → $OPS ops, $RESULT"
fi

# random 2-3 values, repeat 5 times
for i in {1..5}; do
    COUNT=$((RANDOM % 3 + 1))
    ARG=$(shuf -i 0-99 -n $COUNT | tr '\n' ' ')
    OPS=$(./push_swap $ARG | wc -l)
    RESULT=$(./push_swap $ARG | $CHECKER $ARG 2>/dev/null)
    if [ "$RESULT" = "OK" ] && [ "$OPS" -le 3 ]; then
        echo -e "$PASS random $COUNT values '$ARG' → $OPS ops, OK"
    else
        echo -e "$FAIL random $COUNT values '$ARG' → $OPS ops, $RESULT"
    fi
done

# ============================================================
# SECTION 4 — another simple version (5 numbers)
# ============================================================
echo ""
echo "============================================"
echo " SECTION 4 — Another Simple Version (5 numbers)"
echo "============================================"

# exact test from sheet
ARG="1 5 2 4 3"
OPS=$(./push_swap $ARG | wc -l)
RESULT=$(./push_swap $ARG | $CHECKER $ARG)
if [ "$RESULT" = "OK" ] && [ "$OPS" -le 12 ]; then
    if [ "$OPS" -le 8 ]; then
        echo -e "$PASS '1 5 2 4 3' → $OPS ops, OK (excellent — ≤8!)"
    else
        echo -e "$PASS '1 5 2 4 3' → $OPS ops, OK"
    fi
else
    echo -e "$FAIL '1 5 2 4 3' → $OPS ops, $RESULT"
fi

# random 5 values, repeat 5 times
for i in {1..5}; do
    ARG=$(shuf -i 0-99 -n 5 | tr '\n' ' ')
    OPS=$(./push_swap $ARG | wc -l)
    RESULT=$(./push_swap $ARG | $CHECKER $ARG 2>/dev/null)
    if [ "$RESULT" = "OK" ] && [ "$OPS" -le 12 ]; then
        echo -e "$PASS 5 values '$ARG' → $OPS ops, OK"
    else
        echo -e "$FAIL 5 values '$ARG' → $OPS ops, $RESULT"
    fi
done

# ============================================================
# SECTION 5 — middle version (100 numbers)
# ============================================================
echo ""
echo "============================================"
echo " SECTION 5 — Middle Version (100 numbers)"
echo "============================================"

TOTAL=0
FAILS=0
for i in {1..5}; do
    ARG=$(shuf -i 0-1000 -n 100 | tr '\n' ' ')
    OPS=$(./push_swap $ARG | wc -l)
    RESULT=$(./push_swap $ARG | $CHECKER $ARG 2>/dev/null)
    TOTAL=$((TOTAL + OPS))
    if [ "$RESULT" = "OK" ]; then
        if   [ "$OPS" -lt 700  ]; then echo -e "$PASS test $i → $OPS ops (5/5 ⭐⭐⭐⭐⭐)"
        elif [ "$OPS" -lt 900  ]; then echo -e "$PASS test $i → $OPS ops (4/5 ⭐⭐⭐⭐)"
        elif [ "$OPS" -lt 1100 ]; then echo -e "$PASS test $i → $OPS ops (3/5 ⭐⭐⭐)"
        elif [ "$OPS" -lt 1300 ]; then echo -e "$PASS test $i → $OPS ops (2/5 ⭐⭐)"
        elif [ "$OPS" -lt 1500 ]; then echo -e "$PASS test $i → $OPS ops (1/5 ⭐)"
        else echo -e "$FAIL test $i → $OPS ops (0/5 — too many)"
        fi
    else
        echo -e "$FAIL test $i → $OPS ops, $RESULT"
        FAILS=$((FAILS + 1))
    fi
done
AVG=$((TOTAL / 5))
echo -e "$INFO average ops over 5 runs: $AVG"

# ============================================================
# SECTION 6 — advanced version (500 numbers)
# ============================================================
echo ""
echo "============================================"
echo " SECTION 6 — Advanced Version (500 numbers)"
echo "============================================"

TOTAL=0
for i in {1..5}; do
    ARG=$(shuf -i 0-10000 -n 500 | tr '\n' ' ')
    OPS=$(./push_swap $ARG | wc -l)
    RESULT=$(./push_swap $ARG | $CHECKER $ARG 2>/dev/null)
    TOTAL=$((TOTAL + OPS))
    if [ "$RESULT" = "OK" ]; then
        if   [ "$OPS" -lt 5500  ]; then echo -e "$PASS test $i → $OPS ops (5/5 ⭐⭐⭐⭐⭐)"
        elif [ "$OPS" -lt 7000  ]; then echo -e "$PASS test $i → $OPS ops (4/5 ⭐⭐⭐⭐)"
        elif [ "$OPS" -lt 8500  ]; then echo -e "$PASS test $i → $OPS ops (3/5 ⭐⭐⭐)"
        elif [ "$OPS" -lt 10000 ]; then echo -e "$PASS test $i → $OPS ops (2/5 ⭐⭐)"
        elif [ "$OPS" -lt 11500 ]; then echo -e "$PASS test $i → $OPS ops (1/5 ⭐)"
        else echo -e "$FAIL test $i → $OPS ops (0/5 — too many)"
        fi
    else
        echo -e "$FAIL test $i → $OPS ops, $RESULT"
    fi
done
AVG=$((TOTAL / 5))
echo -e "$INFO average ops over 5 runs: $AVG"

# ============================================================
# SECTION 7 — memory leaks
# ============================================================
echo ""
echo "============================================"
echo " SECTION 7 — Memory Leaks (valgrind)"
echo "============================================"

if command -v valgrind &> /dev/null; then
    # test normal run
    LEAK=$(valgrind --leak-check=full --error-exitcode=1 ./push_swap 3 1 2 2>&1)
    if echo "$LEAK" | grep -q "no leaks are possible"; then
        echo -e "$PASS normal run — no leaks"
    else
        echo -e "$WARN normal run — check manually: valgrind --leak-check=full ./push_swap 3 1 2"
    fi

    # test error path
    LEAK=$(valgrind --leak-check=full --error-exitcode=1 ./push_swap 1 a 3 2>&1)
    if echo "$LEAK" | grep -q "no leaks are possible"; then
        echo -e "$PASS error path — no leaks"
    else
        echo -e "$WARN error path — check manually: valgrind --leak-check=full ./push_swap 1 a 3"
    fi
else
    echo -e "$WARN valgrind not found — run manually:"
    echo "  valgrind --leak-check=full ./push_swap 3 1 2"
    echo "  valgrind --leak-check=full ./push_swap 1 a 3"
fi

echo ""
echo "============================================"
echo " Done."
echo "============================================"
echo ""