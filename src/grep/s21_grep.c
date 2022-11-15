#include "s21_grep.h"

int main(int argc, char *argv[]) {
  off_options();
  parser(argc, argv);
  reader(argc, argv);
  return 0;
}

void parser(int argc, char *argv[]) {
  int f;
  while ((f = getopt_long(argc, argv, "e:ivclnhsf:o", 0, 0)) != -1) {
    switch (f) {
      case 'e':
        flag.e = ON;
        ++counts.flag_e;
        flag_e();
        break;
      case 'i':
        flag.i = ON;
        break;
      case 'v':
        flag.v = ON;
        break;
      case 'c':
        flag.c = ON;
        break;
      case 'l':
        flag.l = ON;
        break;
      case 'n':
        flag.n = ON;
        break;
      case 'h':
        flag.h = ON;
        break;
      case 's':
        flag.s = ON;
        break;
      case 'f':
        flag.f = ON;
        flag_f();
        break;
      case 'o':
        flag.o = ON;
        break;
      default:
        if (!flag.s) {
          fprintf(stderr, "grep: Invalid argument\n");
        }
        exit(EXIT_FAILURE);
    }
  }
  if (!flag.e && !flag.f) {
    strcat(pattern, argv[optind++]);
  }
  if (flag.v && flag.o) flag.o = OFF;
}

void reader(int argc, char *argv[]) {
  counts.files = argc - optind;
  if (argc < 3) {
    exit(EXIT_FAILURE);
  }
  while (optind < argc) {
    FILE *file = fopen(argv[optind], "r");
    if (file == NULL) {
      if (!flag.s) {
        fprintf(stderr, "No such file or directory\n");
      }
    } else {
      output(argv, file);
      fclose(file);
    }
    optind++;
  }
}

void flag_e() {
  if (counts.flag_e > 1) {
    strcat(pattern, "|");
  }
  strcat(pattern, optarg);
}

void flag_f() {
  FILE *file = NULL;
  char buffer[MAX_LEN] = {0};
  if ((file = fopen(optarg, "r"))) {
    while (fgets(buffer, MAX_LEN, file) != NULL) {
      if (buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = 0;
      }
      if (counts.flag_e > 0) {
        strcat(pattern, "|");
      }
      strcat(pattern, buffer);
      ++counts.flag_e;
    }
    fclose(file);
  } else {
    fprintf(stderr, "File not found\n");
    exit(EXIT_FAILURE);
  }
}

void output(char *argv[], FILE *file) {
  regex_t re;
  int cflags = REG_EXTENDED;
  int pmatch = 1;
  regmatch_t regmatch[1] = {0};
  int status;
  char buffer[MAX_LEN];
  size_t number_string = 1;
  int count_flag_c = 0;
  if (flag.i) {
    cflags = REG_ICASE;
  }
  regcomp(&re, pattern, cflags);
  while (!feof(file)) {
    if (fgets(buffer, MAX_LEN, file)) {
      int is_new_line = 1;
      status = regexec(&re, buffer, pmatch, regmatch, 0);
      if (flag.v) {
        status = !status;
      }
      if (status != REG_NOMATCH) {
        if (!flag.c && !flag.l) {
          if (!flag.h && counts.files > 1) {
            printf("%s:", argv[optind]);
          }
          if (flag.n) {
            printf("%lu:", number_string);
          }
          if (flag.o && !flag.v) {
            is_new_line = 0;
            char *ptr = buffer;
            while (!status) {
              printf("%.*s\n", (int)(regmatch[0].rm_eo - regmatch[0].rm_so),
                     ptr + regmatch[0].rm_so);
              ptr += regmatch[0].rm_eo;
              status = regexec(&re, ptr, pmatch, regmatch, REG_NOTBOL);
            }
          }
          if (!flag.o) {
            printf("%s", buffer);
          }
          if (buffer[strlen(buffer) - 1] != '\n' && is_new_line) {
            printf("\n");
          }
        }
        ++count_flag_c;
      }
      ++number_string;
    }
  }
  if (flag.c) {
    if (!flag.h && counts.files > 1) {
      printf("%s:", argv[optind]);
    }
    if (flag.l && count_flag_c) {
      printf("1\n");
    } else {
      printf("%d\n", count_flag_c);
    }
  }
  if (flag.l && count_flag_c) {
    printf("%s\n", argv[optind]);
  }
  regfree(&re);
}
