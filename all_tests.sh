# Run all unit tests.
#
#

LIB_ROOT=.
TEST_ROOT=.

gcc $LIB_ROOT/std_lib.c $TEST_ROOT/std_lib_test.c; ./a.out | less
