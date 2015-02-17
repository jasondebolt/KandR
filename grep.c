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

int main(int argc, char *argv[]) {
  int i;
  char s[MAX_LINE_LEN];
  if (argc != 2) {
    printf("USAGE: grep {search term}\n");
  } else {
    while ((i = getLine(s, MAX_LINE_LEN)) != EOF) {
      if (strstr(s, argv[1]) != NULL) {
        printf("%s", s);
      }
    }
  }
}
