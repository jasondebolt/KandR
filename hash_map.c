#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_KEYS 5

struct node {
  char *key;
  char *value;
  struct node *next;
};

struct node *HashTable[MAX_KEYS];

void printList(struct node *n) {
  while (n != NULL) {
    printf("{%s:%s}->", n->key, n->value);
    n = n->next;
  }
  printf("NULL\n");
}

struct node *getNodeAt(struct node *root, int index) {
  if (index < 0)
    return NULL;
  while (--index >= 0 && root != NULL) {
    root = root->next;
  }
  return root;
}

char *strdup2(char *s) {
  char *result = (char *) malloc(strlen(s) + 1);
  strcpy(result, s);
  return result;
}

struct node *createNode(char *key, char *value) {
  struct node *n = (struct node *) malloc(sizeof(struct node));
  n->key = strdup2(key);
  n->value = strdup2(value);
  n->next = NULL;
  return n;
}

struct node *appendNode(struct node *root, struct node *node) {
  struct node *r = root;
  if (root == NULL)
    return node;
  while (root->next != NULL)
    root = root->next;
  root->next = node;
  return r;
}

struct node *createLinkedList(char *s) {
  char *buffer = (char *) malloc(strlen(s) + 1);
  char *b_start = buffer;
  struct node *node = NULL;
  struct node *root = NULL;
  while (isspace(*s))
    s++;
  while (*s != '\0') {
    while (!isspace(*s) && *s != '\0') {
      *buffer++ = *s++;
    }
    *buffer = '\0';
    node = createNode(b_start, "default");
    root = appendNode(root, node);
    while(isspace(*s))
      s++;
    buffer = b_start;
  }
  return root;
}

int getIndex(char * key) {
  int index = 0;
  while (*key != '\0') {
    index += *key++ * 31;
  }
  return index % MAX_KEYS;
}

struct node *updateOrAppendNode(struct node *root, char *key, char *value) {
  struct node *r_start = root;
  struct node *prev;
  if (root == NULL) {
    return createNode(key, value);
  }
  while (root != NULL) {
    if (strcmp(root->key, key) == 0) {
      strcpy(root->value, value);
      break;
    } else {
      prev = root;
      root = root->next;
    }
  }
  if (root == NULL) {
    prev->next = createNode(key, value);
  }
  return r_start;
}

void printHashTable(struct node *table[]) {
  int i;
  for (i = 0; i < MAX_KEYS; ++i) {
    printf("entry %d\n", i);
    printList(table[i]);
  }
}


void Install(struct node *table[], char *key, char *value) {
  int index = getIndex(key);
  struct node *root = table[index];
  root = updateOrAppendNode(root, key, value);
  table[index] = root;
}


void testGetIndex() {
  char *names[] = {"one", "two", "three", "four", "five"};
  const int num_entries = sizeof(names) / sizeof(names[0]);
  int i;
  for (i = 0; i < num_entries; ++i) {
    printf("%s index %d.\n", names[i], getIndex(names[i]));
  }
  printf("getIndex tested\n");
}

void testCreateLinkedList() {
  printList(createLinkedList("A B C D E F"));
  printf("createLinkedList tested.\n");
}

void testUpdateOrAppendNodeExistingNode() {
  struct node *root = createLinkedList("A B C D");
  assert(strcmp(getNodeAt(root, 3)->key, "D") == 0);
  assert(strcmp(getNodeAt(root, 3)->value, "default") == 0);
  root = updateOrAppendNode(root, "D", "new value");
  assert(strcmp(getNodeAt(root, 3)->value, "new value") == 0);
  printf("updateOrAppendNodeExistingNode tested.\n");
}

void testUpdateOrAppendNodeNewNode() {
  struct node *root = createLinkedList("A B C D");
  assert(getNodeAt(root, 4) == NULL);
  root = updateOrAppendNode(root, "E", "new value");
  assert(strcmp(getNodeAt(root, 4)->key, "E") == 0);
  assert(strcmp(getNodeAt(root, 4)->value, "new value") == 0);
  printf("updateOrAppendNodeNewNode tested.\n");
}

void testUpdateOrAppendNodeNoList() {
  struct node *root = NULL;
  assert(getNodeAt(root, 0) == NULL);
  root = updateOrAppendNode(root, "E", "new value");
  assert(strcmp(getNodeAt(root, 0)->key, "E") == 0);
  assert(strcmp(getNodeAt(root, 0)->value, "new value") == 0);
  printf("updateOrAppendNodeNoList tested.\n");
}

void testPrintHashTable() {
  printHashTable(HashTable);
  printf("printHashTable tested.\n");
}

void testInstall() {
  struct node **table = (struct node **) malloc(sizeof(struct node *) * MAX_KEYS);
  char *names[] = {"the", "quick", "brown", "fox", "jumped", "over", "the",
            "lazy", "dog", "and", "the", "very", "slow", "turtle",
            "bit", "the", "dogs", "face", "off"};
  int count = sizeof(names) / sizeof(names[0]);
  int i;
  char b[3]; // Handle numbers with at most two digits + '\0'.
  for (i = 0; i < count; ++i) {
    sprintf(b, "%d", i);
    Install(table, names[i], b);
  }
  Install(table, "poi", "one");
  printHashTable(table);
  printf("install tested\n");
}

int main() {
  testGetIndex();
  testCreateLinkedList();
  testUpdateOrAppendNodeExistingNode();
  testUpdateOrAppendNodeNewNode();
  testUpdateOrAppendNodeNoList();
  testPrintHashTable();
  testInstall();
  return 0;
}
