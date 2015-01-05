#include <stdio.h>
#include <assert.h>

int isBetween(char c, char lower, char upper) {
  return c >= lower && c <= upper;
}

int isDigt(char c) {
  return c >= '0' && c <= '9';
}

int isLowerHexLetter(char c) {
  return c >= 'a' && c <= 'f';
}


int isUpperHexLetter(char c) {
  return isBetween(c, 'A', 'F');
}

int getIntFromHexChar(char c) {
  if (isDigt(c))
    return c - '0';
  else if (isLowerHexLetter(c))
    return c - 'a' + 10;
  else if (isUpperHexLetter(c)) {
    return c - 'A' + 10;
  } else {
    return -1;
  }
}


int htoi(char s[]) {
  int n = 0;
  int i = 0;

  if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
    i += 2;
  }

  while(s[i] != '\0') {
    n = n * 16 + getIntFromHexChar(s[i]);
    ++i;
  }

  return n;
}


int main() {
  assert(isUpperHexLetter('F'));
  assert(getIntFromHexChar('F') == 15);
  assert(getIntFromHexChar('a') == 10);
  assert(getIntFromHexChar('5') == 5);
  assert(htoi("f") == 15);
  assert(htoi("0xff") == 255);
  assert(htoi("0XFF") == 255);
  assert(htoi("ffff") == 65535);
  return 0;
}
