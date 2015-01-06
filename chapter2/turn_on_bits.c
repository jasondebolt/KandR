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

// bitwise OR operator | is used to turn bits on.
void turnOnBits(int *n) {
  *n = *n | btoi("1110");
}

int main() {
  int n = btoi("11110000");
  turnOnBits(&n);
  assert(n == btoi("11111110"));
}
