#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000 /* max #lines to be sorted. */

char *lineptr[MAXLINES];  /* pointers to text line */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void swap(char *v[], int i, int j) {
  char *tmp =  v[i];
  v[i] = v[j];
  v[j] = tmp;
}

/* qsort2: sort v[left]...v[right] into increasing order */
void qsort2(char *v[], int left, int right) {
  int i, last;

  if (left >= right)  /* Do nothing if array contains */
    return;            /* fewer than two elements. */

  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++) {
    if (strcmp(v[i], v[left]) < 0)
      swap(v, ++last, i);
  }
  swap(v, left, last);
  qsort2(v, left, last - 1);
  qsort2(v, last + 1, right);
}


#define MAXLEN 1000   /* max length of any input line */
int getline2(char *line, int maxlen) {
  char c;
  char *start = line;
  while((c = getchar()) != '\n' && c != EOF && line - start < maxlen) {
    *line++ = c;
  }
  // Notice that no newline is appended for EOF
  if (c == '\n')
    *line++ = c;
  *line = '\0';
  return line - start;
}

#define BUFSIZE 1024
static char allocbuf[BUFSIZE];
static char *allocp = allocbuf;

char *alloc2(int n) {
  if (n <= allocbuf + BUFSIZE - allocp) {
    allocp += n;
    return (allocp - n);
  } else {
    fprintf(stderr, "Not enough space.\n");
    exit(1);
  }
}

void free2(char *c) {
  if (c >= allocbuf && c < allocbuf + BUFSIZE) {
    allocp = c;
  } else {
    fprintf(stderr, "Pointer not within range.\n");
    exit(1);
  }
}


/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while ((len = getline2(line, MAXLEN)) > 0) {
    if (nlines >= maxlines || (p = alloc2(len)) == NULL) {
      return -1;
    } else {
      line[len-1] = '\0'; /* delete newline */
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  }
  return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
  int i;
  for (i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
}

/* sort input lins */
main() {
  int nlines;   /* number of input lnies read */

  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    qsort2(lineptr, 0, nlines - 1);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return 1;
  }
}
