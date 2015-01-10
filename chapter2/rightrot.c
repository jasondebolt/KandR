#include <stdio.h>
#include <assert.h>
#include <limits.h>

char rightrot(x, n) {
}

void endToFront(x) {
  1111111111111111111111111111111 >> 1
  0111111111111111111111111111111 >> 1
  ~
  1000000000000000000000000000000 >> 1
  if (x & 01 == 01) { // x is an odd number.
    int mask = ~(~0 >> 1) /// 10000000000000000000...
    x = x >> 1;
    return x | mask;
  } else {
    return x >> 1;
  }
}

void testRightRot() {
  assert(rightrot("00000001", 1), "10000000");
  assert(rightrot("00000001", 2), "01000000");
  assert(rightrot("00000010", 1), "00000001");
  assert(rightrot("00000010", 2), "10000000");
  assert(rightrot("00000010", 3), "01000000");
  assert(rightrot("00101000", 1), "00010100");
  assert(rightrot("00101000", 2), "00001010");
  printf("rightrot tested\n");
}

int main() {
  printf("%d\n", CHAR_MAX);
  testRightRot();

  return 0;
}
