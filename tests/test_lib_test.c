#include "../jlib/test_lib.h"
#include <assert.h>

void testDprint() {
  int x = 28;
  int y = 14;
  dprint(x/y);
  dprint(x + y);
  dprint(x * y);
  dprint(x - y);
  printf("dprint tested.\n");
}

int main() {
  printf("STARTING TEST LIB TESTS.\n");
  testDprint();
  return 0;
}
