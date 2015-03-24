#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_STR_LEN 100
#define COLS 3


void printArrayOfStrings(char arr[][MAX_STR_LEN], int rows) {
        int i;
        for (i = 0; i < rows; ++i) {
                printf("%s\n", arr[i]);
        }
}

void printArrayOfStrings2(char (*arr)[MAX_STR_LEN], int rows) {
        int i;
        for (i = 0; i < rows; ++i) {
                printf("%s\n", arr[i]);
        }
}

void printArrayOfStrings3(char *arr, int rows) {
        int i;
        for (i = 0; i < rows; ++i) {
                printf("%s\n", (arr + i*MAX_STR_LEN));
        }
}

void printArrayOfStrings4(char **arr) {
        while(*arr != NULL) {
                printf("%s\n", *arr++);
        }
}

void printArrayOfInts(int arr[][COLS], int rows) {
        int i;
        for (i = 0; i < rows; ++i) {
                int c;
                for (c = 0; c < COLS; ++c) {
                        printf("%d\t", arr[i][c]);
                }
                printf("\n");
        }
}

void printArrayOfInts2(int (*arr)[COLS], int rows) {
        int i;
        for (i = 0; i < rows; ++i) {
                int c;
                for (c = 0; c < COLS; ++c) {
                        printf("%d\t", arr[i][c]);
                }
                printf("\n");
        }
}

/* Converts a 2D char array to a double char pointer.
 * Args:
 *              arr: address of first element of first row (&arr1[0][0])
 *              rows: sizeof(arr1) / sizeof(arr1[0])
 *              max_len: Max number of chars per row.
 */
char **getDoubleCharPointerArray(char *arr, int rows, int max_len) {
        char **arr_pp = (char **) malloc(sizeof(char *) * (rows + 1));
        int i;
        for (i = 0; i < rows; ++i) {
                char *str = (char *) malloc(strlen(arr) + 1);
                strcpy(str, arr);
                *arr_pp++ = str;
                arr += max_len;
        }
        *arr_pp = NULL;
        return arr_pp - i;
}

void testPrintArrayOfStrings() {
        char arr_s[][MAX_STR_LEN] = {"one", "two", "three"};
        /* OUTPUT:
        *       one
        *       two
        *       three
        */
        printArrayOfStrings(arr_s, sizeof(arr_s) / sizeof(arr_s[0]));
        /* OUTPUT:
        *       one
        *       two
        *       three
        */
        printArrayOfStrings2(arr_s, sizeof(arr_s) / sizeof(arr_s[0]));
        /* OUTPUT:
        *       one
        *       two
        *       three
        */
        char *arr_p = &arr_s[0][0];
        printArrayOfStrings3(arr_p, sizeof(arr_s) / sizeof(arr_s[0]));
        int rows = sizeof(arr_s) / sizeof(arr_s[0]);
        char **arr_pp = getDoubleCharPointerArray(&arr_s[0][0], rows, MAX_STR_LEN);
        /* OUTPUT:
        *       one
        *       two
        *       three
        */
        printArrayOfStrings4(arr_pp);
        free(arr_pp);
        printf("printArrayOfStrings tested\n");
}

void testPrintArrayOfInts() {
        int arr_i[][COLS] = {{1, 2, 3}, {4, 5, 6}};
        /* OUTPUT:
        *       1       2       3
        *       4       5       6
        */
        printArrayOfInts(arr_i, sizeof(arr_i) / sizeof(arr_i[0]));
        /* OUTPUT:
        *       1       2       3
        *       4       5       6
        */
        printArrayOfInts2(arr_i, sizeof(arr_i) / sizeof(arr_i[0]));
        printf("printArrayOfInts tested\n");
}


int main() {
        testPrintArrayOfStrings();
        testPrintArrayOfInts();
        return 0;
}

