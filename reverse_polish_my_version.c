#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAX_STR_SIZE 1024

int isDigit(char c) {
  return c >= '0' && c <= '9';
}


int buffer[MAX_STR_SIZE];
int bufp = 0;

int getch() {
  return (bufp > 0) ? buffer[--bufp] : getchar();
}


void ungetch(int c) {
  if (bufp < MAX_STR_SIZE) {
    buffer[bufp++] = c;
  } else {
    error("ungetch: no more buffer space.\n");
  }
}


#define MAX_STACK_SIZE 1024
double stack[MAX_STACK_SIZE];
int stackp = 0;

void push(double val) {
  if (stackp < MAX_STACK_SIZE) {
    stack[stackp++] = val;
  } else {
    error("push: stack is full!\n");
  }
}

double pop() {
  if (stackp > 0) {
    return stack[--stackp];
  } else {
    error ("pop: stack is empty.\n");
  }
}

/* Returns the next operator or operand.
   This could return a character like '+' or a number like 123.456.
*/
double getOperatorOrOperand() {
  char c;
  double num;
  int i, dot_index;
  num = i = dot_index = 0;


  while ((c = getch()) == ' ' || c == '\t')
    ;

  ungetch(c); // put most recent non-whitespace char back on the buffer.

  while ((c = getch()) != EOF) {
    if (isDigit(c)) {
      while (isDigit(c) || c == '.') {
        if (c == '.') {
          dot_index = i;
          ++i;
          c = getch();
          continue;
        }
        num = num * 10 + c - '0';
        ++i;
        c = getch();
      }
      if (dot_index)
        num = num / pow(10, i - dot_index - 1);
      ungetch(c);
      i = 0;
      continue;
    }
    if (num > 0)
      break;
    switch (c) {
      case '+': case '*': case '-': case '/':
        return c;
        break;
      case '\n':
        if (stackp != 1) {
          error("Stack should only have one value!\n");
          exit(1);
        } else {
          printf("%f\n", pop());
        }
        break;
      default:
        // neither operator or operand. Keep going until you find one.
        break;
    }
  }
  if (c == EOF)
    exit(1);

  return num;
}

int main() {
  double op, tmp;

  while (1) {
    op = getOperatorOrOperand();
    if (op == '+') {
      push(pop() + pop());
    } else if (op == '*') {
      push(pop() * pop());
    } else if (op == '-') {
      tmp = pop();
      push(pop() - tmp);
    } else if (op == '/') {
      tmp = pop();
      push(pop() / tmp);
    } else {
        push(op);
    }
  }
  return 0;
}
