#include <stdio.h>
#define MIN_LENGTH 5 // this should be 80.
#define MAX_LENGTH 1000

int main() {
  int c, cnt, i;
  char vals[MAX_LENGTH];

  cnt = 0;

  for (i = 0; i < MAX_LENGTH; ++i) {
    vals[i] = '\0';
  }

  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      vals[cnt++] = c;
      if (cnt >= MIN_LENGTH) {
        i = 0;
        while (vals[i] != '\0') {
          putchar(vals[i]);
          vals[i++] = '\0';
        }
      }
      cnt = 0;
    } else {
      vals[cnt++] = c;
    }
  }
}
