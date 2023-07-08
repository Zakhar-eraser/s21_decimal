#include "common.h"

s21_decimal s21_m_div(s21_decimal, s21_decimal, s21_decimal *);
int s21_scale(s21_decimal *, s21_decimal *, s21_decimal *, int *);
static void s21_div_round(s21_decimal *result, s21_decimal rem,
                          s21_decimal *value_2, int rs, int rp, int *out);
static void s21_shrink_value(s21_decimal *value_1, s21_decimal *value_2,
                             s21_decimal *result, int *ddpow);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  *result = s21_zero();
  int out = 0;
  if (s21_is_zero(&value_2)) {
    out = 3;
  } else {
    int rs = s21_get_sign(&value_1) ^ s21_get_sign(&value_2);
    s21_decimal rem = value_1;
    int dpow = 0;
    int rp = s21_get_power(&value_1) - s21_get_power(&value_2);
    for (s21_decimal step_res = s21_zero();
         !(s21_is_zero(&rem) || s21_scale(&rem, &value_2, result, &dpow));
         s21_m_add(*result, step_res, result)) {
      rem = s21_m_div(rem, value_2, &step_res);
    }
    rp += dpow;
    s21_div_round(result, rem, &value_2, rs, rp, &out);
  }
  return out;
}

static void s21_div_round(s21_decimal *result, s21_decimal rem,
                          s21_decimal *value_2, int rs, int rp, int *out) {
  if (rp < 0) {
    if (s21_m_mul(*result, s21_m_pow(s21_ten(), -rp), result)) {
      if (rs) {
        *out = 2;
      } else {
        *out = 1;
      }
    } else {
      s21_set_power(result, 0);
    }
  } else if (rp > 28) {
    int shr_pow = rp - 28;
    if (shr_pow == 1) {
      s21_bank_round(result, 1, !s21_is_zero(&rem));
    } else if (shr_pow < 30) {
      s21_bank_round(result, shr_pow, 0);
    } else {
      *result = s21_zero();
    }
    s21_set_power(result, 28);
  } else if (rp == 28) {
    s21_decimal out_m;
    rem = s21_m_div(rem, *value_2, &out_m);
    s21_bank_round(&out_m, s21_log(out_m) + 1, !s21_is_zero(&rem));
    s21_m_add(*result, out_m, result);
    s21_set_power(result, 28);
  } else {
    s21_set_power(result, rp);
  }
  s21_set_sign(result, rs);
}

int s21_scale(s21_decimal *value_1, s21_decimal *value_2, s21_decimal *res,
              int *dpow) {
  int out = 0;
  s21_decimal result;
  int ddpow = s21_log(*value_2) - s21_log(*value_1);
  if (!ddpow) ddpow = 1;
  if (s21_is_m_less(value_1, value_2)) {
    if (s21_m_mul(*value_1, s21_m_pow(s21_ten(), ddpow), &result)) {
      s21_m_mul(*value_1, s21_m_pow(s21_ten(), ddpow - 1), value_1);
      s21_bank_round(value_2, 1, 1);
    } else {
      *value_1 = result;
      s21_shrink_value(value_1, value_2, &result, &ddpow);
    }
    if (s21_m_mul(*res, s21_m_pow(s21_ten(), ddpow), &result)) {
      out = 1;
    } else {
      *dpow += ddpow;
      *res = result;
    }
  }
  return out;
}

static void s21_shrink_value(s21_decimal *value_1, s21_decimal *value_2,
                             s21_decimal *result, int *ddpow) {
  if (s21_is_m_less(value_1, value_2)) {
    if (s21_m_mul(*result, s21_ten(), result)) {
      s21_bank_round(value_2, 1, 1);
    } else {
      *value_1 = *result;
    }
    (*ddpow)++;
  }
}

s21_decimal s21_m_div(s21_decimal value_1, s21_decimal value_2,
                      s21_decimal *result) {
  s21_decimal square = s21_zero();
  for (*result = s21_zero(); s21_is_m_greater_or_equal(&value_1, &value_2);
       s21_m_sub(value_1, square, &value_1)) {
    int pow = s21_dec_log2(&value_1, &square, value_2);
    s21_decimal tmp = s21_zero();
    s21_dec_set_bit(&tmp, pow, 1);
    s21_m_add(*result, tmp, result);
  }
  return value_1;
}
