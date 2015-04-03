#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_BUFF_LEN 100
#define MAX_WORD_LEN 100
#define FILE_TERMINATE EOF

char buffer[MAX_BUFF_LEN];
int buffp = 0;


struct key {
  char *name;
  int count;
} keys[] = {
  "abs", 0,
  "break", 0,
  "case", 0,
  "do", 0,
  "if", 0
};

char getch() {
  return (buffp > 0) ? buffer[--buffp] : getchar();
}

void ungetch(char c) {
  if (buffp < MAX_BUFF_LEN) {
    buffer[buffp++] = c;
  } else {
    fprintf(stderr, "no more buffer space.\n");
  }
}

int getWord(char *s, int max_len) {
  char c, d;
  int len = 0;
  while (isspace(c = getch()))
    ;
  *s++ = c;
  ++len;
  if (c == FILE_TERMINATE) {
    *s = '\0';
    return -1;
  }
  while (!isspace(c = getch()) && --max_len > 0 && c != FILE_TERMINATE) {
    *s++ = c;
    ++len;
  }
  *s = '\0';
  if (c == FILE_TERMINATE)
    ungetch(c);
  return len;
}

struct key *binarySearch(char *name, struct key *keys, int num_keys) {
  struct key *low = keys;   // same as &keys[0]
  struct key *hi = keys + num_keys - 1;
  int diff;
  while (low <= hi) {
    struct key *mid = low + (hi - low) / 2;
    if ((diff = strcmp(name, mid->name)) < 0) {
      hi = mid - 1;
    } else if (diff > 0) {
      low = mid + 1;
    } else {
      return mid;
    }
  }
  return NULL;
}


void testGetch() {
  assert(buffp == 0);
  ungetch('a');
  assert(buffp == 1);
  assert(getch() == 'a');
  assert(buffp == 0);
  printf("getch tested.\n");
}

void testGetWord() {
  printf("enter jason\n");
  char s[MAX_WORD_LEN];
  int len;
  len = getWord(s, MAX_WORD_LEN);
  assert(len == 5);
  assert(strcmp(s, "jason") == 0);
  printf("name: %s\n", s);
  printf("enter jason followed by a period.\n");
  char p[MAX_WORD_LEN];
  len = getWord(p, MAX_WORD_LEN);
  assert(len == -1);
  printf("name: %s\n", p);
  assert(strcmp(s, "jason") == 0);
  printf("getWord tested.\n");
}

void testGetWords() {
  char s[MAX_WORD_LEN];
  int len;
  while((len = getWord(s, MAX_WORD_LEN)) >= 0) {
    printf("%s\n", s);
  }
  printf("getWords tested.\n");
}

void testKeys() {
  assert(sizeof(keys) / sizeof(keys[0]) == 5);
  assert(keys == &keys[0]);
  assert(keys + 1 == &keys[1]);
  assert(keys + 4 == &keys[4]);
  assert(strcmp((keys + 3)->name, "do") == 0);
  printf("keys tested.\n");
}


void testBinarySearch() {
  int len = sizeof(keys) / sizeof(keys[0]);
  assert(binarySearch("abs", keys, len) == &keys[0]);
  assert(binarySearch("break", keys, len) == &keys[1]);
  assert(binarySearch("case", keys, len) == &keys[2]);
  assert(binarySearch("do", keys, len) == &keys[3]);
  assert(binarySearch("if", keys, len) == &keys[4]);
  assert(binarySearch("not found", keys, len) == NULL);
  printf("binarySearch tested.\n");
}

void testLoadKeys() {
  char s[MAX_WORD_LEN];
  int keys_len = sizeof(keys) / sizeof(keys[0]);
  int len;
  struct key *word;
  while((len = getWord(s, MAX_WORD_LEN)) >= 0) {
    word = binarySearch(s, keys, keys_len);
    if (word != NULL)
      word->count++;
  }
  struct key *k = keys;
  for (k = keys; k < keys + keys_len; k++) {
    if (k->count > 0)
      printf("%s, count: %d\n", k->name, k->count);
  }

}

int main() {
  //testGetch();
  //testGetWord();
  //testGetWords();
  //testKeys();
  //testBinarySearch();
  testLoadKeys();
  return 0;
}
