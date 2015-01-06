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

// bit position 0 is at the right end.
unsigned getbits(unsigned x, int p, int n) {
  return (x >> (p + 1 - n)) & ~(~0 << n);
}

int main() {
  int val = btoi("00111100");
  int expected = btoi("1111");
  // Position 5 from the right, n is 4.
  assert(getbits(val, 5, 4) == expected);
  return 0;
}
