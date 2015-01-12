#include "../jlib/search_lib.h"
#include <assert.h>

void testBinSearch() {
  int vals[8] = {1, 3, 4, 5, 9, 10, 23, 34}; // Must be sorted.
  assert(binsearch(1, vals, 8) == 0);
  assert(binsearch(23, vals, 8) == 6);
  assert(binsearch(34, vals, 8) == 7);
  assert(binsearch(11, vals, 8) == -1);
  printf("binary search tested.\n");
}

int main() {
  printf("STARTING SEARCH TESTS.\n");
  testBinSearch();
  return 0;
}
