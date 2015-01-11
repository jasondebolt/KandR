#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "str_lib.h"

#ifndef BIT_LIB_H
#define BIT_LIB_H

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

unsigned btoi(char c[]);
int getBits(int n, int pos, int len);
int setBits(int n, int pos, int len, int y);
int invertBits(int x, int pos, int len);
unsigned char endToFrontChar(unsigned char x);
unsigned char rightRotateChar(unsigned char x, int n);
unsigned int endToFrontInt(unsigned int x);
unsigned int rightRotateInt(unsigned int x, int n);
int bitCount(int n);
char *itob(int n);
void printBits(int n);
void printIntAll(int n);
void printCharAll(char c);

#endif
