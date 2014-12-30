#include <stdio.h>
#include <assert.h>
#define MAX_STR_LEN 1000

int getln(char s[], int limit);
int strln(char s[]);
void reverse(char s[]);
void swap(char *first, char *second);


void fillArray(char s[], int limit) {
  while (--limit >= 0) {
    s[limit] = '\0';
  }
}

int main() {
  char s[MAX_STR_LEN];
  int i;
  fillArray(s, MAX_STR_LEN);
  while ((i = getln(s, MAX_STR_LEN)) >= 0) {
    reverse(s);
    printf("%s\n", s);
  }
  return 0;
}

// Read line into a string literal (character array)
int getln(char s[], int limit) {
  char c;
  int cnt;
  for (cnt = 0; (c = getchar()) != '\n' && cnt <= limit; ++cnt) {
    s[cnt] = c;
  }
  s[cnt] = '\0';
  return cnt;
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
