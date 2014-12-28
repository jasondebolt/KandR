#include <stdio.h>

main() {
  int count, c;

  count = 0;

  while ((c = getchar()) != EOF) {
    ++count;
  }
  printf("%d\n", count);
}
