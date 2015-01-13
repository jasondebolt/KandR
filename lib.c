#include "lib.h"

unsigned btoi(char c[]) {
  unsigned i, n;
  n = 0;

  for (i = 0; c[i] != '\0'; ++i) {
    n = n * 2 + c[i] - '0';
  }
  return n;
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

// There is a much better solution that uses XOR in the book.
// This is my own solution.
int invertBits(int x, int pos, int len) {
  /*
  Invert spots 6 and 5 of 01001010, result is 00101010
  pos = 6
  len = 2
  1) RHS
     a) Invert x
        10110101
     b) Mask off all bits except the first len bits starting at position pos.
        i) Create an ON mask of size len shifted to the left by pos - len + 1
           11111111 ~0
           11111100 << len
           00000011 ~
           01100000 << pos - len + 1
        ii) Apply on mask to inverted x
           10110101 & 01100000
           ~x & ~(~0 << len) << pos - len + 1
        00100000
     c) RHS =00100000
  2) LHS
     a) Mask off the first len bits starting at pos.
        i) Create of OFF mask of size len shifted to the left by pos - len + 1
           11111111 ~0
           11111100 << len
           00000011 ~
           01100000 << pos - len + 1
           10011111 ~
         ii) Apply OFF mask to x
           01001010 & 10011111
           x & ~(~(~0 << len) << pos - len + 1)
        00001010
      b) LHS = 00001010
  3) Return LHS | RHS
            00001010 | 00100000
            00101010
     return x & ~(~(~0 << len) << pos - len + 1) | ~x & ~(~0 << len) << pos - len + 1
  */
  return (x & ~(~(~0 << len) << (pos - len + 1))) | (~x & ~(~0 << len) << (pos - len + 1));
}

// private.
unsigned char endToFrontChar(unsigned char x) {
  if (x & 01 == 01) { // x is an odd number.
    x = x >> 1;
    x = x | ~((unsigned char) ~0 >> 1);
  } else {
    x = x >> 1;
  }
  return x;
}

unsigned char rightRotateChar(unsigned char x, int n) {
  while (--n >= 0) {
    x = endToFrontChar(x);
  }
  return x;
}

// private.
unsigned int endToFrontInt(unsigned int x) {
  if (x & 01 == 01) { // x is an odd number.
    x = x >> 1;
    x = x | ~((unsigned int) ~0 >> 1);
  } else {
    x = x >> 1;
  }
  return x;
}

unsigned int rightRotateInt(unsigned int x, int n) {
  while (--n >= 0) {
    x = endToFrontInt(x);
  }
  return x;
}


/* If we didn't use unsigned int for the arg, we wouldn't
 * be able to test if n > 0 because a signed n may fail this test.
 * The number -1 has 32 bits, for example. This function would return
 * a bitcount of zero for -1 if argument n was signed.
 */
int bitCount(unsigned int n) {
  int bitcount = 0;

  while(n > 0) {
    n &= (n - 1); // Deletes rightmost bit from n.
    ++bitcount;
  }
  //if (n & 01) {
  //  ++bitcount;
  //}
  //n >>= 1;
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
  printf("\t%s\n", itob(n));
}

void printIntAll(int n) {
  printf("(signed/unsigned dec: %d/%u) (bin: %s) (hex: 0x%x) (oct: 0%o)\n",
         n, n, itob(n), n, n);
}

void printCharAll(char c) {
  printf("(char: %c) (signed/unsigned dec: %d/%u) (bin: %s) (hex: 0x%x) (oct: 0%o)\n",
         c, c, c, itob(c), c, c);
}

// Search for x in array v of length n;
int binsearch(int x, int v[], int n) {
  int low, high, mid;

  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (high + low) / 2;
    if (x > v[mid])
      low = mid + 1;
    else if (x < v[mid])
      high = mid - 1;
    else
      return mid;
    
  }
  return -1; // result not found.
}

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

void squeeze(char s[], int c) {
  int i, j;

  for (i = j = 0; s[i] != '\0'; i++) {
    if (s[i] != c) {
      s[j++] = s[i];
    }
  }
  s[j] = '\0';
}

int strln(char one[]) {
  int i = 0;
  while (one[i] != '\0')
    ++i;
  return i;
}

char lower(int c) {
  return (c >= 'A' && c <= 'Z') ? c - 'A' + 'a': c;
}

void lowerAll(char c[]) {
  int i;
  for (i = 0; c[i] != '\0'; ++i)
    c[i] = lower(c[i]);
}

void print10Char(char s[]) {
  int i;
  for (i = 0; i < strln(s); ++i) {
    printf("%c%c", s[i], ((i + 1)  % 10 == 0) ? '\n' : '\t');
  }
  printf("\n");
}

void escape(char s[], char t[]) {
	int i, j;
	char c;
	
	i = j = 0;
	while((c = t[i++]) != 0) {
		switch(c) {
			case '\t':
			case '\n':
				s[j++] = '\\';
				s[j++] = (c == '\t') ? 't' : 'n';
				break;
			default:
				s[j++] = c;
				break;
		}
	}
	s[j] = c; // copy null char;
		
}


void unescape(char s[], char t[]) {
	int i, j;
	char c;
	
	i = j = 0;
	while((c = t[i++]) != '\0') {
		switch(c) {
			case '\\':
				s[j++] = (t[i++] == 't') ? '\t' : '\n';
				break;
			default:
				s[j++] = c;
				break;
		}
	}
	s[j] = c; // copy null char.
}

int isDigit(char c) {
	return c >= '0' && c <= '9';
}

int atoi2(char s[]) {
	int i, sign, n;
	char c;
	
	i = 0;
	while(!isDigit(s[i]) && (s[i] != '-' && s[i] != 0)) {
		++i;
	}
	
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '-')
		++i;
	
	n = 0;
	while(1) {
		if (!isDigit(s[i]))
			break;
		n = n * 10 + s[i++] - '0';
	}
	
	return sign * n;
}
