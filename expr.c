#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 1000
#define NUMBER 1
#define UNKNOWN_TOKEN 2

static int stack[MAX_STACK_SIZE];
static int *stackp = stack;

void push(int item) {
  if (stackp < stack + MAX_STACK_SIZE) {
    *stackp++ = item;
  } else {
    fprintf(stderr, "stack filled, cannot push item.\n");
    exit(1);
  }
}

int pop() {
  if (stackp > stack) {
    return *--stackp;
  } else {
    fprintf(stderr, "no more items to pop.\n");
    exit(1);
  }
}


int getToken(char *s, int *val) {
  int sign;
  int num;

  while (*s == ' ' || *s == '\t')
    s++;

  if (!*(s + 1) || !(*(s + 1) >= '0' || *(s + 1) <= '9')) {
    switch (*s) {
      case '+': case '-': case '*': case '/':
        return *s;
        break;
      default:
        break;
    }
  }

  sign = 1;
  if (*s == '-')
    sign = -1;

  if (*s == '-' || *s == '+')
    s++;
  
  *val = 0;
  if (*s >= '0' && *s <= '9') {
    while (*s) {
      *val = *val * 10 + *s - '0';
      s++;
    }
    *val = *val * sign;
    return NUMBER;
  } else {
    return UNKNOWN_TOKEN;
  }
}

void testStack() {
  push(1);
  push(2);
  push(3);
  printf("%d\n", pop());
  printf("%d\n", pop());
  printf("%d\n", pop());
}


// Dumbed down command line version of a reverse polish calculator.
int main(int argc, char *argv[]) {
  //testStack();
  int token_type;
  int second;
  int val;
  printf("You may have to escape the multiplication symbol.\n");
  printf("2 3 4 + \\*\n\n");
  while (--argc > 0) {
    token_type = getToken(*++argv, &val);
    switch (token_type) {
      case NUMBER:
        push(val);
        break;
      case '+':
        push(pop() + pop());
        break;
      case '-':
        second = pop();
        push(pop() - second);
        break;
      case '*':
        push(pop() * pop());
        break;
      case '/':
        second = pop();
        push(pop() / second);
        break;
      default:
        fprintf(stderr, "Unknown token.\n");
        exit(1);
    }
  }
  printf("%d\n", pop());
}
