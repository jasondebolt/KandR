#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include "lib.h"

#define MAX_BUFF_LEN 100
#define MAX_WORD_LEN 100

char buffer[MAX_BUFF_LEN];
int buffp = 0;

typedef int (*COMP)(char *, char *, int max);

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


struct node {
  struct key *word;
  struct node *left;
  struct node *right;
};

// Compare first n characters of a string.
int compareFirstNChars(char *a, char *b, int max) {
  int diff;
  while ((diff = *a - *b) == 0 && --max > 0) {
    if (*a == '\0')
      return 0;
    a++, b++;
  }
  return *a - *b;
}

int getWord(char *s, int max_len) {
  char c, d;
  int len = 0;
  while (isspace(c = getch()))
    ;
  *s++ = c;
  ++len;
  if (c == EOF) {
    *s = '\0';
    return -1;
  }
  while (!isspace(c = getch()) && --max_len > 0 && c != EOF) {
    *s++ = c;
    ++len;
  }
  *s = '\0';
  if (c == EOF)
    ungetch(c);
  return len;
}

void printNode(struct node *n) {
  printf("name: %s, count: %d\n", n->word->name, n->word->count);
}

void inOrderPrint(struct node *root) {
  if (root != NULL) {
    inOrderPrint(root->left);
    printNode(root);
    inOrderPrint(root->right);
  }
}

struct key *createKey(char *name) {
  struct key *key = (struct key *) malloc(sizeof(struct key));
  key->name = (char *) malloc(strlen(name) + 1);
  strcpy(key->name, name);
  key->count = 1;
  return key;
}

struct node *createNode(char *name) {
  struct node *n = (struct node *) malloc(sizeof(struct node));
  n->word = createKey(name);
  n->left = NULL;
  n->right = NULL;
  return n;
}

void freeKey(struct key **word) {
  if (*word != NULL) {
    free((*word)->name);
    (*word)->name = NULL;
    (*word)->count = -1;
    free(*word);
    *word = NULL;
  }
}

void freeNode(struct node **root) {
  if (*root != NULL) {
    freeNode(&(*root)->left);
    freeNode(&(*root)->right);
    freeKey(&(*root)->word);
    free(*root);
    *root = NULL;
  }
}

struct node *addNode(struct node *root, struct node *node, COMP cmp) {
  if (root == NULL) {
    return node;
  }
  int diff = cmp(node->word->name, root->word->name, UINT_MAX);
  if (diff < 0) {
    root->left = addNode(root->left, node, cmp);
  } else if (diff > 0) {
    root->right = addNode(root->right, node, cmp);
  } else {
    root->word->count++;
  }
  return root;
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

void testNode() {
  struct key l_word = {"abs", 0};
  struct key r_word = {"break", 0};
  struct key ro_word = {"case", 0};
  struct node left = {&l_word, NULL, NULL};
  struct node right = {&r_word, NULL, NULL};
  struct node root = {&ro_word, &left, &right};
  inOrderPrint(&root);
  printf("node tested.\n");
}

void testCreateNode() {
  struct node *n = createNode("new node");
  assert(strcmp(n->word->name, "new node") == 0);
  assert(n->word->count == 1);
  assert(n != NULL);
  freeNode(&n);
  assert(n == NULL);
  printf("createNode tested.\n");
}

void testCreateKey() {
  struct key *key = createKey("new key");
  assert(strcmp(key->name, "new key") == 0);
  assert(key->count == 1);
  assert(key != NULL);
  freeKey(&key);
  assert(key == NULL);
  printf("createKey tested.\n");
}

void testAddNode() {
  struct node *root = createNode("F");
  struct node *g = createNode("G");
  struct node *a = createNode("A");
  struct node *c = createNode("C");
  struct node *h = createNode("H");
  assert(root->right == NULL);
  assert(root->left == NULL);
  COMP cmp = (COMP) strcmp;
  root = addNode(root, g, cmp);
  root = addNode(root, c, cmp);
  assert(root->right == g);
  assert(root->left == c);
  root = addNode(root, a, cmp);
  root = addNode(root, h, cmp);
  root = addNode(root, h, cmp);
  root = addNode(root, h, cmp);
  root = addNode(root, a, cmp);
  root = addNode(root, createNode("jason"), cmp);
  inOrderPrint(root);
  printf("addNode tested.\n");
}

void testLoadKeys() {
  char s[MAX_WORD_LEN];
  struct node *root = NULL;
  int len;
  COMP cmp = (COMP) strcmp;
  while((len = getWord(s, MAX_WORD_LEN)) >= 0) {
    root = addNode(root, createNode(s), cmp);
  }
  inOrderPrint(root);
  printf("loadKeys tested.\n");
}

void testCompareFirstNChars() {
  assert(compareFirstNChars("", "", 6) == 0);
  assert(compareFirstNChars("a", "a", 6) == 0);
  assert(compareFirstNChars(" abc ", " abc ", 6) == 0);
  assert(compareFirstNChars("ab", "aB", 1) == 0);
  assert(compareFirstNChars("abcABC123", "abcABC456", 6) == 0);
  printf("compareFirstNChars tested.\n");
}

void testLoadKeysFirstNCharacters(int argc, char *argv[]) {
  // USAGE: ./a.out 10   --> compare the first 10 characters only.
  assert(argc == 2);
  char s[MAX_WORD_LEN];
  char *s_truncated;
  struct node *root = NULL;
  int len;
  int num_chars;
  //COMP cmp = (COMP) compareFirstNChars;
  COMP cmp = (COMP) strcmp;
  while ((len = getCToken(s, MAX_WORD_LEN)) != EOF) {
    num_chars = atoi(argv[1]);
    s_truncated = s;
    while (--num_chars >= 0)
      s_truncated++;
    *s_truncated = '\0';
    root = addNode(root, createNode(s), cmp);
  }
  inOrderPrint(root);
  printf("loadKeys tested.\n");
}

// ./a.out 6 --> Will compare the first six characters only.
int main(int argc, char *argv[]) {
  //testGetch();
  //testGetWord();
  //testGetWords();
  //testKeys();
  //testNode();
  //testCreateNode();
  //testCreateKey();
  //testAddNode();
  //testCompareFirstNChars();
  //testGetInt();
  //testLoadKeys();
  testLoadKeysFirstNCharacters(argc, argv);
  return 0;
}
