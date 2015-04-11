#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

#define MAX_BUFF_LEN 100
#define MAX_WORD_LEN 100

char buffer[MAX_BUFF_LEN];
int buffp = 0;

struct node {
  char *value;
  struct node *next;
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
  if (c == '.') {
    *s = '\0';
    return -1;
  }
  while (!isspace(c = getch()) && --max_len > 0 && c != '.') {
    *s++ = c;
    ++len;
  }
  *s = '\0';
  if (c == '.')
    ungetch(c);
  return len;
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
  assert(len == 5);
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

char *strval(char *val) {
  char *s = (char *) malloc(strlen(val) + 1);
  strcpy(s, val);
  return s;
}

struct node *createNode(char *s) {
  struct node *n = (struct node*) malloc(sizeof(struct node));
  n->value = (char *) malloc(strlen(s) + 1);
  strcpy(n->value, s);
  n->next = NULL;
  return n;
}

struct node *createLinkedList(int n_args, ...) {
  char s[MAX_WORD_LEN];
  va_list ap;
  va_start(ap, n_args);
  strcpy(s, va_arg(ap, char*));
  struct node *n = createNode(s);
  struct node *n_copy = n;
  while (--n_args >= 1) {
    strcpy(s, va_arg(ap, char*));
    n->next = createNode(s);
    n = n->next;
  }
  va_end(ap);
  return n_copy;
}

void printList(struct node *n) {
  while (n != NULL) {
    printf("val: %s\n", n->value);
    n = n->next;
  }
}

struct node *appendNode(struct node *first, struct node *second) {
  if (first == NULL)
    return second;
  struct node *n = first;
  while (first->next != NULL)
    first = first->next;
  first->next = second;
  return n;
}

struct node *getNodeAt(struct node *node, int index) {
  assert(index >= 0);
  while (--index >= 0 && node != NULL)
    node = node->next;
  return node;
}

//prepend val to head.
struct node *prependNode(struct node *head, struct node *val) {
  if (head == NULL)
    return val;
  val->next = head;
  return val;
}

struct node *popNode(struct node *head) {
  struct node *prev = (struct node *) malloc(sizeof(struct node));
  if (head->next == NULL) {
    // we can't simply do 'head = NULL'
    prev->value = (char *) malloc(strlen(head->value) + 1);
    strcpy(prev->value, head->value);
    prev->next = NULL;
    strcpy(head->value, "(empty)");
    return prev;
  }
  while (head->next != NULL) {
    prev = head;
    head = head->next;
  }
  prev->next = NULL;
  return head;
}

struct node *peekTail(struct node *head) {
  while (head->next != NULL)
    head = head->next;
  return head;
}


// this cannot delete the first node.
void deleteNode(struct node *root, char *name) {
  struct node *prev;
  while (strcmp(root->value, name) != 0) {
    prev = root;
    root = root->next;
  }
  prev->next = root->next;
}


struct node *deleteNode2(struct node *root, char *name) {
  struct node *r = root;
  struct node *prev;
  if (strcmp(root->value, name) == 0)
    return root->next;
  while (strcmp(root->value, name) != 0) {
    prev = root;
    root = root->next;
  }
  prev->next = root->next;
  return r;
}

void insertNodeAt(struct node **node, int index, char *value) {
  struct node *new = createNode(value);
  new->next = getNodeAt(*node, index);
  if (index == 0) {
    *node = new;
  } else {
    getNodeAt(*node, index - 1)->next = new;
  }
}

void testCreateNode() {
  struct node *n = createNode("a node");
  assert(strcmp(n->value, "a node") == 0);
  assert(n->next == NULL);
  printf("createNode tested.\n");
}


void testCreateLinkedList() {
  struct node *node = createLinkedList(6, "A", "B", "C", "D", "E", "F");
  assert(strcmp(node->value, "A") == 0);
  assert(strcmp(node->next->value, "B") == 0);
  assert(strcmp(node->next->next->value, "C") == 0);
  assert(strcmp(node->next->next->next->value, "D") == 0);
  assert(strcmp(node->next->next->next->next->value, "E") == 0);
  assert(strcmp(node->next->next->next->next->next->value, "F") == 0);
  assert(node->next->next->next->next->next->next == NULL);
  printf("createLinkedList tested.\n");
}

void testPrintList() {
  struct node *node = createLinkedList(6, "A", "B", "C", "D", "E", "F");
  printList(node);
  printf("printList tested.\n");
}

void testGetNodeAt() {
  struct node *node = createLinkedList(6, "A", "B", "C", "D", "E", "F");
  assert(strcmp(getNodeAt(node, 0)->value, "A") == 0);
  assert(strcmp(getNodeAt(node, 5)->value, "F") == 0);
  assert(getNodeAt(node, 6) == NULL);
  assert(getNodeAt(node, 6666) == NULL);
  printf("getNodeAt tested.\n");
}

void testAppendNode() {
  struct node *zero = NULL;
  struct node *first = createNode("first");
  struct node *second = createNode("second");
  struct node *third = createNode("third");
  zero = appendNode(zero, first);
  zero = appendNode(zero, second);
  zero = appendNode(zero, third);
  printList(zero);
  printf("appendNode tested.\n");
}

void testPrependNode() {
  struct node *zero = NULL;
  struct node *first = createNode("first");
  struct node *second = createNode("second");
  struct node *third = createNode("third");
  zero = prependNode(zero, first);
  zero = prependNode(zero, second);
  zero = prependNode(zero, third);
  printList(zero);
  printf("prependNode tested.\n");
}

void testPopNode() {
  struct node *head = createLinkedList(6, "A", "B", "C", "D", "E", "F");
  printList(head);
  assert(strcmp(popNode(head)->value, "F") == 0);
  assert(strcmp(peekTail(head)->value, "E") == 0);
  assert(strcmp(popNode(head)->value, "E") == 0);
  assert(strcmp(popNode(head)->value, "D") == 0);
  assert(strcmp(popNode(head)->value, "C") == 0);
  assert(strcmp(popNode(head)->value, "B") == 0);
  assert(strcmp(peekTail(head)->value, "A") == 0);
  assert(strcmp(popNode(head)->value, "A") == 0);
  assert(strcmp(peekTail(head)->value, "(empty)") == 0);
  assert(strcmp(popNode(head)->value, "(empty)") == 0);
  assert(strcmp(popNode(head)->value, "(empty)") == 0);
  printf("popNode tested.\n");
}

void testPeekTailNode() {
  struct node *head = createLinkedList(6, "A", "B", "C", "D", "E", "F");
  assert(strcmp(peekTail(head)->value, "F") == 0);
  assert(strcmp(peekTail(head)->value, "F") == 0);
  printf("peekTailNode tested.\n");
}

void testDeleteNode() {
  struct node *node = createLinkedList(6, "A", "B", "C", "D", "E", "F");
  deleteNode(node, "C");
  deleteNode(node, "D");
  deleteNode(node, "F");
  assert(strcmp(node->value, "A") == 0);
  assert(strcmp(node->next->value, "B") == 0);
  assert(strcmp(node->next->next->value, "E") == 0);
  assert(node->next->next->next == NULL);
  printf("deleteNode tested.\n");
}

void testDeleteNode2() {
  struct node *node = createLinkedList(6, "A", "B", "C", "D", "E", "F");
  node = deleteNode2(node, "C");
  assert(strcmp(node->value, "A") == 0);
  assert(strcmp(node->next->value, "B") == 0);
  assert(strcmp(node->next->next->value, "D") == 0);
  node = deleteNode2(node, "A");
  assert(strcmp(node->value, "B") == 0);
  printf("deleteNode2 tested.\n");
}


void testInsertNodeAt() {
  struct node *node = createLinkedList(6, "A", "B", "C", "D", "E", "F");  assert(strcmp(getNodeAt(node, 2)->value, "C") == 0);
  insertNodeAt(&node, 2, "P");
  assert(strcmp(getNodeAt(node, 1)->value, "B") == 0);
  assert(strcmp(getNodeAt(node, 2)->value, "P") == 0);
  assert(strcmp(getNodeAt(node, 3)->value, "C") == 0);
  insertNodeAt(&node, 0, "T");
  assert(strcmp(getNodeAt(node, 0)->value, "T") == 0);
  assert(strcmp(getNodeAt(node, 1)->value, "A") == 0);
  insertNodeAt(&node, 7, "J");
  assert(strcmp(getNodeAt(node, 7)->value, "J") == 0);
  assert(strcmp(getNodeAt(node, 8)->value, "F") == 0);
  printf("insertNode tested.\n");
}


int main() {
  //testGetch();
  //testGetWord();
  //testGetWords();
  testCreateNode();
  testCreateLinkedList();
  testPrintList();
  testGetNodeAt();
  testAppendNode();
  testPrependNode();
  testPopNode();
  testPeekTailNode();
  testDeleteNode();
  testDeleteNode2();
  testInsertNodeAt();
  return 0;
}
