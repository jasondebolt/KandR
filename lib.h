#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#ifndef STD_LIB_H
#define STD_LIB_H

#define dprint(expr)  printf(#expr " = %d\n", expr)
#define MAX_STR_SIZE 1024
#define MAX_LINE_LEN 1024
#define MAX_LINES 10000
#define MAX_BIT_STRING_SIZE 8
#define BUFSIZE 1024
#define MAX_GETCH_BUFF_SIZE 1024
#define ZERO "00000000"
#define TEN "00001010"
#define TWENTY "00010100"
#define THIRTY_ONE "00011111"
#define THIRTY_TWO "00100000"
#define SIXTY_THREE "00111111"
#define ONE_TWENTY_SEVEN "01111111"
#define ONE_TWENTY_EIGHT "10000000"
#define TWO_FIFTY_FIVE "11111111"
#define VERY_SMALL 1e-8
#define max(A, B) ((A) > (B) ? (A) : (B))
#define swapMacro(t, x, y) (t = *x, *x = *y, *y = t)
#define SWAP(a, b) SwapAwesome(&(a), &(b), sizeof(a))
#define paste(front, back) front ## back
#define square(x) ((x) * (x))

enum Boolean {NO, YES};
enum Escapes {NEWLINE = '\n', TAB = '\t'};
enum Months {JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

char *alloc2(int n);
char getch();
char *itobin(int n);
char *monthName(int n);
char *strncat2(char *s, char *t, unsigned n);
char *strncpy2(char *s, char *t, unsigned n);
char lower(int c);
double atof2(char s[]);
double atof3(char s[]);
double pow3(double base, int exp);
int any(char s[], char t[]);
int atoi2(char s[]);
int atoi3(char *s);
int binsearch(int x, int v[], int n);
int binsearch2(int x, int v[], int n);
int bitCount(unsigned int n);
int dayOfYear(int year, int month, int day);
int getBits(int n, int pos, int len);
int getCToken(char *word, int lim);
int getFloat(double *f);
int getIntFromHexChar(char c);
int getLine2(char s[], int lim);
int getLine3(char s[], int lim);
int getLine4(char *line, int maxlen);
int getword(char *word, int lim);
int htoi(char s[]);
int intArrayEquals(int a[], int b[], int alen);
int invertBits(int x, int pos, int len);
int isAlphaNum(char c);
int isDigit(char c);
int isLeapYear(int year);
int isLower(char c);
int isLowerHexLetter(char c);
int isNumber(char c);
int isUpper(char c);
int isUpperHexLetter(char c);
int pow2(int base, int exp);
int rand2(void);
int setBits(int n, int pos, int len, int y);
int strComp(char s[], char t[]);
int strComp2(char s[], char t[]);
int strComp3(char *s, char *t);
int strComp4(char *s, char *t);
int strCopy3(char to[], char from[]);
int strEnd2(char *s, char *t);
int strIndex(char s[], char t[]);
int strIndex2(char *s, char *t);
int strIndexRight(char s[], char t[]);
int strln(char one[]);
int strncmp2(char *s, char *t, unsigned n);
int trim2(char arr[]);
unsigned btoi(char c[]);
unsigned char endToFrontChar(unsigned char x);
unsigned char rightRotateChar(unsigned char x, int n);
unsigned int endToFrontInt(unsigned int x);
unsigned int rightRotateInt(unsigned int x, int n);
unsigned strCopy4(char *to, char *from);
unsigned strlen2(char s[]);
unsigned strlen3(char *s);
unsigned strlen4(char *s);
void assertAlmostEquals(double a, double b);
void assertIntArrayEquals(int a[], int b[], int alen);
void calculator();
void countChars();
void escape(char s[], char t[]);
void expand(char s[], char c[]);
void free2(char *c);
void getInt(int *n);
void itoa(int n, char s[]);
void itoa2(int n, char s[]);
void itoa3(int n, char s[]);
void itoa4(int n, char s[], int width);
void itoa5(int n, char *s);
void itoaRecurse(int n, char s[], int index);
void itobase(int n, char s[], int base);
void lowerAll(char c[]);
void monthDay(int year, int yearday, int *pmonth, int *pday);
void print10Char(char c[]);
void printBits(int n);
void printCharAll(char c);
void printIntAll(int n);
void printd(int n);
void quickSort(int v[], int left, int right);
void reverse2(char s[]);
void reverse3(char *s);
void reverseRecurse(char s[], int start, int end);
void seq(char *a, char *b);
void shellSort(int v[], int n);
void squeeze(char s[], int c);
void squeezeMulti(char s[], char c[]);
void srand2(unsigned int seed);
void strCat2(char s[], char t[]);
void strCat3(char *s, char *t);
void strCopy2(char s[], char t[]);
void strCopy5(char *to, char *from);
void swap(char *one, char *two);
void swap3(void *a, void *b, size_t size);
void swapInt(int *one, int *two);
void SwapGeneric(void *vals[], int a, int b);
void SwapAwesome(void *first, void *second, size_t i);
void unescape(char s[], char t[]);
void ungetch(int c);
void ungets(char s[]);

#endif
