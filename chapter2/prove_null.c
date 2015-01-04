#include <stdio.h>
#include <assert.h>
#include <limits.h>

int main() {
	assert('\0' == 0);
	assert(NULL == 0);
	assert(NULL == '\x0');
	assert(NULL == '\000');
	assert('\x0' == 0);
	assert('\000' == 0);
	assert('a' == 97);
	assert('\010' == 8);
	assert('\100' == 64);
	assert('\177' == 127);
	assert(CHAR_MAX == 127);
	assert(CHAR_MAX == '\x7f');
	//assert('\200' == 128); // this will break.

	return 0;
}
