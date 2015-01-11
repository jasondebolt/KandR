#include <assert.h>
#include "../jlib/bit_lib.h"

void testBits() {
  assert(~0 << 3 == ~1 << 2);
  printf("bits tested.\n");
}

void testBtoi() {
  assert(btoi("10101010") == 0xAA);
  printf("btoi tested.\n");
}

void testGetBits() {
  assert(getBits(btoi("01000100"), 6, 5) == btoi("10001"));
  assert(getBits(btoi("01000100"), 7, 8) == btoi("01000100"));
  assert(getBits(btoi("01000100"), 3, 4) == btoi("0100"));
  assert(getBits(btoi("01000100"), 0, 1) == btoi("0"));
  printf("getBits tested.\n");
}

void testSetBits() {
  assert(setBits(btoi("01101011"), 4, 3, btoi("00000101")) == btoi("01110111"));
  assert(setBits(btoi("01101011"), 4, 3, btoi("00000101")) == btoi("01110111"));
  assert(setBits(btoi("01101011"), 7, 1, btoi("00000101")) == btoi("11101011"));
  assert(setBits(btoi("01101011"), 7, 8, btoi("00000101")) == btoi("00000101"));
  assert(setBits(btoi("01101011"), 6, 6, btoi("10101010")) == btoi("01010101"));
  assert(setBits(btoi("00000000"), 7, 8, btoi("11111111")) == btoi("11111111"));
  assert(setBits(btoi("00000000"), 7, 4, btoi("11111111")) == btoi("11110000"));
  printf("setBits tested.\n");
}

void testInvertBits() {
  //invert spots 6 and 5 of 01001010, result is 00101010
  //invert spots 6 and 5 of 0x4A, result is 0x2A
  assert(invertBits(0x4A, 6, 2) == 0x2A);
  assert(invertBits(0x4D, 7, 4) == 0xBD);
  assert(invertBits(0x0F, 7, 4) == 0xFF);
  assert(invertBits(0xFF, 3, 4) == 0xF0);
  assert(invertBits(0xAA, 7, 8) == 0x55);
  printf("testInvertBits done.\n");
}

void testRightRotateChar() {
  assert(rightRotateChar(1, 8) == btoi("00000001"));
  assert(rightRotateChar(btoi("00000001"), 8) == btoi("00000001"));
  assert(rightRotateChar(btoi("00000001"), 1) == btoi("10000000"));
  printf("rightRotateChar tested\n");
}

void testRightRotateInt() {
  assert(rightRotateInt(btoi("00000000000000000000000000000001"), 32) ==
         btoi("00000000000000000000000000000001"));
  assert(rightRotateInt(btoi("00000000000000000000000000000001"), 1) ==
         btoi("10000000000000000000000000000000"));
  printf("rightRotateInt tested\n");
}

void testBitCount() {
  assert(bitCount(10) == 2);
  assert(bitCount(20) == 2);
  assert(bitCount(31) == 5);
  assert(bitCount(32) == 1);
  assert(bitCount(INT_MAX) == 31);
  printf("bitCount tested\n");
}

void testItob() {
  seq(itob(0), ZERO);
  seq(itob(10), TEN);
  seq(itob(20), TWENTY);
  seq(itob(31), THIRTY_ONE);
  seq(itob(32), THIRTY_TWO);
  seq(itob(63), SIXTY_THREE);
  seq(itob(127), ONE_TWENTY_SEVEN);
  seq(itob(128), ONE_TWENTY_EIGHT);
  seq(itob(255), TWO_FIFTY_FIVE);
  printf("itob tested.\n");
}

void testPrintIntAll() {
  printIntAll(255);
  printf("printIntAll tested.\n");
}

void testPrintCharAll() {
  printCharAll(65);
  printCharAll('Z');
  printCharAll(97);
  printCharAll('z');
  printf("printCharAll tested.\n");
}

int main() {
  printf("STARTING BIT LIB TESTS.\n");
  testBits();
  testBtoi();
  testGetBits();
  testSetBits();
  testInvertBits();
  testRightRotateChar();
  testRightRotateInt();
  testBitCount();
  testItob();
  testPrintIntAll();
  testPrintCharAll();
  return 0;
}
