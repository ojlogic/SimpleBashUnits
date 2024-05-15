#include "s21_cat.h"

int main(int argc, char *argv[]) {
  FLAGS arg = parse_flags(argc, argv);
  while (argv[optind]) {
    make_stream(argv[optind++], arg);
  }
  return 0;
}

FLAGS parse_flags(int argc, char **argv) {
  FLAGS arg = {0};
  struct option long_options[] = {{"number", no_argument, NULL, 'n'},
                                  {"number-nonblank", no_argument, NULL, 'b'},
                                  {"squeeze-blank", no_argument, NULL, 's'},
                                  {0, 0, 0, 0}};
  int opt;
  while ((opt = getopt_long(argc, argv, "bnsvEeTt", long_options, 0)) != -1) {
    switch (opt) {
      case 'b':
        arg.b = true;
        arg.n = false;
        break;
      case 'n':
        if (arg.b)
          arg.n = false;
        else
          arg.n = true;
        break;
      case 's':
        arg.s = true;
        break;
      case 'e':
        arg.e = true;
        arg.v = true;
        break;
      case 'E':
        arg.s = true;
        arg.e = true;
        break;
      case 't':
        arg.t = true;
        arg.v = true;
        break;
      case 'v':
        arg.v = true;
        break;
      case 'T':
        arg.t = true;
        break;
      default:
        printf("cat: illegal option -- %c\nusage: cat [-belnstuv] [file ...]",
               opt);
        exit(1);
    }
  }

  return arg;
}

void make_stream(char *file_path, FLAGS arg) {
  FILE *stream = fopen(file_path, "r");
  if (stream == NULL) {
    fprintf(stderr, "cat: %s: No such file or directory\n", file_path);
    exit(1);
  } else {
    process_file(stream, arg);
    fclose(stream);
  }
}

void process_file(FILE *stream, FLAGS arg) {
  int new_line = 1;
  int line_count = 1;
  char i = fgetc(stream);
  while (i != EOF) {
    if (i == '\n' && arg.s) {
      if (new_line <= 2) {
        print_line_number(&line_count, arg, new_line, i);
        if (arg.e) printf("$");
        printf("%c", i);
        new_line++;
      }
    } else {
      print_line_number(&line_count, arg, new_line, i);
      if (arg.e && i == '\n') printf("$");
      print_special_characters(&i, arg);
      printf("%c", i);
    }
    new_line++;
    if (i != '\n') new_line = 0;
    i = fgetc(stream);
  }
}

void print_line_number(int *line_count, FLAGS arg, int new_line, char i) {
  if (arg.n && new_line) printf("%6d\t", (*line_count)++);
  if (arg.b && new_line && i != '\n')
    printf("%6d\t", (*line_count)++);
  else if (arg.b && new_line && arg.e && i == '\n')
    printf("      \t");
}

void print_special_characters(char *i, FLAGS arg) {
  if (arg.v && *i >= 0 && *i < 32 && *i != '\t' && *i != '\n') {
    printf("^");
    *i += 64;
  }
  if (arg.t && *i == '\t') {
    printf("^");
    *i += 64;
  }
  if (arg.v && *i == 127) {
    printf("^");
    *i = '?';
  }
}
