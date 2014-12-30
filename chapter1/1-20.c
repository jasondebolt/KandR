#include <stdio.h>
#include <assert.h>
#define MAX_STR_LEN 1000
#define BLANKS_PER_TAB 4


int fillArray(char s[], int limit);
int getln(char s[], int limit);
int replaceTabsWithSpaces(char s[], int limit);
int copy(char to[], char from[]);
int escapeCopy(char s[]);


int main() {
  char s[MAX_STR_LEN]; 
  int n;
  n = fillArray(s, MAX_STR_LEN);
  
  while ((n = getln(s, MAX_STR_LEN)) >= 0) {
    replaceTabsWithSpaces(s, MAX_STR_LEN);
    escapeCopy(s);
    printf("%s\n", s);
  }
  return 0;
}

int escapeCopy(char s[]) {
  char escape_version[MAX_STR_LEN];
  int i, escape_version_i;
  escape_version_i = i = 0;
  while (s[i] != '\0') {
    if (s[i] == ' ') { // Replace spaces with \s to verify.
      escape_version[escape_version_i++] = '\\';
      escape_version[escape_version_i++] = 's';
    } else {
      escape_version[escape_version_i++] = s[i];
    }
    ++i;
  }
  escape_version[escape_version_i] = '\0';
  copy(s, escape_version);
  return escape_version_i;
}

int fillArray(char s[], int limit) {
  int i = 0;
  while (i < limit) {
    s[i++] = '\0';
  }
  return i;
}

int getln(char s[], int limit) {
  int i;
  char c;
  for (i = 0; i <= limit && (c = getchar()) != '\n'; ++i) {
    s[i] = c;
  }
  s[i] = '\0';
  return i;
}

int replaceTabsWithSpaces(char s[], int limit) {
  int i, j, spaces_i;
  i = 0;
  char spaces_version[MAX_STR_LEN];
  spaces_i = i;
  while (s[i] != '\0') {
    if (s[i] == '\t') {
      for (j = 0; j < BLANKS_PER_TAB; ++j) {
        spaces_version[spaces_i++] = ' ';
      }
    } else {
      spaces_version[spaces_i++] = s[i];
    }
    ++i;
  }
  spaces_version[spaces_i] = '\0';
  copy(s, spaces_version);
  return i;
}

int copy(char to[], char from[]) {
  int i;
  i = 0;
  while ((to[i] = from[i]) != '\0') {
    ++i;
  }
  return i;
}
