#include <stdio.h>
#include <assert.h>

main() {
  printf("EOF: %d\n", EOF);
  assert(EOF == -1);
}
