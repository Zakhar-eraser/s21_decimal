#include "common.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  s21_set_sign(&value, !s21_get_sign(&value));
  *result = value;
  return 0;
}