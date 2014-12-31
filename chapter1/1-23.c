#include <stdio.h>
#define MAX_STR_LEN 1000

//for (every character in the file) DONE
//  if (the character is a double quote) DONE
//    (putchar until next double quote is found) DONE
//  else if (the character is a single quote) DONE
//    (putchar until next single quote is found) DONE
//  else if (the next two characters are //)
//    (skip characters until hitting newline)
//  else if (the next character two characters are /*)
//    (skip characters until next two characters are */)
//  else
//    (putchar)

int main() {
  char c, tmp, c2;
  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      putchar(c);
    } else if (c == '"') {
      putchar(c); // put the first "
      while ((c = getchar()) != '"') {
        putchar(c);
      }
      putchar(c); // put the last "
    } else if (c == '\'') {
      putchar(c); // put the first '
      while ((c = getchar()) != '\'') {
        putchar(c);
      }
      putchar(c); // put the last '
    } else if (c == '/') {
      tmp = getchar();
      if (tmp == '/') {
        while ((c = getchar()) != '\n') {
          //pass
        }
      } else if (tmp == '*') {
        while ((c == getchar()) != '/') {
          //pass
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
