CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Werror -Wuninitialized -fpermissive
CLIBS  = -lgtest -lgtest_main
FOLDERS = ./s21_allocators/* ./s21_iterators/* ./s21_sequence_containers/* \
					./s21_associative_containers/* ./s21_container_adaptors/* ./s21_set_containers/*

all: test

clean:
	rm -f *.a *.gcda *.gcno
	rm -rf build

test: clean s21_containers.h s21_containersplus.h
	mkdir -p build
	$(CC) $(CFLAGS) tests/* -o build/tests $(CLIBS)
	./build/tests

s21_containers.o: clean
	mkdir -p build
	$(CC) $(CFLAGS) s21_containers.h -o build/s21_containers.o

s21_containersplus.o: clean
	mkdir -p build
	$(CC) $(CFLAGS) s21_containersplus.h -o build/s21_containersplus.o

gcov-report: CFLAGS+= --coverage
gcov-report: test
	lcov -t "tests" -o ./build/gcov-report.info -c -d . --no-external
	genhtml -o ./build/report ./build/gcov-report.info
	#open ./build/report/index.html

googlestyle:
	cp ../materials/linters/.clang-format ./
	clang-format -i $(FOLDERS) ./tests/*
	rm -f ./.clang-format

clang-format:
	cp ../materials/linters/.clang-format ./
	clang-format -n $(FOLDERS) ./tests/*
	rm -f ./.clang-format

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --std=c++17 --language=c++ \
	$(FOLDERS)

valgrind: CFLAGS+= -g
valgrind: test
	valgrind --tool=memcheck --leak-check=yes -s -q ./build/tests

leaks: test
	CK_FORK=no leaks -atExit -- ./build/tests

