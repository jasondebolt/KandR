#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define MAX_LINE_LEN 14
#define MAX_LINES 20
#define MAX_BUFF_LEN 1024

char buffer[MAX_BUFF_LEN];
size_t buffp = 0;


char getch() {
        return (buffp > 0) ? buffer[--buffp] : getchar();
}

void ungetch(char c) {
        if (buffp < MAX_BUFF_LEN) {
                buffer[buffp++] = c;
        } else {
                fprintf(stderr, "ERROR: buffer is full\n");
        }
}

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


// Gets the next token from an input stream.
int getToken(char *s, int max_len) {
  char c;
  int len = 0;
  while (isspace(c = getchar()))
    ;
  *s++ = c;
  len++;
  while (!isspace(c = getchar()) && c != EOF) {
    *s++ = c;
    len++;
  }
  if (c == EOF)
    return EOF;
  *s = '\0';
  return len;
}


int binarySearch(char **list, char *p, int len) {
        int low = 0;
        int high = len - 1;
        int mid, diff;
        while (low <= high) {
                mid = (low + high) / 2;
                if ((diff = strcmp(p, list[mid])) < 0) {
                        high = mid - 1;
                } else if (diff > 0) {
                        low = mid + 1;
                } else {
                        return mid;
                }
        }
        return -1;
}

int binarySearch2(struct key keys[], char *p, int len) {
        int low = 0;
        int high = len - 1;
        int mid, diff;
        while (low <= high) {
                mid = (low + high) / 2;
                if ((diff = strcmp(p, keys[mid].name)) < 0) {
                        high = mid - 1;
                } else if (diff > 0) {
                        low = mid + 1;
                } else {
                        return mid;
                }
        }
        return -1;
}


void testKeys() {
        assert(strcmp(keys[0].name, "abs") == 0);
        assert(keys[3].count == 0);
        printf("keys tested.\n");
}


void testGetToken() {
        char s[MAX_LINE_LEN];
        while (getToken(s, MAX_LINE_LEN) >= 0) {
                printf("%s\n", s);
        }
        printf("getToken tested.\n");
}


void testBinarySearch() {
        char *s[10] = {"apple", "berry", "cherry", "lemon", "orange"};
        assert(binarySearch(s, "apple", 5) == 0);
        assert(binarySearch(s, "berry", 5) == 1);
        assert(binarySearch(s, "cherry", 5) == 2);
        assert(binarySearch(s, "lemon", 5) == 3);
        assert(binarySearch(s, "orange", 5) == 4);
        assert(binarySearch(s, "not found", 5) == -1);
        printf("binarySearch tested.\n");
}

void testBinarySearch2() {
        struct key keys[5] = {
                "abs", 0,
                "break", 0,
                "case", 0,
                "do", 0,
                "if", 0
        };
        assert(binarySearch2(keys, "abs", 5) == 0);
        assert(binarySearch2(keys, "break", 5) == 1);
        assert(binarySearch2(keys, "case", 5) == 2);
        assert(binarySearch2(keys, "do", 5) == 3);
        assert(binarySearch2(keys, "if", 5) == 4);
        assert(binarySearch2(keys, "not found", 5) == -1);
        printf("binarySearch2 tested\n");
}

void testLoadKeys() {
        char s[MAX_LINE_LEN];
        int index;
        int num_keys = sizeof(keys) / sizeof(keys[0]);
        printf("Enter some c keywords...\n");
        while (getToken(s, MAX_LINE_LEN) >= 0) {
                index = binarySearch2(keys, s, num_keys);
                keys[index].count++;
        }
        int i;
        for (i = 0; i < num_keys; ++i) {
                printf("%s, count: %d\n", keys[i].name, keys[i].count);
        }
        printf("loadKeys tested.\n");
}

void testGetchAndUngetch() {
  assert(buffp == 0);
  ungetch('a');
  assert(buffp == 1);
  assert(getch() == 'a');
  assert(buffp == 0);
  printf("testGetchAndUngetch tested.\n");
}


int main() {
        testKeys();
        testGetchAndUngetch();
        //testGetToken();
        testBinarySearch();
        testBinarySearch2();
        testLoadKeys();
        return 0;
}
