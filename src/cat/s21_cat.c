#include "s21_cat.h"

void reader(char *argv[], flags *flag) {
  FILE *file;
  file = fopen(argv[optind], "r");
  if (file != NULL) {
    int str_count = 1;
    int empty_str_count = 0;
    int last = '\n';
    while (!feof(file)) {
      int ch = fgetc(file);
      if (ch == EOF) break;
      if (flag->s && ch == '\n' && last == '\n') {
        empty_str_count++;
        if (empty_str_count > 1) {
          continue;
        }
      } else {
        empty_str_count = 0;
      }
      if (last == '\n' && ((flag->b && ch != '\n') || flag->n))
        printf("%6d\t", str_count++);
      if (flag->t && ch == '\t') {
        printf("^");
        ch = 'I';
      }
      if (flag->e && ch == '\n') printf("$");
      if (flag->v) {
        if ((ch >= 0 && ch < 9) || (ch > 10 && ch < 32) ||
            (ch > 126 && ch <= 160)) {
          printf("^");
          if (ch > 126) {
            ch -= 64;
          } else {
            ch += 64;
          }
        }
      }
      printf("%c", ch);
      last = ch;
    }
    fclose(file);
  } else {
    exit(EXIT_FAILURE);
  }
}

int parser(int argc, char *argv[], flags *flag) {
  int f;
  const char *f_options = "+benstvET";
  static struct option options[] = {
      {"number-nonblank", 0, 0, 'b'},
      {"number", 0, 0, 'n'},
      {"squeeze-blank", 0, 0, 's'},
      {0, 0, 0, 0},
  };
  while ((f = getopt_long(argc, argv, f_options, options, NULL)) != -1) {
    switch (f) {
      case 'b':
        flag->b = ON;
        break;
      case 'e':
        flag->e = ON;
        flag->v = ON;
        break;
      case 'n':
        flag->n = ON;
        break;
      case 's':
        flag->s = ON;
        break;
      case 't':
        flag->t = ON;
        flag->v = ON;
        break;
      case 'v':
        flag->v = ON;
        break;
      case 'E':
        flag->e = ON;
        break;
      case 'T':
        flag->t = ON;
        break;
      default:
        printf("Wrong flag\n");
        exit(EXIT_FAILURE);
        break;
    }
    if (flag->b && flag->n) flag->n = OFF;
  }
  return 0;
}
