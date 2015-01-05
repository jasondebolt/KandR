#include <stdio.h>
#include <assert.h>



// There is a simpler squeeze implementation on page 47 of K&R.
void squeeze(char s[], int c) {
  int i, j;

  i = 0;
  j = 0;
  
  while (s[i] != c)
    ++i;
  
  if (s[i] != '\0') {
    for (j = i; s[j] != '\0'; j++) {
      if (s[j] != c) {
        s[i++] = s[j];
      }
    }
  }
  s[i] = '\0';
}


void squeeze2(char s[], int c) {
  int i, j;

  for (i = j = 0; s[i] != '\0'; i++) {
    if (s[i] != c) {
      s[j++] = s[i];
    }
  }
  s[j] = '\0';
}


int strCmp(char one[], char two[]) {
  int i = 0;
  while (1) {
    if (one[i] < two[i])
      return -1;
    else if (one[i] > two[i])
      return 1;
    else if (one[i] == '\0' && two[i] == '\0')
      return 0;
    else
      ++i;
  }
  return 0;
}

int strln(char one[]) {
  int i = 0;
  while (one[i] != '\0')
    ++i;
  return i;
}

int main() {
  char name[] = "my first name";
  char name2[] = "-one-two-three-four five--six";
  char name3[] = "AoneAtwoAthree";
  squeeze2(name, ' ');
  squeeze2(name2, '-');
  squeeze2(name3, 'A');
  assert(strCmp(name, "myfirstname") == 0);
  assert(strCmp(name2, "onetwothreefour fivesix") == 0);
  assert(strCmp(name3, "onetwothree") == 0);
  return 0;
}
