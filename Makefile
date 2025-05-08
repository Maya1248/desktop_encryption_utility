CC=gcc

all: aes-util

aes-util: ./src/main.c
	gcc ./src/main.c -o ./bin/aes-util

