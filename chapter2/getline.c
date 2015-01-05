#include <stdio.h>
#define MAX_LINE_LEN 1000


int getln(char s[], int lim) {
  int c, i;
  for (i = 0; i < lim && (c = getchar()) != EOF && c != '\n'; i++) {
    s[i] = c;
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
