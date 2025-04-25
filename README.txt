Desktop (Windows, Linux etc.) command line utility.
Encryption/Decryption of files/folders with a password.

Algorithm: AES-256 ECB (no IV)
Password storage: SHA-256 of the password stored in a dictionary in a home directory
Dictionary: key-value pair holding absolute names of files next to the hashes

Usage:
aes-util <argument> <option> <name>

argument  - encrypt/decrypt
option    - file/folder
name      - name of the file or folder in current working directory

=Warning=:
Losing the dictionary means losing all of your password hashes,
then you are left with just your memory of the passwords you used and where...

Encryption adds entries to the dictionary, while decryption removes entries.

If you delete an encrypted file, the dictionary will not auto-update.
In case of deletion of encrypted files, run "aes-util-update" to clean up the
dictionary.

