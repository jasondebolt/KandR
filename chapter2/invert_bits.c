#include <stdio.h>
#include <assert.h>


// There is a much better solution that uses XOR in the book.
// This is my own solution.
int invert(x, pos, len) {
  /*
  Invert spots 6 and 5 of 01001010, result is 00101010
  pos = 6
  len = 2
  1) RHS
     a) Invert x
        10110101
     b) Mask off all bits except the first len bits starting at position pos.
        i) Create an ON mask of size len shifted to the left by pos - len + 1
           11111111 ~0
           11111100 << len
           00000011 ~
           01100000 << pos - len + 1
        ii) Apply on mask to inverted x
           10110101 & 01100000
           ~x & ~(~0 << len) << pos - len + 1
        00100000
     c) RHS =00100000
  2) LHS
     a) Mask off the first len bits starting at pos.
        i) Create of OFF mask of size len shifted to the left by pos - len + 1
           11111111 ~0
           11111100 << len
           00000011 ~
           01100000 << pos - len + 1
           10011111 ~
         ii) Apply OFF mask to x
           01001010 & 10011111
           x & ~(~(~0 << len) << pos - len + 1)
        00001010
      b) LHS = 00001010
  3) Return LHS | RHS
            00001010 | 00100000
            00101010
     return x & ~(~(~0 << len) << pos - len + 1) | ~x & ~(~0 << len) << pos - len + 1
  */
  return x & ~(~(~0 << len) << pos - len + 1) | ~x & ~(~0 << len) << pos - len + 1;
}

void testInvert() {
  //invert spots 6 and 5 of 01001010, result is 00101010
  //invert spots 6 and 5 of 0x4A, result is 0x2A
  assert(invert(0x4A, 6, 2) == 0x2A);
  assert(invert(0x4D, 7, 4) == 0xBD);
  assert(invert(0x0F, 7, 4) == 0xFF);
  assert(invert(0xFF, 3, 4) == 0xF0);
  assert(invert(0xAA, 7, 8) == 0x55);
  printf("testInvert done.\n");
}

int main() {
  testInvert();
  return 0;
}
