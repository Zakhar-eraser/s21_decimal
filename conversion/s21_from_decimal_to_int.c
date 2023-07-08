#include "common.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int s = s21_get_sign(&src);
  s21_m_div(src, s21_m_pow(s21_ten(), s21_get_power(&src)), &src);
  unsigned int res = src.bits[0];
  int out;
  *dst = 0;
  if (src.bits[1] || src.bits[2] || (!s && res > 0x7FFFFFFF) ||
      (s && res > 0x80000000)) {
    out = 1;
  } else {
    out = 0;
    *dst = src.bits[0];
    if (s) *dst *= -1;
  }
  return out;
}