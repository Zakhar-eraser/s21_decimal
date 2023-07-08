#ifndef _SRC_HEADERS_COMMON_COMMON_H_
#define _SRC_HEADERS_COMMON_COMMON_H_

#include <math.h>

#include "s21_decimal.h"

s21_decimal s21_zero();
s21_decimal s21_one();
s21_decimal s21_ten();
int s21_dec_s_lshift(s21_decimal *value, int ign_loss);
int s21_dec_lshift(s21_decimal *value, int shift);
int s21_dec_s_rshift(s21_decimal *value, int ign_loss);
int s21_abs(int x);
int s21_get_bit(int value, int bit_order);
int s21_dec_get_bit(s21_decimal *value, int bit_order);
void s21_set_bit(int *value, int bit_order, int bit);
void s21_dec_set_bit(s21_decimal *value, int bit_order, int bit);
int s21_m_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_m_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_m_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
s21_decimal s21_m_div(s21_decimal value_1, s21_decimal value_2,
                      s21_decimal *result);
s21_decimal s21_inverse(s21_decimal *value);
int s21_get_sign(s21_decimal *value);
void s21_set_sign(s21_decimal *dst, int bit);
int s21_get_power(s21_decimal *value);
void s21_inc_power(s21_decimal *value);
void s21_set_power(s21_decimal *value, int power);
void s21_dec_power(s21_decimal *value);
int s21_is_zero(s21_decimal *value);
int s21_dec_log2(s21_decimal *value, s21_decimal *closest_square,
                 s21_decimal init);
int s21_add_with_ovf(int value_1, int value_2, int *result);
int s21_is_m_equal(s21_decimal *val_1, s21_decimal *val_2);
int s21_is_m_not_equal(s21_decimal *val_1, s21_decimal *val_2);
int s21_is_m_less(s21_decimal *val_1, s21_decimal *val_2);
int s21_is_m_greater(s21_decimal *val_1, s21_decimal *val_2);
int s21_is_m_less_or_equal(s21_decimal *val_1, s21_decimal *val_2);
int s21_is_m_greater_or_equal(s21_decimal *val_1, s21_decimal *val_2);
s21_decimal s21_m_pow(s21_decimal value, int pow);
int s21_log(s21_decimal value);
int s21_bank_round_cond(s21_decimal *high, s21_decimal low, int pow, int cont);
void s21_bank_round(s21_decimal *value, int pow, int cont);
void s21_neg_swap(s21_decimal *val_1, s21_decimal *val_2);
int s21_comparator(s21_decimal *val_1, s21_decimal *val_2, int is_greater,
                   int (*f_comp)(s21_decimal *, s21_decimal *));
int s21_normalize(s21_decimal *val_1, s21_decimal *val_2, s21_decimal **lp,
                  s21_decimal **gp);
void s21_clean_zero(s21_decimal *val);
int s21_common_add(s21_decimal val_1, s21_decimal val_2, s21_decimal *result);

#endif  // _SRC_HEADERS_COMMON_COMMON_H_
