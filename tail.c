#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LEN 1024
#define MAX_LINES 10000


// Returns the length of a single line, or EOF.
int getLine(char *s, int maxlen) {
  char c;
  int line_count = 0;
  while ((c = getchar()) != '\n' && c != EOF && line_count < maxlen - 2) {
    *s++ = c;
    ++line_count;
  }
  if (c == '\n') {
    *s++ = c;
    ++line_count;
  }
  *s++ = '\0';
  if (c == EOF) {
    return EOF;
  }
  return line_count;
}


// Returns the number of lines.
int getLines(char *lines[], int maxlines) {
  int num_lines = 0;
  int line_len;
  char s[MAX_LINE_LEN];
  while ((line_len = getLine(s, MAX_LINE_LEN)) != EOF && num_lines < maxlines) {
    char *s2 = (char *) malloc(sizeof(char) * line_len + 1);
    strcpy(s2, s);
    *lines++ = s2;
    ++num_lines;
  }
  return num_lines;
}


// USAGE: my_tail -10
// cat some_file | my_tail -10
int main(int argc, char *argv[]) {
  char *lines[MAX_LINES];
  char **lines_ptr = lines;
  int tail_num = 10;
  if (argc > 1)
    tail_num = atoi(++argv[1]);
  int line_count;
  int num_lines_to_skip;
  line_count = getLines(lines, MAX_LINES);
  num_lines_to_skip = line_count - tail_num;
  while (--num_lines_to_skip >= 0) {
    ++lines_ptr;
  }
  while (--tail_num >= 0)
    printf("%s", *lines_ptr++);
}
