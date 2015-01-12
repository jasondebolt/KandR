#include "search_lib.h"

// Search for x in array v of length n;
int binsearch(int x, int v[], int n) {
  int low, high, mid;

  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (high + low) / 2;
    if (x > v[mid])
      low = mid + 1;
    else if (x < v[mid])
      high = mid - 1;
    else
      return mid;
    
  }
  return -1; // result not found.
}
