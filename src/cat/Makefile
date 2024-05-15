# обязательно подключить для работы diff
SHELL := /bin/bash
FLAG = -Wall -Werror -Wextra -std=c11
FILE = samp1.txt samp2.txt

all: s21_cat

s21_cat: clean
#clang-format -i s21_cat.c s21_cat.h
	gcc $(FLAG) s21_cat.c -o s21_cat

test:
	cd test_cat && sh test_func_cat.sh

leak:
	cd test_cat&&sh test_leak_cat.sh

clean:
	rm -f s21_cat
	-clear
