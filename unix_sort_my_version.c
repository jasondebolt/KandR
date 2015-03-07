#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define MAX_LINE_LEN 1024
#define MAX_DELTA 0.0000000001
#define MAX_LINES 10000
#define MAX_FIELD_NUM 1024
#define MAX_BUF_LEN MAX_LINE_LEN * MAX_LINES
#define MAX_LINE_STORE MAX_LINES * 100
#define DEBUG 0

typedef int (*COMP)(void *, void *, int, int, int);

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

char * skipUntilLetterNumberBlankOrNull(char *c) {
  // We check for null to ensure we do not go beyond the end of the string.
  while (!isLetterNumberBlank(*c) && *c != '\0') {
    ++c;
  }
  return c;
}

int strCompFold(char *a, char *b, int reverse, int folding, int directory) {
  if (directory) {
    a = skipUntilLetterNumberBlankOrNull(a);
    b = skipUntilLetterNumberBlankOrNull(b);
  }
  if (folding) {
    while (toLower(*a) == toLower(*b) && *a != '\0') {
      a++;
      b++;
      if (directory) {
        a = skipUntilLetterNumberBlankOrNull(a);
        b = skipUntilLetterNumberBlankOrNull(b);
      }
    }
    return (reverse) ? toLower(*b) - toLower(*a) : toLower(*a) - toLower(*b);
  } else {
    while (*a == *b && *a != '\0') {
      a++;
      b++;
      if (directory) {
        a = skipUntilLetterNumberBlankOrNull(a);
        b = skipUntilLetterNumberBlankOrNull(b);
      }
    }
    return (reverse) ? *b - *a : *a - *b;
  }
}

int strComp(char *a, char *b, int reverse, int folding, int directory) {
  return strCompFold(a, b, reverse, folding, directory);
}


int strFieldComp(char *a, char *b, int folding, int reverse, int directory) {
  if (directory) {
    a = skipUntilLetterNumberBlankOrNull(a);
    b = skipUntilLetterNumberBlankOrNull(b);
  }
  if (folding) {
    while (toLower(*a) == toLower(*b) && *a != '\0' && *a != ' ') {
      a++;
      b++;
      if (directory) {
        a = skipUntilLetterNumberBlankOrNull(a);
        b = skipUntilLetterNumberBlankOrNull(b);
      }
    }
    return (reverse) ? toLower(*b) - toLower(*a) : toLower(*a) - toLower(*b);
  } else {
    while (*a == *b && *a != '\0' && *a != ' ') {
      a++;
      b++;
      if (directory) {
        a = skipUntilLetterNumberBlankOrNull(a);
        b = skipUntilLetterNumberBlankOrNull(b);
      }
    }
    return (reverse) ? *b - *a : *a - *b;
  }
}

int numFieldComp(char *a, char *b, int folding, int reverse, int directory) {
  // Skip whitespace.
  while (*a == ' ' || *a == '\t')
    a++;
  while (*b == ' ' || *a == '\t')
    b++;
  int a_negative, b_negative;
  a_negative = b_negative = 0;
  if (*a == '-') {
    a_negative = 1;
    a++;
  }
  if (*b == '-') {
    b_negative = 1;
    b++;
  }
  if (directory) {
    // Implement sqeeze.
    char *a_start = a;
    char *a_numbers_only = a;
    while (*a != '\0' && *a != ' ') {
      if ((*a >= '0' && *a <= '9') || *a == '.') {
        *a_numbers_only++ = *a;
      }
      a++;
    }
    *a_numbers_only = '\0';
    a = a_start;
    // Implement sqeeze.
    char *b_start = b;
    char *b_numbers_only = b;
    while (*b != '\0' && *b != ' ') {
      if ((*b >= '0' && *b <= '9') || *b == '.') {
        *b_numbers_only++ = *b;
      }
      b++;
    }
    *b_numbers_only = '\0';
    b = b_start;
  }
  double result = atof(a) - atof(b);
  double a_result = (result < 0) ? -1 * result : result;
  if (a_result < MAX_DELTA || result == 0) {
    return 0;
  } else if (result < 0) {
    return (reverse) ? 1 : -1;
  } else {
    return (reverse) ? -1 : 1;
  }
}

// field_num is 0 indexed.
int compAnyField(const char *a, const char *b, int field_num, int numeric,
    int folding, int reverse, int directory) {

  COMP comp = (COMP) ((numeric) ? numFieldComp : strFieldComp);
  // skip intial whitespace.
  while (*a == ' ')
    a++;
  while (*b == ' ')
    b++;

  while (--field_num >= 0) {
    while (*a != ' ' && *a != '\0')
      a++;
    while (*b != ' ' && *b != '\0')
      b++;

    // Handle case of either string not having enough fields before field_num.
    if (*a == '\0' || *b == '\0')
      return *a - *b; // A string without enough fields will be place before.

    // skip white space between fields.
    while (*a == ' ' && *a != '\0')
      ++a;
    while (*b == ' ' && *b != '\0')
      ++b;
  }
  if (DEBUG)
    printf("%s Comparing a: %s, to b: %s\n", (numeric) ? "Num" : "Str", a, b);

  // Finally, we compare.
  return comp((void *)a, (void *)b, folding, reverse, directory);
}

// Sets flags based on an argv field string like "-5nr".
void setFlagsFromArgv(
    char *argv2, int *field_num, int *numeric, int *folding, int *reverse,
    int *directory) {
    if (*argv2 != '-')
      fprintf(stderr, "Field argument must start with a dash.");

    // skip dash.
    argv2++;
    if (!(*argv2 >= '0' || *argv2 <= '9'))
      fprintf(stderr, "field number is required.");

    char num[MAX_FIELD_NUM];
    char *num_p = num;
    while (*argv2 >= '0' && *argv2 <= '9') {
      *num_p++ = *argv2++;
    }
    *num_p = '\0';
    *field_num = (int) atof(num);

    while (*argv2) {
      switch (*argv2) {
        case 'n':
          *numeric = 1;
          break;
        case 'f':
          *folding = 1;
          break;
        case 'r':
          *reverse = 1;
          break;
        case 'd':
          *directory= 1;
          break;
      }
      argv2++;
    }
}

// *argv may be something like "./a.out -F -0rf -1nd -4rn
int badAssCompare(const char *a, const char *b, int argc, char *argv[]) {
  int field_num, numeric, folding, reverse, directory;
  int comp_result;
  while (--argc > 0) {
    field_num = numeric = folding = reverse = directory = 0;
    char *argv2 = *++argv;
    // Skip "-F" field.
    if (strcmp(argv2, "-F") == 0) {
      continue;
    }
    setFlagsFromArgv(argv2, &field_num, &numeric, &folding, &reverse, &directory);
    if ((comp_result = compAnyField(
        a, b, field_num, numeric, folding, reverse, directory)) != 0) {
      if (DEBUG)
        printf("comp_result is %d, returning.\n", comp_result);
      return comp_result;
    }
    if (DEBUG)
      printf("comp_result is %d, continuing.\n", comp_result);
  }
  return 0;
}

int strCompFirstField(const char *a, const char *b, int folding,
    int reverse, int directory) {
  while (*a == *b && *a != '\0' && *a != ' ') {
    ++a;
    ++b;
  }
  return *a - *b;
}


int strCompSecondField(const char *a, const char *b, int folding,
    int reverse, int directory) {
  // skip intial whitespace.
  while (*a == ' ')
    a++;
  while (*b == ' ')
    b++;

  // skip first field.
  while (*a != ' ' && *a != '\0')
    a++;
  while (*b != ' ' && *b != '\0')
    b++;

  // Handle case of either string not having a second field.
  if (*a == '\0' || *b == '\0')
    return *a - *b;

  ++a, ++b; // skip white space.
  while (*a == *b && *a != '\0' && *a != ' ')
    ++a, ++b;
  return *a - *b;
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

void QuickSortMulti(void *vals[], int low, int high, int argc, char *argv[]) {
  if (high <= low)
    return;
  int mid = (low + high) / 2;
  int k, i;
  SwapGeneric((void **) vals, low, mid);
  for (k = low, i = low + 1; i <= high; ++i) {
    if (badAssCompare(vals[i], vals[low], argc, argv) < 0)
      SwapGeneric((void **) vals, ++k, i);
  }
  SwapGeneric((void **) vals, k, low);
  QuickSortMulti((void **) vals, low, k - 1, argc, argv);
  QuickSortMulti((void **) vals, k + 1, high, argc, argv);
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

void testStrCompFirstField() {
  char first[MAX_LINE_LEN] = "ccc ddd";
  char second[MAX_LINE_LEN] = "aaa bbb";
  assert(strCompFirstField(first, second, 0, 0, 0) > 0);
  assert(strCompFirstField(second, first, 0, 0, 0) < 0);
  assert(strCompFirstField(first, first, 0, 0, 0) == 0);
  assert(strCompFirstField(second, second, 0, 0, 0) == 0);
  printf("strCompFirstField tested.\n");
}

void testStrCompSecondField() {
  char first[MAX_LINE_LEN] = "ccc ddd";
  char second[MAX_LINE_LEN] = "aaa bbb";
  char third[MAX_LINE_LEN] = "aaa ddd";
  char fourth[MAX_LINE_LEN] = "aaa abcd";
  char fifth[MAX_LINE_LEN] = "zoo aaa";
  char sixth[MAX_LINE_LEN] = "zoo";
  char seventh[MAX_LINE_LEN] = "     one ddd";
  assert(strCompSecondField(first, third, 0, 0, 0) == 0);
  assert(strCompSecondField(first, second, 0, 0, 0) > 0);
  assert(strCompSecondField(second, third, 0, 0, 0) < 0);
  assert(strCompSecondField(fourth, fifth, 0, 0, 0) > 0);
  assert(strCompSecondField(fifth, sixth, 0, 0, 0) > 0);
  assert(strCompSecondField(sixth, fifth, 0, 0, 0) < 0);
  assert(strCompSecondField(first, seventh, 0, 0, 0) == 0);
  printf("strCompSecondField tested.\n");
}

void testCompAnyFieldWithString() {
  char zeroth[MAX_LINE_LEN] = "cc";
  char first[MAX_LINE_LEN] = "ccc ddd ggg hhh nnn";
  char second[MAX_LINE_LEN] = "aaa bbb jjj kkk ccc";
  assert(compAnyField(zeroth, first, 0, 0, 0, 0, 0) < 0);
  assert(compAnyField(zeroth, first, 4, 0, 0, 0, 0) < 0);
  assert(compAnyField(first, second, 0, 0, 0, 0, 0) > 0);
  assert(compAnyField(first, second, 1, 0, 0, 0, 0) > 0);
  assert(compAnyField(first, second, 2, 0, 0, 0, 0) < 0);
  assert(compAnyField(first, second, 3, 0, 0, 0, 0) < 0);
  assert(compAnyField(first, second, 4, 0, 0, 0, 0) > 0);
  printf("compAnyField with string tested.\n");
}

void testCompAnyFieldWithNumber() {
  char first[MAX_LINE_LEN] = "123.456 888.999";
  char second[MAX_LINE_LEN] = "123.456 111.444";
  char third[MAX_LINE_LEN] = "01";
  char fourth[MAX_LINE_LEN] = "1925071251257125.94875987298752525247082623 14";
  char fifth[MAX_LINE_LEN] = "1925071251257125.94875987298752525247082623 29.14";
  char sixth[MAX_LINE_LEN] = "11";
  char seventh[MAX_LINE_LEN] = "100";
  assert(compAnyField(first, second, 0, 1, 0, 0, 0) == 0);
  assert(compAnyField(first, second, 1, 1, 0, 0, 0) > 0);
  assert(compAnyField(first, third,  0, 1, 0, 0, 0) > 0);
  assert(compAnyField(fourth, fifth, 0, 1, 0, 0, 0) == 0);
  assert(compAnyField(fourth, fifth, 1, 1, 0, 0, 0) < 0);
  assert(compAnyField(sixth, seventh, 0, 1, 0, 0, 0) < 0);
  printf("compAnyField with number tested.\n");
}

void testSetFlagsFromArgv() {
  int field_num, numeric, folding, reverse, directory;

  field_num = numeric = folding = reverse = directory = 0;
  setFlagsFromArgv("-0rn", &field_num, &numeric, &folding, &reverse, &directory);
  assert(field_num == 0 && numeric && !folding && reverse && !directory);

  field_num = numeric = folding = reverse = directory = 0;
  setFlagsFromArgv("-6rnfd", &field_num, &numeric, &folding, &reverse, &directory);
  assert(field_num == 6 && numeric && folding && reverse && directory);

  field_num = numeric = folding = reverse = directory = 0;
  setFlagsFromArgv("-13d", &field_num, &numeric, &folding, &reverse, &directory);
  assert(field_num == 13 && !numeric && !folding && !reverse && directory);

  field_num = numeric = folding = reverse = directory = 0;
  setFlagsFromArgv("-28rdf", &field_num, &numeric, &folding, &reverse, &directory);
  assert(field_num == 28 && !numeric && folding && reverse && directory);

  field_num = numeric = folding = reverse = directory = 0;
  setFlagsFromArgv("-0", &field_num, &numeric, &folding, &reverse, &directory);
  assert(field_num == 0 && !numeric && !folding && !reverse && !directory);

  printf("setFlagsFromArgv tested.\n");
}

void testNumFieldComp() {
  char first[MAX_LINE_LEN] = "333";
  char second[MAX_LINE_LEN] = "/Ejasonblah2/22/2";
  char third[MAX_LINE_LEN] = "  bbb333   ";
  char fourth[MAX_LINE_LEN] = "    BBB/2/2/2/2 ";
  assert(numFieldComp(first, second, 0, 0, 1) < 0);
  assert(numFieldComp(third, fourth, 0, 0, 1) < 0);
  printf("numFieldComp tested.\n");
}

void testBadAssCompare() {
  char first[MAX_LINE_LEN] = "ccc 123";
  char second[MAX_LINE_LEN] = "bbb 2/22";
  char third[MAX_LINE_LEN] = "BBB 333";
  char fourth[MAX_LINE_LEN] = "aaa 123";
  char *argv[MAX_LINE_LEN] = {"./a.out", "-F", "-0rf", "-1nd"};
  assert(badAssCompare(first, second, 4, argv) < 0);
  assert(badAssCompare(second, third, 4, argv) < 0);
  assert(badAssCompare(third, fourth, 4, argv) < 0);
  // Sort first by second column numeric/directory, then by first
  // colum string reverse folding.
  // "ccc 123"       "ccc 123"
  // "bbb 2/22" -->  "aaa 123"
  // "BBB 333";      "bbb 2/22"
  // "aaa 123";      "BBB 333"
  char *argv2[MAX_LINE_LEN] = {"./a.out", "-F", "-1nd", "-0rf"};
  assert(badAssCompare(first, fourth, 4, argv2) < 0);
  assert(badAssCompare(fourth, second, 4, argv2) < 0);
  assert(badAssCompare(second, third, 4, argv2) < 0);

  char first_2[MAX_LINE_LEN] =  "a b c g e p/ ;t 23 c()";
  char second_2[MAX_LINE_LEN] = "d a i g r (P T$ 23 &c[]";

  char *argv4[MAX_LINE_LEN] = {"./a.out", "-F", "-0"};
  assert(badAssCompare(first_2, second_2, 3, argv4) < 0);

  char *argv5[MAX_LINE_LEN] = {"./a.out", "-F", "-1"};
  assert(badAssCompare(second_2, first_2, 3, argv5) < 0);

  char *argv6[MAX_LINE_LEN] = {"./a.out", "-F", "-0r"};
  assert(badAssCompare(second_2, first_2, 3, argv6) < 0);

  char *argv7[MAX_LINE_LEN] = {"./a.out", "-F", "-3"};
  assert(badAssCompare(first_2, second_2, 3, argv7) == 0);

  char *argv8[MAX_LINE_LEN] = {"./a.out", "-F", "-3", "-4"};
  assert(badAssCompare(first_2, second_2, 4, argv8) < 0);

  char *argv9[MAX_LINE_LEN] = {"./a.out", "-F", "-3", "-7"};
  assert(badAssCompare(first_2, second_2, 4, argv9) == 0);

  char *argv10[MAX_LINE_LEN] = {"./a.out", "-F", "-3", "-5df", "-6df", "-7"};
  assert(badAssCompare(first_2, second_2, 6, argv10) == 0);

  char *argv11[MAX_LINE_LEN] = {"./a.out", "-F", "-7", "-6df", "-5df", "-3"};
  assert(badAssCompare(first_2, second_2, 6, argv11) == 0);

  char *argv12[MAX_LINE_LEN] = {"./a.out", "-F", "-8d"};
  assert(badAssCompare(first_2, second_2, 3, argv12) == 0);

  char first_1[MAX_LINE_LEN] = "k t c() 4 /g";
  char second_1[MAX_LINE_LEN] = "j l &c[] - ;G";
  char *argv3[MAX_LINE_LEN] = {"./a.out", "-F", "-2d", "-4df"};
  assert(badAssCompare(first_1, second_1, 4, argv3) == 0);

  char first_3[MAX_LINE_LEN] =  "a    b     c   g   e   p/   ;t   23  c()";
  char second_3[MAX_LINE_LEN] = "d a i g r (P T$ 23 &c[]";

  char *argv38[MAX_LINE_LEN] = {"./a.out", "-F", "-0"};
  assert(badAssCompare(first_3, second_3, 3, argv38) < 0);

  char *argv39[MAX_LINE_LEN] = {"./a.out", "-F", "-1"};
  assert(badAssCompare(second_3, first_3, 3, argv39) < 0);

  printf("badAssCompare tested.\n");
}


// USAGE: ./a.out
// ./a.out -nrrf
// ./a.out -n -r -f -d
void UnixSortTest(int argc, char *argv[]) {
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
  testUnixSortGeneric(comp, reverse, folding, directory);
  printf("Unix sort tested.\n");
}

void MultiFieldUnixSortTest(int argc, char *argv[]) {
  char *g[MAX_LINES];
  char linestore[MAX_LINE_STORE];
  size_t len;
  len = ReadLinesFaster(g, linestore, MAX_LINES);
  QuickSortMulti((void **) g, 0, len - 1, argc, argv);
  WriteLines(g, len);
  printf("\nMulti fiel unix sort tested.\n");
}

void BaseTests() {
  // Interactive tests...
  //testReadLine();
  //testReadLines();
  //testWriteLine();
  //testWriteLines();
  //testUnixSort();
  testAlloc();
  testQuickSortStrings();
  testSwapGeneric();
  testNumComp();
  testAtof();
  testQuickSort();
  testStrCompFold();
  testToLower();
  testStrCompFirstField();
  testStrCompSecondField();
  testCompAnyFieldWithString();
  testCompAnyFieldWithNumber();
  testSetFlagsFromArgv();
  testNumFieldComp();
  testBadAssCompare();
  printf("Base tests tested.\n");
}

/* USAGE:
 * d: directory (ignore any chars that are not letters, numbers, or whitespace)
 * f: fold: (ignore case)
 * n: numeric: (sort numerically, convert string to double)
 * r: reverse: (reverse sort)
 *
 *   For UnixSort:
 *     ./a.out -nrrf
 *     ./a.out -n -r -f -d
 *
 *   For MultiFieldUnixSort:
 *     ./a.out -F -0nr  // First field numeric reverse sort.
 *     ./a.out -F -1df  // Second field ignore non-alphanumeric/case chars sort.
 *     ./a.out -F -7n -5df -3d -0rn // Sort by 8th field numeric, then by 6th
 *                                  // field directory folding, then by 4th
 *                                  // field directory, then by first field
 *                                  // numeric reverse order.
 */
int main(int argc, char *argv[]) {
  //BaseTests();
  //UnixSortTest(argc, argv);
  // TODO(jason): Handle delimeter types other than blank space(s).
  // TODO(jason): When using comma as a delimeter, handle
  //              double optional quote delimited fields by default (jason "De Bolt")
  //              (See the fake_data_with_quotes.csv and
  //               fake_data_with_optional_quotes.csv files) The last field in
  //               latter file has optional quotes.
  // TODO(jason): Handle sorting dates in mm/dd/yyyy forat (hard to do)
  if (argc == 1 || strcmp(argv[1], "-F") != 0 ) {
    printf("./a.out -F -0nr  // First field numeric reverse sort.\n");
    printf("./a.out -F -1df  // Second field ignore non-alphanumeric/case chars sort.\n");
    printf("./a.out -F -7n -5df -3d -0rn // Sort by 8th field numeric, then by 6th\n");
    printf("                             // field directory folding, then by 4th\n");
    printf("                             // field directory, then by first field\n");
    printf("                                  // numeric reverse order.\n");
    printf("cat {file} | ./a.out -F -0\n");
  } else {
    MultiFieldUnixSortTest(argc, argv);
  }
}
