#include <stdio.h>

main() {
  int c;
  int ns;

  ns = 0;
  
  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      ++ns;
    } else {
      ns = 0;
    }
    if (ns <= 1) {
      putchar(c);
    }
  }
}
