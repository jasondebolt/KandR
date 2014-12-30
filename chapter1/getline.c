#include <stdio.h>
#define MAX_LINE_LENGTH 100

int getlin(char s[], int max);
void copy(char to[], char from[]);

int main() {
  int len, max;
  char vals[MAX_LINE_LENGTH];
  char longest[MAX_LINE_LENGTH];

  max = 0;
  while ((len = getlin(vals, MAX_LINE_LENGTH)) > 0) {
    if (len > max) {
      max = len;
      copy(longest, vals);
    }
  }
  printf("%s\n", longest);
  return 0;
}

// Read input into a char array.
int getlin(char s[], int max) {
  int c, len;
  len = 0;

  while ((c = getchar()) != '\n') {
    s[len++] = c;
  }
  s[len] = '\0';
  return len; 
}

void copy(char to[], char from[]) {
  int i;
  i = 0;
  while ((to[i++] = from[i]) != '\0');
}
