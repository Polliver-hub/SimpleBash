#include "s21_cat.h"

int main(int argc, char *argv[]) {
  flags flag = {0};
  parser(argc, argv, &flag);
  while (optind < argc) {
    reader(argv, &flag);
    optind++;
  }
  return 0;
}
