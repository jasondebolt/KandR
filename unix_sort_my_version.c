#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LEN 1024
#define MAX_LINES 10000
#define MAX_BUF_LEN MAX_LINE_LEN * MAX_LINES
#define MAX_LINE_STORE MAX_LINES * 100

static char buf[MAX_BUF_LEN];
static char *bufp = buf;

char *alloc2(size_t len) {
  if (bufp + len <= buf + MAX_BUF_LEN) {
    bufp += len;
    return bufp - len;
  } else {
    fprintf(stderr, "Not enough buffer space.");
  }
}

void free2(char *p) {
  if (p >= buf && p < buf + MAX_BUF_LEN) {
    bufp = p;
  } else {
    fprintf(stderr, "Cannot free: pointer out of range.");
  }
}


int ReadLine(char *s, size_t max_len) {
  char c;
  int i = 0;
  while ((c = getchar()) != '\n' && c != EOF) {
    s[i++] = c;
  }
  if (c == '\n')
    s[i++] = c;
  s[i++] = '\0';
  if (c == EOF)
    return EOF;
  return i;
}

size_t ReadLines(char **g, size_t max_lines) {
  int cnt;
  char s[MAX_LINE_LEN];
  for (cnt = 0; ReadLine(s, MAX_LINE_LEN) != EOF && cnt < max_lines; ++cnt) {
    *g = alloc2(MAX_LINE_LEN);
    strcpy(*g++, s);
  }
  return cnt;
}

size_t ReadLinesFaster(char **g, char *linestore, size_t max_lines) {
  int len, cnt = 0;
  char *p = linestore;
  char s[MAX_LINE_LEN];
  while ((len = ReadLine(s, MAX_LINE_LEN)) != EOF && cnt < max_lines && p + len <= linestore + MAX_LINE_STORE) {
    strcpy(p, s);
    *g++ = p;
    p += len;
    cnt++;
  }
  return cnt;
}


int WriteLine(char *s) {
  printf("%s", s);
}


int WriteLines(char **s, size_t len) {
  int i;
  for (i = 0; i < len; ++i) {
    WriteLine(*s++);
  }
}

void swapCharPtr(char **a, char **b) {
  char *tmp = *a;
  *a = *b;
  *b = tmp;
}

void QuickSortStrings(char *vals[], int low, int high) {
  if (high <= low)
    return;
  int mid = (low + high) / 2;
  int k, i;
  swapCharPtr(&vals[low], &vals[mid]);
  for (k = low, i = low + 1; i <= high; ++i) {
    if (strcmp(vals[i], vals[low]) < 0)
      swapCharPtr(&vals[++k], &vals[i]);
  }
  swapCharPtr(&vals[k], &vals[low]);
  QuickSortStrings(vals, low, k - 1);
  QuickSortStrings(vals, k + 1, high);
}

void testAlloc() {
  char *p = alloc2(MAX_LINES * MAX_LINE_LEN);
  free2(p);
  p = alloc2(MAX_LINES * MAX_LINE_LEN);
  free2(p);
  printf("alloc2 tested.\n");
}

void testReadLine() {
  char s[MAX_LINE_LEN];
  ReadLine(s, MAX_LINE_LEN);
  printf("%s", s);
}

void testReadLines() {
  char **g = calloc(MAX_LINES, sizeof(char *));
  char **gc = g;
  int i;
  size_t len;
  len = ReadLines(g, MAX_LINES);
  for (i = 0; i < len; ++i) {
    printf("%s", *gc++);
  }
}

void testWriteLine() {
  char s[MAX_LINE_LEN];
  ReadLine(s, MAX_LINE_LEN);
  WriteLine(s);
}

void testWriteLines() {
  char **g = calloc(MAX_LINES, sizeof(char *));
  char **gc = g;
  int i;
  size_t len;
  len = ReadLines(g, MAX_LINES);
  WriteLines(g, len);
}

void printStrVals(char *vals[], size_t len) {
  int i;
  for (i = 0; i < len; ++i) {
    printf("%s\t", vals[i]);
  }
  printf("\n");
}

void testQuickSortStrings() {
  char *vals[] = {"jason", "brian", "zelda", "stella", "jessica"};
  size_t len = sizeof(vals) / sizeof(vals[0]);
  printStrVals(vals, len);
  QuickSortStrings(vals, 0, len - 1);
  printStrVals(vals, len);
}

void testUnixSort() {
  char **g = calloc(MAX_LINES, sizeof(char *));
  size_t len;
  len = ReadLines(g, MAX_LINES);
  QuickSortStrings(g, 0, len - 1);
  WriteLines(g, len);
  printf("\nUnix sort tested.\n");
}

void testUnixSortFaster() {
  char *g[MAX_LINES];
  char linestore[MAX_LINE_STORE];
  size_t len;
  len = ReadLinesFaster(g, linestore, MAX_LINES);
  QuickSortStrings(g, 0, len - 1);
  WriteLines(g, len);
  printf("\nUnix sort faster tested.\n");
}

int main() {
  //testAlloc();
  //testReadLine();
  //testReadLines();
  //testWriteLine();
  //testWriteLines();
  //testQuickSortStrings();
  //testUnixSort();
  testUnixSortFaster();
}
