#include <stdio.h>
#include <assert.h>

int btoi(char c[]) {
  int i, n;
  n = 0;

  for (i = 0; c[i] != '\0'; ++i) {
    n = n * 2 + c[i] - '0';
  }
  return n;
}

/* Return x with the n bits that begin at position p set to the
 * rightmost n bits of y, leaving other bits unchanged.
 * position p starts on the right side.
 */
int setbits(x, p, n, y) {
  1) Make copy of first called tmp.
  2) Shift left tmp by (7 - 4 + 1) = 4
  3) Set the 4 bits in second beginning from position 7 to the right zero.
  4) Use the OR operator to set the 4 right bits starting as position 7 to those in tmp.
}

int main() {
  int first = btoi("00001101");
  int second = btoi("00000000");
  second = setbits(second, 7, 4, first);
  assert(second == btoi("11010000");
}

