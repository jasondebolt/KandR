#include <stdio.h>
#define INSIDE 1
#define OUTSIDE 0

static int paren_state = OUTSIDE;
static int bracket_state = OUTSIDE;
static int brace_state = OUTSIDE;
static int single_quote_state = OUTSIDE;
static int double_quote_state = OUTSIDE;
static int multi_comment_state = OUTSIDE;
static int comment_state = OUTSIDE;

int insideSingleQuoteString() {
  return single_quote_state == INSIDE;
}

int insideDoubleQuoteString() {
  return double_quote_state == INSIDE;
}

int insideString() {
  return insideSingleQuoteString() || insideDoubleQuoteString();
}

int insideComment() {
  return multi_comment_state == INSIDE || comment_state == INSIDE;
}

int insideCode() {
  return !insideString() && !insideComment();
}

void escape(char c) {
  if (c == '\\') {
    putchar(c);
    putchar(getchar());
  } else {
    putchar(c);
  }
}

void setSingleQuoteState(char s) {
  if (!insideComment() && !insideDoubleQuoteString()) {
    if (single_quote_state == INSIDE) {
      single_quote_state = OUTSIDE;
    } else {
      single_quote_state = INSIDE;
    }
  }
  putchar(s);
}

void setDoubleQuoteState(char s){
  if (!insideComment() && !insideSingleQuoteString()){
    if (double_quote_state == INSIDE){
      double_quote_state = OUTSIDE;
    } else {
      double_quote_state = INSIDE;
    }
  }
  putchar(s);
}

void maybeStartComment(char s){
  char s_next = getchar();
  if (!insideComment() && !insideString()) {
    if (s_next == '/') {
      comment_state = INSIDE;
    } else if (s_next == '*') {
      multi_comment_state = INSIDE;
    }
  }
  putchar(s);
  putchar(s_next);
}

void maybeEndComment(char s) {
  char s_next = getchar();
  if (multi_comment_state == INSIDE) {
    if (s_next == '/'){
      multi_comment_state = OUTSIDE;
    }
  }
  putchar(s);
  putchar(s_next);
}

int main(){
  char c, tmp;
  int p1, p2, c1, c2, b1, b2;

  p1 = p2 = c1 = c2 = b1 = b2 = 0;

  while((c = getchar()) != EOF) {
    if (c == '\'') {
      setSingleQuoteState(c);
    } else if (c == '"') {
      setDoubleQuoteState(c);
    } else if (insideString()) {
      escape(c);
    } else if (c == '/') {
      maybeStartComment(c);
    } else if (c == '*') {
      maybeEndComment(c);
    } else if (c == '\n' && comment_state == INSIDE) {
      comment_state = OUTSIDE;
      putchar(c);
    } else {
      if (insideCode()) {
        if (c == '(')
          ++p1;
        else if (c == ')')
          ++p2;
        else if (c == '{')
          ++c1;
        else if (c == '}')
          ++c2;
        else if (c == '[')
          ++b1;
        else if (c == ']')
          ++b2;
      putchar(c);
      }
    }
  }
  if (p1 != p2 || c1 != c2 || b1 != b2 || insideString() || insideComment()) {
    printf("\nERROR\n");
    return -1;
  } else {
    printf("\nSUCCESS\n");
  }
  return 0;
}
