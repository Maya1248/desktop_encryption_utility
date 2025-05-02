Desktop (Windows, Linux etc.) command line utility.
Simplistic Encryption/Decryption of files with a password.

Algorithm:
AES-256 ECB (no IV)

Password storage:
Non-existent. 16 bytes of alternating 01 pattern is added at the end of the file and encrypted.
Password is checked such that the last 16 bytes are decrypted using whatever password you provided;
If the result ends up being the static 01 pattern, your password is correct and the whole file is decrypted. 

Note:
The method here used is rather simplistic and weak to wordlist attacks.
But if someone already got access to your device in order to do that, you kind of have bigger problems >:3

Usage:
aes-util ARGUMENT FILE PASSWORD

ARGUMENT  - encrypt, decrypt
FILE      - file name
PASSWORD  - password

=Lib sources=:
AES_256_ECB.h  - https://github.com/halloweeks/AES-256-ECB/blob/main/AES_256_ECB.h
SHA_256.h      - https://gist.github.com/AugFJTan/ad5979f4d5f1147baa9ebe269ed5e107
