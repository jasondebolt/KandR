#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAX_STACK_SIZE 1024

int stack[MAX_STACK_SIZE];
int stackp = 0;

void push(int val) {
  if (stackp < MAX_STACK_SIZE) {
    stack[stackp++] = val;
  } else {
    error("Stack is full, cannot push.\n");
    exit(1);
  }
}

int pop() {
  if (stackp > 0) {
    return stack[--stackp];
  } else {
    fprintf(stderr, "Stack is empty, cannot pop.\n");
    exit(1);
  }
}

int peek() {
  int val;
  if (stackp > 0) {
    val = pop();
    push(val);
    return val;
  } else {
    fprintf(stderr, "Stack is empty, cannot peek.\n");
  }
}

void swapTopTwo() {
  int top = pop();
  int second = pop();
  push(top);
  push(second);
}

void clearStack() {
  while (stackp > 0) {
    pop();
  }
}

int isEmpty() {
  return stackp <= 0;
}

int main() {
  push(10);
  push(20);
  push(30);
  push(40);
  assert(pop() == 40);
  assert(pop() == 30);
  assert(pop() == 20);
  assert(peek() == 10);
  assert(peek() == 10);
  assert(pop() == 10);
  // new stack items.
  push(3);
  push(8);
  push(2);
  push(1);
  swapTopTwo();
  assert(pop() == 2);
  assert(pop() == 1);
  assert(pop() == 8);
  assert(pop() == 3);
  // new stack items.
  push(3);
  push(9);
  push(2);
  push(5);
  assert(!isEmpty());
  clearStack();
  assert(isEmpty());
  return 0;
}
