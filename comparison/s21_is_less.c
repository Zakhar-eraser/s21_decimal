#include "common.h"

int s21_is_less(s21_decimal val_1, s21_decimal val_2) {
  return s21_comparator(&val_1, &val_2, 0, s21_is_m_less);
}

int s21_is_m_less(s21_decimal *val_1, s21_decimal *val_2) {
  int ne_idx = 2;
  for (; ne_idx > 0 && val_1->bits[ne_idx] == val_2->bits[ne_idx]; ne_idx--)
    ;
  return (unsigned int)(val_1->bits[ne_idx]) <
         (unsigned int)(val_2->bits[ne_idx]);
}
