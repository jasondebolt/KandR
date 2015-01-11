#include <stdio.h>
#include <assert.h>
#include "../jlib/str_lib.h"

void testStrComp() {
  char a[] = "one";
  char b[] = "onf";
  char name[] = "my first name";
  char name2[] = "-one-two-three-four five--six";
  char name3[] = "AoneAtwoAthree";
  assert(strComp(a, b) == -1);
  assert(strComp(b, a) == 1);
  assert(strComp(a, a) == 0);
  printf("strComp tested.\n");
}

void testReverse2() {
  char name[] = "jason";
  reverse2(name);
  assert(strComp(name, "nosaj") == 0);
  printf("reverse2 tested.\n");
}

void testSqueeze() {
  char name[] = "my first name";
  char name2[] = "-one-two-three-four five--six";
  char name3[] = "AoneAtwoAthree";
  squeeze(name, ' ');
  squeeze(name2, '-');
  squeeze(name3, 'A');
  assert(strComp(name, "myfirstname") == 0);
  assert(strComp(name2, "onetwothreefour fivesix") == 0);
  assert(strComp(name3, "onetwothree") == 0);
  printf("squeeze tested.\n");
}

void testLower() {
  assert(lower('A') == 'a');
  printf("lower tested.");
}

void testLowerAll() {
  char name[] = "Jason";
  char name2[] = "ABCDEF";
  lowerAll(name);
  assert(strComp(name, "jason") == 0);
  lowerAll(name2);
  assert(strComp(name2, "abcdef") == 0);
  printf("lowerAll tested.");
}

int main() {
  printf("STARTING STRING LIB TESTS.\n");
  testStrComp();
  testReverse2();
  testSqueeze();
  testLower();
  testLowerAll();
  return 0;
}
