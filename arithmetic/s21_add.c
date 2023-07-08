#include "common.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  return s21_common_add(value_1, value_2, result);
}

int s21_common_add(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result) {
  s21_decimal *lp, *gp;
  int s1 = s21_get_sign(&value_1), s2 = s21_get_sign(&value_2);
  int dp = s21_normalize(&value_1, &value_2, &lp, &gp);
  int rs, p = s21_get_power(lp);
  s21_decimal divider = s21_m_pow(s21_ten(), dp);
  s21_decimal high2, rem = s21_m_div(*gp, divider, &high2);
  if (s1 == s2) {
    rs = s1;
    if (s21_m_add(*lp, high2, result)) {
      p--;
      dp++;
      s21_decimal high1, low1 = s21_m_div(*lp, s21_ten(), &high1);
      s21_decimal low2 = s21_m_div(high2, s21_ten(), &high2);
      s21_m_add(high1, high2, result);
      s21_m_add(low1, low2, &rem);
      rem = s21_m_div(rem, s21_ten(), &high2);
      s21_m_add(*result, high2, result);
    }
  } else if (dp) {
    rs = s21_get_sign(lp);
    s21_m_sub(*lp, s21_one(), lp);
    s21_m_sub(*lp, high2, result);
    s21_m_sub(divider, rem, &rem);
  } else if (s21_is_m_less(&value_1, &value_2)) {
    s21_m_sub(value_2, value_1, result);
    rs = s2;
  } else {
    s21_m_sub(value_1, value_2, result);
    rs = s1;
  }
  int out = 0;
  if (dp) {
    s21_decimal tmp;
    high2 = s21_m_div(*result, s21_ten(), &tmp);
    if (s21_bank_round_cond(&high2, rem, dp, 0))
      out = s21_m_add(*result, s21_one(), result);
  }
  if (out || p < 0) {
    if (rs) {
      out = 2;
    } else {
      out = 1;
    }
  } else {
    s21_set_power(result, p);
    s21_set_sign(result, rs);
  }
  return out;
}

int s21_m_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  result->bits[3] = 0;
  int rem1 = s21_add_with_ovf(value_1.bits[0], value_2.bits[0], result->bits);
  int rem2 =
      s21_add_with_ovf(value_1.bits[1], value_2.bits[1], result->bits + 1) +
      s21_add_with_ovf(result->bits[1], rem1, result->bits + 1);
  int rem3 =
      s21_add_with_ovf(value_1.bits[2], value_2.bits[2], result->bits + 2) +
      s21_add_with_ovf(result->bits[2], rem2, result->bits + 2);
  return rem3 != 0;
}