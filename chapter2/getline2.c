#include <stdio.h>
#define MAX_LINE_LEN 1000

int getln(char s[], int lim) {
  int c, i;

  i = 0;
  while (1) {
    c = getchar();
    if (i >= lim)
      break;
    else if (c == EOF)
      break;
    else if (c == '\n')
      break;
    else
      s[i] = c;
      ++i;
  }
  s[i] = '\0';
  return i;
}

int main() {
  char line[MAX_LINE_LEN];
  int i;

  while ((i = getln(line, MAX_LINE_LEN)) >= 0) {
    printf("%s\tlen:%d\n", line, i);
  }
  return 0;
}
