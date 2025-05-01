#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../lib/AES_256_ECB.h"
#include "../lib/SHA_256.h"
#include "../lib/file_ops.h"

void dump_bytes(unsigned char *bytes, int size) {
	for (int i=0; i<size; i++) {
		printf("%02x", bytes[i]);
	}
	printf("\n");
}

void help() {
	printf("Usage: aes-util ARGUMENT FILE PASSWORD\n");
	printf("ARGUMENT - encrypt, decrypt\n");
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

	if (argc != 4) {  // Handles arguments
		help();
		return 1;
	}
	if (strcmp(argv[1], "encrypt") != 0 && strcmp(argv[1], "decrypt") != 0) {
		help();
		printf("Wrong argument provided.\n");
		return 1;
	}
	if (is_writable(argv[2]) != 0) {  // SHOULD handle relative/absolute file paths, not just current working directory...
		help();
		printf("Can not access file.\n");
		return 1;
	} // Assuming the user performs proper path handling in linux/windows on terminal.
	
	
	if (hasEnc(argv[2]) != 0) {
		printf("File does not have .enc extension and is assumed not encrypted.\n");
		return 1;
	}



	// Password check
	if (check_password(argv[3], argv[2]) != 0) {
		printf("Wrong password!\n");
		printf("NOTE: Keep in mind, I assume that this file even has a password to begin with.\n");
		return 1;
	}



	return 0;
}
