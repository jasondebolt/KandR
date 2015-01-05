#include <stdio.h>

int atoi(char s[]) {
  int i, n;

  n = 0;
  for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i) {
    n = 10 * n + (s[i] - '0');
  }
  return n;
}

int main() {
  
  printf("%d\n", atoi("123"));
  return 0;
}
