#include "common.h"

int s21_is_less_or_equal(s21_decimal val_1, s21_decimal val_2) {
  return s21_comparator(&val_1, &val_2, 0, s21_is_m_less_or_equal);
}

int s21_is_m_less_or_equal(s21_decimal *val_1, s21_decimal *val_2) {
  return s21_is_m_equal(val_1, val_2) || s21_is_m_less(val_1, val_2);
}
