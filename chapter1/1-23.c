#include <stdio.h>
#define MAX_STR_LEN 1000

// Remove comments from a C program, line by line.
int main() {
  char c, tmp, b1, b2;
  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      putchar(c);
    } else if (c == '"') {
      putchar(c); // put the first "
      while (1) {
        tmp = c;
        c = getchar();
        putchar(c);
        if (c == '"') {
          // Make sure things like " foo \" bar" are printed.
          if (tmp != '\\') {
            break;
          }
        }
      }
    } else if (c == '\'') {
      putchar(c); // put the first '
      while (1) {
        tmp = c;
        c = getchar();
        putchar(c);
        if (c == '\'') {
          // Make sure things like ' foo \' bar' are printed.
          if (tmp != '\\') {
            break;
          }
        }
      }
    } else if (c == '/') {
      tmp = getchar();
      if (tmp == '/') {
        while ((c = getchar()) != '\n') {
          //pass
        }
        putchar(c); // Put the newline
      } else if (tmp == '*') {
        b1 = getchar();
        b2 = getchar();
        while (!(b1 == '*' && b2 == '/')) {
          b1 = b2;
          b2 = getchar();
        }
      } else {
        putchar(c);
        putchar(tmp);
      }
    } else {
      putchar(c);
    }
  }
  return 0;
}
