#include <stdio.h>
#define NUM_QUESTIONS 7
#define MAX_STR_SIZE 1024

void showAnswers() {
  int x, y;
  x = y = 4;
  printf("%d\n", 13>>4+2*3/1&4|2||3);
  x = y = 4;
  printf("%d\n", --x>>3*++y/4&5);
  x = y = 4;
  printf("%d\n", y++-4<<4|2);
  x = y = 4;
  printf("%d\n", 0x22+y++- --x*3<<2);
  x = y = 4;
  printf("%d\n", 0312&0x49|3<<4*3/4/y++&++x);
  x = y = 4;
  printf("%d\n", x-->=4^++y%10<<3>>1);
  x = y = 4;
  printf("%d\n", x--+--y<<3*1/4*12<<1%2);
}

// Gets an int from standard input.
int getInt() {
  char c;
  int n = 0;
  while ((c = getchar()) != '\n') {
    n = 10 * n + c - '0';
  }
  return n;
}

/* An expression using a combination of increment, decrement, or assignment
 * operators which modifies the same object more than once is undefined:
 *
 *   http://c-faq.com/expr/evalorder2.html
 *
 * An expression like this might have different results on differnt compilers:
 *   
 *   x++ * --y - --x + x++ + y++ - --y
 */
int main() {
  int i, x, y;
  int answer, numCorrect;
  char questions[NUM_QUESTIONS][MAX_STR_SIZE] = {
      "13>>4+2*3/1&4|2||3",
      "--x>>3*++y/4&5",
      "y++-4<<4|2",
      "0x22+y++- --x*3<<2",
      "0312&0x49|3<<4*3/4/y++&++x",
      "x-->=4^++y%10<<3>>1",
      "x--+--y<<3*1/4*12<<1%2"
  };

  int answers[] = {1, 0, 2, 116, 73, 21, 14};
  numCorrect = 0;
  //showAnswers();


  printf("Welcome to 7 Expressions!\n\n");
  printf("Assume x = y = 4\n");
  for (i = 0; i < NUM_QUESTIONS; ++i) {
    printf("%s\n", questions[i]);
    answer = getInt();
    if (answer == answers[i]) {
      printf("Correct!!\n");
      ++numCorrect;
    } else {
      printf("Incorrect.\n");
    }
  }
  printf("Score: %d/%d\n", numCorrect, NUM_QUESTIONS);
  
  return 0;
}
