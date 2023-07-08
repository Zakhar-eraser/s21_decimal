#include "common.h"
#define MAX_POWER 28

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int return_val = 0;
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;
  if (fabs(src) < powl(10.0, -1 * MAX_POWER) && fabs(src) != 0.0) {
    return_val = 1;
  } else if (fabs(src) > powl(2, 96)) {
    return_val = 1;
  } else if (fabs(src) <= powl(2, -96) && fabs(src) != 0.0) {
    return_val = 1;
  } else {
    int scale = 0;
    if (src < 0.0) s21_set_sign(dst, 1);
    src = fabsl(src);
    for (; !(int)src && scale < MAX_POWER; src = src * 10) {
      scale++;
    }  // normalize

    int i = 0;
    for (; src < powl(2.0, 96) && scale < MAX_POWER && i < 7; i++) {
      src *= (long double)10.0;
      scale++;
    }
    src = (long double)roundl(src);
    for (i = 0; src >= powl(10.0, -1 * (7 + 1)) && i < 96; i++) {
      src = floorl(src) / 2;
      if (src - floorl(src) > powl(10.0, -1 * (7 + 1))) {
        s21_dec_set_bit(dst, i, 1);
      }
    }
    for (int i = 0; i < 4; i++) {
    }
    s21_set_power(dst, scale);
  }
  return return_val;
}