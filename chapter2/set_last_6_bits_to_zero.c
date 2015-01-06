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

void setLastSixBitsToZero(int *n) {
  *n = *n & ~077;
}

int main() {
  int n = btoi("11111111");
  setLastSixBitsToZero(&n);
  assert(n == btoi("11000000"));
}
