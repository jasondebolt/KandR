#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include "../jlib/bit_lib.h"

void nullTests() {
  assert('\0' == 0);
  assert(NULL == 0);
  assert(NULL == '\x0');
  assert(NULL == '\000');
  assert('\x0' == 0);
  assert('\000' == 0);
  printf("Null tests tested.\n");
}

void intTests() {
  assert(UINT_MAX == pow(2, 32) - 1);
  assert(UINT_MAX == 0xFFFFFFFF);
  assert(INT_MAX == pow(2, 31) - 1);
  assert(INT_MAX == 0x7FFFFFFF);
  assert(USHRT_MAX == pow(2, 16) - 1);
  assert(USHRT_MAX == 0xFFFF);
  assert(SHRT_MAX == pow(2, 15) - 1);
  assert(SHRT_MAX == 0x7FFF);
  assert(UCHAR_MAX == pow(2, 8) - 1);
  assert(CHAR_MAX == pow(2, 7) - 1);
  assert((unsigned int) 0xFFFFFFFF == UINT_MAX); // 32 on bits.
  assert((unsigned int) 0xFFFFFFFE == UINT_MAX - 1); // 31 on bits.
  assert((signed int) 0xFFFFFFFF == -1); // 32 on bits.
  assert((signed int) 0xFFFFFFFE == -2); // 31 on bits.
  assert((unsigned int) 0x7FFFFFFF == (signed int) 0x7FFFFFFF);
  assert((signed int) UINT_MAX == -1);
  assert((unsigned int) -1 == UINT_MAX);
  printf("Int tests tested.\n");
}

void limitTests() {
  assert(CHAR_MAX == 127);
  assert(CHAR_MAX == '\x7f');
  printf("CHAR_BIT: %d\n", CHAR_BIT);
  printf("CHAR_MIN: %d\n", CHAR_MIN);
  printf("CHAR_MAX: %d\n", CHAR_MAX);
  printf("SCHAR_MIN: %d\n", SCHAR_MIN);
  printf("SCHAR_MAX: %d\n", SCHAR_MAX);
  printf("UCHAR_MAX: %u\n", UCHAR_MAX); // Use 'u', not 'd'
  printf("SHRT_MIN: %d\n", SHRT_MIN);
  printf("SHRT_MAX: %d\n", SHRT_MAX);
  printf("USHRT_MAX: %u\n", USHRT_MAX); // Use 'u', not 'd'
  printf("INT_MIN: %d\n", INT_MIN);
  // Network Roofm Giraffe == 2^31
  printf("INT_MAX: %d\n", INT_MAX);
  // Rainbow Rubbish Can Beach == 2^32
  printf("UINT_MAX: %u\n", UINT_MAX);  // Use 'u', not 'd'
  printf("LONG_MIN: %ld\n", LONG_MIN);
  printf("LONG_MAX: %ld\n", LONG_MAX);
  printf("ULONG_MAX: %lu\n", ULONG_MAX); // Use 'u', not 'd'
  printf("numbers tested.\n");
  printf("Limit tests tested.\n");
}

void octalTests() {
  assert('\010' == 8);
  assert(010 == 8);
  assert('\100' == 64);
  assert(0100 == 64);
  assert('\177' == 127);
  assert(0177 == 127);
  //assert('\200' == 128); // char only goes up to 127. This will break.
  assert(0200 == 128);
  printf("Octal tests tested.\n");
}

void charTests() {
  assert('a' == 97);
  assert('\x7F' == CHAR_MAX);
  assert(0xFF == UCHAR_MAX);
  assert((signed char)0xFF == -1);
  assert((unsigned char) -1 == UCHAR_MAX);
  printf("Char tests tested.\n");
}


void negativeOneTests() {
  // Negative one can have many different representations!!!
  assert(-1 == 0xFFFFFFFF);
  assert((unsigned long) -1 == 0xFFFFFFFF);
  assert((unsigned int) -1 == 0xFFFFFFFF);
  assert((unsigned short) -1 == 0xFFFF);
  assert((unsigned char) -1 == 0xFF);
  assert((signed char) 0xFF == -1);
  printf("Negative one tests tested.\n");
}

void minimumsTests() {
  assert((signed int) 0x80000000 == INT_MIN);
  assert((signed short) 0x8000 == SHRT_MIN);
  assert((signed char) 0x80 == CHAR_MIN);
  printf("Minimums tested.\n");
}

void maximumsTests() {
  assert((signed int) 0x7FFFFFFF == INT_MAX);
  assert((signed short) 0x7FFF == SHRT_MAX);
  assert((signed char) 0x7F == CHAR_MAX);
  assert((unsigned int) 0xFFFFFFFF == UINT_MAX);
  assert((unsigned short) 0xFFFF == USHRT_MAX);
  assert((unsigned char) 0xFF == UCHAR_MAX);
  printf("Maximums tested.\n");
}

void testLogicalOperatorsCast() {
  // Looks like logical operators cast to signed int by default
  assert(0xFFFFFFFF == -1);
  assert(0xFFFFFFFF > 0); // WTF?
  assert(0xFFFF == USHRT_MAX);
  assert(0xFF == UCHAR_MAX);
  printf("Logical operators tested.\n");
}

// See page 44 of K&R for details.
void testComparisonBetweenSignedAndUnsignedValues() {
  signed int si = -1;
  unsigned int ui = 1;
  unsigned short us = 1;
  assert(us > si); // This comparison works as expected.
  assert(si < us); // This comparison works. Unsigned short is promoted to signed int.
  assert(si > ui); // WTF? This comparison does not work. Signed int is converted into
                   // an unsigned int, thus appearing to be a very large positive number.
  /* Lesson to be learned: DO NOT COMPARE SIGNED AND UNSIGNED VALUES!!!
     - See page 44 of K&R for details.
  */
  printf("Comparison between signed and unsigned values tested.\n");
}

int main() {
  printf("STARTING NUMBER TESTS.\n");
  nullTests();
  intTests();
  limitTests();
  octalTests();
  charTests();
  negativeOneTests();
  minimumsTests();
  maximumsTests();
  testLogicalOperatorsCast();
  testComparisonBetweenSignedAndUnsignedValues();
  return 0;
}
