#include <stdio.h>
#include <assert.h>

int any(char s[], char t[]) {
  int i, j;

  for (i = 0; s[i] != '\0'; ++i) {
    for(j = 0; t[j] != '\0'; j++) {
       if (s[i] == t[j]) {
          return i;
        }
      }
  }
  return -1;
}

int main() {

  assert(any("jason", "n") == 4);
  assert(any("today i am working today.", "t") == 0);
  assert(any("abcdefghijk zef", " fi") == 5);

  return 0;
}
