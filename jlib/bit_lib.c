#include "bit_lib.h"


unsigned btoi(char c[]) {
  unsigned i, n;
  n = 0;

  for (i = 0; c[i] != '\0'; ++i) {
    n = n * 2 + c[i] - '0';
  }
  return n;
}

// K&R page 49 has a better version. I created this one.
// Get len number of bits starting from position pos of int n.
int getBits(int n, int pos, int len) {
  // btoi("01000100"), 6, 5 --> "10001"
  // 00000001 --> 1
  // 11111110 --> ~1
  // 11100000 --> (~1 << len - 1)
  // 00011111 --> ~(~1 << len - 1)
  return (n >> (pos - len + 1)) & ~(~1 << (len - 1));
}

// see page 49 of K&R for original question.
// Get rightmost len bits from y and put them into position pos of int n.
// My solution below is surprisingly close to the book solution!
int setBits(int n, int pos, int len, int y) {
  /*
     assert(setBits(btoi("01101011"), 7, 1, btoi("00000101")) == btoi("11101011"));
     assert(setBits(btoi("01101011"), 4, 3, btoi("00000101")) == btoi("01110111"))
      RIGHT MASK
        POS 7, LEN 1                       POS 4, LEN 3               OPERATION
        00000001                           00000001                   1
        11111110                           11111110                   ~
        11111110                           11111000                   << len - 1
        00000001                           00000111                   ~
        y = y & 00000001                   y = y & 00000111
        y = 00000101 & 00000001            y = 00000101 & 00000111
        y = 00000001                       y = 00000101
        y = y << (pos - len + 1)           y = y << (pos - len + 1)
        y = 00000001 <<< 7 - 1 + 1         y = 00000101 << 4 - 3 + 1
        y = 10000000                       y = 00010100

     LEFT MASK
        POS 7, LEN 1                    POS 4, LEN 3              OPERATION
        00000001                        00000001                  1
        11111110                        11111110                  ~
        11111110                        11111000                  << len - 1
        00000001                        00000111                  ~
        10000000                        00011100                  << pos - len + 1
        01111111                        11100011                  ~
        n = n & 01111111                n = n & 11100011
        n = 01101011 & 01111111         n = 01101011 & 11100011
        n = 01101011                    n = 01100011

     FINAL RESULT
        return n | y                    return n | y
        return 01101011 | 10000000      return 01100011 | 00010100
        return 11101011                 return 01110111
   */
  n = n & ~(~(~1 << (len - 1)) << (pos - len + 1));
  y = (y & ~(~1 << (len - 1))) << (pos - len + 1);
  return n | y;
}

// There is a much better solution that uses XOR in the book.
// This is my own solution.
int invertBits(int x, int pos, int len) {
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
  return (x & ~(~(~0 << len) << (pos - len + 1))) | (~x & ~(~0 << len) << (pos - len + 1));
}

// private.
unsigned char endToFrontChar(unsigned char x) {
  if (x & 01 == 01) { // x is an odd number.
    x = x >> 1;
    x = x | ~((unsigned char) ~0 >> 1);
  } else {
    x = x >> 1;
  }
  return x;
}

unsigned char rightRotateChar(unsigned char x, int n) {
  while (--n >= 0) {
    x = endToFrontChar(x);
  }
  return x;
}

// private.
unsigned int endToFrontInt(unsigned int x) {
  if (x & 01 == 01) { // x is an odd number.
    x = x >> 1;
    x = x | ~((unsigned int) ~0 >> 1);
  } else {
    x = x >> 1;
  }
  return x;
}

unsigned int rightRotateInt(unsigned int x, int n) {
  while (--n >= 0) {
    x = endToFrontInt(x);
  }
  return x;
}


/* If we didn't use unsigned int for the arg, we wouldn't
 * be able to test if n > 0 because a signed n may fail this test.
 * The number -1 has 32 bits, for example. This function would return
 * a bitcount of zero for -1 if argument n was signed.
 */
int bitCount(unsigned int n) {
  int bitcount = 0;

  while(n > 0) {
    if (n & 01) {
      ++bitcount;
    }
    n = n >> 1;
  }
  return bitcount;
}

char *itob(int n) {
  char *result = malloc(MAX_BIT_STRING_SIZE + 1);
  int j;
  int i = 0;

  while (n > 0) {
    if (n & 01) {
      result[i] = '1';
    } else {
      result[i] = '0';
    }
    n = n >> 1;
    ++i;
  }
  while(i < MAX_BIT_STRING_SIZE) {
    result[i] = '0';
    ++i;
  }
  result[i] = '\0';
  reverse2(result);
  return result;
}

void printBits(int n) {
  printf("\t%s\n", itob(n));
}

void printIntAll(int n) {
  printf("(signed/unsigned dec: %d/%u) (bin: %s) (hex: 0x%x) (oct: 0%o)\n",
         n, n, itob(n), n, n);
}

void printCharAll(char c) {
  printf("(char: %c) (signed/unsigned dec: %d/%u) (bin: %s) (hex: 0x%x) (oct: 0%o)\n",
         c, c, c, itob(c), c, c);
}
