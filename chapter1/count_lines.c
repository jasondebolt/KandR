#include <stdio.h>

main() {
  int lc, c;

  lc = 0;
  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      ++lc;
    }
  }
  printf("%d\n", lc);
}
