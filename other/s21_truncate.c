#include "common.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int s = s21_get_sign(&value);
  s21_m_div(value, s21_m_pow(s21_ten(), s21_get_power(&value)), result);
  s21_set_sign(result, s);
  return 0;
}