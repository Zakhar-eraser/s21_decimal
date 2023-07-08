#include "common.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int return_val = 0;
  *dst = 0.0;
  int scale = s21_get_power(&src);
  for (int i = 0; i < 96; i++) {
    if (s21_dec_get_bit(&src, i)) {
      *dst += powl(2, i);
    }
  }
  while (scale) {
    *dst /= 10;
    scale--;
  }
  if (s21_get_sign(&src)) {
    *dst = *dst * (-1);
  }
  // }
  return return_val;
}