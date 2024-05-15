#ifndef S21_CAT_H
#define S21_CAT_H

#define _GNU_SOURCE

#include <errno.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  int b, e, n, s, t, v;  // Флаги, которые будут использоваться
} FLAGS;

FLAGS parse_flags(int argc, char **argv);
void make_stream(char *file_path, FLAGS arg);
void print_line_number(int *line_count, FLAGS arg, int new_line, char i);
void print_special_characters(char *i, FLAGS arg);
void process_file(FILE *stream, FLAGS arg);
#endif  // S21_CAT_H