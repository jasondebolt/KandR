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

enum Boolean {NO, YES};
enum Escapes {NEWLINE = '\n', TAB = '\t'};
enum Months {JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

static unsigned long int next2 = 1;

char *itobin(int n);
char lower(int c);
int any(char s[], char t[]);
int atoi2(char s[]);
int binsearch(int x, int v[], int n);
int binsearch2(int x, int v[], int n);
int bitCount(unsigned int n);
int getBits(int n, int pos, int len);
int getIntFromHexChar(char c);
int getLine2(char s[], int lim);
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
int rand2(void);
int setBits(int n, int pos, int len, int y);
int strComp(char s[], char t[]);
int strln(char one[]);
int trim2(char arr[]);
unsigned btoi(char c[]);
unsigned char endToFrontChar(unsigned char x);
unsigned char rightRotateChar(unsigned char x, int n);
unsigned int endToFrontInt(unsigned int x);
unsigned int rightRotateInt(unsigned int x, int n);
unsigned strlen2(char s[]);
void assertIntArrayEquals(int a[], int b[], int alen);
void countChars();
void escape(char s[], char t[]);
void expand(char s[], char c[]);
void itoa(int n, char s[]);
void itoa2(int n, char s[]);
void itoa3(int n, char s[]);
void itoa4(int n, char s[], int width);
void itobase(int n, char s[], int base);
void lowerAll(char c[]);
void print10Char(char c[]);
void printBits(int n);
void printCharAll(char c);
void printIntAll(int n);
void reverse2(char s[]);
void seq(char *a, char *b);
void shellSort(int v[], int n);
void squeeze(char s[], int c);
void squeezeMulti(char s[], char c[]);
void srand2(unsigned int seed);
void strCat2(char s[], char t[]);
void strCopy2(char s[], char t[]);
void swap(char *one, char *two);
void unescape(char s[], char t[]);

#endif
