#include <stdio.h>

#define OUT 0
#define IN 1
#define MAX_WORD_LENGTH 10
#define HEADING "WordCount\nFrequency\n"

// Count Frequency
// 1 ==========
// 3 ======
// 5 ==
// 4 =
int main() {
  int i, c, state, cc;
  int freq[MAX_WORD_LENGTH];

  cc = 0;

  for (i = 0; i < MAX_WORD_LENGTH; ++i) {
    freq[i] = 0;
  }

  while ((c = getchar()) != EOF) {
    if (c == '\n' || c == '\t' || c == ' ') {
      if (state == IN) {
        ++freq[cc];
      }
      cc = 0;
      state = OUT;
    }
    else {
      state = IN;
      ++cc;
    }
  }

  printf(HEADING);
  for (i = 0; i < MAX_WORD_LENGTH; ++i) {
    printf("%d\t%d\n", i, freq[i]);
  }

  return 0;
}
