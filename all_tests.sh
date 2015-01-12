# Run all unit tests.
#
#

LIB_ROOT=jlib
TEST_ROOT=tests

gcc $LIB_ROOT/bit_lib.c $LIB_ROOT/str_lib.c $TEST_ROOT/bit_lib_test.c; ./a.out
gcc $LIB_ROOT/str_lib.c $TEST_ROOT/str_lib_test.c; ./a.out
gcc $LIB_ROOT/test_lib.c $TEST_ROOT/test_lib_test.c; ./a.out
gcc $LIB_ROOT/bit_lib.c $LIB_ROOT/str_lib.c $TEST_ROOT/number_test.c; ./a.out
gcc $LIB_ROOT/bit_lib.c $LIB_ROOT/str_lib.c $LIB_ROOT/search_lib.c $TEST_ROOT/search_lib_test.c; ./a.out
