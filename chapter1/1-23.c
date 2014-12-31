#include <stdio.h>
#define INSIDE_COMMENT 1
#define NOT_INSIDE_COMMENT 0

static int state = NOT_INSIDE_COMMENT;

for (every character in the file)
  if (the character is a double quote)
    (putchar until next double quote is found)
  else if (the character is a single quote)
    (putchar until next single quote is found)
  else if (the character starts with /)
    if (the next character is /)
      (state = INSIDE_COMMENT
      (if newline is encountered, putchar it)
      (skip character until hitting newline)
    else if (the next character is *)
      (state = INSIDE_COMMENT
      (if newline is encountered, putchar it)
      (skip character until hitting /)
  else
    (putchar)

/*
*/
int main() {
  printf(
}
