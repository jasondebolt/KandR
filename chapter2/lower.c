#include <stdio.h>
#include <assert.h>

char lower(int c) {
  return (c >= 'A' && c <= 'Z') ? c - 'A' + 'a': c;
}

void lowerAll(char c[]) {
  int i;
  for (i = 0; c[i] != '\0'; ++i)
    c[i] = lower(c[i]);
}

int strCmp(char one[], char two[]) {
  int i = 0;
  while (1) {
    if (one[i] < two[i])
      return -1;
    else if (one[i] > two[i])
      return 1;
    else if (one[i] == '\0' && two[i] == '\0')
      return 0;
    else
      ++i;
  }
  return 0;
}

int strln(char one[]) {
  int i = 0;
  while (one[i] != '\0')
    ++i;
  return i;
}

int main() {
  assert(lower('A') == 'a');
  char name[] = "Jason";
  lowerAll(name);
  assert(strCmp(name, "jason") == 0);
  assert(strCmp("abc", "abd") == -1);
  assert(strCmp("ggg", "aaa") == 1);
  char name2[] = "ABCDEF";
  lowerAll(name2);
  assert(strCmp(name2, "abcdef") == 0);
  return 0;
}
