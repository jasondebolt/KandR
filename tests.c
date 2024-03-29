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
  //assert((unsigned long) -1 == 0xFFFFFFFF); // doesn't work on mac.
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
  assert(strComp(a, b) < 0);
  assert(strComp(b, a) > 0);
  assert(strComp(a, a) == 0);
  printf("StrComp tested.\n");
}

void testStrComp2() {
  char a[] = "one";
  char b[] = "onf";
  char name[] = "my first name";
  char name2[] = "-one-two-three-four five--six";
  char name3[] = "AoneAtwoAthree";
  assert(strComp2(a, b) < 0);
  assert(strComp2(b, a) > 0);
  assert(strComp2(a, a) == 0);
  printf("StrComp2 tested.\n");
}

void testStrComp3() {
  char a[] = "one";
  char b[] = "onf";
  char name[] = "my first name";
  char name2[] = "-one-two-three-four five--six";
  char name3[] = "AoneAtwoAthree";
  assert(strComp3(a, b) < 0);
  assert(strComp3(b, a) > 0);
  assert(strComp3(a, a) == 0);
  printf("StrComp3 tested.\n");
}

void testStrComp4() {
  char a[] = "one";
  char b[] = "onf";
  char name[] = "my first name";
  char name2[] = "-one-two-three-four five--six";
  char name3[] = "AoneAtwoAthree";
  assert(strComp4(a, b) < 0);
  assert(strComp4(b, a) > 0);
  assert(strComp4(a, a) == 0);
  printf("StrComp4 tested.\n");
}

void testReverse2() {
  char name[] = "jason";
  char name2[] = "four";
  char name3[] = "a";
  reverse2(name);
  assert(strComp(name, "nosaj") == 0);
  reverse2(name2);
  assert(strComp(name2, "ruof") == 0);
  reverse2(name3);
  assert(strComp(name3, "a") == 0);
  printf("Reverse2 tested.\n");
}

void testReverse3() {
  char name[] = "jason";
  char name2[] = "four";
  char name3[] = "a";
  reverse3(name);
  assert(strComp(name, "nosaj") == 0);
  reverse3(name2);
  assert(strComp(name2, "ruof") == 0);
  reverse3(name3);
  assert(strComp(name3, "a") == 0);
  printf("Reverse3 tested.\n");
}

void testReverseRecurse() {
  char name[] = "jason";
  char name2[] = "four";
  char name3[] = "a";
  reverseRecurse(name, 0, 4);
  assert(strComp(name, "nosaj") == 0);
  reverseRecurse(name2, 0, 3);
  assert(strComp(name2, "ruof") == 0);
  reverseRecurse(name3, 0, 0);
  assert(strComp(name3, "a") == 0);
  printf("ReverseRecurse tested.\n");
}

void testShellSort() {
  int arr[] = {7, 4, 3, 9, 1, 5, 2, 8};
  int arr2[] = {1, 2, 3, 4, 5, 7, 8, 9};
  shellSort(arr, 8);
  assertIntArrayEquals(arr, arr2, 8);
  printf("ShellSort tested.\n");
}

void testQuickSort() {
  int arr[] = {7, 4, 3, 9, 1, 5, 2, 8};
  int arr2[] = {1, 2, 3, 4, 5, 7, 8, 9};
  int len = sizeof(arr) / sizeof(arr[0]);
  quickSort(arr, 0, len - 1);
  assertIntArrayEquals(arr, arr2, len);
  int arr3[] = {5, 3, 2, 4, 2, 1};
  int arr4[] = {1, 2, 2, 3, 4, 5};
  len = sizeof(arr3) / sizeof(arr3[0]);
  quickSort(arr3, 0, len - 1);
  assertIntArrayEquals(arr3, arr4, len);
  printf("QuickSort tested.\n");
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

void testAtoi3() {
  assert(atoi3("12345") == 12345);
  assert(atoi3("  5678910") == 5678910);
  assert(atoi3("+123") == 123);
  assert(atoi3("-456") == -456);
  assert(atoi3("    -7810") == -7810);
  assert(atoi3("  -111333abc") == -111333);
  printf("Atoi3 tested.\n");
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

void testStrCat3() {
  char name[30] = "jason";
  strCat3(name, " debolt");
  assert(strComp4(name, "jason debolt") == 0);
  printf("StrCat3 tested.\n");
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

void testStrCopy3() {
  char s1[MAX_STR_SIZE];
  char s2[MAX_STR_SIZE];
  int result = strCopy3(s1, " jason ");
  seq(s1, " jason ");
  assert(result == 7);
  printf("StrCopy3 tested.\n");
}

void testStrCopy4() {
  char s1[MAX_STR_SIZE];
  char s2[MAX_STR_SIZE];
  unsigned result = strCopy4(s1, " jason ");
  seq(s1, " jason ");
  assert(result == 7);
  result = strCopy4(s1, "");
  seq(s1, "");
  assert(result == 0);
  printf("StrCopy4 tested.\n");
}

void testStrCopy5() {
  char s1[MAX_STR_SIZE];
  char s2[MAX_STR_SIZE];
  strCopy5(s1, " jason ");
  seq(s1, " jason ");
  strCopy5(s1, "");
  seq(s1, "");
  printf("StrCopy5 tested.\n");
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

void testItoa5() {
  int num = 123456789;
  char s[MAX_STR_SIZE];

  itoa5(num, s);
  seq(s, "123456789");

  num = -3819300;
  itoa5(num, s);
  seq(s, "-3819300");

  num = INT_MAX;
  itoa5(num, s);
  seq(s, "2147483647");

  num = INT_MIN;
  itoa5(num, s);
  seq(s, "-2147483648");

  printf("Itoa5 tested.\n");
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


void testStrIndex() {
  char s[MAX_STR_SIZE] = "jason was here.";
  char t[MAX_STR_SIZE] = "was";
  assert(strIndex(s, t) == 6);

  strCopy2(s, "foo bar baz");
  strCopy2(t, "z");
  assert(strIndex(s, t) == 10);

  strCopy2(s, "foo bar baz");
  strCopy2(t, "f");
  assert(strIndex(s, t) == 0);

  printf("StrIndex tested.\n");
}


void testStrIndex2() {
  char s[MAX_STR_SIZE] = "jason was here.";
  char t[MAX_STR_SIZE] = "was";
  assert(strIndex2(s, t) == 6);

  strCopy2(s, "foo bar baz");
  strCopy2(t, "z");
  assert(strIndex2(s, t) == 10);

  strCopy2(s, "foo bar baz");
  strCopy2(t, "f");
  assert(strIndex2(s, t) == 0);

  printf("StrIndex2 tested.\n");
}


void testStrIndexRight() {
  char s[MAX_STR_SIZE] = "was was";
  char t[MAX_STR_SIZE] = "was";
  assert(strIndexRight(s, t) == 4);

  strCopy2(s, "foo bar baz");
  strCopy2(t, "a");
  assert(strIndexRight(s, t) == 9);

  strCopy2(s, "abcdef");
  strCopy2(t, "a");
  assert(strIndexRight(s, t) == 0);

  strCopy2(s, "abcdef");
  strCopy2(t, "f");
  assert(strIndexRight(s, t) == 5);

  printf("StrIndexRight tested.\n");
}


void testAtof2() {
  char s[MAX_STR_SIZE] = "1.23";
  assert(atof2(s) == 1.23);

  strCopy2(s, "123.456");
  assert(atof2(s) == 123.456);

  strCopy2(s, "    -999.3451");
  assert(atof2(s) == -999.3451);

  strCopy2(s, "1");
  assert(atof2(s) == 1);

  strCopy2(s, "0.1");
  assert(atof2(s) == 0.1);

  strCopy2(s, "0");
  assert(atof2(s) == 0);

  strCopy2(s, "0.001");
  assert(atof2(s) == 0.001);

  printf("Atof2 tested.\n");
}


void testAtof3() {
  char s[MAX_STR_SIZE] = "1.23";
  assert(atof3(s) == 1.23);

  strCopy2(s, "123456");
  assert(atof3(s) == 123456);

  strCopy2(s, "123.456");
  assert(atof3(s) == 123.456);

  strCopy2(s, "    -999.3451");
  assert(atof3(s) == -999.3451);

  strCopy2(s, "1");
  assert(atof3(s) == 1);

  strCopy2(s, "0.1");
  assert(atof3(s) == 0.1);

  strCopy2(s, "0");
  assert(atof3(s) == 0);

  strCopy2(s, "0.001");
  assert(atof3(s) == 0.001);

  strCopy2(s, "1.23e0");
  assert(atof3(s) == 1.23);

  strCopy2(s, "1.23e1");
  assert(atof3(s) == 12.3);

  strCopy2(s, "1.23e-1");
  assert(atof3(s) == 0.123);

  strCopy2(s, "1.23E-2");
  assert(atof3(s) == 0.0123);

  strCopy2(s, "1.23E6");
  assert(atof3(s) == 1230000);

  strCopy2(s, "1.23E-5");
  assertAlmostEquals(atof3(s), 0.0000123);

  strCopy2(s, "1.23E-6");
  assertAlmostEquals(atof3(s), 0.00000123);

  strCopy2(s, "1.23E-18");
  assertAlmostEquals(atof3(s), 0.00000000000000000123);

  strCopy2(s, "1.23009e19");
  assertAlmostEquals(atof3(s), 12300900000000000000UL);

  printf("Atof3 tested.\n");
}

void testPow2() {
  assert(pow2(10, 2) == 100);
  assert(pow2(10, 3) == 1000);
  assert(pow2(10, 4) == 10000);
  assert(pow2(2, 31) - 1 == INT_MAX);
  assert(pow2(2, 32) - 1 == UINT_MAX);
  assert(pow2(10, 0) == 1);
  printf("Pow2 tested.\n");
}

void testPow3() {
  assert(pow3(10, 2) == 100);
  assert(pow3(10, 3) == 1000);
  assert(pow3(10, 4) == 10000);
  assert(pow3(2, 31) - 1 == INT_MAX);
  assert(pow3(2, 32) - 1 == UINT_MAX);
  assert(pow3(10, 0) == 1);
  assert(pow3(10, -1) == 0.1);
  assert(pow3(10, -2) == 0.01);
  assert(pow3(10, -3) == 0.001);
  assert(pow3(10, -4) == 0.0001);
  assert(pow3(10, -5) == 0.00001);
  assert(pow3(10, -6) == 0.000001);
  assert(pow3(10, -7) == 0.0000001);
  assert(pow3(1.2, 2) == 1.44);
  assert(pow3(2.5, -2) == 0.16);
  printf("Pow3 tested.\n");
}

void testGetLine2() {
  char s[MAX_STR_SIZE];
  int result;

  printf("Type the name 'jason' and press enter: ");
  result = getLine2(s, MAX_STR_SIZE);
  char expected[MAX_STR_SIZE] = {'j', 'a', 's', 'o', 'n', '\n'};
  seq(s, expected);
  printf("GetLine2 tested.\n");
}

void testGetLine3() {
  char s[MAX_STR_SIZE];
  int result;

  printf("Type the name 'jason' and press enter: ");
  result = getLine3(s, MAX_STR_SIZE);
  char expected[MAX_STR_SIZE] = {'j', 'a', 's', 'o', 'n', '\n'};
  seq(s, expected);
  printf("GetLine3 tested.\n");
}

void testGetLine4() {
  char s[MAX_STR_SIZE];
  int result;

  printf("Type the name 'jason' and press enter: ");
  result = getLine4(s, MAX_STR_SIZE);
  char expected[MAX_STR_SIZE] = {'j', 'a', 's', 'o', 'n', '\n'};
  seq(s, expected);
  printf("GetLine4 tested.\n");
}

void testAssertAlmostEquals() {
  assertAlmostEquals(.000000011, .000000012);
  assertAlmostEquals(.111111123, .1111111229);
  printf("Assert almost equals tested.\n");
}


void testPrintd() {
  printd(-123);
  printf("\t");
  printd(0);
  printf("\t");
  printd(1);
  printf("\t");
  printd(10);
  printf("\t");
  printd(456);
  printf("\nPrintd tested.\n");
}

void testItoaRecurse() {
  char s[MAX_STR_SIZE];
  itoaRecurse(-987654, s, 0);
  seq(s, "-987654");
  itoaRecurse(1, s, 0);
  seq(s, "1");
  itoaRecurse(12345, s, 0);
  seq(s, "12345");
  itoaRecurse(0, s, 0);
  seq(s, "0");
  itoaRecurse(-10101010, s, 0);
  seq(s, "-10101010");
  printf("ItoaRecurse tested.\n");
}


void testMax() {
  // test the max macro.
  assert(max(1, 2) == 2);
  assert(max(3, 2) == 3);
  assert(max(1.23, 1.21) == 1.23);
  assert(max('c', 'z') == 'z');
  assert(max(3UL, 10UL) == 10UL);
  printf("Max macro tested.\n");
}

void testSquare() {
  int z = 3;
  assert(square(3) == 9);
  assert(square(z + 1) == 16);
  printf("Square tested.\n");
}

// paste(arg1, arg2) into token arg1arg2.
void testPaste() {
  char name1[MAX_STR_SIZE];
  char nameA[MAX_STR_SIZE];
  // paste(1, 2) is replaced by token 12.
  assert(paste(1, 2) == 12);
  // paste(name, 1) is replaced with token name1.
  assert(paste(name, 1) == name1);
  assert(paste(name, A) == nameA);
  printf("paste macro tested.\n");
}

void testSwapMacro() {
  // test the max macro.

  int tmp, x = 1, y = 2;
  swapMacro(tmp, &x, &y);
  assert(x == 2 && y == 1);

  char tmp2, a = 'a', b = 'b';
  swapMacro(tmp2, &a, &b);
  assert(a == 'b' && b == 'a');

  double tmp3, first = 2.34, second = -9.23;
  swapMacro(tmp3, &first, &second);
  assert(first == -9.23 && second == 2.34);

  printf("swapMacro macro tested.\n");
}

void testSwap3() {
  // test swap 3.

  int x = 1, y = 2;
  swap3(&x, &y, sizeof(int));
  assert(x == 2 && y == 1);

  char a = 'a', b = 'b';
  swap3(&a, &b, sizeof(char));
  assert(a == 'b' && b == 'a');

  double first = 2.34, second = -9.23;
  swap3(&first, &second, sizeof(double));
  assert(first == -9.23 && second == 2.34);

  printf("swap3 tested.\n");
}

void testSwapGeneric() {
  char *vals[] = {"one", "two", "three", "four"};
  SwapGeneric((void **) vals, 0, 1);
  assert(strcmp(vals[0], "two") == 0);
  assert(strcmp(vals[1], "one") == 0);
  int a = 1, b = 2, c = 3, d = 4;
  int *ap = &a, *bp = &b, *cp = &c, *dp = &d;
  int *vals2[] = {ap, bp, cp, dp};
  SwapGeneric((void **) vals2, 2, 3);
  assert(*vals2[2] == 4);
  assert(*vals2[3] == 3);
  printf("Swap generic tested.\n");
}

void testSwapAwesome() {

  // Test swap ints
  int a = 1, b = 2;
  SWAP(a, b);
  assert(a == 2 && b == 1);

  // Test swap strings.
  char first[50] = "jason";
  char second[50] = "amazing";
  SWAP(first, second);
  assert(strcmp(first, "amazing") == 0);
  assert(strcmp(second, "jason") == 0);

  // Test swap nodes.
  struct node {
    int value;
    struct node *next;
  };
  struct node one = {28, NULL};
  struct node two = {89, NULL};
  SWAP(one, two);
  assert(one.value == 89);
  assert(two.value == 28);

  // Test swap node pointers.
  struct node *node1 = &one;
  struct node *node2 = &two;
  SWAP(node1, node2);
  assert(node1->value == 28);
  assert(node2->value == 89);

  printf("SwapAwesome tested.\n");
}

void testGetInt() {
  int n;
  getInt(&n);
  printf("There number you typed was %d\n", n);
  printf("getInt tested.\n");
}


void testGetFloat() {
  double f;
  printf("Enter a floating point number: ");
  int error = getFloat(&f);
  if (error) {
    fprintf(stderr, "This number you entered was not a number.\n");
    exit(1);
  }
  printf("%f\n", f);
  printf("There number you typed was %f\n", f);
  printf("getFloat tested.\n");
}


void testStrLen3() {
  char s[MAX_STR_SIZE] = "jason";
  assert(strlen3(s) == 5);
  strCopy2(s, "");
  assert(strlen3(s) == 0);
  printf("strlen3 tested.\n");
}


void testStrLen4() {
  char s[MAX_STR_SIZE] = "jason";
  assert(strlen4(s) == 5);
  strCopy2(s, "");
  assert(strlen4(s) == 0);
  printf("strlen4 tested.\n");
}

void testStrEnd2() {
  assert(strEnd2("jason", "on") == 1);
  assert(strEnd2("jason ", "on ") == 1);
  assert(strEnd2("jason a ", " ") == 1);
  assert(strEnd2("jason", "n") == 1);
  assert(strEnd2(" j a s o n ", " a s o n ") == 1);
  assert(strEnd2(" j a s o n ", " j a s o n ") == 1);
  printf("strEnd2 tested.\n");
}

void testAlloc2() {
  // TODO(jason): Figure out why address of allocp is unchanged after alloc2 is
  // called.
  char *bp = alloc2(1024);
  free2(bp);
  bp = alloc2(1024);
  free2(bp);
  printf("alloc2 tested.\n");
}

void testStrnCpy2() {
  char s[MAX_STR_SIZE];
  char t[MAX_STR_SIZE] = "jason";
  char *result = strncpy2(s, t, 1);
  seq(result, "j");
  result = strncpy2(s, "a  bcde", 3);
  seq(result, "a  ");
  result = strncpy2(s, "a  bcde", 100);
  seq(result, "a  bcde");
  printf("StrnCpy2 tested.\n");
}


void testStrnCat2() {
  char s[MAX_STR_SIZE] = "jason";
  char t[MAX_STR_SIZE] = " foo blah";
  char *result = strncat2(s, t, 4);
  seq(s, "jason foo");
  result = strncat2(s, " bar.", 100);
  seq(s, "jason foo bar.");
  result = strncat2(s, t, 100);
  seq(s, "jason foo bar. foo blah");
  printf("StrnCat2 tested.\n");
}


void testStrnCmp2() {
  char s[MAX_STR_SIZE] = "jason";
  char t[MAX_STR_SIZE] = "jasoo";
  assert(strncmp2(s, s, 0) == 0);
  assert(strncmp2(s, s, 1) == 0);
  assert(strncmp2(s, s, 2) == 0);
  assert(strncmp2(s, s, 3) == 0);
  assert(strncmp2(s, s, 4) == 0);
  assert(strncmp2(s, t, 5) < 0);
  assert(strncmp2(s, t, 100) < 0);
  assert(strncmp2(t, s, 5) > 0);
  assert(strncmp2(t, s, 100) > 0);
  printf("StrnCmp2 tested.\n");
}

void testStrings1() {
  char *vals[] = {"jason", "stella", "rachelle", "justin", "greg", "kourtni", "adam", NULL};
  int i;
  for (i = 0; vals[i] != NULL; ++i)
    printf("%s\t", vals[i]);
  printf("\ntestStrings1 tested.\n");
}

void testStrings2() {
  char *vals[] = {"jason", "stella", "rachelle", "justin", "greg", "kourtni", "adam", NULL};
  char **items = vals;
  while (*items != NULL)
    printf("%s\t", *items++);
  printf("\ntestStrings2 tested.\n");
}

void testStrings3() {
  char *vals[] = {"jason", "stella", "rachelle", "justin", "greg", "kourtni", "adam"};
  int i;
  for (i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
    printf("%s\t", vals[i]);
  }
  printf("\ntestString3 tested.\n");
}

void testStrings4() {
  char *vals[] = {"jason", "stella", "rachelle", "justin", "greg", "kourtni", "adam"};
  char **items = vals;
  int i;
  seq(*items, "jason");
  assert(**items == 'j');
  assert(*(*items)++ == 'j');
  assert(*(*items)++ == 'a');
  assert(*(*items)++ == 's');
  assert(*(*items)++ == 'o');
  assert(*(*items)++ == 'n');
  assert(*(*items) == '\0');
  seq(*++items, "stella");
  assert(*(*items)++ == 's');
  assert(*(*items)++ == 't');
  assert(*(*items)++ == 'e');
  assert(*(*items)++ == 'l');
  assert(*(*items)++ == 'l');
  assert(*(*items)++ == 'a');
  assert(*(*items) == '\0');
  seq(*++items, "rachelle");
  seq(*++items, "justin");
  seq(*++items, "greg");
  seq(*++items, "kourtni");
  seq(*++items, "adam");
  // *++items is garbage after this...
  printf("\ntestStrings4 tested.\n");
}


void testDayOfYear() {
  assert(dayOfYear(2012, 1, 31) == 31);
  assert(dayOfYear(2012, 2, 20) == 51);
  assert(dayOfYear(1999, 3, 1) == 60);
  assert(dayOfYear(2000, 3, 1) == 61); // leap year.
  assert(dayOfYear(1999, 12, 31) == 365);
  assert(dayOfYear(2000, 12, 31) == 366); // leap year.
  printf("DayOfYear tested.\n");
}

void testMonthDay() {
  int pmonth, pday;
  monthDay(2012, 31, &pmonth, &pday);
  assert(pmonth == 1 && pday == 31);
  monthDay(2012, 51, &pmonth, &pday);
  assert(pmonth == 2 && pday == 20);
  monthDay(1999, 60, &pmonth, &pday);
  assert(pmonth == 3 && pday == 1);
  monthDay(2000, 61, &pmonth, &pday);
  assert(pmonth == 3 && pday == 1);
  monthDay(1999, 365, &pmonth, &pday);
  assert(pmonth == 12 && pday == 31);
  monthDay(2000, 366, &pmonth, &pday);
  assert(pmonth == 12 && pday == 31);
  printf("MonthDay tested.\n");
}

void testMonthName() {
  seq(monthName(0), "Illegal month");
  seq(monthName(1), "January");
  seq(monthName(3), "March");
  seq(monthName(6), "June");
  seq(monthName(9), "September");
  seq(monthName(12), "December");
  seq(monthName(13), "Illegal month");
  printf("MonthName tested.\n");
}

void testGetchAndUngetch() {
  extern int getch_buffp;
  getch_buffp = 0;
  assert(getch_buffp == 0);
  ungetch('a');
  assert(getch_buffp == 1);
  getch();
  assert(getch_buffp == 0);
  printf("Getch and ungetch tested.\n");
}

void testUngets() {
  extern int getch_buffp;
  getch_buffp = 0;
  assert(getch_buffp == 0);
  ungets("jason");
  assert(getch_buffp == 5);
  assert(getch() == 'j');
  assert(getch() == 'a');
  assert(getch() == 's');
  assert(getch() == 'o');
  assert(getch() == 'n');
  assert(getch_buffp == 0);
  ungetch(EOF);
  assert(getch() == EOF);
  printf("Ungets tested.\n");
}

void testGetWord() {
  printf("Enter the following string: "
         "ab12 AB12 12ab 12AB test 123 455abc_* 1jason2\n");
  char c, word[MAX_LINE_LEN];
  c = getword(word, MAX_LINE_LEN);
  assert(c == 'a');
  assert(strcmp(word, "ab12") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == 'A');
  assert(strcmp(word, "AB12") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '1');
  assert(strcmp(word, "1") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '2');
  assert(strcmp(word, "2") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == 'a');
  assert(strcmp(word, "ab") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '1');
  assert(strcmp(word, "1") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '2');
  assert(strcmp(word, "2") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == 'A');
  assert(strcmp(word, "AB") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == 't');
  assert(strcmp(word, "test") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '1');
  assert(strcmp(word, "1") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '2');
  assert(strcmp(word, "2") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '3');
  assert(strcmp(word, "3") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '4');
  assert(strcmp(word, "4") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '5');
  assert(strcmp(word, "5") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '5');
  assert(strcmp(word, "5") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == 'a');
  assert(strcmp(word, "abc") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '_');
  assert(strcmp(word, "_") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '*');
  assert(strcmp(word, "*") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == '1');
  assert(strcmp(word, "1") == 0);
  c = getword(word, MAX_LINE_LEN);
  assert(c == 'j');
  assert(strcmp(word, "jason2") == 0);
  printf("getWord tested.\n");
}

void testGetCToken() {
  printf("Enter the following program:\n"
         "#include <stdio.h>\n"
         "\n"
         "/* this is the /*main* program\n"
         " * to \"execute\" in this file.\n"
         " */\n"
         "int main() {\n"
         "  // create a string.\n"
         "  char _someName_123[10] = \"jason\";\n"
         "  return 123 / 12 ** 4;\n"
         "}\n");
  char c, word[MAX_LINE_LEN];
  //while ((c = getCToken(word, MAX_LINE_LEN)) != EOF) {
  //  printf("assert(c == '%c');\n", c);
  //  printf("assert(strcmp(word, \"%s\") == 0);\n", word);
  //}
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == '#');
  assert(strcmp(word, "#include <stdio.h>") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == 'i');
  assert(strcmp(word, "int") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == 'm');
  assert(strcmp(word, "main") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == '(');
  assert(strcmp(word, "(") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == ')');
  assert(strcmp(word, ")") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == '{');
  assert(strcmp(word, "{") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == 'c');
  assert(strcmp(word, "char") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == '_');
  assert(strcmp(word, "_someName_123") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == '[');
  assert(strcmp(word, "[") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == '1');
  assert(strcmp(word, "1") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == '0');
  assert(strcmp(word, "0") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == ']');
  assert(strcmp(word, "]") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == '=');
  assert(strcmp(word, "=") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == '"');
  assert(strcmp(word, "\"jason\"") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == ';');
  assert(strcmp(word, ";") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == 'r');
  assert(strcmp(word, "return") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == '1');
  assert(strcmp(word, "1") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == '2');
  assert(strcmp(word, "2") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == '3');
  assert(strcmp(word, "3") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == '/');
  assert(strcmp(word, "/") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == '1');
  assert(strcmp(word, "1") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == '2');
  assert(strcmp(word, "2") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == '*');
  assert(strcmp(word, "*") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == '*');
  assert(strcmp(word, "*") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == '4');
  assert(strcmp(word, "4") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == ';');
  assert(strcmp(word, ";") == 0);
  c = getCToken(word, MAX_LINE_LEN);
  assert(c == '}');
  assert(strcmp(word, "}") == 0);
  printf("getWord2 tested.\n");
}

int main() {
  /* Interactive programs */
  //testCountChars();
  //testGetLine2();
  //testGetLine3();
  //testGetLine4();
  //calculator();
  //testGetInt();
  //testGetFloat();
  //testGetWord();
  //testGetCToken();
  testStrings1();
  testStrings2();
  testStrings3();
  testStrings4();
  charTests();
  intTests();
  limitTests();
  maximumsTests();
  minimumsTests();
  negativeOneTests();
  nullTests();
  octalTests();
  testAny();
  testAssertAlmostEquals();
  testAtof2();
  testAtof3();
  testAtoi2();
  testAtoi3();
  testAlloc2();
  testBinSearch();
  testBinSearch2();
  testBitCount();
  testBits();
  testBtoi();
  testComparisonBetweenSignedAndUnsignedValues();
  testDayOfYear();
  testDprint();
  testEscapeAndUnescape();
  testExpand();
  testGetBits();
  testGetchAndUngetch();
  testGetIntFromHexChar();
  testHtoi();
  testIntArrayEquals();
  testInvertBits();
  testIsLeapYear();
  testItoa();
  testItoa2();
  testItoa3();
  testItoa4();
  testItoa5();
  testItoa2();
  testItoaRecurse();
  testItobase();
  testItobin();
  testLogicalOperatorsCast();
  testLower();
  testLowerAll();
  testMax();
  testMonthDay();
  testMonthName();
  testPaste();
  testPow2();
  testPow3();
  testPrintd();
  testPrint10Char();
  testPrintCharAll();
  testPrintIntAll();
  testQuickSort();
  testRand2AndSrand2();
  testReverse2();
  testReverse3();
  testReverseRecurse();
  testRightRotateChar();
  testRightRotateInt();
  testSetBits();
  testShellSort();
  testSquare();
  testSqueeze();
  testSqueezeMulti();
  testStrnCpy2();
  testStrnCat2();
  testStrnCmp2();
  testStrCat();
  testStrCat3();
  testStrComp();
  testStrComp2();
  testStrComp3();
  testStrComp4();
  testStrCopy2();
  testStrCopy3();
  testStrCopy4();
  testStrCopy5();
  testStrEnd2();
  testStrIndex();
  testStrIndex2();
  testStrIndexRight();
  testStrLen3();
  testStrLen4();
  testSwap3();
  testSwapGeneric();
  testSwapAwesome();
  testSwapMacro();
  testTrim();
  testUpperHexLetter();
  testUngets();
  return 0;
}
