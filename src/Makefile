CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Werror
CLIBS  = $(shell pkg-config --cflags --libs gtest)
SRC  := $(shell find -name "s21*.h" | sed 's/\.\///')
OBJS := $(SRC:%.h=build/%.o)

all: test

clean:
	rm -f *.a
	rm -rf build

test: clean s21_containers.a
	$(CC) $(CFLAGS) tests.cpp -o build/tests s21_matrix_oop.a $(CLIBS)
	./build/tests

s21_containers.a: $(OBJS)
	ar -rcs s21_containers.a $(OBJS)

build/%.o: %.h
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

gcov-report: CFLAGS+= --coverage
gcov-report: test
	lcov -t "tests" -o ./build/gcov-report.info -c -d . --no-external
	genhtml -o ./build/report ./build/gcov-report.info
	#open ./build/report/index.html

codestyle:
	cp ../materials/linters/.clang-format ./
	clang-format -i ./*.h
	rm -f ./.clang-format

clang-format:
	cp ../materials/linters/.clang-format ./
	clang-format -n ./*.h
	rm -f ./.clang-format

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --std=c++17 --language=c++ ./*.h ./*.cpp

valgrind: CFLAGS+= -g
valgrind: test
	valgrind --leak-check=full --leak-resolution=high -s -q ./build/tests

leaks: test
	CK_FORK=no leaks -atExit -- ./build/tests

