#include <stdio.h>

#define IN 1   /* Inside a word */
#define OUT 0  /* Outside a word */

// When transition from IN to OUT, print newline
// When transition from OUT to OUT, do nothing
// Anytime in IN, print character.

main() {
  int c, state;

  state = OUT;

  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\n' || c == '\t') {
      if (state == OUT) {
        // Transition from OUT to OUT, do nothing.
      } else {
        putchar('\n');  /* Transition from IN to OUT. */
        state = OUT;
      }
    } else {
      state = IN;
      putchar(c);  /* In IN. */
    }
  }
}
