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

enum {NAME, PARENS, BRACKETS, COMMA, TYPE, AUTO, CHAR, CONST, DOUBLE, EXTERN,
      FLOAT, INT, LONG, REGISTER, SHORT, SIGNED, STATIC, TYPEDEF, UNSIGNED,
      VOID, VOLATILE};
char token[MAX_TOKEN_LEN];   // The last taken read.
int token_type;  // either NAME, PARENS, BRACKETS, TYPE, etc.
char buffer[BUFFER_SIZE];  // getchar buffer size.
int buffer_p = 0;
char out[MAX_OUTPUT_LEN];
char name[MAX_NAME_LEN];
char data_type[MAX_NAME_LEN];
int very_last_token_type = -1;

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

struct type {
  char *token;
  int token_id;
  char *token_class;
} types[] = {
  "auto",      AUTO,     "storage-class-specifier",
  "char",      CHAR,     "type-specifier",
  "const",     CONST,    "type-qualifier",
  "double",    DOUBLE,   "type-specifier",
  "extern",    EXTERN,   "storage-class-specifier",
  "float",     FLOAT,    "type-specifier",
  "int",       INT,      "type-specifier",
  "long",      LONG,     "type-specifier",
  "register",  REGISTER, "storage-class-specifier",
  "short",     SHORT,    "type-specifier",
  "signed",    SIGNED,   "type-specifier",
  "static",    STATIC,   "storage-class-specifier",
  "typedef",   TYPEDEF,  "storage-class-specifier",
  "unsigned",  UNSIGNED, "type-specifier",
  "void",      VOID,     "type-specifier",
  "volatile",  VOLATILE, "type-qualifier"
};


// Gets the type from a token.
// Returns 0 if result found, else -1.
int getTypeFromToken(struct type *tp, char *token) {
  int mid;
  int low = 0;
  int high = sizeof(types) / sizeof(types[0]) - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if (strcmp(token, types[mid].token) < 0) {
      high = mid - 1;
    } else if (strcmp(token, types[mid].token) > 0) {
      low = mid + 1;
    } else {
      *tp = types[mid];
      return 0;
    }
  }
  return -1;
}

// Gets the type from a token id.
int getTypeFromTokenId(struct type *tp, int token_id) {
  int mid;
  int low = 0;
  int high = sizeof(types) / sizeof(types[0]) - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if (token_id < types[mid].token_id) {
      high = mid - 1;
    } else if (token_id > types[mid].token_id) {
      low = mid + 1;
    } else {
      *tp = types[mid];
      return 0;
    }
  }
  return -1;
}

int isTypeToken(int token_id) {
  return token_id >= AUTO && token_id <= VOLATILE;
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
  char tmp2[MAX_NAME_LEN];

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
      struct type *tp = (struct type *) malloc(sizeof(struct type));
      if (getTypeFromToken(tp, token) == 0) {
        very_last_token_type = TYPE;
      } else {
        very_last_token_type = NAME;
      }
      return token_type = NAME;
    } else if (c == '(') {
      if ((d = mygetchar()) == ')') {
        strcpy(token, "()");
        return token_type = PARENS;
      } else if (very_last_token_type == NAME) {
        // This is probably a function with parameters.
        myungetchar(d);
        *tmp++ = '(';
        while ((c = mygetchar()) != ')') {
          *tmp++ = c;
        }
        *tmp++ = ')';
        *tmp = '\0';
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
      *tmp++ = c; // This is needed for char (*foo[23])() to output correctly.
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
  int last_token_type = -1;
  if (token_type == NAME) {
    last_token_type = NAME;
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
      exit(1);
    }
  }
  while (getToken() >= 0 && (token_type == PARENS || token_type == BRACKETS)) {
    if (token_type == PARENS) {
      if (last_token_type == BRACKETS) {
        fprintf(stderr, "Cannot have an array of functions. "
                        "Use of array of pointers to functions instead "
                        "(*foo[])().\n");
        exit(1);
      }
      if (last_token_type == NAME) {
        printf("Last token type was a name!!!\n");
      }
      last_token_type = PARENS;
      strcat(out, "function");
      strcat(out, token);
      strcat(out, " returning ");
    }
    if (token_type == BRACKETS) {
      if (last_token_type == PARENS) {
        fprintf(stderr, "Cannot return an array from a function. "
                        "Return a pointer to an array instead (*foo())[].\n");
        exit(1);
      }
      last_token_type = BRACKETS;
      strcat(out, "array");
      strcat(out, token);
      strcat(out, " of ");
    }
  }
  if (token_type != ')' && token_type != EOF) {
    fprintf(stderr, "Invalid token input within dir_dcl\n");
    exit(1);
  }
  return 0;
}

void printTokenOutput() {
  printf("Enter a declaration:\n");
  while (getToken() != EOF) {
    printf("%s: %d %s\n", ((token_type == NAME) ? "NAME" :
                       (token_type == PARENS) ? "PARENS":
                       (token_type == BRACKETS) ? "BRACKETS" : "OTHER"),
                        token_type, token);
  }
}

void validateDataType(char *token) {
  struct type t;
  struct type *tp = &t;
  if (getTypeFromToken(tp, token) == -1) {
    fprintf(stderr, "Unknown data type.\n");
    exit(1);
  }
}

void RunDcl() {
  printf("Enter something like 'char (*foo[23])(int, float)'\n");
  char tmp[MAX_NAME_LEN];
  char tmp2[MAX_OUTPUT_LEN];
  int storage_specifier, type_specifier, type_qualifier;
  storage_specifier = type_specifier = type_qualifier = 0;
  struct type *tp = (struct type *) malloc(sizeof(struct type));
  data_type[0] = '\0';
  for (; getToken(), getTypeFromToken(tp, token) != -1;) {
    if (strcmp(tp->token_class, "storage-class-specifier") == 0) {
      if (storage_specifier >= 1) {
        fprintf(stderr, "Storage specifier can only be listed once.\n");
        exit(1);
      }
      storage_specifier = 1;
    }
    if (strcmp(tp->token_class, "type-specifier") == 0) {
      if (type_specifier >= 1) {
        fprintf(stderr, "Type specifier can only be listed once.\n");
        exit(1);
      }
      type_specifier = 1;
    }
    if (strcmp(tp->token_class, "type-qualifier") == 0) {
      if (type_qualifier >= 1) {
        fprintf(stderr, "Type qualifier can only be listed once.\n");
        exit(1);
      }
      type_qualifier = 1;
    }
    if (strlen(data_type) == 0) {
      strcpy(tmp, token);
    } else {
      sprintf(tmp, "%s %s", data_type, token);
    }
    strcpy(data_type, tmp);
  }
  if (DEBUG) {
    printf("calling dcl() from main()\t");
    printState();
  }
  dcl();
  sprintf(tmp2, "%s: %s%s\n", name, out, data_type);
  strcpy(out, tmp2);
  printf("%s\n", out);
}

// Converts streams like x () * [] * () char
// to
// char (*(*x())[])()
void un_dcl() {
  getToken();
  strcpy(out, token);
  char tmp[MAX_OUTPUT_LEN];
  int last_token = -1;
  while (getToken() != EOF) {
    if (token_type == NAME) {
      last_token = NAME;
      strcpy(data_type, token);
    } else if (token_type == PARENS) {
      if (last_token == '*') {
        sprintf(tmp, "(%s)", out);
        strcpy(out, tmp);
      }
      last_token = PARENS;
      strcat(out, token);
    } else if (token_type == BRACKETS) {
      if (last_token == '*') {
        sprintf(tmp, "(%s)", out);
        strcpy(out, tmp);
      }
      last_token = BRACKETS;
      strcat(out, token);
    } else if (token_type == '*') {
      last_token = '*';
      sprintf(tmp, "*%s", out);
      strcpy(out, tmp);
    }
  }
  sprintf(tmp, "%s %s", data_type, out);
  strcpy(out, tmp);
  printf("%s\n", out);
}

void RunUnDcl() {
  printf("Enter something like 'foo * [] * () char' \n"
         "(foo is a pointer to an array returning a pointers "
         "to functions returning char)\n");
  un_dcl();
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

void testUnDcl() {
  printf("Copy and past this string:\n"
         "foo * [123] * (int, float) char\n");
  un_dcl();
  assert(strcmp(out, "char (*(*foo)[123])(int, float)") == 0);
  printf("un_dcl tested.\n");
}

void testDcl() {
  printf("Copy and paste this string:\n"
         "char (*(*(*(*func[12])(int, char, float))"
         "(unsigned double, struct point))(char, struct rect))))\n");
  RunDcl();
  assert(strcmp(out, "func: array[12] of pointer to function(int, char, float) "
                     "returning pointer to function(unsigned double, struct "
                     "point) returning pointer to function(char, struct rect) "
                     "returning pointer to char\n") == 0);
  printf("dcl tested.\n");
}

void testGetTypeFromTokenId() {
  struct type *tp = (struct type *) malloc(sizeof(struct type));
  assert(getTypeFromTokenId(tp, CHAR) == 0);
  assert(strcmp(tp->token, "char") == 0);
  assert(getTypeFromTokenId(tp, VOLATILE) == 0);
  assert(strcmp(tp->token, "volatile") == 0);
  assert(getTypeFromTokenId(tp, 123456) == -1);
  printf("getTypeFromTokenId tested.\n");
}

void testGetTypeFromToken() {
  struct type *tp = (struct type *) malloc(sizeof(struct type));
  assert(getTypeFromToken(tp, "char") == 0);
  assert(tp->token_id == CHAR);
  assert(getTypeFromToken(tp, "volatile") == 0);
  assert(tp->token_id == VOLATILE);
  assert(getTypeFromToken(tp, "blah") == -1);
  printf("getTypeFromTokenToken tested.\n");
}

/* Page 122 of K&R...
 *
 * dcl:        optional *'s direct-dcl
 * direct-dcl: name
 *             (dcl)
 *             direct-dcl[optoinal size]
 *             direct-dcl()
 */
int main() {
  /* Interactive tests */
  // printTokenOutput();
  // testGetToken();
  // testDcl();
  // testUnDcl();

  /* Non-Interactive tests. */
  // testGetTypeFromToken();
  // testGetTypeFromTokenId();

  /* programs */
  //RunUnDcl();
  RunDcl();

  /* NEXT STEPS FOR UN-DCL:
   * - Convert 'foo () []' to '(*foo())[]' instead of foo()[]'?
   */
  return 0;
}
