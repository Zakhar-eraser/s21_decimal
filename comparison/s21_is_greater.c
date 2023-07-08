#include "common.h"

int s21_is_greater(s21_decimal val_1, s21_decimal val_2) {
  return s21_comparator(&val_1, &val_2, 1, s21_is_m_greater);
}

int s21_is_m_greater(s21_decimal *val_1, s21_decimal *val_2) {
  return !(s21_is_m_equal(val_1, val_2) || s21_is_m_less(val_1, val_2));
}
