#include "lib.h"
#include "math.h"


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
  if ((x & 01) == 01) { // x is an odd number.
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
  if ((x & 01) == 01) { // x is an odd number.
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

char *itobin(int n) {
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
  printf("\t%s\n", itobin(n));
}

void printIntAll(int n) {
  printf("(signed/unsigned dec: %d/%u) (bin: %s) (hex: 0x%x) (oct: 0%o)\n",
         n, n, itobin(n), n, n);
}

void printCharAll(char c) {
  printf("(char: %c) (signed/unsigned dec: %d/%u) (bin: %s) (hex: 0x%x) (oct: 0%o)\n",
         c, c, c, itobin(c), c, c);
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

/* Search for index of value x in sorted array 'arr' of length len.
 * This is faster than binsearch.
 */
int binsearch2(int x, int v[], int n) {
  int low, mid, high;

  low = 0;
  high = n - 1;
  mid = (low + high) / 2;

  while (low <= high && x != v[mid]) {
    mid = (low + high) / 2;
    if (x < v[mid])
      high = mid - 1;
    else
      low = mid + 1;
  }

  if (x == v[mid]) {
    return mid;
  } else {
    return -1; // x not found.
  }
}

void swap(char *one, char *two) {
  char tmp = *one;
  *one = *two;
  *two = tmp;
}

// Copied from the web. Works with any object.
// Use the SWAP macro + SwapAwesome function below instead of this one.
void swap3(void *a, void *b, size_t size) {
  unsigned char *ap = a;
  unsigned char *bp = b;
  size_t i;

  for (i = 0; i < size; ++i) {
    unsigned char tmp = ap[i];
    ap[i] = bp[i];
    bp[i] = tmp;
  }
}

void swapInt(int *one, int *two) {
  int tmp = *one;
  *one = *two;
  *two = tmp;
}


// This doesn't work for arrays of non-pointers, like arrays of ints.
void SwapGeneric(void *vals[], int a, int b) {
  void *tmp = vals[a];
  vals[a] = vals[b];
  vals[b] = tmp;
}

// Use the SWAP macro defined in lib.h which calls this function.
// This works for everything!
// USAGE:
//   SWAP(a, b) where a, b are anything (primitives, strings, chars, pointers, etc.)
void SwapAwesome(void *first, void *second, size_t i) {
  uint8_t tmp, *a = first, *b = second;
  while (i--)
    tmp = a[i], a[i] = b[i], b[i] = tmp;
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


int strComp2(char s[], char t[]) {
  int i;
  for (i = 0; s[i] == t[i]; ++i) {
    if (s[i] == '\0')
      return 0;
  }
  return s[i] - t[i];
}


int strComp3(char *s, char *t) {
  while (*s == *t) {
    if (*s == '\0')
      return 0;
    s++;
    t++;
  }
  return *s - *t;
}


int strComp4(char *s, char *t) {
  for ( ;*s == *t; s++, t++) {
    if (*s == '\0')
      return 0;
  }
  return *s - *t;
}

// Assert string equals.
void seq(char *a, char *b) {
  assert(strComp(a, b) == 0);
}

/* Test if integer array equals.
 * alen is length of array a.
 * Assume array a and b are the same length.
 */
int intArrayEquals(int a[], int b[], int len) {
  int i;
  for (i = 0; i < len; ++i) {
    if (a[i] != b[i])
      return 0;
  }
  return 1;
}

void assertIntArrayEquals(int a[], int b[], int alen) {
  assert(intArrayEquals(a, b, alen));
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


void reverseRecurse(char s[], int start, int end) {
  if (start + 1 < end - 1)
    reverseRecurse(s, start + 1, end - 1);
  swap(&s[start], &s[end]);
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

int isLowerHexLetter(char c) {
  return c >= 'a' && c <= 'f';
}

int isUpperHexLetter(char c) {
  return c >= 'A' && c <= 'F';
}

int getIntFromHexChar(char c) {
  if (isDigit(c))
    return c - '0';
  else if (isLowerHexLetter(c))
    return c - 'a' + 10;
  else if (isUpperHexLetter(c)) {
    return c - 'A' + 10;
  } else {
    return -1;
  }
}

int htoi(char s[]) {
  int n = 0;
  int i = 0;

  if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
    i += 2;
  }

  while(s[i] != '\0') {
    n = n * 16 + getIntFromHexChar(s[i]);
    ++i;
  }

  return n;
}

int any(char s[], char t[]) {
  int i, j;

  for (i = 0; s[i] != '\0'; ++i) {
    for(j = 0; t[j] != '\0'; j++) {
       if (s[i] == t[j]) {
          return i;
        }
      }
  }
  return -1;
}

void squeezeMulti(char s[], char c[]) {

  int i, j, k, match;

  for (i = j = 0; s[i] != '\0'; ++i) {
    match = 0;
    for (k = 0; k < strln(c); ++k) {
      if (s[i] == c[k]) {
        match = 1;
      }
    }
    if (!match) {
      s[j++] = s[i];
    }
  }

  s[j] = '\0';
}

/* strCat: concatenate t to end of s; s must be big enough */
void strCat2(char s[], char t[]) {
  int i, j;

  i = j = 0;

  while (s[i] != '\0') { // find end of s.
    i++;
  }

  while ((s[i++] = t[j++]) != '\0') /* copy */
    ;
}

void strCopy2(char s[], char t[]) {
  int i = 0;
  while ((s[i] = t[i]) != '\0')
    ++i;
}

static unsigned long int next2 = 1;
int rand2(void) {
  next2 = next2 * 1103515245 + 12345;
  return (unsigned int)(next2/65536) % 32768;
}

void srand2(unsigned int seed) {
  next2 = seed;
}

int isLeapYear(int year) {
  if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
    return 1;
  return 0;
}


/* Counts number of digits, whitespace, and other chars.
*/
void countChars() {
  char c, i, arr[10];
  int numDigits, numWhiteSpaces, numOther;

  numDigits = numWhiteSpaces = numOther = 0;

  for (i = 0; i < 10; ++i)
    arr[i] = 0;

  while ((c = getchar()) != EOF) {
    switch(c) {
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        arr[c - '0']++;
        ++numDigits;
        break;
      case ' ':
      case '\t':
      case '\n':
        ++numWhiteSpaces;
        break;
      default:
        ++numOther;
        break;
    }
  }

  for (i = 0; i < 10; ++i)
    printf("digit: %d, count: %d\n", i, arr[i]);

  printf("digits: %d, ws: %d, other: %d\n", numDigits, numWhiteSpaces, numOther);
}

/* This function was copied directory from page 62 of K&R.
 * Sort v[0]...v[n - 1] into increasing order.
 */
void shellSort(int v[], int n) {
  int gap, i, j, tmp;

  for (gap = n/2; gap > 0; gap /=2) {
    for (i = gap; i < n; i++) {
      for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap) {
        tmp = v[j];
        v[j] = v[j + gap];
        v[j + gap] = tmp;
      }
    }
  }
}


/* This function was copied directory from page 87 of K&R.
 * I modified it slightly to work with my swap function.
 * Sort v[left]...v[right] into increasing order.
 */
void quickSort(int v[], int left, int right) {
  int i, last;

  if (left >= right)
    return;

  swapInt(&v[left], &v[(left + right) / 2]);
  last = left;
  for (i = left + 1; i <= right; i++) { /* partition */
    if (v[i] < v[left])
      swapInt(&v[++last], &v[i]);
  }
  swapInt(&v[left], &v[last]);
  quickSort(v, left, last - 1);
  quickSort(v, last + 1, right);
}


int trim2(char arr[]) {
  int i;

  for (i = strlen2(arr) - 1; i >= 0; i--) {
    if (arr[i] != '\n' && arr[i] != '\t' && arr[i] != ' ')
      break;
  }
  arr[i + 1] = '\0';
  return i + 1;
}

int isNumber(char c) {
	return c >= '0' && c <= '9';
}

int isLower(char c) {
	return c >= 'a' && c <= 'z';
}

int isUpper(char c) {
	return c >= 'A' && c <= 'Z';
}

int isAlpha(char c) {
	return isLower(c) || isUpper(c);
}

int isAlphaNum(char c) {
	return isNumber(c) || isAlpha(c);
}


// expand c into s.
// if c is 'a-z', then s is 'abcde...xyz'.
// This took me a while to get right. Could be simplified.
void expand(char s[], char c[]) {
  int i, j, diff;
  char before, after;

  i = j = 0;
  s[j++] = c[i++]; // Copy first character.
  while (1) {
    if (c[i] == '\0') {
      s[j] = c[i];
      break;
    }
    if (c[i] == '-') {
      before = c[i - 1];
      after = c[i + 1];
      diff = after - before;
      if ((isLower(before) && isLower(after)) ||
          (isUpper(before) && isUpper(after)) ||
          (isNumber(before) && isNumber(after))) {
        if (diff == 1) {
          i++;
          s[j] = c[i];
        } else if (diff > 1) {
          while (--diff >= 1) {
            s[j++] = ++before;
          }
          ++i;
        }
      }
    }
    s[j++] = c[i++];
  }
}

// Handle only positive numbers.
void itoa(int n, char s[]) {
  int last, sign;
  int i = 0;

  while (n > 0) {
    s[i++] = (n % 10) + '0';
    n = n / 10;
  }
  s[i] = '\0';
  reverse2(s);
}

// Handle negative numbers.
void itoa2(int n, char s[]) {
  int last, sign;
  int i = 0;

  if ((sign = n) < 0) {
    n = -n;
  }
  while (n > 0) {
    s[i++] = (n % 10) + '0';
    n = n / 10;
  }
  if (sign < 0) {
    s[i++] = '-';
  }
  s[i] = '\0';
  reverse2(s);
}

// Handle INT_MIN case. (see question 3-4 of K&R).
void itoa3(int n, char s[]) {
  int last, sign;
  int i = 0;
  int is_int_min = 0;

  if (n == INT_MIN) {
    n = n + 1;
    is_int_min = 1;
  }

  if ((sign = n) < 0) {
    n = -n;
  }
  while (n > 0) {
    s[i] = (n % 10) + '0' + ((is_int_min && (i == 0)) ? 1 : 0);
    ++i;
    n = n / 10;
  }
  if (sign < 0) {
    s[i++] = '-';
  }
  s[i] = '\0';
  reverse2(s);
}

// Provide left padding by minimum field with. (see question 3-6 of K&R).
void itoa4(int n, char s[], int width) {
  char t[MAX_STR_SIZE];
  int i;

  itoa3(n, t);

  for (i = 0; i < width; ++i)
    s[i] = ' ';
  s[i] = '\0';

  strCat2(s, t);
}

void itoaRecurse(int n, char s[], int index) {
  static int max_depth;
  static int is_neg;
  if (index == 0) {
    if (n < 0) {
      s[index] = '-';
      is_neg = 1;
      n = -n;
    } else {
      is_neg = 0;
    }
  }

  if (n / 10) {
    itoaRecurse(n / 10, s, index + 1);
  } else {
    // we've hit the end.
    s[index + 1 + is_neg] = '\0';
    max_depth = index + is_neg;
  }

  s[max_depth - index] = n % 10 + '0';
}

// This only handles positive numbers.
void itobase(int n, char s[], int base) {
  int result;
  int i = 0;

  while (n > 0) {
    result = n % base + '0'; 
    s[i++] = (result > '9') ? (result - '9' - 1 + 'A') : result;
    n = n / base;
  }
  s[i] = '\0';
  reverse2(s);
}

// Find location, if any, of string t in string s.
int strIndex(char s[], char t[]) {
  int i, j, k;
  char c;

  for (i = 0; s[i] != '\0'; ++i) {
    for (j = i, k = 0; t[k] == s[j] && t[k] != '\0'; ++j, ++k)
      ;

    if (t[k] == '\0')
      return i;
  }
  return -1;
}

// Find rightmost position of string t in string s.
int strIndexRight(char s[], char t[]) {
  int i, j, k, len_s, len_t;
  char c;

  i = len_s = 0;
  while (s[i++] != '\0')
    ++len_s;

  i = len_t = 0;
  while (t[i++] != '\0')
    ++len_t;

  for (i = len_s - 1; i >= 0; --i) {
    for (j = i, k = len_t - 1; t[k] == s[j] && k >= 0; --j, --k)
      ;

    if (k == -1)
      return i - len_t + 1;
  }
  return -1;
}

// Convert string s to double.
// leading whitespace and negative numbers are supported.
double atof2(char s[]) {
  int i, sign, dot_index, power;
  double n;

  i = n = 0;

  while (s[i] == ' ')
    i++;

  sign = (s[i] == '-') ? -1 : 1;

  if (sign == -1)
    ++i; 

  dot_index = 0;
  while (s[i] != '\0') {
    if (s[i] == '.') {
      dot_index = i;
    } else {
      n = n * 10 + s[i] - '0';
    }
    ++i;
  }
  if (dot_index) {
    power = i - dot_index - 1;
    n = n / pow2(10, power);
  }
  return sign * n;
}

int pow2(int base, int exp) {
  int n = 1;
  while (--exp >= 0)
    n = n * base;
  return n;
}

/* Handles negative exponents and doubles. */
double pow3(double base, int exp) {
  double n = 1;
  int sign;
  sign = (exp < 0) ? -1 : 1;
  exp *= sign;
  while (--exp >= 0)
    n = n * base;
  if (sign < 0)
    n = 1/n;
  return n;
}

/* Reads a line of input into char s[], returns the length.
 *
 * USAGE:
 *   char line[MAX_LINE_LEN];
 *   int i;
 *   while ((i = getLine2(line, MAX_LINE_LEN)) >= 0) {
 *     printf("%s\tlen:%d\n", line, i);
 *   }
 */
int getLine2(char s[], int lim) {
  int c, i;

  i = 0;
  while (1) {
    c = getchar();
    if (i >= lim)
      break;
    else if (c == EOF)
      break;
    else if (c == '\n')
      break;
    else
      s[i] = c;
      ++i;
  }
  if (c == '\n')
    s[i++] = '\n';
  s[i] = '\0';
  return i;
}

/* Reads a line of input into char s[], returns the length.
 */
int getLine3(char s[], int lim) {
  int i;
  char c;

  for (i = 0; ((c = getchar()) != '\n' && c != EOF) && i < lim; ++i) {
    s[i] = c;
  }
  // Notice that no newline is appended for EOF
  if (c == '\n')
    s[i++] = '\n';
  s[i] = '\0';
  return i;
}


int getLine4(char *line, int maxlen) {
  char c;
  char *start = line;
  while((c = getchar()) != '\n' && c != EOF && line - start < maxlen) {
    *line++ = c;
  }
  // Notice that no newline is appended for EOF
  if (c == '\n')
    *line++ = c;
  *line = '\0';
  return line - start;
}

void calculator() {
  char s[MAX_STR_SIZE];
  int len, num, sum;
  sum = 0;
  while ((len = getLine3(s, MAX_STR_SIZE)) > 0) {
    num = atoi2(s);
    printf("\t%d\n", sum += num);
  }
}

// Convert string s to double.
// leading whitespace and negative numbers are supported.
// Handle scientific notation like '123.45e-6'
double atof3(char s[]) {
  int i, i2, sign, esign, dot_index, power1, power2, after_e;
  double n, n2;

  i = n = after_e = n2 = i2 = power1 = power2 = 0;

  while (s[i] == ' ')
    i++;

  sign = (s[i] == '-') ? -1 : 1;
  esign = 1;

  if (sign == -1)
    ++i; 

  dot_index = 0;
  while (s[i] != '\0') {
    if (s[i] == '.') {
      dot_index = i;
    } else if (s[i] == 'e' || s[i] == 'E') {
      ++i2;
      after_e = 1;
    } else if (after_e && s[i] == '-') {
      ++i2;
      esign = -1;
    } else if (after_e) {
      ++i2;
      n2 = n2 * 10 + s[i] - '0';
    } else {
      n = n * 10 + s[i] - '0';
    }
    ++i;
  }
  power2 = esign * n2;
  if (dot_index) {
    power1 = i - dot_index - 1 - i2;
  }
  n = n * pow3(10, power2 - power1);
  return sign * n;
}

void assertAlmostEquals(double a, double b) {
  double diff = (a - b) < 0 ? (b - a) : (a - b);
  assert(diff < VERY_SMALL);
}


// Recursively print an integer, similar to itoa.
void printd(int n) {
  if (n < 0) {
    putchar('-');
    n = -n;
  }

  if (n / 10)
    printd(n / 10);

  putchar(n % 10 + '0');
}


void getInt(int *n) {
  char c;
  int sign;

  while ((c = getchar()) == ' ' || c == '\t')
    ;

  sign = (c == '-') ? -1 : 1;

  if (c == '-' || c == '+')
    c = getchar();

  *n = 0;
  if (isDigit(c)) {
    while (isDigit(c)) {
      *n = *n * 10 + c - '0';
      c = getchar();
    }
  }

  *n = *n * sign;
}


// Reads a line of input into pointer to a double.
int getFloat(double *f) {
  char c;
  int sign, dot_index, len;

  while((c = getchar()) == ' ' || c == '\t')
    ;

  sign = (c == '-') ? -1 : 1;

  if (c == '-' || c == '+')
    c = getchar();

  len = 0;
  *f = 0;
  while (c != '\n' && c != EOF) {
    if (c == '.') {
      dot_index = len;
    } else if (isDigit(c)) {
      *f = *f * 10 + c - '0';
    } else {
      return -1; // c is not a number.
    }
    ++len;
    c = getchar();
  }

  *f = *f / pow3(10, len - dot_index - 1);
  *f = sign * *f;
  return 0;
}

unsigned strlen3(char *s) {
  int len = 0;
  while (*s++ != '\0')
    ++len;
  return len;
}

unsigned strlen4(char *s) {
  char *c = s;
  while (*s != '\0') {
    s++;
  }
  return s - c;
}

static char allocbuf[BUFSIZE];
static char *allocp = allocbuf;
char *alloc2(int n) {
  if (n <= allocbuf + BUFSIZE - allocp) {
    allocp += n;
    return (allocp - n);
  } else {
    fprintf(stderr, "Not enough space.\n");
    exit(1);
  }
}

void free2(char *c) {
  if (c >= allocbuf && c < allocbuf + BUFSIZE) {
    allocp = c;
  } else {
    fprintf(stderr, "Pointer not within range.\n");
    exit(1);
  }
}


int strCopy3(char to[], char from[]) {
  int i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
  return i;
}


unsigned strCopy4(char *to, char *from) {
  char *diff = to;
  while ((*to++ = *from++) != '\0')
    ;
  return to - diff - 1;
}

void strCopy5(char *to, char *from) {
  while (*to++ = *from++) // '\0'
    ;
}


void strCat3(char *s, char *t) {
  while (*s != '\0')
    s++;
  for (; (*s = *t) != '\0'; s++, t++)
    ;
}

int strEnd2(char *s, char *t) {
  char *p = t;
  while (*t != '\0')
    t++;
  while (*s != '\0')
    s++;
  for (; *s == *t; --s, --t) {
    if (p == t)
      return 1;
  }
  return 0;
}

char *strncpy2(char *s, char *t, unsigned n) {
  int i;
  char *p = s;
  for (i = 0; i < n; ++i, ++s, ++t) {
    *s = *t;
    if (*s == '\0')
      return p;
  }
  *s = '\0';
  return p;
}

char *strncat2(char *s, char *t, unsigned n) {
  int i;
  char *p = s;
  while (*s != '\0')
    ++s;
  for (i = 0; i < n; ++i, ++s, ++t) {
    *s = *t;
    if (*s == '\0')
      return p;
  }
  *s = '\0';
  return p;
}

int strncmp2(char *s, char *t, unsigned n) {
  char *p = s;
  while (*s == *t && s - p < n) {
    if (*s == '\0')
      return 0;
    s++;
    t++;
  }
  return *s - *t;
}

int atoi3(char *s) {
  int n, sign;

  while (*s == ' ' || *s == '\t')
    ++s;

  sign = (*s == '-') ? -1 : 1;

  if (*s == '+' || *s == '-')
    ++s;

  n = 0;
  while (*s != '\0' && isDigit(*s)) {
    n = n * 10 + *s - '0';
    ++s;
  }

  return sign * n;
}

void itoa5(int n, char *s) {
  int last, sign, is_max_or_min;

  char *p = s;
  sign = 1;

  is_max_or_min = 0;
  if (n == INT_MAX) {
    n = n - 1;
    is_max_or_min = 1;
  }
  if (n == INT_MIN) {
    n = n + 1;
    is_max_or_min = 1;
  }

  if (n < 0) {
    sign = -1;
    n = -n;
  }

  while (n > 0) {
    last = n % 10;
    *s++ = last + '0';
    n = (n - last) / 10;
  }
  if (is_max_or_min) {
    *p = *p + 1;
  }
  if (sign == -1)
    *s++ = '-';
  *s = '\0';
  reverse2(p);
}

void reverse3(char *s) {
  char tmp, *p = s;

  while (*p != '\0')
    ++p;
  --p;

  for (; s < p; s++, p--) {
    tmp = *s, *s = *p, *p = tmp;
  }
}

int strIndex2(char *s, char *t) {
  char *sp, *tp, *start = s;
  for (; *s != '\0'; ++s) {
    for (sp = s, tp = t; *sp == *tp && *tp != '\0'; ++sp, ++tp)
      ;
    if (*tp == '\0')
      return  s - start;
  }
  return -1;
}

static char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

// Copied from page 111 of K&R.
int dayOfYear(int year, int month, int day) {
  int i, leap;

  if (year < 0 || month < 1 || day < 1 || month > 12 || day > 31) {
    fprintf(stderr, "invalid input for dayOfYear function.\n");
  }
  
  int *dayp = &day;
  leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  for (i = 1; i < month; i++) {
    //day += daytab[leap][i];
    day += *(*(daytab + leap) + i);
  }
  return day;
}

// Copied from page 111 of K&R.
void monthDay(int year, int yearday, int *pmonth, int *pday) {
  int i, leap;

  if (year < 0 || yearday < 1 || yearday > 366) {
    fprintf(stderr, "invalid input for monthDay function.\n");
  }

  leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  for (i = 1; yearday > *(*(daytab + leap) + i); i++) {
    //yearday -= daytab[leap][i];
    yearday -= *(*(daytab + leap) + i);
  }
  *pmonth = i;
  *pday = yearday;
}

char *monthName(int n) {
  static char *name[] = {
    "Illegal month", "January", "February", "March",
    "April", "May", "June", "July", "August",
    "September", "October", "November", "December"
  };
  return (n < 1 || n > 12) ? name[0] : name[n];
}

static int getch_buffer[MAX_GETCH_BUFF_SIZE];
int getch_buffp = 0;

char getch() {
  return (getch_buffp > 0) ? getch_buffer[--getch_buffp] : getchar();
}

void ungetch(int c) {
  if (getch_buffp < MAX_GETCH_BUFF_SIZE) {
    getch_buffer[getch_buffp++] = c;
  } else {
    fprintf(stderr, "getch_buffer full.\n");
    exit(1);
  }
}

void ungets(char s[]) {
  int i;
  i = 0;
  while (s[i] != '\0')
    ++i;

  while (i > 0)
    ungetch(s[--i]);
}

/* getword: get next word or character from input.
 * Copied from page 136 of K&R.
 * Fetches the next "word" from the input, where a word is either a string
 * of letters and digits beginning with a letter, or a single non-whitespace
 * character. The return value is the first character of the word, or EOF
 * for end of file, or the character itself if it is not alphabetic.
 */
int getword(char *word, int lim) {
  int c;
  char *w = word;
  while (isspace(c = getch()))
    ;
  if (c != EOF)
    *w++ = c;
  if (!isalpha(c)) {
    *w = '\0';
    return c;
  }
  for ( ; --lim > 0; w++) {
    if (!isalnum(*w = getch())) {
      ungetch(*w);
      break;
    }
  }
  *w = '\0';
  return word[0];
}

/* getCToken: get next word or character from input.
 * Same as getword above, except we handle underscores, string constants
 * and preprocessor control lines.
 * USAGE:
 *   char s[MAX_STR_SIZE];
 *   int c;
 *   while ((c = getCToken(s, MAX_STR_SIZE)) != EOF) {
 *     printf("assert(c == '%c');\n", c);
 *     printf("assert(strcmp(word, \"%s\") == 0);\n", s);
 *   }
 * A word is one of the following:
 *   - A string starting with a letter or an understore, containg letters, numbers
 *      or underscores.
 *   - A string literal, including the quotes.
 *   - A preprocessor control line (#include <ctype.h>)
 *   - A single non-whitespace character.
 */
int getCToken(char *word, int lim) {
  char c, next, last, end;
  char *w = word;
  // At this point, c is a non whitespace character.
  while ((c = getch()) != EOF) {
    if (c == '#') {
      *w++ = c;
      while ((c = getch()) != '\n')
        *w++ = c;
      *w = '\0';
      // Save preprocessor directive until end of line.
      break;
    } else if (c == '"') {
      // We may have a string literal.
      *w++ = c;
      while ((c = getch()) != '"')
        *w++ = c;
      *w++ = c;
      *w = '\0';
      break;
    } else if (isspace(c)) {
      while (isspace(c = getch()))
        ;
      ungetch(c);  // ungetch the last non-whitespace char.
    } else if (c == '/') {                     // Check if inside comment.
      next = getch();                          // If inside comment, skip past comment.
      if (next == '/') {                       // If not inside comment, ungetch one char.
        // We're in a single line comment.
        // skip through the entire comment.
        while ((c = getch()) != '\n')
          ;
      } else if (next == '*') {
        // We're in a possible multi-line comment.
        // Skip through the entire multi-line comment.
        while (1) {
          // skip until the next '*' char. This may be the end.
          while ((last = getch()) != '*')
            ;
          // Check to see if this really is the end of the comment.
          if ((end = getch()) == '/') {
            // We've found the end of the comment.
            break;
          } else {
            ungetch(next);
          }
        }
      } else {
        // This is not a comment. Return the single '/' char.
        ungetch(next);
        *w++ = c;
        *w = '\0';
        break;
      }
    } else if (isalpha(c) || c == '_') {
      // We may have a full word.
      // Loop through all digit, chars, and underscores until reach space.
      // Store results in word.
      // Return first char.
      *w++ = c;
      while (isalnum(c = getch()) || c == '_')
        *w++ = c;
      *w = '\0';
      ungetch(c); // ungetch that last non _aA123 char.
      break;
    } else {
      // Store single character in word.
      // Return character. (could be digit, /, *, etc.)
      *w++ = c;
      *w = '\0';
      break;
    }
  }
  if (c == EOF)
    return EOF;
  return word[0];
}
