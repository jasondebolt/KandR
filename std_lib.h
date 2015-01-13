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

char *itob(int n);
char lower(int c);
int binsearch(int x, int v[], int n);
int bitCount(unsigned int n);
int getBits(int n, int pos, int len);
int invertBits(int x, int pos, int len);
int setBits(int n, int pos, int len, int y);
int strComp(char s[], char t[]);
int strln(char one[]);
unsigned btoi(char c[]);
unsigned char endToFrontChar(unsigned char x);
unsigned char rightRotateChar(unsigned char x, int n);
unsigned int endToFrontInt(unsigned int x);
unsigned int rightRotateInt(unsigned int x, int n);
unsigned strlen2(char s[]);
void lowerAll(char c[]);
void print10Char(char c[]);
void printBits(int n);
void printCharAll(char c);
void printIntAll(int n);
void reverse2(char s[]);
void seq(char *a, char *b);
void squeeze(char s[], int c);
void swap(char *one, char *two);

#endif
