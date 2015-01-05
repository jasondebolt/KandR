#include <stdio.h>
#include <assert.h>

void squeezeMulti(char s[], char c[]) {

  int i, j, k, match;

  for (i = j = 0; s[i] != '\0'; ++i) {
    match = 0;
    for (k = 0; k < strln(c); ++k) {
      if (s[i] == c[k]) {
        match = 1;
      }
    }
    if (!match) {
      s[j++] = s[i];
    }
  }

  s[j] = '\0';
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

int strln(char c[]) {
  int i;
  i = 0;

  while (c[i] != '\0')
    ++i;

  return i;
}

int main() {
  char name[] = "jason debolt";
  char name2[] = " this is it...now what.. ";
  squeezeMulti(name, "jaol");
  squeezeMulti(name2, " .");
  assert(strCmp(name, "sn debt") == 0);
  assert(strCmp(name2, "thisisitnowwhat") == 0);
  return 0;
}
