#include <stdio.h>

#define IN 1   /* Inside a word */
#define OUT 0  /* Outside a word */

// This differs slightly from the book version since
// I wrote this myself after looking at the book's solution.

/* count lines, words, and characters in input */
main() {
  int c, nl, nw, nc, state;

  state = OUT;
  nl = nw = nc = 0;
  while ((c = getchar()) != EOF) {
    ++nc;
    if (c == '\n') {
      ++nl;
    }
    if (c == ' ' || c == '\n' || c == '\t') {
      if (state == IN) {
        ++nw;
      }
      state = OUT;
    } else {
      state = IN;
    }
  }
  printf("nc: %d, nl: %d, nw: %d\n", nc, nl, nw);
  
}
