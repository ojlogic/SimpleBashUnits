#ifndef S21_GREP_H
#define S21_GREP_H
#define _GNU_SOURCE

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ARGS 128
#define MAX_ARG_LENGTH 512
#define MAX_ROW_LENGTH 4096

typedef struct {
  bool e, f, i, v, c, l, n, h, o, s;
  int args_quantity;  // инлекс в массиве строк
  regex_t patterns_list[MAX_ARGS];
  char *arg_list[MAX_ARGS];  // нескомпелированные паттерны
  int files_quantity;
} OPTS;

void Parse_args(int argc, char **argv, OPTS *data);
void Parse_no_optarg(OPTS *data, int *argc, char **argv);
void Start_grep(char **argv, OPTS *data);
void C_process(FILE *stream, OPTS *data, char *file_path);
void L_process(FILE *stream, OPTS *data, char *file_path);
void V_process(FILE *stream, OPTS *data, char *file_path);
void Process(FILE *stream, OPTS *data, char *file_path);
void Free(OPTS *data);
void Make_patterns(OPTS *data);

#endif  // S21_GREP_H
