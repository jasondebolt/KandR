#include <assert.h>
#include <limits.h>
#include <math.h>
#include "lib.h"

void testBits() {
  assert(~0 << 3 == ~1 << 2);
  printf("Bits tested.\n");
}

void testBtoi() {
  assert(btoi("10101010") == 0xAA);
  printf("Btoi tested.\n");
}

void testGetBits() {
  assert(getBits(btoi("01000100"), 6, 5) == btoi("10001"));
  assert(getBits(btoi("01000100"), 7, 8) == btoi("01000100"));
  assert(getBits(btoi("01000100"), 3, 4) == btoi("0100"));
  assert(getBits(btoi("01000100"), 0, 1) == btoi("0"));
  printf("GetBits tested.\n");
}

void testSetBits() {
  assert(setBits(btoi("01101011"), 4, 3, btoi("00000101")) == btoi("01110111"));
  assert(setBits(btoi("01101011"), 4, 3, btoi("00000101")) == btoi("01110111"));
  assert(setBits(btoi("01101011"), 7, 1, btoi("00000101")) == btoi("11101011"));
  assert(setBits(btoi("01101011"), 7, 8, btoi("00000101")) == btoi("00000101"));
  assert(setBits(btoi("01101011"), 6, 6, btoi("10101010")) == btoi("01010101"));
  assert(setBits(btoi("00000000"), 7, 8, btoi("11111111")) == btoi("11111111"));
  assert(setBits(btoi("00000000"), 7, 4, btoi("11111111")) == btoi("11110000"));
  printf("SetBits tested.\n");
}

void testInvertBits() {
  //invert spots 6 and 5 of 01001010, result is 00101010
  //invert spots 6 and 5 of 0x4A, result is 0x2A
  assert(invertBits(0x4A, 6, 2) == 0x2A);
  assert(invertBits(0x4D, 7, 4) == 0xBD);
  assert(invertBits(0x0F, 7, 4) == 0xFF);
  assert(invertBits(0xFF, 3, 4) == 0xF0);
  assert(invertBits(0xAA, 7, 8) == 0x55);
  printf("TestInvertBits done.\n");
}

void testRightRotateChar() {
  assert(rightRotateChar(1, 8) == btoi("00000001"));
  assert(rightRotateChar(btoi("00000001"), 8) == btoi("00000001"));
  assert(rightRotateChar(btoi("00000001"), 1) == btoi("10000000"));
  printf("RightRotateChar tested\n");
}

void testRightRotateInt() {
  assert(rightRotateInt(btoi("00000000000000000000000000000001"), 32) ==
         btoi("00000000000000000000000000000001"));
  assert(rightRotateInt(btoi("00000000000000000000000000000001"), 1) ==
         btoi("10000000000000000000000000000000"));
  printf("RightRotateInt tested\n");
}

void testBitCount() {
  unsigned int i;
  assert(bitCount(0) == 0);
  assert((unsigned int) 0x80000000 == (UINT_MAX & ~((unsigned int)~0 >> 1)));
  for (i = (unsigned int) 0x80000000; i > 0; i >>= 1) {
    assert(bitCount(i) == 1);
  }
  assert(bitCount(10) == 2);
  assert(bitCount(20) == 2);
  assert(bitCount(31) == 5);
  assert(bitCount(32) == 1);
  assert(bitCount(INT_MAX) == 31);
  assert(bitCount(UINT_MAX) == 32);
  assert(bitCount(-1) == 32);
  assert(bitCount(-2) == 31);
  printf("BitCount tested\n");
}

void testItobin() {
  seq(itobin(0), ZERO);
  seq(itobin(10), TEN);
  seq(itobin(20), TWENTY);
  seq(itobin(31), THIRTY_ONE);
  seq(itobin(32), THIRTY_TWO);
  seq(itobin(63), SIXTY_THREE);
  seq(itobin(127), ONE_TWENTY_SEVEN);
  seq(itobin(128), ONE_TWENTY_EIGHT);
  seq(itobin(255), TWO_FIFTY_FIVE);
  printf("Itobin tested.\n");
}

void testPrintIntAll() {
  printIntAll(255);
  printf("PrintIntAll tested.\n");
}

void testPrintCharAll() {
  printCharAll(65);
  printCharAll('Z');
  printCharAll(97);
  printCharAll('z');
  printf("PrintCharAll tested.\n");
}

void nullTests() {
  assert('\0' == 0);
  assert(NULL == 0);
  assert(NULL == '\x0');
  assert(NULL == '\000');
  assert('\x0' == 0);
  assert('\000' == 0);
  printf("Null tests tested.\n");
}

void intTests() {
  assert(UINT_MAX == pow(2, 32) - 1);
  assert(UINT_MAX == 0xFFFFFFFF);
  assert(INT_MAX == pow(2, 31) - 1);
  assert(INT_MAX == 0x7FFFFFFF);
  assert(USHRT_MAX == pow(2, 16) - 1);
  assert(USHRT_MAX == 0xFFFF);
  assert(SHRT_MAX == pow(2, 15) - 1);
  assert(SHRT_MAX == 0x7FFF);
  assert(UCHAR_MAX == pow(2, 8) - 1);
  assert(CHAR_MAX == pow(2, 7) - 1);
  assert((unsigned int) 0xFFFFFFFF == UINT_MAX); // 32 on bits.
  assert((unsigned int) 0xFFFFFFFE == UINT_MAX - 1); // 31 on bits.
  assert((signed int) 0xFFFFFFFF == -1); // 32 on bits.
  assert((signed int) 0xFFFFFFFE == -2); // 31 on bits.
  assert((unsigned int) 0x7FFFFFFF == (signed int) 0x7FFFFFFF);
  assert((signed int) UINT_MAX == -1);
  assert((unsigned int) -1 == UINT_MAX);
  printf("Int tests tested.\n");
}

void limitTests() {
  assert(CHAR_MAX == 127);
  assert(CHAR_MAX == '\x7f');
  printf("CHAR_BIT: %d\n", CHAR_BIT);
  printf("CHAR_MIN: %d\n", CHAR_MIN);
  printf("CHAR_MAX: %d\n", CHAR_MAX);
  printf("SCHAR_MIN: %d\n", SCHAR_MIN);
  printf("SCHAR_MAX: %d\n", SCHAR_MAX);
  printf("UCHAR_MAX: %u\n", UCHAR_MAX); // Use 'u', not 'd'
  printf("SHRT_MIN: %d\n", SHRT_MIN);
  printf("SHRT_MAX: %d\n", SHRT_MAX);
  printf("USHRT_MAX: %u\n", USHRT_MAX); // Use 'u', not 'd'
  printf("INT_MIN: %d\n", INT_MIN);
  // Network Roofm Giraffe == 2^31
  printf("INT_MAX: %d\n", INT_MAX);
  // Rainbow Rubbish Can Beach == 2^32
  printf("UINT_MAX: %u\n", UINT_MAX);  // Use 'u', not 'd'
  printf("LONG_MIN: %ld\n", LONG_MIN);
  printf("LONG_MAX: %ld\n", LONG_MAX);
  printf("ULONG_MAX: %lu\n", ULONG_MAX); // Use 'u', not 'd'
  printf("Numbers tested.\n");
  printf("Limit tests tested.\n");
}

void octalTests() {
  assert('\010' == 8);
  assert(010 == 8);
  assert('\100' == 64);
  assert(0100 == 64);
  assert('\177' == 127);
  assert(0177 == 127);
  //assert('\200' == 128); // char only goes up to 127. This will break.
  assert(0200 == 128);
  printf("Octal tests tested.\n");
}

void charTests() {
  assert('a' == 97);
  assert('\x7F' == CHAR_MAX);
  assert(0xFF == UCHAR_MAX);
  assert((signed char)0xFF == -1);
  assert((unsigned char) -1 == UCHAR_MAX);
  printf("Char tests tested.\n");
}


void negativeOneTests() {
  // Negative one can have many different representations!!!
  assert(-1 == 0xFFFFFFFF);
  assert((unsigned long) -1 == 0xFFFFFFFF);
  assert((unsigned int) -1 == 0xFFFFFFFF);
  assert((unsigned short) -1 == 0xFFFF);
  assert((unsigned char) -1 == 0xFF);
  assert((signed char) 0xFF == -1);
  printf("Negative one tests tested.\n");
}

void minimumsTests() {
  assert((signed int) 0x80000000 == INT_MIN);
  assert((signed short) 0x8000 == SHRT_MIN);
  assert((signed char) 0x80 == CHAR_MIN);
  printf("Minimums tested.\n");
}

void maximumsTests() {
  assert((signed int) 0x7FFFFFFF == INT_MAX);
  assert((signed short) 0x7FFF == SHRT_MAX);
  assert((signed char) 0x7F == CHAR_MAX);
  assert((unsigned int) 0xFFFFFFFF == UINT_MAX);
  assert((unsigned short) 0xFFFF == USHRT_MAX);
  assert((unsigned char) 0xFF == UCHAR_MAX);
  printf("Maximums tested.\n");
}

void testLogicalOperatorsCast() {
  // Looks like logical operators cast to signed int by default
  assert(0xFFFFFFFF == -1);
  assert(0xFFFFFFFF > 0); // WTF?
  assert(0xFFFF == USHRT_MAX);
  assert(0xFF == UCHAR_MAX);
  printf("Logical operators tested.\n");
}

// See page 44 of K&R for details.
void testComparisonBetweenSignedAndUnsignedValues() {
  signed int si = -1;
  unsigned int ui = 1;
  unsigned short us = 1;
  assert(us > si); // This comparison works as expected.
  assert(si < us); // This comparison works. Unsigned short is promoted to signed int.
  assert(si > ui); // WTF? This comparison does not work. Signed int is converted into
                   // an unsigned int, thus appearing to be a very large positive number.
  /* Lesson to be learned: DO NOT COMPARE SIGNED AND UNSIGNED VALUES!!!
     - See page 44 of K&R for details.
  */
  printf("Comparison between signed and unsigned values tested.\n");
}

void testBinSearch() {
  int vals[8] = {1, 3, 4, 5, 9, 10, 23, 34}; // Must be sorted.
  assert(binsearch(1, vals, 8) == 0);
  assert(binsearch(23, vals, 8) == 6);
  assert(binsearch(34, vals, 8) == 7);
  assert(binsearch(11, vals, 8) == -1);
  printf("Binary search tested.\n");
}

void testBinSearch2() {
  int vals[8] = {1, 3, 4, 5, 9, 10, 23, 34}; // Must be sorted.
  assert(binsearch2(1, vals, 8) == 0);
  assert(binsearch2(23, vals, 8) == 6);
  assert(binsearch2(34, vals, 8) == 7);
  assert(binsearch2(11, vals, 8) == -1);
  printf("Binary search 2 tested.\n");
}

void testStrComp() {
  char a[] = "one";
  char b[] = "onf";
  char name[] = "my first name";
  char name2[] = "-one-two-three-four five--six";
  char name3[] = "AoneAtwoAthree";
  assert(strComp(a, b) == -1);
  assert(strComp(b, a) == 1);
  assert(strComp(a, a) == 0);
  printf("StrComp tested.\n");
}

void testReverse2() {
  char name[] = "jason";
  char name2[] = "four";
  reverse2(name);
  assert(strComp(name, "nosaj") == 0);
  reverse2(name2);
  assert(strComp(name2, "ruof") == 0);
  printf("Reverse2 tested.\n");
}

void testShellSort() {
  int arr[] = {7, 4, 3, 9, 1, 5, 2, 8};
  int arr2[] = {1, 2, 3, 4, 5, 7, 8, 9};
  shellSort(arr, 8);
  assertIntArrayEquals(arr, arr2, 8);
  printf("Shellsort tested.\n");
}

void testSqueeze() {
  char name[] = "my first name";
  char name2[] = "-one-two-three-four five--six";
  char name3[] = "AoneAtwoAthree";
  squeeze(name, ' ');
  squeeze(name2, '-');
  squeeze(name3, 'A');
  assert(strComp(name, "myfirstname") == 0);
  assert(strComp(name2, "onetwothreefour fivesix") == 0);
  assert(strComp(name3, "onetwothree") == 0);
  printf("Squeeze tested.\n");
}

void testLower() {
  assert(lower('A') == 'a');
  printf("Lower tested.\n");
}

void testLowerAll() {
  char name[] = "Jason";
  char name2[] = "ABCDEF";
  lowerAll(name);
  assert(strComp(name, "jason") == 0);
  lowerAll(name2);
  assert(strComp(name2, "abcdef") == 0);
  printf("LowerAll tested.\n");
}

void testPrint10Char() {
  print10Char("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
  printf("Print10Char tested.\n");
}

void testDprint() {
  int x = 28;
  int y = 14;
  dprint(x/y);
  dprint(x + y);
  dprint(x * y);
  dprint(x - y);
  printf("Dprint tested.\n");
}

void testEscapeAndUnescape() {
  char t[] = "hi\tjason\nNext line.";
  char s[MAX_STR_SIZE], us[MAX_STR_SIZE];
  assert(strComp(t, "hi\tjason\nNext line.") == 0);
  escape(s, t);
  assert(strComp(s, "hi\\tjason\\nNext line.") == 0);
  unescape(us, s);
  assert(strComp(us, "hi\tjason\nNext line.") == 0);
  printf("Escape and unescape tested.\n");
}

void testAtoi2() {
  assert(atoi2("12345") == 12345);
  assert(atoi2("  5678910") == 5678910);
  assert(atoi2("+123") == 123);
  assert(atoi2("-456") == -456);
  assert(atoi2("    -7810") == -7810);
  assert(atoi2("  -111333abc") == -111333);
  printf("Atoi2 tested.\n");
}

void testUpperHexLetter() {
  assert(isUpperHexLetter('F'));
  printf("IsUpperHexLetter tested.\n");
}

void testGetIntFromHexChar() {
  assert(getIntFromHexChar('F') == 15);
  assert(getIntFromHexChar('a') == 10);
  assert(getIntFromHexChar('5') == 5);
  printf("GetIntFromHexChar tested.\n");
}

void testHtoi() {
  assert(htoi("f") == 15);
  assert(htoi("0xff") == 255);
  assert(htoi("0XFF") == 255);
  assert(htoi("ffff") == 65535);
  printf("Htoi tested.\n");
}

void testAny() {
  assert(any("jason", "n") == 4);
  assert(any("today i am working today.", "t") == 0);
  assert(any("abcdefghijk zef", " fi") == 5);
  printf("Any tested.\n");
}

void testSqueezeMulti() {
  char name[] = "jason debolt";
  char name2[] = " this is it...now what.. ";
  squeezeMulti(name, "jaol");
  squeezeMulti(name2, " .");
  assert(strComp(name, "sn debt") == 0);
  assert(strComp(name2, "thisisitnowwhat") == 0);
  printf("SqueezeMulti tested.\n");
}

void testStrCat() {
  char name[30] = "jason";
  strCat2(name, " debolt");
  assert(strComp(name, "jason debolt") == 0);
  printf("StrCat2 tested.\n");
}

void testRand2AndSrand2() {
  int i;
  for (i = 0; i < 3; ++i) {
    printf("%d\t", rand2());
  }
  printf("\n");
  srand2(24);
  for (i = 0; i < 3; ++i) {
    printf("%d\t", rand2());
  }
  printf("\n");
  printf("Rand and srand tested.\n");
}

void testIsLeapYear() {
  assert(isLeapYear(1600) == 1);
  assert(isLeapYear(1796) == 1);
  assert(isLeapYear(1800) == 0);
  assert(isLeapYear(1804) == 1);
  assert(isLeapYear(1896) == 1);
  assert(isLeapYear(1900) == 0);
  assert(isLeapYear(1904) == 1);
  assert(isLeapYear(1996) == 1);
  assert(isLeapYear(2000) == 1);
  assert(isLeapYear(2004) == 1);
  printf("IsLeapYear tested.\n");
}

void testCountChars() {
  countChars();
}

void testIntArrayEquals() {
  int one[] = {4, 1, 9, 1, 0, 0, 0, 10, 0};
  int two[] = {4, 1, 9, 1, 0, 0, 0, 10, 0};
  int three[] = {4, 1, 9, 1, 0, 0, 0, 10, 1};
  assert(intArrayEquals(one, two, 9));
  assert(intArrayEquals(one, three, 9) == 0);
  printf("IntArrayEquals tested.\n");
}

void testTrim() {
  char name[] = "jason   ";
  char name2[] = "jason\t\t"; // with tabs.
  char name3[] = "jason\n";
  trim2(name);
  seq(name, "jason");
  trim2(name2);
  seq(name2, "jason");
  trim2(name3);
  seq(name3, "jason");
  printf("Trim2 tested.\n");
}

void testStrCopy2() {
  char s1[MAX_STR_SIZE];
  char s2[MAX_STR_SIZE];
  strCopy2(s1, " jason ");
  seq(s1, " jason ");
  printf("StrCopy2 tested.\n");
}

void testExpand() {
  char s[MAX_STR_SIZE];
  char c[MAX_STR_SIZE];

  strCopy2(c, "one two three -a-dA-Z5-9-a-b-c- four five");
  expand(s, c);
  seq(s, "one two three -abcdABCDEFGHIJKLMNOPQRSTUVWXYZ56789-abc- four five");

  strCopy2(c, "-a-dA-Z5-9-a-b-c-");
  expand(s, c);
  seq(s, "-abcdABCDEFGHIJKLMNOPQRSTUVWXYZ56789-abc-");

  strCopy2(c, "a-z");
  expand(s, c);
  seq(s, "abcdefghijklmnopqrstuvwxyz");

  strCopy2(c, "\\ --0-9");
  expand(s, c);
  seq(s, "\\ --0123456789");

  strCopy2(c, "  a-b-c");
  expand(s, c);
  seq(s, "  abc");

  strCopy2(c, "a-j-A-t-A-G");
  expand(s, c);
  seq(s, "abcdefghij-A-t-ABCDEFG");
  printf("Expand tested.\n");
}

void testItoa() {
  int num = 123456789;
  char s[MAX_STR_SIZE];

  itoa(num, s);
  seq(s, "123456789");

  num = INT_MAX;
  itoa(num, s);
  seq(s, "2147483647");

  printf("Itoa tested.\n");
}

void testItoa2() {
  int num = 123456789;
  char s[MAX_STR_SIZE];

  itoa2(num, s);
  seq(s, "123456789");

  num = INT_MAX;
  itoa2(num, s);
  seq(s, "2147483647");

  num = -3819300;
  itoa2(num, s);
  seq(s, "-3819300");

  printf("Itoa2 tested.\n");
}

void testItoa3() {
  int num = 123456789;
  char s[MAX_STR_SIZE];

  itoa3(num, s);
  seq(s, "123456789");

  num = -3819300;
  itoa3(num, s);
  seq(s, "-3819300");

  num = INT_MAX;
  itoa3(num, s);
  seq(s, "2147483647");

  num = INT_MIN;
  itoa3(num, s);
  seq(s, "-2147483648");

  printf("Itoa3 tested.\n");
}

void testItoa4() {
  int num = 123456789;
  char s[MAX_STR_SIZE];

  itoa4(num, s, 4);
  seq(s, "    123456789");

  num = -3819300;
  itoa4(num, s, 1);
  seq(s, " -3819300");

  num = INT_MAX;
  itoa4(num, s, 10);
  seq(s, "          2147483647");

  num = INT_MIN;
  itoa4(num, s, 0);
  seq(s, "-2147483648");

  printf("Itoa4 tested.\n");
}

void testItobase() {
  char s[MAX_STR_SIZE];

  itobase(10, s, 2);
  seq(s, "1010");
  
  itobase(123, s, 10);
  seq(s, "123");
  
  itobase(8, s, 8);
  seq(s, "10");
  
  itobase(63, s, 8);
  seq(s, "77");
  
  itobase(15, s, 16);
  seq(s, "F");
  
  itobase(16, s, 16);
  seq(s, "10");
  
  itobase(255, s, 16);
  seq(s, "FF");
  
  itobase(1, s, 16);
  seq(s, "1");

  printf("Itobase tested.\n");
}

int main() {
  //testCountChars(); interactive program.
  charTests();
  intTests();
  limitTests();
  maximumsTests();
  minimumsTests();
  negativeOneTests();
  nullTests();
  octalTests();
  testAny();
  testAtoi2();
  testBinSearch();
  testBinSearch2();
  testBitCount();
  testBits();
  testBtoi();
  testComparisonBetweenSignedAndUnsignedValues();
  testDprint();
  testEscapeAndUnescape();
  testExpand();
  testGetBits();
  testGetIntFromHexChar();
  testHtoi();
  testIntArrayEquals();
  testInvertBits();
  testIsLeapYear();
  testItoa();
  testItoa2();
  testItoa3();
  testItoa4();
  testItobase();
  testItobin();
  testLogicalOperatorsCast();
  testLower();
  testLowerAll();
  testPrint10Char();
  testPrintCharAll();
  testPrintIntAll();
  testRand2AndSrand2();
  testReverse2();
  testRightRotateChar();
  testRightRotateInt();
  testSetBits();
  testShellSort();
  testSqueeze();
  testSqueezeMulti();
  testStrCat();
  testStrComp();
  testStrCopy2();
  testTrim();
  testUpperHexLetter();
  return 0;
}
