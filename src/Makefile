G++ = g++ -std=c++17
CHECKFLAGS = -Wall -Werror -Wextra
SRC = model/calculation.cc model/notation.cc  model/validator.cc model/model.cc model/parser.cc model/creditcalc.cc model/depositcalc.cc
TEST_SRC = tests/test.cc
TEST_LIBS = -lgtest -pthread 
OBJ = $(SRC:%.cc=%.o)
OS = $(shell uname -s)

ifeq ($(OS), Darwin)
	NAME_APP=SmartCalc.app
else
	NAME_APP=SmartCalc
endif

all: clean tests

tests: clean
	$(G++) $(TEST_SRC) $(SRC)  $(CHECKFLAGS) $(TEST_LIBS) -o test
	./test

clean:
	rm -rf Archive_s21_smartcalc test.dSYM qt_files/.qtc_clangd qt_files/SmartCalc.pro.user.baeeba1 qt_files/.qmake.stash model/*.o *.css qt_files/.DS_Store .DS_Store *.html *.gcda *.gcno *.a test qt_files/.qm qt_files/*.o *.tgz qt_files/.qmake.stash qt_files/*.qrc  qt_files/ui_*  qt_files/*.app test_output gcov_test report qt_files/moc_* qt_files/SmartCalc.pro.user qt_files/SmartCalc ./build/

html: doxygen
	open ../documentation/html/annotated.html

install: 
	rm -rf build
	mkdir build
	cd qt_files && qmake && make && mv $(NAME_APP) ../build && cd ../
	./build/$(NAME_APP)

uninstall:
	rm -rf build*
	rm -rf qt_files/moc*
	rm -rf qt_files/*.o
	rm -rf qt_files/ui*
	rm -rf qt_files/.qmake.stash
	rm -rf qt_files/view-94*
	rm -rf qt_files/Makefile

dist: install
	rm -rf Archive_s21_smartcalc/
	mkdir Archive_s21_smartcalc/
	mkdir Archive_s21_smartcalc/src
	cp -r ./build/$(NAME_APP) Archive_s21_smartcalc/src/
	tar cvzf Archive_s21_smartcalc.tgz Archive_s21_smartcalc/
	rm -rf Archive_s21_smartcalc/

gcov_report: clean
	$(G++) --coverage $(TEST_SRC) $(SRC) $(CHECKFLAGS) $(TEST_LIBS) -o gcov_test $(shell pkg-config --libs --cflags check)
	./gcov_test
	gcovr -r . --html --html-details -o smartcalc.html
	open ./smartcalc.html

clang: 
	clang-format -style=google -i model/*.cc view/*.cc controller/*.cc qt_files/*.cc
	clang-format -style=google -i model/*.h view/*.h controller/*.h qt_files/*.h

clang-format: 
	clang-format -style=google -n model/*.cc view/*.cc controller/*.cc qt_files/*.cc
	clang-format -style=google -n model/*.h view/*.h controller/*.h qt_files/*.h

doxygen:
	cd ../documentation && doxygen Doxyfile && cd ../src
	
fsanitize: 
	$(G++) $(TEST_SRC) $(SRC)  $(CHECKFLAGS) -g -fsanitize=address $(TEST_LIBS) -o test
	./test

valgrind: tests
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./test
