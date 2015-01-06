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

void setAllButLowerOrderSevenBitsToZero(int *n) {
  *n = *n & 0177;
}

int main() {
  int n = btoi("1111111111111111"); // 2 bytes.
  setAllButLowerOrderSevenBitsToZero(&n);
  assert(n == btoi("0000000001111111"));
}

