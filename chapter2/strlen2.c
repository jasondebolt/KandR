#include <stdio.h>
#include <assert.h>

int strlen2(char s[]) {
	int i = 0;
	
	while (s[i] != '\0')
	  i++;
	return i;
}

int main() {
	
	assert(strlen2("jason ") == 6);
	return 0;
}
