#include <stdio.h>

int main() {
	const char full_name[] = "jason debolt";
	int i = 0;
	
	while(full_name[i] != '\0') {
		printf("%c ", full_name[i++]);
	}
	printf("\n");
	
	i = 0;
	while(full_name[i] != '\0') {
		printf("%d ", full_name[i++]);
	}
	printf("\n");
	
	i = 0;
	while(full_name[i] != '\0') {
		printf("%o ", full_name[i++]);
	}
	printf("\n");	
	
	i = 0;
	while(full_name[i] != '\0') {
		printf("%x ", full_name[i++]);
	}
	printf("\n");
	
	return 0;
}
