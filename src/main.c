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

	if (argc != 4) {  // Handles arguments
		help();
		return 1;
	}

	char *argument = argv[1];
	char *file_name = argv[2];
	char *password = argv[3];

	if (strcmp(argument, "encrypt") != 0 && strcmp(argument, "decrypt") != 0) {
		help();
		printf("Wrong argument provided.\n");
		return 1;
	}
	if (is_writable(file_name) != 0) {  // SHOULD handle relative/absolute file paths, not just current working directory...
		help();
		printf("Can not access file.\n");
		return 1;
	} // Assuming the user performs proper path handling in linux/windows on terminal.


	if (strcmp(argument, "encrypt") == 0) {
		if (hasEnc(file_name) == 0) {
			printf("This file has .enc extension and is assumed to be already encrypted. Exiting...\n");
			return 1;
		}

		encrypt_file(file_name, password);
		printf("%s encrypted.\n", file_name);

	} else if (strcmp(argument, "decrypt") == 0) {
		if (hasEnc(file_name) != 0) {
			printf("This file does not have .enc extension and is assumed to be not encrypted. Exiting...\n");
			return 1;
		}
		if (get_file_size(file_name) < 16) {
			printf("Stop messing around! You just took a tini-tiny file and added .enc at the end to see what would happen >:3\n");
			return 1;
		}
		if (get_file_size(file_name) % 16 != 0) {
			printf("If this file were encrypted by me, the file size would be divisible by 16 bytes. This one is not. Can not proceed.\n");
			return 1;
		}

		// Password check
		if (check_password(password, file_name) != 0) {
			printf("Wrong password!\n");
			return 1;
		}

		decrypt_file(file_name, password);
		printf("%s decrypted.\n", file_name);
	}

	return 0;
}
