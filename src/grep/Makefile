FLAG = -Wall -Werror -Wextra -std=c11

all: s21_grep

s21_grep: clean
#clang-format -i s21_grep.c s21_grep.h
	gcc $(FLAG) s21_grep.c -o s21_grep
	
test:
	cd test_grep&&sh test_func_grep.sh

leak:
	cd test_grep&&sh test_leak_grep.sh

clean:
	rm -f s21_grep
	-clear