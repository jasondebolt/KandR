#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#define MAX_BIT_STRING_SIZE 8
#define MAX_STR_SIZE 1024
#define ZERO "00000000"
#define TEN "00001010"
#define TWENTY "00010100"
#define THIRTY_ONE "00011111"
#define THIRTY_TWO "00100000"
#define SIXTY_THREE "00111111"
#define ONE_TWENTY_SEVEN "01111111"
#define ONE_TWENTY_EIGHT "10000000"
#define TWO_FIFTY_FIVE "11111111"

void swap(char *one, char *two) {
	char tmp = *one;
	*one = *two;
	*two = tmp;
}

int strComp(char s[], char t[]) {
	int i = 0;
	
	while (1) {
		if (s[i] < t[i])
			return -1;
		else if (s[i] > t[i])
			return 1;
		else if (s[i] == '\0' && t[i] == '\0')
			return 0;
		else
			++i;
	}
}

void seq(char *a, char *b) {
	assert(strComp(a, b) == 0);
}

unsigned strlen2(char s[]) {
	int i = 0;
	while (s[i] != '\0') {
		if (i >= MAX_STR_SIZE)
			return -1;
		++i;
	}
	return i;
}

void reverse2(char s[]) {
	int i, j;
	int len = strlen2(s);
	
	for (i = 0, j = len - 1; i < j; ++i, --j) {
		swap(&s[i], &s[j]);
	}
}


unsigned btoi(char c[]) {
	unsigned i, n;
	n = 0;
	
	for (i = 0; c[i] != '\0'; ++i) {
		n = n * 2 + c[i] - '0';
	}
	return n;
}

int lastSixToZero(int n) {
	return n & ~077;
}

int lastBitToZero(int n) {
	//return n & 077777777776;
	//return n & INT_MAX - 1;
	return n & ~1;
}

int allBitsToZero(int n) {
	return n & 0;
}

int allBitsToOne(int n) {
	return 255;
}
 

int bitsThreeToSixToZero(int n) {
	return n & ~(0xf << 3);
}

int bitCount(int n) {
	int bitcount = 0;
	
	while(n > 0) {
		if (n & 01) {
			++bitcount;
		}
		n = n >> 1;
	}
	return bitcount;
}

char *itob(int n) {
	char *result = malloc(MAX_BIT_STRING_SIZE + 1);
	int j;
	int i = 0;
	
	while (n > 0) {
		if (n & 01) {
			result[i] = '1';
		} else {
			result[i] = '0';
		}
		n = n >> 1;
		++i;
	}
	while(i < MAX_BIT_STRING_SIZE) {
		result[i] = '0';
		++i;
	}
	result[i] = '\0';
	reverse2(result);
	return result;
}

void printBits(int n) {
	printf("%s\n", itob(n));
}

void printInt(int n) {
	printf("%d\n", n);
}

void printIntAll(int n) {
	printBits(n);
	printInt(n);
	
}

// K&R page 49 has a better version. I created this one. 
// Get len number of bits starting from position pos of int n.
int getBits(int n, int pos, int len) {
	// btoi("01000100"), 6, 5 --> "10001"
	// 00000001 --> 1
	// 11111110 --> ~1
	// 11100000 --> (~1 << len - 1)
	// 00011111 --> ~(~1 << len - 1)
	return (n >> (pos - len + 1)) & ~(~1 << (len - 1));
}

// see page 49 of K&R for original question.
// Get rightmost len bits from y and put them into position pos of int n.
// My solution below is surprisingly close to the book solution!
int setBits(int n, int pos, int len, int y) {
  /*
	   assert(setBits(btoi("01101011"), 7, 1, btoi("00000101")) == btoi("11101011"));
	   assert(setBits(btoi("01101011"), 4, 3, btoi("00000101")) == btoi("01110111"))
	    RIGHT MASK
	      POS 7, LEN 1                       POS 4, LEN 3               OPERATION
	      00000001                           00000001                   1
	      11111110                           11111110                   ~
	      11111110                           11111000                   << len - 1
	      00000001                           00000111                   ~
        y = y & 00000001                   y = y & 00000111
        y = 00000101 & 00000001            y = 00000101 & 00000111
        y = 00000001                       y = 00000101
        y = y << (pos - len + 1)           y = y << (pos - len + 1)
        y = 00000001 <<< 7 - 1 + 1         y = 00000101 << 4 - 3 + 1
        y = 10000000                       y = 00010100

	   LEFT MASK
	      POS 7, LEN 1                    POS 4, LEN 3              OPERATION
	      00000001                        00000001                  1
	      11111110                        11111110                  ~
	      11111110                        11111000                  << len - 1
	      00000001                        00000111                  ~
	      10000000                        00011100                  << pos - len + 1
	      01111111                        11100011                  ~   
	      n = n & 01111111                n = n & 11100011
	      n = 01101011 & 01111111         n = 01101011 & 11100011 
	      n = 01101011                    n = 01100011
	      
	   FINAL RESULT
	      return n | y                    return n | y 
	      return 01101011 | 10000000      return 01100011 | 00010100
	      return 11101011                 return 01110111
   */
	n = n & ~(~(~1 << (len - 1)) << (pos - len + 1));
	y = (y & ~(~1 << (len - 1))) << (pos - len + 1);
	return n | y;
}


// Solution book answer.
unsigned setBitsBook(unsigned x, int p, int n, unsigned y) {
  return x & ~(~(~0 << n) << (p + 1 - n)) |
        (y &   ~(~0 << n)) << (p + 1 - n);
}


int setBitsBen(int n, int pos, int len, int y) {
	int mask = ~(~0x0 << pos) & ~(~0x0 << len);
	return (n & ~mask) | (y & mask);
}


void testBitCount() {
	assert(bitCount(10) == 2);
	assert(bitCount(20) == 2);
	assert(bitCount(31) == 5);
	assert(bitCount(32) == 1);
	assert(bitCount(INT_MAX) == 31);
	printf("bitCount tested\n");
}

void testAllBitsToZero() {
	assert(allBitsToZero(10) == 0);
	assert(allBitsToZero(255) == 0);
	printf("allBitsToZero tested.\n");
}

void testAllBitsToOne() {
	assert(allBitsToOne(0) == 255);
	printf("allBitsToOne tested.\n");
}

void testLastSixToZero() {
	assert(lastSixToZero(255) == btoi("11000000"));
	printf("lastSixToZero tested.\n");
}

void testLastBitToZero() {
	assert(lastBitToZero(255) == 254);
	assert(lastBitToZero(31) == 30);
	assert(lastBitToZero(513) == 512);
	assert(lastBitToZero(333333) == 333332);
	assert(lastBitToZero(INT_MAX) == INT_MAX - 1);
	printf("lastBitToZero tested.\n");
}

void testBitsThreeToSixToZero() {
	assert(btoi("10000111") == bitsThreeToSixToZero(255));
	printIntAll(bitsThreeToSixToZero(255));
	printf("bitsThreeToSixToZero tested.\n");
}

void testStrComp() {
	char a[] = "one";
	char b[] = "onf";
	assert(strComp(a, b) == -1);
	assert(strComp(b, a) == 1);
	assert(strComp(a, a) == 0);
	printf("strComp tested.\n");
}

void testReverse2() {
	char name[] = "jason";
	reverse2(name);
	assert(strComp(name, "nosaj") == 0);
	printf("reverse tested.\n");
}

void testItob() {
	seq(itob(0), ZERO);
	seq(itob(10), TEN);
	seq(itob(20), TWENTY);
	seq(itob(31), THIRTY_ONE);
	seq(itob(32), THIRTY_TWO);
	seq(itob(63), SIXTY_THREE);
	seq(itob(127), ONE_TWENTY_SEVEN);
	seq(itob(128), ONE_TWENTY_EIGHT);
	seq(itob(255), TWO_FIFTY_FIVE);
	printf("itob tested.\n");
}

void testGetBits() {
	assert(getBits(btoi("01000100"), 6, 5) == btoi("10001"));
	assert(getBits(btoi("01000100"), 7, 8) == btoi("01000100"));
	assert(getBits(btoi("01000100"), 3, 4) == btoi("0100"));
	assert(getBits(btoi("01000100"), 0, 1) == btoi("0"));
	printf("getBits tested.\n");
}

void testSetBits() {
	assert(setBits(btoi("01101011"), 4, 3, btoi("00000101")) == btoi("01110111"));
	assert(setBits(btoi("01101011"), 4, 3, btoi("00000101")) == btoi("01110111"));
	assert(setBits(btoi("01101011"), 7, 1, btoi("00000101")) == btoi("11101011"));
	assert(setBits(btoi("01101011"), 7, 8, btoi("00000101")) == btoi("00000101"));
	assert(setBits(btoi("01101011"), 6, 6, btoi("10101010")) == btoi("01010101"));
	assert(setBits(btoi("00000000"), 7, 8, btoi("11111111")) == btoi("11111111"));
	assert(setBits(btoi("00000000"), 7, 4, btoi("11111111")) == btoi("11110000"));
	//assert(setBitsBen(btoi("10000000"), 4, 2, btoi("00001111")) == btoi("10001100"));
	//assert(setBitsBen(btoi("11111111"), 4, 3, btoi("00000000")) == btoi("11110001"));
	printf("setBits tested.\n");
}

void testBits() {
  assert(~0 << 3 == ~1 << 2); 
  printf("Bits tested.\n");
}


int main() {
	testBitCount(); 
	testAllBitsToZero();
	testAllBitsToOne();
	testLastSixToZero();
	testLastBitToZero();
	testBitsThreeToSixToZero();
	testStrComp();
	testReverse2();
	testItob();
	testGetBits();
	testSetBits();
  testBits();
	printIntAll(INT_MAX);
	printIntAll(0xffffff);	
}
