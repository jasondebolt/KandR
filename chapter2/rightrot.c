#include <stdio.h>
#include "../lib.h"

void testRightRot() {
  printf("rightrot tested.\n");
}

void testUnsigned() {
  printf("%d\n", btoi("10101010"));
  dprint((unsigned char) 0xFF == 255);
  dprint(btoi("10101010"));
  dprint((signed char) 0xFF == -1);
  dprint((signed char) 0x80 == -128);
  dprint((unsigned char) 0x80 == 128);
  printf("unsigned tested.\n");
}

int main() {
  testRightRot();
  testUnsigned();


  return 0;
}
