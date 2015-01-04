#include <stdio.h>
#include <assert.h>

int isLeapYear(int year) {
  // Is the year divisible by 400?
  //   - then this is a leap year.
  // Is this year divisible by 4 but NOT divisible by 100?
  //   - then this is a leap year.
  if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
    return 1;
  return 0;
}

int main() {

  assert(isLeapYear(1600) == 1);
  assert(isLeapYear(1796) == 1);
  assert(isLeapYear(1800) == 0);
  assert(isLeapYear(1804) == 1);
  assert(isLeapYear(1896) == 1);
  assert(isLeapYear(1900) == 0);
  assert(isLeapYear(1904) == 1);
  assert(isLeapYear(1996) == 1);
  assert(isLeapYear(2000) == 1);
  assert(isLeapYear(2004) == 1);
  return 0;
}
