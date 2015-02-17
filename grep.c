#include <stdio.h>
#include <string.h>
#define MAX_LINE_LEN 1024


int getLine(char *s, int max_len) {
  int i;
  char c;
  for (i = 0; (c = getchar()) != EOF && c != '\n' && i < max_len - 2; ++i) {
    *s++ = c;
  }
  if (c == '\n')
    *s++ = c;
  *s = '\0';
  if (c == EOF)
    return EOF;
  return i;
}


// grep -n -x foo
// grep -nx foo
int main(int argc, char *argv[]) {
  int i, linecount;
  char s[MAX_LINE_LEN];
  int number = 0;
  int exclude = 0;
  int unknown = 0;
  while (--argc > 0 && (*++argv)[0] == '-') {
    i = 1;
    while ((*argv)[i]) {
      switch ((*argv)[i++]) {
        case 'n':
          number = 1;
          break;
        case 'x':
          exclude = 1;
          break;
        default:
          unknown = 1;
          break;
      }
    }
  }
  linecount = 1;
  if (unknown) {
    fprintf(stderr, "Usage: grep -x -n pattern\n");
    return 1;
  } else {
    while ((i = getLine(s, MAX_LINE_LEN)) != EOF) {
      if (strstr(s, *argv) != NULL && !exclude) {
        if (number)
          printf("%d: ", linecount);
        printf("%s", s);
      } else if (exclude && strstr(s, *argv) == NULL) {
        if (number)
          printf("%d: ", linecount);
        printf("%s", s);
      }
      linecount++;
    }
  }
}
