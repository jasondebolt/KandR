#include <stdio.h>

main() {
  int i, c, numwhite, numother;
  int vals[10];

  numwhite = numother = 0;

  for (i = 0; i < 10; ++i) {
    vals[i] = 0;
  }
  
  while ((c = getchar()) != EOF) {
    if (c >= '0' && c <= '9')
      ++vals[c - '0'];
    else if (c == ' ' || c == '\n' || c == '\t')
      ++numwhite;
    else
      ++numother;
  }

  for (i = 0; i < 10; ++i)
    printf("%d %d\n", i, vals[i]);

  printf("numwhite: %d, numother: %d\n", numwhite, numother);
}
