CC=gcc
CFLAGS=-Wall -Wextra -Werror

all: s21_cat

s21_cat: main.c s21_cat.c
	$(CC) $(CFLAGS) -o s21_cat main.c s21_cat.c

clean:
	rm -rf s21_cat

rebuild: clean all
