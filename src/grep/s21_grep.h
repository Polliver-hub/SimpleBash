#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 2048
#define OFF 0
#define ON 1

struct options_grep {
  int e, v, i, c, n, l, h, s, f, o;
} flag;

struct counts_for_options {
  int files;
  int flag_e;
} counts;

char pattern[MAX_LEN] = {0};

void parser(int argc, char *argv[]);
void reader(int argc, char *argv[]);
void output(char *argv[], FILE *file);
void flag_e();
void flag_f();

void off_options() {
  flag.e = OFF;
  flag.v = OFF;
  flag.i = OFF;
  flag.c = OFF;
  flag.n = OFF;
  flag.l = OFF;
  flag.h = OFF;
  flag.s = OFF;
  flag.f = OFF;
  flag.o = OFF;

  counts.files = 0;
  counts.flag_e = 0;
}

#endif  //  SRC_GREP_S21_GREP_H_
