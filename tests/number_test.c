#include <stdio.h>
#include <assert.h>
#include <limits.h>

int main() {
  printf("STARTING NUMBER TESTS.\n");
  assert('\0' == 0);
  assert(NULL == 0);
  assert(NULL == '\x0');
  assert(NULL == '\000');
  assert('\x0' == 0);
  assert('\000' == 0);
  assert('a' == 97);
  assert('\010' == 8);
  assert('\100' == 64);
  assert('\177' == 127);
  assert(CHAR_MAX == 127);
  assert(CHAR_MAX == '\x7f');
  //assert('\200' == 128); // this will break.
  printf("CHAR_BIT: %d\n", CHAR_BIT);
  printf("CHAR_MIN: %d\n", CHAR_MIN);
  printf("CHAR_MAX: %d\n", CHAR_MAX);
  printf("SCHAR_MIN: %d\n", SCHAR_MIN);
  printf("SCHAR_MAX: %d\n", SCHAR_MAX);
  printf("UCHAR_MAX: %d\n", UCHAR_MAX);
  printf("SHRT_MIN: %d\n", SHRT_MIN);
  printf("SHRT_MAX: %d\n", SHRT_MAX);
  printf("USHRT_MAX: %d\n", USHRT_MAX);
  printf("INT_MIN: %d\n", INT_MIN);
  printf("INT_MAX: %d\n", INT_MAX);
  printf("UINT_MAX: %d\n", UINT_MAX);
  printf("LONG_MIN: %ld\n", LONG_MIN);
  printf("LONG_MAX: %ld\n", LONG_MAX);
  printf("ULONG_MAX: %ld\n", ULONG_MAX);
  printf("numbers tested.\n");
  return 0;
}
