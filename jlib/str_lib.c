#include "str_lib.h"

void swap(char *one, char *two) {
  char tmp = *one;
  *one = *two;
  *two = tmp;
}

int strComp(char s[], char t[]) {
  int i = 0;

  while (1) {
    if (s[i] < t[i])
      return -1;
    else if (s[i] > t[i])
      return 1;
    else if (s[i] == '\0' && t[i] == '\0')
      return 0;
    else
      ++i;
  }
}

void seq(char *a, char *b) {
  assert(strComp(a, b) == 0);
}

unsigned strlen2(char s[]) {
  int i = 0;
  while (s[i] != '\0') {
    if (i >= MAX_STR_SIZE)
      return -1;
    ++i;
  }
  return i;
}

void reverse2(char s[]) {
  int i, j;
  int len = strlen2(s);

  for (i = 0, j = len - 1; i < j; ++i, --j) {
    swap(&s[i], &s[j]);
  }
}

void squeeze(char s[], int c) {
  int i, j;

  for (i = j = 0; s[i] != '\0'; i++) {
    if (s[i] != c) {
      s[j++] = s[i];
    }
  }
  s[j] = '\0';
}

int strln(char one[]) {
  int i = 0;
  while (one[i] != '\0')
    ++i;
  return i;
}

char lower(int c) {
  return (c >= 'A' && c <= 'Z') ? c - 'A' + 'a': c;
}

void lowerAll(char c[]) {
  int i;
  for (i = 0; c[i] != '\0'; ++i)
    c[i] = lower(c[i]);
}

void print10Char(char s[]) {
  int i;
  for (i = 0; i < strln(s); ++i) {
    printf("%c%c", s[i], ((i + 1)  % 10 == 0) ? '\n' : '\t');
  }
  printf("\n");
}
