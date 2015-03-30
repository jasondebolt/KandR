#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#define MAX_LINE_LEN 1024
#define dprint(expr) printf(#expr " = %g\n", expr)

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
 * A word is one of the following:
 *   - A string starting with a letter or an understore, containg letters, numbers
 *      or underscores.
 *   - A string literal, including the quotes.
 *   - A preprocessor control line (#include <ctype.h>)
 *   - A single non-whitespace character.
 */
int getword2(char *word, int lim) {
  char c, next, last, end;
  char *w = word;
  // At this point, c is a non whitespace character.
  while ((c = getch()) != EOF) {
    if (c == '#') {
      *w++ = c;
      while ((c = getch()) != '\n')
        *w++ = c;
      *w = '\0';
      // Save preprocessor directive until end of line.
      break;
    } else if (c == '"') {
      // We may have a string literal.
      *w++ = c;
      while ((c = getch()) != '"')
        *w++ = c;
      *w++ = c;
      *w = '\0';
      break;
    } else if (isspace(c)) {
      while (isspace(c = getch()))
        ; 
      ungetch(c);  // ungetch the last non-whitespace char.
    } else if (c == '/') {
      next = getch();
      if (next == '/') {
        // We're in a single line comment.
        // skip through the entire comment.
        while ((c = getch()) != '\n')
          ;
      } else if (next == '*') {
        // We're in a possible multi-line comment.
        // Skip through the entire multi-line comment.
        while (1) {
          // skip until the next '*' char. This may be the end.
          while ((last = getch()) != '*')
            ;
          // Check to see if this really is the end of the comment.
          if ((end = getch()) == '/') {
            // We've found the end of the comment.
            break;
          } else {
            ungetch(next);
          }
        }
      } else {
        // This is not a comment. Return the single '/' char.
        ungetch(next);
        *w++ = c;
        *w = '\0';
        break;
      }
      // Check if inside comment.
      // If inside comment, skip past comment.
      // If not inside comment, ungetch one char.
    } else if (isalpha(c) || c == '_') {
      // We may have a full word.
      // Loop through all digit, chars, and underscores until reach space.
      // Store results in word.
      // Return first char.
      *w++ = c;
      while (isalnum(c = getch()) || c == '_')
        *w++ = c;
      *w = '\0';
      ungetch(c); // ungetch that last non _aA123 char.
      break;
    } else {
      // Store single character in word.
      // Return character. (could be digit, /, *, etc.)
      *w++ = c;
      *w = '\0';
      break;
    }
  }
  return word[0];
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
  assert(strcmp(word, "1") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '2');
  assert(strcmp(word, "2") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == 'a');
  assert(strcmp(word, "ab") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '1');
  assert(strcmp(word, "1") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '2');
  assert(strcmp(word, "2") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == 'A');
  assert(strcmp(word, "AB") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == 't');
  assert(strcmp(word, "test") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '1');
  assert(strcmp(word, "1") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '2');
  assert(strcmp(word, "2") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '3');
  assert(strcmp(word, "3") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '4');
  assert(strcmp(word, "4") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '5');
  assert(strcmp(word, "5") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '5');
  assert(strcmp(word, "5") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == 'a');
  assert(strcmp(word, "abc") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '_');
  assert(strcmp(word, "_") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '*');
  assert(strcmp(word, "*") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '1');
  assert(strcmp(word, "1") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == 'j');
  assert(strcmp(word, "jason2") == 0);
  printf("getWord tested.\n");
}

void testGetWord2() {
  printf("Enter the following program:\n"
         "#include <stdio.h>\n"
         "\n"
         "/* this is the /*main* program\n"
         " * to \"execute\" in this file.\n"
         " */\n"
         "int main() {\n"
         "  // create a string.\n"
         "  char _someName_123[10] = \"jason\";\n"
         "  return 123 / 12 ** 4;\n"
         "}\n");
  char c, word[MAX_LINE_LEN];
  //while ((c = getword2(word, MAX_LINE_LEN))) {
  //  printf("assert(c == '%c');\n", c);
  //  printf("assert(strcmp(word, \"%s\") == 0);\n", word);
  //}
  c = getword2(word, MAX_LINE_LEN);
  assert(c == '#');
  assert(strcmp(word, "#include <stdio.h>") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == 'i');
  assert(strcmp(word, "int") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == 'm');
  assert(strcmp(word, "main") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == '(');
  assert(strcmp(word, "(") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == ')');
  assert(strcmp(word, ")") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == '{');
  assert(strcmp(word, "{") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == 'c');
  assert(strcmp(word, "char") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == '_');
  assert(strcmp(word, "_someName_123") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == '[');
  assert(strcmp(word, "[") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == '1');
  assert(strcmp(word, "1") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == '0');
  assert(strcmp(word, "0") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == ']');
  assert(strcmp(word, "]") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == '=');
  assert(strcmp(word, "=") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == '"');
  assert(strcmp(word, "\"jason\"") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == ';');
  assert(strcmp(word, ";") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == 'r');
  assert(strcmp(word, "return") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == '1');
  assert(strcmp(word, "1") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == '2');
  assert(strcmp(word, "2") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == '3');
  assert(strcmp(word, "3") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == '/');
  assert(strcmp(word, "/") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == '1');
  assert(strcmp(word, "1") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == '2');
  assert(strcmp(word, "2") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == '*');
  assert(strcmp(word, "*") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == '*');
  assert(strcmp(word, "*") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == '4');
  assert(strcmp(word, "4") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == ';');
  assert(strcmp(word, ";") == 0);
  c = getword2(word, MAX_LINE_LEN);
  assert(c == '}');
  assert(strcmp(word, "}") == 0);
  printf("getWord2 tested.\n");
}

int main() {
  //testGetchAndUngetch();
  //testUngets();
  //testGetWord();
  testGetWord2();
  return 0;
}
