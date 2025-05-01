#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../lib/AES_256_ECB.h"
#include "../lib/SHA_256.h"

void dump_bytes(unsigned char *bytes, int size) {
	for (int i=0; i<size; i++) {
		printf("%02x", bytes[i]);
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	
	/*
	unsigned char *bytes;
	bytes = hash("Test 0 1 Test   2");

	dump_bytes(bytes, 32);

	free(bytes);

	
	for (int i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}
	*/

	if (argc != 4) {
		printf("Usage: aes-util ARGUMENT FILE PASSWORD\n");
		printf("ARGUMENT - encrypt, decrypt\n");
		return 1;
	}

	

	return 0;
}
