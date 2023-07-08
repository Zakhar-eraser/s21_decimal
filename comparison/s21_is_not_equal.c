#include "common.h"

int s21_is_not_equal(s21_decimal val_1, s21_decimal val_2) {
  s21_clean_zero(&val_1);
  s21_clean_zero(&val_2);
  int out;
  s21_decimal *tmp1, *tmp2;
  if (s21_normalize(&val_1, &val_2, &tmp1, &tmp2)) {
    out = 1;
  } else {
    out = s21_get_sign(&val_1) != s21_get_sign(&val_2) ||
          s21_is_m_not_equal(&val_1, &val_2);
  }
  return out;
}

int s21_is_m_not_equal(s21_decimal *val_1, s21_decimal *val_2) {
  return !s21_is_m_equal(val_1, val_2);
}
