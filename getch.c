#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_BUFF_SIZE 1024
int buffer[MAX_BUFF_SIZE];
int buffp = 0;

char getch() {
  return (buffp > 0) ? buffer[--buffp] : getchar();
}

void ungetch(int c) {
  if (buffp < MAX_BUFF_SIZE) {
    buffer[buffp++] = c;
  } else {
    fprintf(stderr, "buffer full.\n");
    exit(1);
  }
}

void ungets(char s[]) {
  int i;
  i = 0;
  while (s[i] != '\0')
    ++i;

  while (i > 0)
    ungetch(s[--i]);
}

void testGetchAndUngetch() {
  assert(buffp == 0); 
  ungetch('a');
  assert(buffp == 1); 
  getch();
  assert(buffp == 0); 
}

void testUngets() {
  assert(buffp == 0); 
  ungets("jason");
  assert(buffp == 5); 
  assert(getch() == 'j');
  assert(getch() == 'a');
  assert(getch() == 's');
  assert(getch() == 'o');
  assert(getch() == 'n');
  assert(buffp == 0); 
  ungetch(EOF);
  assert(getch() == EOF);
}


int main() {
  testGetchAndUngetch();
  testUngets();
  return 0;
}
