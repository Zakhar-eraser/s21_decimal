#include "common.h"

int s21_round(s21_decimal, s21_decimal *);

int s21_round(s21_decimal value, s21_decimal *result) {
  *result = value;
  int pow = s21_get_power(result);
  if (pow) {
    s21_decimal rem = s21_m_div(*result, s21_m_pow(s21_ten(), pow), result);
    s21_m_div(rem, s21_m_pow(s21_ten(), pow - 1), &rem);
    if (rem.bits[0] >= 5) s21_m_add(*result, s21_one(), result);
    s21_set_sign(result, s21_get_sign(&value));
  }
  return 0;
}
