#ifndef _SRC_HEADERS_COMMON_TEST_H_
#define _SRC_HEADERS_COMMON_TEST_H_

#include <check.h>
#include <stdlib.h>

#include "common.h"

#define LENGTH(X) sizeof(X) / sizeof(X[0])

s21_decimal s21_ints_to_decimal(int *value, int power, int sign);
s21_decimal s21_long_to_decimal(long long value, int power, int sign);
float Rand_R(float a, float b);
#endif  // _SRC_HEADERS_COMMON_TEST_H_
