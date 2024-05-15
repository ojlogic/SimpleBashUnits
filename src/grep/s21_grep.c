#include "s21_grep.h"

int main(int argc, char *argv[]) {
  OPTS data = {0};
  Parse_args(argc, argv, &data);  // парсим аргументы
  Parse_no_optarg(&data, &argc, argv);  // парсинг паттернов без f e
  Make_patterns(&data);  // создание списка скомпеллированных регулярок
  Start_grep(argv, &data);  // инициализация оcновной логики программы
  Free(&data);  // свобода памяти
}

void e_extract(OPTS *data) {
  data->e = true;
  data->arg_list[data->args_quantity] =
      (char *)malloc(sizeof(char) * (strlen(optarg) + 1));
  strcpy(data->arg_list[data->args_quantity++], optarg);
}

void f_extract(OPTS *data) {
  data->f = true;
  FILE *stream;
  stream = fopen(optarg, "r");
  if (stream == NULL) {
    fprintf(stderr, "grep: %s: No such file or directory\n", optarg);
  } else {
    char buffer[MAX_ARG_LENGTH];
    while (fgets(buffer, MAX_ARG_LENGTH - 1, stream)) {
      data->arg_list[data->args_quantity] =
          (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
      strcpy(data->arg_list[data->args_quantity++], buffer);
    }
    fclose(stream);
  }
}

void Parse_args(int argc, char **argv, OPTS *data) {
  int option = 0;
  while ((option = getopt(argc, argv, "cse:nof:ilvnh")) != -1) {
    switch (option) {
      case 'e':
        e_extract(data);
        break;
      case 'f':
        f_extract(data);
        break;
      case 'i':
        data->i = true;
        break;
      case 'v':
        data->v = true;
        break;
      case 'c':
        data->c = true;
        break;
      case 'l':
        data->l = true;
        break;
      case 'n':
        data->n = true;
        break;
      case 'h':
        data->h = true;
        break;
      case 's':
        data->s = true;
        break;
      case 'o':
        data->o = true;
        break;
      default:
        printf(
            "usage: grep [-abcdDEFGHhIiJLlMmnOopqRSsUVvwXxZz] [-A num] [-B "
            "num] "
            "[-C[num]]\n[-e pattern] [-f file] [--binary-files=value] "
            "[--color=when]\n[--context[=num]] [--directories=action] "
            "[--label] "
            "[--line-buffered]\n[--null] [pattern] [file ...]\n");
        exit(1);
    }
  }
}

void Parse_no_optarg(OPTS *data, int *argc, char **argv) {
  if (!data->args_quantity) {
    data->arg_list[data->args_quantity] =
        (char *)malloc(sizeof(char) * (strlen(argv[optind]) + 1));
    strcpy(data->arg_list[data->args_quantity++], argv[optind++]);
  }
  data->files_quantity = *argc - optind;
}

void Make_patterns(OPTS *data) {
  for (int i = 0; i < data->args_quantity; i++)
    regcomp(&data->patterns_list[i], data->arg_list[i],
            data->i ? REG_ICASE : 0);
}

void Start_grep(char **argv, OPTS *data) {
  char *file_path;
  while ((file_path = argv[optind++])) {
    FILE *stream;
    stream = fopen(file_path, "r");
    if (stream == NULL) {
      if (!data->s)
        fprintf(stderr, "grep: %s: No such file or directory\n", file_path);
    } else {
      if (data->c)
        C_process(stream, data, file_path);
      else if (data->l)
        L_process(stream, data, file_path);
      else if (data->v)
        V_process(stream, data, file_path);
      else
        Process(stream, data, file_path);
    }
  }
}

void C_process(FILE *stream, OPTS *data, char *file_path) {
  char buffer[MAX_ROW_LENGTH];
  int match_count = 0;
  while (fgets(buffer, MAX_ROW_LENGTH - 1, stream)) {
    for (int i = 0; i < data->args_quantity; i++) {
      if (!data->v &&
          regexec(&data->patterns_list[i], buffer, 0, NULL, 0) == 0) {
        match_count++;
        break;  // флаг v выключен
      }
      if (data->v &&
          regexec(&data->patterns_list[i], buffer, 0, NULL, 0) != 0) {
        match_count++;
        break;  // инверсия
      }
    }
  }
  if (data->files_quantity > 1 && !data->h) printf("%s:", file_path);
  if (match_count > 0 && data->l)
    printf("1\n%s\n", file_path);
  else
    printf("%d\n", match_count);
}

void L_process(FILE *stream, OPTS *data, char *file_path) {
  char buffer[MAX_ROW_LENGTH];
  bool kill = false;
  while (fgets(buffer, MAX_ROW_LENGTH - 1, stream)) {
    for (int i = 0; i < data->args_quantity; i++) {
      if (!data->v &&
          regexec(&data->patterns_list[i], buffer, 0, NULL, 0) == 0) {
        printf("%s\n", file_path);
        kill = true;
        break;
      }
      if (data->v &&
          regexec(&data->patterns_list[i], buffer, 0, NULL, 0) != 0) {
        printf("%s\n", file_path);
        kill = true;
        break;
      }
    }
    if (kill) return;
  }
}

void V_process(FILE *stream, OPTS *data, char *file_path) {
  char buffer[MAX_ROW_LENGTH];
  int rows = 1;
  while (fgets(buffer, MAX_ROW_LENGTH - 1, stream)) {
    if (buffer[strlen(buffer) - 1] == '\n') buffer[strlen(buffer) - 1] = '\0';
    for (int i = 0; i < data->args_quantity; i++) {
      if (regexec(&data->patterns_list[i], buffer, 0, NULL, 0) != 0) {
        if (!data->h && data->files_quantity > 1) printf("%s:", file_path);
        if (data->n) printf("%d:", rows);
        printf("%s\n", buffer);
      }
      rows++;
    }
  }
}

void Process(FILE *stream, OPTS *data, char *file_path) {
  char *buffer;
  buffer = (char *)malloc(sizeof(char) * MAX_ROW_LENGTH);
  char *free_buffer = buffer;
  int rows = 1;
  bool kill = false;
  regmatch_t match_t = {0};
  while (fgets(buffer, MAX_ROW_LENGTH - 1, stream)) {
    if (buffer[strlen(buffer) - 1] == '\n') buffer[strlen(buffer) - 1] = '\0';
    for (int i = 0; i < data->args_quantity; i++) {
      while (regexec(&data->patterns_list[i], buffer, 1, &match_t, 0) == 0) {
        if (!data->h && data->files_quantity > 1) printf("%s:", file_path);
        if (data->n) printf("%d:", rows);
        if (!data->o) {
          printf("%s\n", buffer);
          kill = true;
          break;
        }
        for (int i = match_t.rm_so; i < match_t.rm_eo; i++)
          printf("%c", buffer[i]);
        printf("\n");
        buffer += match_t.rm_eo;
      }
      if (kill) break;
    }
    rows++;
  }
  free(free_buffer);
}

void Free(OPTS *data) {
  for (int i = 0; i < data->args_quantity; i++) {
    regfree(&data->patterns_list[i]);
    free(data->arg_list[i]);
  }
}