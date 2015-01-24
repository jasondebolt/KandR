#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#define CALC_ERROR -2
#define RESULT 0
#define NUMBER 1
#define VARIABLE_GET 2
#define SIN 3
#define EXP 4
#define POW 5

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

void ungets(char s[]) {
  int i;
  i = 0;
  while (s[i] != '\0')
    ++i;

  while (i > 0)
    ungetch(s[--i]);
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

double peek() {
  double top = pop();
  push(top);
  return top;
}

int getop(char s[]) {
  int c, c1, c2, i;
  i = 0;
  
  while ((c = getch()) == ' ')
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
    if (c >= 'a' && c <= 'z') {
      s[i++] = c;
      s[i] = '\0';
      return VARIABLE_GET;
    }
    if (c == '\t') {
      if ((c1 = getch()) >= 'b' && c1 <= 'z') { // 'a' cannot be assigned to.
        return c1;
      }
      ungetch(c1);
    }
    if (c == '\n')
      return RESULT;
  }

  if (c == EOF)
    return EOF;

  return CALC_ERROR;
}

void testUngets() {
  assert(buffp == 0); 
  ungetch('a');
  assert(buffp == 1); 
  getch();
  assert(buffp == 0); 
  ungets("jason");
  assert(buffp == 5); 
  assert(getch() == 'j');
  assert(getch() == 'a');
  assert(getch() == 's');
  assert(getch() == 'o');
  assert(getch() == 'n');
  assert(buffp == 0); 
}

#define MAX_NUM_SIZE 1024
int main() {
  char s[MAX_NUM_SIZE];
  double vars[26], result;
  int i;
  double tmp;

  printf("Welcome to Reverse Polish Calc.\n");
  printf("Usage:\n");
  printf("\t (2 * 1 ) + (3 * 4) should be typed as 2 1 * 3 4 * +\n");
  printf("\t Most recent result is assigned to variable a.\n");
  printf("\t Follow expression by tab and variables b through z for assignment.\n");
  printf("\t 6.2 3.1 / 4 5 * * should return 40.\n");
  printf("\t a -4 / should return -10.\n");
  printf("\t 2 3 +[TAB]b assigns 5 to variable b.\n");

  printf("\n");

  while ((i = getop(s)) != EOF) {
    switch(i) {
      case CALC_ERROR:
        fprintf(stderr, "main: getop could not return a valid response.\n");
        break;
      case RESULT:
        vars['a' - 'a'] = result = pop(); // store result in variable a.
        printf("%f\n", result);
        break;
      case NUMBER:
        push(atof(s));
        break;
      case VARIABLE_GET:
        push(vars[s[0] - 'a']); // push the value of the variable.
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
        if (tmp == 0) {
          fprintf(stderr, "main: zero division error.\n");
          exit(1);
        }
        push(pop() / tmp);
        break;
      case '%':
        tmp = pop();
        push(fmod(pop(), tmp));
        break;
      case 'b': case 'c': case 'd': case 'e': case 'f':
      case 'g': case 'h': case 'i': case 'j': case 'k':
      case 'l': case 'm': case 'n': case 'o': case 'p':
      case 'q': case 'r': case 's': case 't': case 'u':
      case 'v': case 'w': case 'x': case 'y': case 'z':
        vars[i - 'a'] = peek();
        break;
      default:
        break;
    }
  }

  printf("Thank you for using Reverse Polish Calculator.\n");
  return 0;
}
