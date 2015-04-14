#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "lib.h"
#define MAX_LINE_NUMBERS 1000

static char *WORDS_TO_IGNORE[] = {"a", "and", "of", "or", "the", "to"};
static int NUM_WORDS_TO_IGNORE = sizeof(WORDS_TO_IGNORE) / sizeof(WORDS_TO_IGNORE[0]);

// Node representing a word in a file.
// word: an actual word.
// line_number: List of int line numbers.
// word_count: Number of occurrences of word in file.
struct node {
  char *word;
  int *line_numbers;
  int word_count;
  int line_count;
  struct node *left;
  struct node *right;
};

struct node *createNode(char *word, int line_number) {
  struct node *node = (struct node *) malloc(sizeof(struct node));
  node->word = (char *) malloc(strlen(word) + 1);
  strcpy(node->word, word);
  node->line_numbers = (int *) malloc(sizeof(int) * MAX_LINE_NUMBERS);
  *node->line_numbers = line_number;
  node->word_count = 1;
  node->line_count = 1;
  node->left = NULL;
  node->right = NULL;
  return node;
}

struct node *addLineNumberToNode(struct node *node, int line_number) {
  node->word_count++;
  int i;
  for (i = 0; i < node->line_count; ++i) {
    if (node->line_numbers[i] == line_number)
      return node; // Don't add duplicate line numbers.
  }
  node->line_numbers[node->line_count] = line_number;
  node->line_count++;
  return node;
}

struct node *addNode(struct node *root, char *word, int line_number) {
  int diff;
  if (root == NULL)
    return createNode(word, line_number);
  if ((diff = strcmp(word, root->word)) < 0) {
    root->left = addNode(root->left, word, line_number);
  } else if (diff > 0) {
    root->right = addNode(root->right, word, line_number);
  } else {
    // We're updating an existing node.
    root = addLineNumberToNode(root, line_number);
  }
  return root;
}

void displayResults(struct node *root) {
  if (root != NULL) {
    displayResults(root->left);
    printf("word: %s, count: %d, ", root->word, root->word_count);
    int i;
    printf("index: [");
    for (i = 0; i < root->line_count; ++i)
      printf("%d%s", root->line_numbers[i], (i + 1 == root->line_count) ? "" : ",");
    printf("]\n");
    displayResults(root->right);
  }
}

int getCrossReferenceWord(char *s, int max_word_len) {
  char c;
  char first_char;
  while ((c = getch()) == ' ' || c == '\t')
    ;
  if (c == EOF)
    return EOF;
  if (c == '\n')
    return '\n';
  if (!isalnum(c)) {
    *s++ = c;
    *s = '\0';
    return c;
  }
  ungetch(c);
  first_char = c = getch();
  while (isalnum(c)) {
    *s++ = c;
    c = getch();
  }
  *s++ = '\0';
  ungetch(c);
  return first_char;
}

int binarySearch(char **arr, char *word, int size) {
  int low = 0;
  int hi = size - 1;
  int mid, diff;
  while (low <= hi) {
    mid = (low + hi) / 2;
    if ((diff=strcmp(word, arr[mid])) < 0) {
      hi = mid - 1;
    } else if (diff > 0) {
      low = mid + 1;
    } else {
      return mid;
    }
  }
  return -1;
}

int isWordToIgnore(char *word) {
  return binarySearch(WORDS_TO_IGNORE, word, NUM_WORDS_TO_IGNORE) >= 0;
}

void testGetWord() {
  char s[MAX_LINE_LEN];
  char c;
  int line_number = 1;
  while ((c = getCrossReferenceWord(s, MAX_LINE_LEN)) != EOF) {
    if (c == '\n') {
      line_number++;
      continue;
    }
    printf("next word is: %s, first char: %c, (line %d)\n", s, c, line_number);
  }
  printf("getCrossReferenceWord tested.\n");
}

void testBinarySearch() {
  assert(binarySearch(WORDS_TO_IGNORE, "a", NUM_WORDS_TO_IGNORE) == 0);
  assert(binarySearch(WORDS_TO_IGNORE, "and", NUM_WORDS_TO_IGNORE) == 1);
  assert(binarySearch(WORDS_TO_IGNORE, "of", NUM_WORDS_TO_IGNORE) == 2);
  assert(binarySearch(WORDS_TO_IGNORE, "or", NUM_WORDS_TO_IGNORE) == 3);
  assert(binarySearch(WORDS_TO_IGNORE, "the", NUM_WORDS_TO_IGNORE) == 4);
  assert(binarySearch(WORDS_TO_IGNORE, "to", NUM_WORDS_TO_IGNORE) == 5);
  assert(binarySearch(WORDS_TO_IGNORE, "jason", NUM_WORDS_TO_IGNORE) == -1);
  printf("binarySearch tested.\n");
}

void testAddNode() {
  struct node *root = NULL;
  root = addNode(root, "foo", 45);
  root = addNode(root, "foo", 23);
  root = addNode(root, "bar", 100);
  root = addNode(root, "bar", 74);
  root = addNode(root, "baz", 200);
  assert(strcmp(root->word, "foo") == 0);
  assert(root->word_count == 2);
  assert(root->line_numbers[0] == 45);
  assert(root->line_numbers[1] == 23);
  assert(strcmp(root->left->word, "bar") == 0);
  assert(root->left->word_count == 2);
  assert(root->left->line_numbers[0] == 100);
  assert(root->left->line_numbers[1] == 74);
  assert(strcmp(root->left->right->word, "baz") == 0);
  assert(root->left->right->word_count == 1);
  assert(root->left->right->line_numbers[0] == 200);
  assert(root->right == NULL);
  assert(root->left->left == NULL);
  assert(root->left->right->left == NULL);
  assert(root->left->right->right == NULL);
  printf("addNode tested.\n");
}

void testIsWordToIgnore() {
  assert(isWordToIgnore("a") == 1);
  assert(isWordToIgnore("jason") == 0);
  printf("isWordToIgnore tested.\n");
}

void testCreateNode() {
  struct node *node = createNode("foo", 26);
  assert(strcmp(node->word, "foo") == 0);
  assert(*node->line_numbers == 26);
  assert(node->line_numbers[0] == 26);
  assert(node->word_count == 1);
  printf("createNode tested.\n");
}

void testAddLineNumberToNode() {
  struct node *node = createNode("foo", 26);
  node = addLineNumberToNode(node, 45);
  node = addLineNumberToNode(node, 101);
  node = addLineNumberToNode(node, 13);
  assert(strcmp(node->word, "foo") == 0);
  assert(node->line_numbers[0] == 26);
  assert(node->line_numbers[1] == 45);
  assert(node->line_numbers[2] == 101);
  assert(node->line_numbers[3] == 13);
  assert(node->word_count == 4);
  printf("addLineNumberToNode tested.\n");
}

void testAll() {
  //testGetWord();
  testBinarySearch();
  testAddNode();
  testIsWordToIgnore();
  testCreateNode();
  testAddLineNumberToNode();
}


/* See K&R question 6-3
 * Write a cross-referencer that prints a list of all words in a document,
 * and, for each word, a list of the line numbers on which it occurs.
 * Remove noise words like "the", "and", and so on.
 */
void testProgram() {
  struct node *root = NULL;
  char word[MAX_LINE_LEN];
  char w;
  int line_number = 1;
  while ((w = getCrossReferenceWord(word, MAX_LINE_LEN)) != EOF) {
    if (w == '\n') {
      ++line_number;
      continue;
    }
    if (!isWordToIgnore(word)) {
      root = addNode(root, word, line_number);
    }
  }
  displayResults(root);
}

int main() {
  //testAll();
  testProgram();
  return 0;
}
