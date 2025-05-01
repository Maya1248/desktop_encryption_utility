Desktop (Windows, Linux etc.) command line utility.
Simplistic Encryption/Decryption of files with a password.

Algorithm: AES-256 ECB (no IV)
Password storage: SHA-256 of the password stored at the end of a file. 32 bytes are added to the file for the hash at the end.
Note: The password storage method is rather weak. Vulnerable to multiple attacks such as: rainbow tables, wordlist brute-forcing etc.

Usage:
aes-util ARGUMENT FILE PASSWORD

ARGUMENT  - encrypt, decrypt
FILE      - file name
PASSWORD  - password

=Lib sources=:
AES_256_ECB.h  - https://github.com/halloweeks/AES-256-ECB/blob/main/AES_256_ECB.h
SHA_256.h      - https://gist.github.com/AugFJTan/ad5979f4d5f1147baa9ebe269ed5e107
