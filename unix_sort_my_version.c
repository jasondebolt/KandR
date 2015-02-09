#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LEN 1024
#define MAX_LINES 10000

#define BUF_SIZE MAX_LINE_LEN * MAX_LINES
static char buf[BUF_SIZE];
static char *allocp = buf;

char *alloc2(int len) {
  if (allocp + len <= buf + BUF_SIZE) {
    allocp += len;
    return (allocp - len);
  }
  fprintf(stderr, "Not enough space.");
}

void free2(char *p) {
  if (p >= buf && p <= buf + BUF_SIZE) {
    allocp = p;
  } else {
    fprintf(stderr, "p is not within the alloc buffer.");
  }
}

int ReadLine(char *s, int max) {
  char c;
  int i;
  i = 0;
  while ((c = getchar()) != EOF && c != '\n' && ++i < max) {
    *s++ = c;
  }
  if (c == '\n') {
    *s++ = '\n';
  }
  *s = '\0';
  if (c == EOF) {
    return EOF;
  } else {
    return i;
  }
}

int ReadLines(char *s[]) {
  char line[MAX_LINE_LEN];
  char *buffer;
  int cnt, val;
  while ((cnt = ReadLine(line, MAX_LINE_LEN)) != EOF) {
    buffer = alloc2(MAX_LINE_LEN);
    strcpy(buffer, line);
    *s++ = buffer;
  }
}

void SortLines(char *s[]) {
}

void WriteLines(char *s[]) {
  printf("\n");
  while (*s != NULL)
    printf("%s", *s++);
}

void testReadLine() {
  char s[MAX_LINE_LEN];
  int cnt;
  while ((cnt = ReadLine(s, MAX_LINE_LEN)) != EOF) {
    printf("len: %d...%s", cnt, s);
  }
}

void testAlloc() {
  char *p = alloc2(1024);
  free2(p);
  p = alloc2(1024);
  free2(p);
}

int main() {
  // Interactive test.
  //testReadLine();
  testAlloc();
  char *lines[MAX_LINES];
  ReadLines(lines);
  SortLines(lines);
  WriteLines(lines);
}
