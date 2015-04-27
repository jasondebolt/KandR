#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "lib.h"

#define MAX_WORD_LEN 1000
#define MAX_WORD_OCCURRENCES 10000

struct node {
  char *word;
  int word_count;
  int child_node_count;
  int child_word_count;
  struct node *left;
  struct node *right;
};

static struct node **NODE_LIST;

void displayNode(struct node *node) {
  printf("word: %s, word_count: %d, child_node_count: %d, "
         "child_word_count: %d\n", node->word, node->word_count,
         node->child_node_count, node->child_word_count);
}

void displayReverseStringResult(struct node *node) {
  if (node != NULL) {
    displayReverseStringResult(node->right);
    displayNode(node);
    displayReverseStringResult(node->left);
  }
}

void quickSortInts(int vals[], int start_i, int end_i) {
  if (start_i >= end_i) {
    return;
  }
  int mid = (start_i + end_i) / 2;
  int cursor = start_i; // cursor is incremented after swaps.
  int i; // i is increment after each loop iteration.
  SWAP(vals[start_i], vals[mid]); // swap value at start with value at mid.
  for (i = start_i + 1; i <= end_i; ++i) {
    if (vals[i] <= vals[start_i]) {
      SWAP(vals[++cursor], vals[i]);
    }
  }
  SWAP(vals[start_i], vals[cursor]);
  quickSortInts(vals, start_i, cursor - 1);
  quickSortInts(vals, cursor + 1, end_i);
}

void quickSortNodes(struct node **nodes, int start_i, int end_i, int reverse) {
  if (start_i >= end_i) {
    return;
  }
  int mid = (start_i + end_i) / 2;
  int cursor = start_i; // cursor is incremented after swaps.
  int i; // i is increment after each loop iteration.
  SWAP(nodes[start_i], nodes[mid]); // swap value at start with value at mid.
  for (i = start_i + 1; i <= end_i; ++i) {
    if (reverse) {
      if (!(nodes[i]->word_count <= nodes[start_i]->word_count)) {
        SWAP(nodes[++cursor], nodes[i]);
      }
    } else {
      if ((nodes[i]->word_count <= nodes[start_i]->word_count)) {
        SWAP(nodes[++cursor], nodes[i]);
      }
    }
  }
  SWAP(nodes[start_i], nodes[cursor]);
  quickSortNodes(nodes, start_i, cursor - 1, reverse);
  quickSortNodes(nodes, cursor + 1, end_i, reverse);
}

void buildListOfNodesFromTree(struct node *root) {
  if (root != NULL) {
    buildListOfNodesFromTree(root->left);
    *NODE_LIST = root;
    ++NODE_LIST;
    buildListOfNodesFromTree(root->right);
  }
}

int getWord13(char *word, int max_word_len) {
  char c, first_char;
  while (isspace(c = getch()))
    ;
  first_char = c;
  if (c == EOF)
    return EOF;
  if (!isalnum(c)) {
    *word++ = c;
    *word = '\0';
    return first_char;
  }
  while (isalnum(c) && --max_word_len > 0) {
    *word++ = c;
    c = getch();
  }
  ungetch(c);
  *word = '\0';
  return first_char;
}

struct node *createNode(char *word) {
  struct node *node = (struct node *) malloc(sizeof(struct node));
  node->word = (char *) malloc(strlen(word) + 1);
  strcpy(node->word, word);
  node->word_count = 1;
  node->left = NULL;
  node->right = NULL;
  node->child_node_count = 0;
  node->child_word_count = 0;
  return node;
}

struct node *addNode(struct node *root, char *word) {
  if (root == NULL)
    return createNode(word);
  int diff;
  if ((diff = strcmp(word, root->word)) < 0) {
    root->child_word_count++;
    root->left = addNode(root->left, word);
  } else if (diff > 0) {
    root->child_word_count++;
    root->right = addNode(root->right, word);
  } else {
    root->word_count++;
  }
  root->child_node_count = 0;
  if (root->left != NULL) {
    root->child_node_count += root->left->child_node_count;
    root->child_node_count++; // for left node.
  }
  if (root->right != NULL) {
    root->child_node_count += root->right->child_node_count;
    root->child_node_count++; // for right node.
  }
  return root;
}

void testQuickSortInts() {
  int nums[] = {2, 4, 1, 3, 2, 2, 9, 8, 7, 13, 8, 7, 6, 10, 5};
  size_t len = sizeof(nums) / sizeof(nums[0]);
  int i;
  for (i = 0; i < len; ++i) {
    printf("%d ", nums[i]);
  }
  quickSortInts(nums, 0, len - 1);
  printf("\n");
  for (i = 0; i < len; ++i) {
    printf("%d ", nums[i]);
  }
  printf("\n");
  printf("quickSortInts tested.\n");
}


// Prints a list of nodes in descending order by word count.
// Just start typing in words and characters at the prompt.
// Then press enter, then CTRL-D.
int main() {
  char c;
  char word[MAX_WORD_LEN];
  struct node *root = NULL;
  //testQuickSortInts();
  while ((c = getWord13(word, MAX_WORD_LEN)) != EOF) {
    root = addNode(root, word);
  }
  //displayReverseStringResult(root);
  int num_nodes = root->child_node_count + 1;
  NODE_LIST = (struct node **) malloc(sizeof(struct node *) * num_nodes);
  struct node **n_copy = NODE_LIST;
  buildListOfNodesFromTree(root);
  int is_reverse = 1;
  // Sort by word count, descending order.
  quickSortNodes(n_copy, 0, num_nodes - 1, is_reverse);
  int i;
  for (i = 0; i < num_nodes; ++i)
    printf("word: %s, word_count: %d\n", n_copy[i]->word, n_copy[i]->word_count);
  return 0;
}
