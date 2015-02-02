# Run all unit tests.
#
#

LIB_ROOT=.
TEST_ROOT=.

gcc -Wno-parentheses $LIB_ROOT/lib.c $TEST_ROOT/tests.c; ./a.out
