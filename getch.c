#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#define MAX_LINE_LEN 1024

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

/* getword: get next word or character from input.
 * Copied from page 136 of K&R.
 * Fetches the next "word" from the input, where a word is either a string
 * of letters and digits beginning with a letter, or a single non-whitespace
 * character. The return value is the first character of the word, or EOF
 * for end of file, or the character itself if it is not alphabetic.
 */
int getword(char *word, int lim) {
  int c;
  char *w = word;
  while (isspace(c = getch()))
    ;
  if (c != EOF)
    *w++ = c;
  if (!isalpha(c)) {
    *w = '\0';
    return c;
  }
  for ( ; --lim > 0; w++) {
    if (!isalnum(*w = getch())) {
      ungetch(*w);
      break;
    }
  }
  *w = '\0';
  return word[0];
}

/* getword2: get next word or character from input.
 * Same as getword above, except we handle underscores, string constants
 * and preprocessor control lines.
 */
int getword2(char *word, int lim) {
  char c, c1, c2, c3;
  char *w = word;
  while (isspace(c = getch()) || c == '/') {
    ungetch(c);
    while (isspace(c = getch()))
      ;
    if (c == '/') {
      if ((c1 = getch()) == '/') {
        // We are in a comment. Go to the end.
        while ((c2 = getch()) != '\n')
          ;
      } else if (c1 == '*') {
        while (1) {
          while ((c2 = getch()) != '*')
            ;
          // At this point, we might have the end of comment.
          if ((c3 = getch()) == '/') {
            break;
          } else {
            ungetch(c3);
          }
        }
      } else {
        // This wasn't a comment.
        ungetch(c1);
      }
    }
  }
  if (c == '"') {
    *w++ = c;
    while ((c = getch()) != '"') {
      *w++ = c;
      if (c == '\\') {
        *w++ = getch();
      }
    }
    *w++ = c;
    *w= '\0';
    return *word;
  }
  while (isalnum(c) || c == '_') {
    *w++ = c;
    c = getch();
  }
  ungetch(c);
  *w = '\0';
  return w[0];
}

void testGetchAndUngetch() {
  assert(buffp == 0);
  ungetch('a');
  assert(buffp == 1);
  getch();
  assert(buffp == 0);
  printf("Getch and ungetch tested.\n");
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
  printf("Ungets tested.\n");
}

void testGetWord() {
  printf("Enter the following string: "
         "ab12 AB12 12ab 12AB test 123 455abc_* 1jason2\n");
  char c, word[MAX_LINE_LEN];
  c = getword(word, MAX_LINE_LEN);
  assert(c == 'a');
  assert(strcmp(word, "ab12") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == 'A');
  assert(strcmp(word, "AB12") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '1');
  c = getword(word, MAX_LINE_LEN);
  assert(c == '2');
  c = getword(word, MAX_LINE_LEN);
  assert(c == 'a');
  assert(strcmp(word, "ab") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '1');
  c = getword(word, MAX_LINE_LEN);
  assert(c == '2');
  c = getword(word, MAX_LINE_LEN);
  assert(c == 'A');
  assert(strcmp(word, "AB") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == 't');
  assert(strcmp(word, "test") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '1');
  c = getword(word, MAX_LINE_LEN);
  assert(c == '2');
  c = getword(word, MAX_LINE_LEN);
  assert(c == '3');
  c = getword(word, MAX_LINE_LEN);
  assert(c == '4');
  c = getword(word, MAX_LINE_LEN);
  assert(c == '5');
  c = getword(word, MAX_LINE_LEN);
  assert(c == '5');
  c = getword(word, MAX_LINE_LEN);
  assert(c == 'a');
  assert(strcmp(word, "abc") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '_');
  c = getword(word, MAX_LINE_LEN);
  assert(c == '*');
  c = getword(word, MAX_LINE_LEN);
  assert(c == '1');
  c = getword(word, MAX_LINE_LEN);
  assert(c == 'j');
  assert(strcmp(word, "jason2") == 0);
  printf("getWord tested.\n");
}

void testGetWord2() {
  printf("Enter the following string: "
         "_ab12 AB_12 12ab_ 12AB test 123 455abc_* 1jason2 "
         "\"this is a 125#test&.\"\n");
  char c, word[MAX_LINE_LEN];
  c = getword2(word, MAX_LINE_LEN);
  printf("c %c\n", c);
  printf("word %s\n", word);
  printf("getWord2 tested.\n");
}

int main() {
  //testGetchAndUngetch();
  //testUngets();
  //testGetWord();
  testGetWord2();
  return 0;
}
