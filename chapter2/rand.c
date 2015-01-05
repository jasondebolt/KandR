#include <stdio.h>
#define MAX_ITERATIONS 5

unsigned long int next = 1;

int rand(void) {
  next = next * 1103515245 + 12345;
  return (unsigned int)(next/65536) % 32768;
}

void srand(unsigned int seed) {
  next = seed;
}

void printSomeNumbers() {
  int i;
  for (i = 0; i < MAX_ITERATIONS; ++i) {
    printf("%d\t", rand());
  }
  printf("\n");
}

int main() {
  int c;
  int count = 0;
  printf("Enter a seed value: ");
  srand(getchar());
  printSomeNumbers();
  return 0;
}
