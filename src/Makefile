.PHONY: s21_string.a test gcov_report check rebuild clean
CC = gcc -Wall -Wextra -Werror -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
OS=$(shell uname -s)
LIBS=-lcheck
# Определяем параметры для Linux систем
# LINUX=-lcheck -lsubunt -lm -lpthread -lrt
LINUX = -pthread -lcheck_pic -pthread -lrt -lm -lsubunit 
HEADERS = s21_matrix.h
SOURCES = $(wildcard *.c)
SRC= s21_matrix.c

OBJ_LIBRARY := $(patsubst %.c, %.o, $(SRC))
# Добавляем флаги в зависимости от операционной системы
ifeq ($(OS), Linux)
 CC += -D OS_LINUX
endif
ifeq ($(OS), Darwin)
 CC += -D OS_MAC
endif

# Компиляция объектных файлов
%.o: %.c $(HEADER)
	$(CC) -c $< -o $@

# Цель по умолчанию - очистить, построить библиотеку, выполнить тесты и отчёт покрытия
all: clean s21_matrix.a test gcov_report

# Построение статической библиотеки
s21_matrix.a: $(OBJ_LIBRARY) $(HEADERS)
	ar rcs s21_matrix.a $(OBJ_LIBRARY)
	ranlib s21_matrix.a
	rm -rf *.o

# Сборка и выполнение тестов
test: s21_matrix.a s21_matrix_tests.c
ifeq ($(OS), Darwin)
	$(CC) s21_matrix_tests.c s21_matrix.a -o test.out $(LIBS) -lm
else
	$(CC) s21_matrix_tests.c s21_matrix.a -o test.out $(LIBS) $(LINUX)
endif
	./test.out

# Создание отчёта покрытия кода тестами
gcov_report: clean_test
ifeq ($(OS), Darwin)
	$(CC) $(GCOVFLAGS) s21_matrix_tests.c ${SRC} -o test.out $(LIBS) -lm
else
	$(CC) $(GCOVFLAGS) s21_matrix_tests.c ${SRC} -o test.out $(LIBS) $(LINUX)
endif
	./test.out
	lcov -t "stest" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
ifeq ($(OS), Linux)
	links ./report/index.html
else
	open -a safari ./report/index.html
endif

# Запуск тестов с использованием Valgrind
# запускать через докер
valgrind: clean test
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test.out

# Проверка соответствия форматированию кода
check:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.c
	clang-format -n *.h
	rm -rf .clang-format

# Полная пересборка проекта
rebuild: clean all

# Очистка проекта от объектных файлов и результатов предыдущих сборок
clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.out *.gcov
	rm -rf test
	rm -rf ./report
	rm -rf *.dSYM

clean_test:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf test
	rm -rf report
