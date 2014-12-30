#include <stdio.h>
#include <assert.h>

void reverse(char s[]);
int strln(char s[]);
void swap(char *first, char *second);

int main() {
  char s[] = "jason was here";
  reverse(s);
  printf("%s\n", s);
  return 0;
}

void reverse(char s[]) {
  int i, len;
  for (i = 0, len=strln(s) - 1; i <= len; i++, len--) {
    swap(&s[i], &s[len]);
  }
}

void swap(char * first, char * second) {
  int tmp = *first;
  *first = *second;
  *second = tmp;
}

int strln(char s[]) {
  int len = 0;
  while (s[len] != '\0') {
    ++len;
  }
  return len;
}
