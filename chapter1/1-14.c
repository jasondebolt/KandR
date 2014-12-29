#include <stdio.h>

int main() {
  int i, c;
  int vals[128];

  for (i = 0; i < 128; ++i) {
    vals[i] = 0;
  }

  while ((c = getchar()) != EOF) {
    ++vals[c];
  }

  for (i = 0; i < 128; ++i) {
    printf("%c %d ", i, vals[i]);
  }

  return 0;
}
