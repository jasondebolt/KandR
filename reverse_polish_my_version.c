#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define CALC_ERROR -2
#define RESULT 0
#define NUMBER 1
#define VARIABLE_GET 2
#define SIN 3
#define EXP 4
#define POW 5


#define MAX_STACK_SIZE 1024
double stack[MAX_STACK_SIZE];
double *stack_ptr = stack;

double pop() {
  if (stack_ptr > stack) {
    return *(--stack_ptr);
  } else {
    fprintf(stderr, "stack is empty, cannot pop.\n");
    exit(1);
  }
}

void push(double c) {
  if (stack_ptr < stack + MAX_STACK_SIZE) {
    *(stack_ptr++) = c;
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

#define MAX_STR_SIZE 1024
int getop(char *s) {
  static char line[MAX_STR_SIZE];
  static char *ptr = line;
  int c, c1;

  /* INPUT CODE START */
  if (ptr == line) { // This block should only execute on the very first function call.
    while ((c = getchar()) != '\n' && (ptr + 1 != NULL) && c != EOF) {
      *ptr++ = c;
    }

    if (c == EOF)
      return EOF;

    *ptr++ = '\n';
    *ptr = '\0';
    ptr = line; // Send pointer back to first element of line, which now has data.
  }
  /* INPUT CODE END */

  while ((c = *ptr) == ' ')
    ++ptr;

  while ((c = *ptr) != EOF) {
    if (c == '-') {
      if (isdigit(c1 = *(ptr + 1)) || c1 == '.') {
        *s++ = c; // save the negative sign.
        c = *(++ptr); // number or dot after negative sign is our new char.
      }
    }
    if (isdigit(c) || c == '.') {
      *s++ = c;
      c = *(++ptr);
      while (isdigit(c) || c == '.') {
        *s++ = c;
        c = *(++ptr);
      }
      *s = '\0';
      return NUMBER;
    }
    if (c == '+' || c == '*' || c == '-' || c == '/' || c == '%') {
      ++ptr;
      return c;
    }
    if (c == 's' && *(ptr + 1) == 'i' && *(ptr + 2) == 'n') {
      ptr += 3;
      return SIN;
    }
    if (c == 'e' && *(ptr + 1) == 'x' && *(ptr + 2) == 'p') {
      ptr += 3;
      return EXP;
    }
    if (c == 'p' && *(ptr + 1) == 'o' && *(ptr + 2) == 'w') {
      ptr += 3;
      return POW;
    }
    if (c >= 'a' && c <= 'z') {
      *s++ = c;
      *s = '\0';
      ++ptr;
      return VARIABLE_GET;
    }
    if (c == '\t') {
      if ((c1 = *(ptr + 1)) >= 'b' && c1 <= 'z') { // 'a' cannot be assigned to.
        ++ptr;
        return c1;
      }
    }
    if (c == '\n') {
      ptr = line; // Reset pointer to we can gather user input again.
      return RESULT;
    }

    return CALC_ERROR;
  }

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
  printf("\t CTRL-D sends EOF to program to signal exit.\n");

  printf("\n");

  while ((i = getop(s)) != EOF) {
    switch(i) {
      case CALC_ERROR:
        fprintf(stderr, "main: getop could not return a valid response.\n");
        exit(1);
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
