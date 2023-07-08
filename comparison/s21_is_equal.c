#include "common.h"

int s21_is_equal(s21_decimal val_1, s21_decimal val_2) {
  int out;
  s21_clean_zero(&val_1);
  s21_clean_zero(&val_2);
  s21_decimal *tmp1, *tmp2;
  if (s21_normalize(&val_1, &val_2, &tmp1, &tmp2)) {
    out = 0;
  } else {
    out = s21_get_sign(&val_1) == s21_get_sign(&val_2) &&
          s21_is_m_equal(&val_1, &val_2);
  }
  return out;
}

void s21_clean_zero(s21_decimal *val) {
  if (s21_is_zero(val)) *val = s21_zero();
}

int s21_is_m_equal(s21_decimal *val_1, s21_decimal *val_2) {
  return val_1->bits[2] == val_2->bits[2] && val_1->bits[1] == val_2->bits[1] &&
         val_1->bits[0] == val_2->bits[0];
}
