#include <stdio.h>
#include <assert.h>

double pow(double base, double exp) {
  int i, result;
  result = 1;
  for (i = 1; i <= exp; ++i) {
    result = result * base;
  }
  return result;
}

int main() {
  assert(pow(2, 3) == 8);
  assert(pow(1, 6) == 1);
  assert(pow(3, 3) == 27);
  assert(pow(2, 8) == 256);
  assert(pow(9, 2) == 81);
  return 0;
}
