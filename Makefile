# COMMON
COMMON_SRCS+=common
# ARITHMETIC
ARITHMETIC_SRCS+=s21_add
ARITHMETIC_SRCS+=s21_sub
ARITHMETIC_SRCS+=s21_mul
ARITHMETIC_SRCS+=s21_div
# COMPARISON
COMPARISON_SRCS+=s21_is_equal
COMPARISON_SRCS+=s21_is_greater_or_equal
COMPARISON_SRCS+=s21_is_greater
COMPARISON_SRCS+=s21_is_less_or_equal
COMPARISON_SRCS+=s21_is_less
COMPARISON_SRCS+=s21_is_not_equal
# CONVERSION
CONVERSION_SRCS+=s21_from_int_to_decimal
CONVERSION_SRCS+=s21_from_decimal_to_int
CONVERSION_SRCS+=s21_float_conversions
# OTHER
OTHER_SRCS+=s21_round
OTHER_SRCS+=s21_floor
OTHER_SRCS+=s21_truncate
OTHER_SRCS+=s21_negate
#################  DO NOT CHANGE BELOW  #################
BUILD_DIR=build/
ARITHMETIC_DIR=arithmetic/
COMPARISON_DIR=comparison/
CONVERSION_DIR=conversion/
OTHER_DIR=other/
COMMON_DIR=common/
UNIT_TESTS_DIR=unit_tests/
HEADERS_DIR=./ headers/
IFLAGS=$(addprefix -I, $(HEADERS_DIR))
CFLAGS=-Wall -Wextra -Werror -std=c11
COMPILER=gcc
COMMON_TARGETS_OBJ=$(addsuffix .o, $(addprefix $(COMMON_DIR), $(COMMON_SRCS)))
TARGETS+=$(addprefix $(ARITHMETIC_DIR), $(ARITHMETIC_SRCS))
TARGETS+=$(addprefix $(COMPARISON_DIR), $(COMPARISON_SRCS))
TARGETS+=$(addprefix $(CONVERSION_DIR), $(CONVERSION_SRCS))
TARGETS+=$(addprefix $(OTHER_DIR), $(OTHER_SRCS))
TARGETS_OBJ=$(addsuffix .o, $(TARGETS))
TEST_TARGERS_OBJ=$(addprefix $(UNIT_TESTS_DIR), $(addsuffix _test.o, $(TARGETS)))
TEST_TARGERS_OBJ+=$(UNIT_TESTS_DIR)common_test.o

all: s21_decimal.a

s21_decimal.a: $(TARGETS_OBJ) $(COMMON_TARGETS_OBJ)
	ar rc $@ $(addprefix $(BUILD_DIR), $(COMMON_TARGETS_OBJ)) $(addprefix $(BUILD_DIR), $(TARGETS_OBJ))
	ranlib $@

test: s21_decimal.a $(TEST_TARGERS_OBJ)
	$(COMPILER) $(CFLAGS) $(IFLAGS) $(addprefix $(BUILD_DIR), $(TEST_TARGERS_OBJ)) $(UNIT_TESTS_DIR)s21_decimal_tests_runner.c -o s21_decimal_test.out s21_decimal.a `pkg-config --cflags --libs check`

test_debug: CFLAGS+=-g -DS21_NOFORK
test_debug: test

debug: CFLAGS+=-g
debug: s21_decimal.a
	$(COMPILER) $(CFLAGS) $(IFLAGS) debug_function.c s21_decimal.a -o debug_function.out

gcov_report: CFLAGS += -fprofile-arcs -ftest-coverage
gcov_report: test
	-./s21_decimal_test.out
	lcov -t "report" -o report.info -c -d .
	genhtml -o "html_report" report.info
	open html_report/index.html

clean:
	-rm -rf $(BUILD_DIR)
	-rm s21_decimal.a
	-rm *.gcda
	-rm *.gcno
	-rm -rf html_report
	-rm report.info
	-rm s21_decimal_test.out
	-rm debug_function

mytest: s21_decimal.a
	gcc test.c s21_decimal.a -lm

%.o: %.c
	mkdir -p $(BUILD_DIR)$(@D)
	$(COMPILER) $(CFLAGS) $(IFLAGS) -c $< -o $(BUILD_DIR)$@
