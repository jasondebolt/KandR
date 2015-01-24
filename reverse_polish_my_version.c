#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define CALC_ERROR -2
#define RESULT 0
#define NUMBER 1
#define SIN 2
#define EXP 3
#define POW 4

#define MAX_BUFF_SIZE 1024
char buffer[MAX_BUFF_SIZE];
int buffp = 0;

char getch() {
  return (buffp > 0) ? buffer[--buffp] : getchar();
}

void ungetch(char c) {
  if (buffp < MAX_BUFF_SIZE) {
    buffer[buffp++] = c;
  } else {
    fprintf(stderr, "buffer full.\n");
    exit(1);
  }
}

#define MAX_STACK_SIZE 1024
double stack[MAX_STACK_SIZE];
int stackp = 0;

double pop() {
  if (stackp > 0) {
    return stack[--stackp];
  } else {
    fprintf(stderr, "stack is empty, cannot pop.\n");
    exit(1);
  }
}

void push(double c) {
  if (stackp < MAX_STACK_SIZE) {
    stack[stackp++] = c;
  } else {
    fprintf(stderr, "stack is full, cannot push.\n");
    exit(1);
  }
}


int getop(char s[]) {
  int c, c1, c2, i;
  i = 0;
  
  while ((c = getch()) == ' ' || c == '\t')
    ;
  ungetch(c);

  while ((c = getch()) != EOF) {
    if (c == '-') {
      if (isdigit(c1 = getch()) || c1 == '.') {
        s[i++] = c; // save the negative sign.
        c = c1; // number or dot after negative sign is our new char.
      } else {
        ungetch(c1); // char wasn't a digit, put it back.
      }
    }
    if (isdigit(c) || c == '.') {
      s[i++] = c;
      while (isdigit(c = getch()) || c == '.') {
        s[i++] = c;
      }
      ungetch(c);
      s[i] = '\0';
      return NUMBER;
    }
    if (c == '+' || c == '*' || c == '-' || c == '/' || c == '%')
      return c;
    if (c == 's' || c == 'e' || c == 'p') {
      c1 = getch();
      c2 = getch();
      if (c == 's' && c1 == 'i' && c2 == 'n')
        return SIN;
      if (c == 'e' && c1 == 'x' && c2 == 'p')
        return EXP;
      if (c == 'p' && c1 == 'o' && c2 == 'w')
        return POW;
      ungetch(c2);
      ungetch(c1);
    }
    if (c == '\n')
      return RESULT;
  }

  if (c == EOF)
    return EOF;

  return CALC_ERROR;
}

#define MAX_NUM_SIZE 1024
int main() {
  char s[MAX_NUM_SIZE];
  int i;
  double tmp;

  while ((i = getop(s)) != EOF) {
    switch(i) {
      case CALC_ERROR:
        fprintf(stderr, "main: getop could not return a valid response.\n");
        break;
      case RESULT:
        printf("%f\n", pop());
        break;
      case NUMBER:
        push(atof(s));
        break;
      case SIN:
        push(sin(pop()));
        break;
      case EXP:
        push(exp(pop()));
        break;
      case POW:
        tmp = pop();
        push(pow(pop(), tmp));
        break;
      case '+':
        push(pop() + pop());
        break;
      case '*':
        push(pop() * pop());
        break;
      case '-':
        tmp = pop();
        push(pop() - tmp);
        break;
      case '/':
        tmp = pop();
        push(pop() / tmp);
        break;
      case '%':
        tmp = pop();
        push(fmod(pop(), tmp));
        break;
      default:
        break;
    }
  }

  printf("Thank you for using Reverse Polish Calculator.\n");
  return 0;
}
