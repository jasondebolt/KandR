#include <stdio.h>
#define MAX_LENGTH 10

int main() {
  int c, cnt;
  cnt = 0;
  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      ++cnt;
      if (cnt > MAX_LENGTH) {
        printf("...");
      }
      printf("\t%d\n", cnt);
      cnt = 0;
    }
    else {
      if (++cnt <= MAX_LENGTH) {
        putchar(c);
      }
    }
  }
}
