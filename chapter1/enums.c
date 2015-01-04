#include <stdio.h>
#include <assert.h>

enum Boolean {NO, YES};
enum Escapes {NEWLINE = '\n', TAB = '\t'};
enum Months {JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

void printMonth(enum Months month) {
  printf("%d\n", month);
}

int main() {
  printf("%d\n", YES);
  printf("%c", NEWLINE);
  printf("this%cis%cit.", TAB, TAB);
  printf("%c", NEWLINE);
  printf("%c", NEWLINE);
  printf("%c", NEWLINE);
  assert(JAN == 1);
  assert(FEB == 2);
  assert(DEC == 12);
  printMonth(JUN);
  printMonth('a'); // Not sure why this still works
}
