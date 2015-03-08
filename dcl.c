#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define DEBUG 0
#define MAX_NAME_LEN 50
#define MAX_TOKEN_LEN 100
#define MAX_OUTPUT_LEN 1024
#define BUFFER_SIZE 10

enum {NAME, PARENS, BRACKETS};
char token[MAX_TOKEN_LEN];   // The last taken read.
int token_type;  // either NAME, PARENS, BRACKETS.
char buffer[BUFFER_SIZE];  // getchar buffer size.
int buffer_p = 0;
char out[MAX_OUTPUT_LEN];
char name[MAX_NAME_LEN];
char data_type[MAX_NAME_LEN];

int getToken();
int dcl();
int dir_dcl();

void printState() {
  printf("token_type: %d \t token: %s\n", token_type, token);
}

char mygetchar() {
  if (buffer_p <= 0) {
    return getc(stdin);
  } else {
    return buffer[--buffer_p];
  }
}

void myungetchar(char c) {
  buffer[buffer_p++] = c;
}


/* Gets the next declaration token.
 *
 * A token is one of the following:
 *  1) An alphanumeric string (NAME)
 *  2) Opening and closing parens (PARENS)
 *  3) Opening and closing brackets, possibly with a value between (BRACKETS)
 *  4) Any other single non-whitespace character.
 */
int getToken() {
  char d;
  char c = mygetchar();
  char *tmp = token;

  while (c == ' ' || c == '\t')
    c = mygetchar();

  while (c != '\n' && c != EOF) {
    // Check for name.
    if (isalnum(c)) {
      while (isalnum(c)) {
        *tmp++ = c;
        c = mygetchar();
      }
      myungetchar(c);
      *tmp = '\0';
      return token_type = NAME;
    } else if (c == '(') {
      if ((d = mygetchar()) == ')') {
        strcpy(token, "()");
        return token_type = PARENS;
      } else {
        myungetchar(d);
        *tmp++ = c;
        *tmp = '\0';
        return token_type = c;
      }
    } else if (c == '[') {
      if ((d = mygetchar()) == ']') {
        strcpy(token, "[]");
        return token_type = BRACKETS;
      } else {
        myungetchar(d);
      }
      *tmp++ = c;
      while (isdigit(d = mygetchar())) {
        *tmp++ = d;
      }
      if (d == ']') {
        *tmp++ = d;
        *tmp = '\0';
        return token_type = BRACKETS;
      }
    }
    *tmp++ = c;
    *tmp = '\0';
    return token_type = c;
  }
  *tmp = '\0';
  return token_type = -1;
}

int dcl() {
  int num_pointers = 0;
  char tmp[MAX_OUTPUT_LEN];
  tmp[0] = '\0';
  while (token_type == '*') {
    getToken();
    num_pointers++;
  }
  if (DEBUG) {
    printf("calling dir_dcl() from dcl()\t");
    printState();
  }
  dir_dcl();
  if (DEBUG) {
    printf("finished calling dir_dcl() from dcl()\t");
    printState();
  }
  while (--num_pointers >= 0) {
    strcat(tmp, "pointer to ");
  }
  strcat(out, tmp);
  return 0;
}

int dir_dcl() {
  char tmp[MAX_OUTPUT_LEN];
  if (token_type == NAME) {
    strcpy(name, token);
  } else if (token_type == '(') {
    getToken();
    if (DEBUG) {
      printf("calling dcl() from dir_dcl()\t");
      printState();
    }
    dcl();
    if (DEBUG) {
      printf("finished calling dcl() from dir_dcl()\t");
      printState();
    }
    if (token_type != ')') {
      printf("Token was actually %c", token_type);
      fprintf(stderr, "Error: There was no closing parentheses.\n");
    }
  }
  while (getToken() >= 0 && token_type != ')') {
    if (token_type == PARENS) {
      strcat(out, "function returning ");
    }
    if (token_type == BRACKETS) {
      strcat(out, "array");
      strcat(out, token);
      strcat(out, " of ");
    }
  }
  return 0;
}


void testGetToken() {
  int result;
  printf("Enter the following declaration: (*pfa[])():\n");
  result = getToken();
  assert(result == 40 && strcmp(token, "(") == 0);
  result = getToken();
  assert(result == 42 && strcmp(token, "*") == 0);
  result = getToken();
  assert(result == NAME && strcmp(token, "pfa") == 0);
  result = getToken();
  assert(result == BRACKETS && strcmp(token, "[]") == 0);
  result = getToken();
  assert(result == 41 && strcmp(token, ")") == 0);
  result = getToken();
  assert(result == PARENS && strcmp(token, "()") == 0);
  printf("getToken tested.\n");
}

void testGetTokenInteractive() {
  printf("Enter a declaration:\n");
  int result;
  while ((result = getToken()) >= 0) {
    printf("result: %d, token: %s\n", result, token);
  }
  printf("getToken interactive tested.\n");
}


void testSPrintf() {
  char tmp[100] = "bar";
  sprintf(tmp, "foo %s baz", tmp);
  printf("%s\n", tmp);
}

int main() {
  //testSPrintf();
  //testGetTokenInteractive();
  //testGetToken();

  getToken();
  // first token will be the data type.
  strcpy(data_type, token);
  getToken();
  if (DEBUG) {
    printf("calling dcl() from main()\t");
    printState();
  }
  dcl();
  printf("%s: %s%s\n", name, out, data_type);
  return 0;
}
