#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/AES_256_ECB.h"
#include "../lib/SHA_256.h"

void dump_bytes(unsigned char *bytes, int size) {
	for (int i=0; i<size; i++) {
		printf("%02x", bytes[i]);
	}
	printf("\n");
}

int main() {
	unsigned char *bytes;
	bytes = hash("hai Mamma Mia");

	dump_bytes(bytes, 32);

	free(bytes);
	return 0;
}
