#include "common.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  *dst = s21_zero();
  if (src < 0) {
    s21_set_sign(dst, 1);
    dst->bits[0] = -src;
  } else {
    dst->bits[0] = src;
  }
  return 0;
}
