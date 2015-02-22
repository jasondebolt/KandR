#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define MAX_LINE_LEN 1024
#define MAX_LINES 10000
#define MAX_BUF_LEN MAX_LINE_LEN * MAX_LINES
#define MAX_LINE_STORE MAX_LINES * 100

static char buf[MAX_BUF_LEN];
static char *bufp = buf;

int isUpper(char c) {
  return c <= 'Z' && c >= 'A';
}

int isLower(char c) {
  return c <= 'z' && c >= 'a';
}

int isNumber(char c) {
  return c <= '9' && c >= '0';
}

int isBlank(char c) {
  return c == ' ';
}

int isLetterNumberBlank(char c) {
  return isUpper(c) || isLower(c) || isNumber(c) || isBlank(c);
}

char toLower(char c) {
  if (isUpper(c)) {
    return c + 'a' - 'A';
  }
  return c;
}

int numComp(char *a, char *b, int reverse, int folding, int directory) {
  double one = atof(a);
  double two = atof(b);
  if (one < two) {
    return (reverse) ? 1: -1;
  } else if (one > two) {
    return (reverse) ? -1 : 1;
  }
  return 0;
}

char * skipUntilLetterNumberBlank(char *c) {
  while (!isLetterNumberBlank(*c)) {
    ++c;
  }
  return c;
}

int strCompFold(char *a, char *b, int reverse, int folding, int directory) {
  if (directory) {
    a = skipUntilLetterNumberBlank(a);
    b = skipUntilLetterNumberBlank(b);
  }
  if (folding) {
    while (toLower(*a) == toLower(*b) && *a != '\0') {
      a++;
      b++;
      if (directory) {
        a = skipUntilLetterNumberBlank(a);
        b = skipUntilLetterNumberBlank(b);
      }
    }
    return (reverse) ? toLower(*b) - toLower(*a) : toLower(*a) - toLower(*b);
  } else {
    while (*a == *b && *a != '\0') {
      a++;
      b++;
      if (directory) {
        a = skipUntilLetterNumberBlank(a);
        b = skipUntilLetterNumberBlank(b);
      }
    }
    return (reverse) ? *b - *a : *a - *b;
  }
}


int strComp(char *a, char *b, int reverse, int folding, int directory) {
  return strCompFold(a, b, reverse, folding, directory);
}

char *alloc2(size_t len) {
  if (bufp + len <= buf + MAX_BUF_LEN) {
    bufp += len;
    return bufp - len;
  } else {
    fprintf(stderr, "Not enough buffer space.");
    return NULL;
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


void WriteLine(char *s) {
  printf("%s", s);
}


int WriteLines(char **s, size_t len) {
  int i;
  for (i = 0; i < len; ++i) {
    WriteLine(*s++);
  }
  return i;
}

void swapCharPtr(char **a, char **b) {
  char *tmp = *a;
  *a = *b;
  *b = tmp;
}

void SwapGeneric(void *vals[], int a, int b) {
  void *tmp = vals[a];
  vals[a] = vals[b];
  vals[b] = tmp;
}

void QuickSort(void *vals[], int low, int high,
    int (*comp)(void *, void *, int, int, int), int reverse,
    int folding, int directory) {
  if (high <= low)
    return;
  int mid = (low + high) / 2;
  int k, i;
  SwapGeneric((void **) vals, low, mid);
  for (k = low, i = low + 1; i <= high; ++i) {
    if ((*comp)(vals[i], vals[low], reverse, folding, directory) < 0)
      SwapGeneric((void **) vals, ++k, i);
  }
  SwapGeneric((void **) vals, k, low);
  QuickSort((void **) vals, low, k - 1, comp, reverse, folding, directory);
  QuickSort((void **) vals, k + 1, high, comp, reverse, folding, directory);
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
  printf("QuickSortStrings tested.\n");
}

void testQuickSort() {
  char *vals[] = {"jason", "brian", "zelda", "stella", "jessica"};
  size_t len = sizeof(vals) / sizeof(vals[0]);
  printStrVals(vals, len);
  QuickSort((void **) vals, 0, len - 1, (int (*)(void *, void *, int, int, int)) strComp, 0, 0, 0);
  printStrVals(vals, len);
  char *vals2[] = {"913.14", "82", "504", "0", "0.01", "123"};
  size_t len2 = sizeof(vals2) / sizeof(vals2[0]);
  QuickSort((void **) vals2, 0, len2 - 1, (int (*)(void *, void *, int, int, int)) numComp, 0, 0, 0);
  printStrVals(vals2, len2);
  printf("QuickSort tested.\n");
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

void testUnixSortGeneric(int (*comp)(void *, void *, int, int, int),
    int reverse, int folding, int directory) {
  char *g[MAX_LINES];
  char linestore[MAX_LINE_STORE];
  size_t len;
  len = ReadLinesFaster(g, linestore, MAX_LINES);
  QuickSort((void **) g, 0, len - 1, comp, reverse, folding, directory);
  WriteLines(g, len);
  printf("\nUnix sort generic tested.\n");
}

void testNumComp() {
  char a[MAX_LINE_LEN], b[MAX_LINE_LEN];
  strcpy(a, "0"), strcpy(b, "0");
  assert(numComp(a, b, 0, 0, 0) == 0);
  strcpy(a, "123.45"), strcpy(b, "123.45");
  assert(numComp(a, b, 0, 0, 0) == 0);
  strcpy(a, "123.444"), strcpy(b, "123.555");
  assert(numComp(a, b, 0, 0, 0) == -1);
  strcpy(a, ".0031"), strcpy(b, ".0000045");
  assert(numComp(a, b, 0, 0, 0) == 1);
  printf("NumComp tested.\n");
}

void testSwapGeneric() {
  char *vals[] = {"one", "two", "three", "four"};
  SwapGeneric((void **) vals, 0, 1);
  assert(strComp(vals[0], "two", 0, 0, 0) == 0);
  assert(strComp(vals[1], "one", 0, 0, 0) == 0);
  int a = 1, b = 2, c = 3, d = 4;
  int *ap = &a, *bp = &b, *cp = &c, *dp = &d;
  int *vals2[] = {ap, bp, cp, dp};
  SwapGeneric((void **) vals2, 2, 3);
  assert(*vals2[2] == 4);
  assert(*vals2[3] == 3);
  printf("Swap generic tested.\n");
}

void testStrCompFold() {
  assert(strCompFold("a", "a", 0, 0, 0) == 0);
  assert(strCompFold("a", "b", 0, 0, 0) == -1);
  assert(strCompFold("b", "a", 0, 0, 0) == 1);
  assert(strCompFold("a", "a", 1, 0, 0) == 0);
  assert(strCompFold("a", "b", 1, 0, 0) == 1);
  assert(strCompFold("b", "a", 1, 0, 0) == -1);
  assert(strCompFold("A", "a", 0, 1, 0) == 0);
  assert(strCompFold("a", "B", 0, 1, 0) == -1);
  assert(strCompFold("B", "a", 0, 1, 0) == 1);
  assert(strCompFold("a", "A", 1, 1, 0) == 0);
  assert(strCompFold("A", "B", 1, 1, 0) == 1);
  assert(strCompFold("B", "a", 1, 1, 0) == -1);
  printf("StrCompFold tested.\n");
}


void testToLower() {
  assert(toLower('A') == 'a');
  assert(toLower('B') == 'b');
  assert(toLower('Z') == 'z');
  assert(toLower('0') == '0');
  assert(toLower('\n') == '\n');
  assert(toLower('\0') == '\0');
  printf("ToLower tested.\n");
}


void testAtof() {
  printf("%f\n", atof("abc"));
  printf("Atof tested.\n");
}


// USAGE: ./a.out
// ./a.out -nr
// ./a.out -n -r
int main(int argc, char *argv[]) {
  int (*comp)(void *, void *, int, int, int);
  comp = (int (*)(void *, void *, int, int, int)) strComp;
  // Handle numeric sort.
  int numeric = 0;
  int reverse = 0;
  int folding = 0;
  int directory = 0;
  for (++argv; --argc > 0; ++argv) {
    if (*argv[0] == '-') {
      (*argv)++;
      while (**argv) {
        if (**argv == 'n') {
          printf("Numeric yes!!!\n");
          numeric = 1;
        } else if (**argv == 'r') {
          printf("Reverse yes!!!\n");
          reverse = 1;
        } else if (**argv == 'f') {
          printf("Folding/Ignore case yes!!!\n");
          folding = 1;
        } else if (**argv == 'd') {
          printf("Directory yes!!!\n");
          directory = 1;
        }
        (*argv)++;
      }
    }
  }
  if (numeric)
    comp = (int (*)(void *, void *, int, int, int)) numComp;
  //testAlloc();
  //testReadLine();
  //testReadLines();
  //testWriteLine();
  //testWriteLines();
  //testQuickSortStrings();
  //testSwapGeneric();
  //testNumComp();
  //testAtof();
  //testQuickSort();
  //testUnixSort();
  testStrCompFold();
  testToLower();
  testUnixSortGeneric(comp, reverse, folding, directory);
}
