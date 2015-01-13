# Run all unit tests.
#
#

LIB_ROOT=.
TEST_ROOT=.

gcc $LIB_ROOT/lib.c $TEST_ROOT/tests.c; ./a.out
