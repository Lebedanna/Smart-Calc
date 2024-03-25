CC=g++
CFLAGS=-Wall -Wextra -Werror -std=c++17 -g
TESTFLAGS=-lgtest
TESTFILES=Tests/tests.cpp
INST_DIR=s21_smart_calc
DIST_DIR=s21_smart_calc_archive

all: valgrind install clean

install:
	@mkdir $(INST_DIR)
	@cd $(INST_DIR); qmake ../View/s21_smart_calc.pro
	@cd $(INST_DIR); make
	@cd $(INST_DIR); make clean
	@open $(INST_DIR)

uninstall:
	@rm -r $(INST_DIR)

clean:
	@rm -rf $(TARGET)  test *.a *.o *.out *.cfg fizz *.gc* *.info .stash report CPPLINT.cfg $(INST_DIR)
	@rm -rf *.o *.out *.cfg *.tar manual .clang-format

dvi:
	open About/dvi.html

dist:
	rm -rf $(DIST_DIR)/
	mkdir $(DIST_DIR)/
	mkdir $(DIST_DIR)/src $(DIST_DIR)/src/Controller/ $(DIST_DIR)/src/Model/ $(DIST_DIR)/src/View/ $(DIST_DIR)/src/Tests/ $(DIST_DIR)/src/About/
	cp Makefile $(DIST_DIR)/src/
	cp About/dvi.html $(DIST_DIR)/src/About
	cp Controller/* $(DIST_DIR)/src/Controller/
	cp Model/* $(DIST_DIR)/src/Model/
	cp View/* $(DIST_DIR)/src/View/
	cp Tests/* $(DIST_DIR)/src/Tests/
	tar cvzf $(DIST_DIR).tar $(DIST_DIR)/
	mv $(DIST_DIR).tar $(HOME)/
	rm -rf $(DIST_DIR)/


tests:
	@$(CC) $(CFLAGS) Tests/*.cpp Model/s21_smart_calc_model.cpp -o test -lgtest_main -lgtest -lpthread
	@./test

style:
	@cp ../materials/linters/.clang-format .
	@clang-format -n Controller/* Model/* Tests/*
	@rm .clang-format

gcov_report:
	@$(CC) $(CFLAGS) Tests/*.cpp Model/s21_smart_calc_model.cpp --coverage -o test -lgtest_main -lgtest -lpthread
	@./test
	@lcov -t "test" -o test.info -c -d ./ --no-external
	@genhtml -o report test.info
	@open report/index.html
	@rm *.gcno *.gcda *.info test

valgrind:
	@make tests
	@valgrind --leak-check=full --leak-resolution=med -s ./test

.PHONY: all, install, uninstall, clean, dvi, dist, tests