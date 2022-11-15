CC=gcc
CFLAGS=-Wall -Wextra -Werror

all: s21_grep

s21_grep: s21_grep.c
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep

clean:
	rm -rf s21_grep

rebuild: clean all
