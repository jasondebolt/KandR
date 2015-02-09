#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_VALS 1024
#define MAX_LINES 1024
#define MAX_LINE_LEN 1024


void pna(int *vals, int len) {
  int i;
  for (i = 0; i < len; ++i) {
    printf("%d ", vals[i]);
  }
  printf("\n");
}

int numComp(int *a, int *b) {
  return *a - *b;
}

int strComp(char *a, char *b) {
  while (*a == *b && *a != '\0') {
    ++a;
    ++b;
  }
  return *a - *b;
}

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void swap2(void *arr[], int a, int b) {
  void *tmp = arr[a];
  arr[a] = arr[b];
  arr[b] = tmp;
}

void MergeSort(int *vals, int low, int high) {
  int i, tmp;
  int mid = (low + high) / 2;
  int result;
  //printf("low: %d, mid: %d, high: %d\n", low, mid, high);

  if (high - low <= 1) {
    printf("len is <= 1\n");
    return;
  }
  MergeSort(vals, low, mid);
  MergeSort(vals, mid, high);
  for (i = low; (i + 1) <= high; ++i) {
    printf("(low: %d, mid %d, high: %d) Iter %d\n", low, mid, high, i);
    result = vals[i] > vals[i + 1];
    printf("is %d larger than %d? %d\n", vals[i], vals[i + 1], result);
    if (vals[i] > vals[i + 1]) {
      printf("swapping\n");
      //pna(vals, 8);
      swap(&vals[i], &vals[i + 1]);
    }
  }
}

void MergeSort2(void *vals[], int low, int high, int (*comp)(void *, void *)) {
  int i, tmp;
  int mid = (low + high) / 2;
  int result;
  //printf("low: %d, mid: %d, high: %d\n", low, mid, high);
  if (high - low <= 1)
    return;
  MergeSort2(vals, low, mid, comp);
  MergeSort2(vals, mid, high, comp);
  for (i = low; (i + 1) <= high; ++i) {
    //result = (*comp)(&vals[i], &vals[i + 1]);
    //printf("comparing %d with %d: %d\n", (int)vals[i], (int)vals[i + 1], result);
    //if ((*comp)(&vals[i], &vals[i + 1]) > 0) {
    //  printf("swapping\n");
    //  swap2(vals, i, i + 1);
    //}
    result = (*comp)(vals[i], vals[i + 1]);
    printf("comparing %s with %s: %d\n", (char *)vals[i], (char *)vals[i + 1], result);
    if ((*comp)(vals[i], vals[i + 1]) > 0) {
      printf("swapping\n");
      swap2(vals, i, i + 1);
    }
  }
}

void testMergeSortNumeric() {
  //int vals[] = {5, 1, 3, 2, 4};
  //int vals[] = {10, 19, 1, 18, 10, 7};
  int vals[] = {4, 3, 2, 1};
  int len = sizeof(vals) / sizeof(vals[0]);
  pna(vals, len);
  MergeSort(vals, 0, len - 1);
  pna(vals, len);
  //int vals[MAX_VALS] = {4, 9, 2, 3, 4, 7, 5, 8, 6};
  //pna(vals, 9);
  //MergeSort(vals, 0, 8);
  //pna(vals, 9);
}

void testMergeSort2Numeric() {
  int vals[] = {4, 9, 2, 3, 4, 7, 5, 8, 6};
  int len = sizeof(vals) / sizeof(vals[0]);
  pna(vals, len);
  MergeSort2((void **)vals, 0, len - 1, (int (*)(void*, void*))(numComp));
  pna(vals, len);
}

void testMergeSort2Strings() {
  //char *vals[] = {"jason", "stella", "aj", "rachelle", "justin", "greg", "kourtni", "adam", "bob"};
  //int i;
  // int len = sizeof(vals) / sizeof(vals[0]);
  //for (i = 0; i < len; ++i)
  //  printf("%s\t", vals[i]);
  //printf("\n");
  //MergeSort2((void **)vals, 0, len - 1, (int (*)(void*, void*))(strComp));
  //for (i = 0; i < len; ++i)
  //  printf("%s\t", vals[i]);
  //printf("\n");
  //char *vals[] = {"j", "s", "a", "r", "j", "g", "k", "a", "b"};
  char *vals[] = {"j", "s", "a", "r", "j", "g"};
  int i;
  int len = sizeof(vals) / sizeof(vals[0]);
  for (i = 0; i < len; ++i)
    printf("%s\t", vals[i]);
  printf("\n");
  MergeSort2((void **)vals, 0, len - 1, (int (*)(void*, void*))(strComp));
  for (i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i)
    printf("%s\t", vals[i]);
  printf("\n");
}

void testStrComp() {
  assert(strComp("jason", "jason") == 0);
  assert(strComp("jason", "stella") < 0);
  assert(strComp("abc", "abd") < 0);
  assert(strComp("abd", "abc") > 0);
}


void mergeChar(char v[], int low, int mid, int high) {
  char *p1 = &v[low];
  char *p2 = &v[mid + 1];
  char arr[high - low + 1];
  char *arrp = arr;
  while (arrp - arr < (high - low + 1)) {
    if (p1 > &v[mid]) {
      *arrp++ = *p2++;
    } else if (p2 > &v[high]) {
      *arrp++ = *p1++;
    } else {
      *arrp++ = (*p1 < *p2) ? *p1++ : *p2++;
    }
  }
  *arrp = '\0';
  // copy arr into v.
  strcpy(v, arr);
}

void testMergeChar() {
  char v[] = {'b', 'c', 'f', 'a', 'd', 'e', '\0'};
  int low = 0, mid = 2, high = 5;
  mergeChar(v, low, mid, high);
  assert(v[0] == 'a');
  assert(v[1] == 'b');
  assert(v[2] == 'c');
  assert(v[3] == 'd');
  assert(v[4] == 'e');
  assert(v[5] == 'f');
  printf("mergeChar tested.\n");
}

void mergeInt(int v[], int low, int mid, int high) {
  int *p1 = &v[low];
  int *p2 = &v[mid + 1];
  int arr[high - low + 1];
  int *arrp = arr;
  while (arrp - arr < (high - low + 1)) {
    if (p1 > &v[mid]) {
      *arrp++ = *p2++;
    } else if (p2 > &v[high]) {
      *arrp++ = *p1++;
    } else {
      *arrp++ = (*p1 < *p2) ? *p1++ : *p2++;
    }
  }
  *arrp = '\0';
  // copy arr into v.
  int i;
  for (i = 0; i <= high; ++i) {
    v[i] = arr[i];
  }
}

void testMergeInt() {
  int v[] = {1, 3, 5, 2, 4, 8, '\0'};
  int low = 0, mid = 2, high = 5;
  mergeInt(v, low, mid, high);
  assert(v[0] == 1);
  assert(v[1] == 2);
  assert(v[2] == 3);
  assert(v[3] == 4);
  assert(v[4] == 5);
  assert(v[5] == 8);
  printf("mergeInt tested.\n");
}

void mergeString(char **v, int low, int mid, int high) {
  printf("%c\n", *(*v)++);
  printf("%c\n", *(*v)++);
}

void testMergeString() {
  char *v[] = {"afoo", "cfoo", "ffoo", "bfoo", "dfoo", "jfoo", NULL};
  int low = 0, mid = 2, high = 5;
  mergeString(v, low, mid, high);
  //printf("%s\n", v[0]);
  //printf("%s\n", v[1]);
  //printf("%s\n", v[2]);
  //printf("%s\n", v[3]);
  //printf("%s\n", v[4]);
  //printf("%s\n", v[5]);
  printf("mergeString tested.\n");
}

int main() {
  testStrComp();
  testMergeChar();
  testMergeInt();
  testMergeString();
  //testMergeSortNumeric();
  //testMergeSort2Numeric();
  //testMergeSort2Strings();
}
