#include "common.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int pow = s21_get_power(&value);
  int s = s21_get_sign(&value);
  value = s21_m_div(value, s21_m_pow(s21_ten(), pow), result);
  if (s && !s21_is_zero(&value)) s21_m_add(*result, s21_one(), result);
  s21_set_sign(result, s);
  return 0;
}