#include <stdio.h>
#include <assert.h>
#ifndef STR_LIB_H
#define STR_LIB_H

#define MAX_STR_SIZE 1024

void swap(char *one, char *two);
int strComp(char s[], char t[]);
void seq(char *a, char *b);
unsigned strlen2(char s[]);
void reverse2(char s[]);
void squeeze(char s[], int c);
int strln(char one[]);
char lower(int c);
void lowerAll(char c[]);


#endif
