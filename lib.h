#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#ifndef STD_LIB_H
#define STD_LIB_H

#define dprint(expr)  printf(#expr " = %d\n", expr)
#define MAX_STR_SIZE 1024
#define MAX_BIT_STRING_SIZE 8
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
#define swap2(t, x, y) (t = *x, *x = *y, *y = t)
#define paste(front, back) front ## back
#define square(x) ((x) * (x))

enum Boolean {NO, YES};
enum Escapes {NEWLINE = '\n', TAB = '\t'};
enum Months {JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

static unsigned long int next2 = 1;

#define BUFSIZE 1024
static char allocbuf[BUFSIZE];
static char *allocp = allocbuf;

char *itobin(int n);
char lower(int c);
char *alloc2(int n);
char *strncpy2(char *s, char *t, unsigned n);
char *strncat2(char *s, char *t, unsigned n);
int strncmp2(char *s, char *t, unsigned n);
double atof2(char s[]);
double atof3(char s[]);
double pow3(double base, int exp);
int any(char s[], char t[]);
int atoi2(char s[]);
int atoi3(char *s);
int binsearch(int x, int v[], int n);
int binsearch2(int x, int v[], int n);
int bitCount(unsigned int n);
int getBits(int n, int pos, int len);
int getFloat(double *f);
int getIntFromHexChar(char c);
int getLine2(char s[], int lim);
int getLine3(char s[], int lim);
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
void assertIntArrayEquals(int a[], int b[], int alen);
void assertAlmostEquals(double a, double b);
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
void print10Char(char c[]);
void printBits(int n);
void printCharAll(char c);
void printd(int n);
void printIntAll(int n);
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
void swapInt(int *one, int *two);
void unescape(char s[], char t[]);

#endif
