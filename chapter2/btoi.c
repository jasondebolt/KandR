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


int main() {

  assert(btoi("0001") == 1);
  assert(btoi("0010") == 2);
  assert(btoi("1111") == 15);
  return 0;
}
