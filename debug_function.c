#include <stdio.h>
#include <stdlib.h>

#include "common.h"

void print_decimal(s21_decimal *val) {
  printf("{%i, %i, %i}\n", val->bits[0], val->bits[1], val->bits[2]);
}

int main() {
  s21_decimal v1 = {{2}};
  s21_decimal result = {{0}};
  if (result.bits[0]) {
    s21_m_mul(v1, s21_m_pow(s21_ten(), 14), &result);
  }
  s21_m_mul(v1, s21_m_pow(s21_ten(), 14), &result);
  print_decimal(&result);
  return 0;
}