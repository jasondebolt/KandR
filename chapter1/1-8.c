#include <stdio.h>

main() {
  int bc, tc, nc, c;

  bc = tc = nc = 0;
  while ((c = getchar()) != EOF) {
    if (c == ' ')
      ++bc;
    if (c == '\t')
      ++tc;
    if (c == '\n')
      ++nc;
  }
  printf("bc: %d, tc: %d, nc: %d\n", bc, tc, nc);
}
