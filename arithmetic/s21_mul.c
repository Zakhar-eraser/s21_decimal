#include "common.h"

int s21_m_mul(s21_decimal, s21_decimal, s21_decimal *);
void s21_product_parts(s21_decimal *, s21_decimal *, s21_decimal *,
                       s21_decimal *, s21_decimal *, s21_decimal *,
                       s21_decimal *);
int s21_sum_parts(s21_decimal, s21_decimal, s21_decimal, s21_decimal,
                  s21_decimal, int, s21_decimal *);
int s21_part_to_term(s21_decimal *, int, int, int);

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int out = 0;
  *result = s21_zero();
  if (!((s21_is_zero(&value_1) || s21_is_zero(&value_2)))) {
    int res_sign = s21_get_sign(&value_1) ^ s21_get_sign(&value_2);
    int mdpow = s21_log(value_1) + s21_log(value_2) - 28;
    if (mdpow < 0) mdpow = 0;
    int spows = s21_get_power(&value_1) + s21_get_power(&value_2);
    int pow = spows - mdpow;
    int dpow = pow - 28;
    if (dpow < 0) dpow = 0;
    int shrink_pow = dpow + mdpow;
    s21_decimal p1, p2, p3, p4, p5;
    s21_product_parts(&value_1, &value_2, &p1, &p2, &p3, &p4, &p5);
    if (s21_sum_parts(p1, p2, p3, p4, p5, shrink_pow, result)) {
      pow--;
      shrink_pow++;
      s21_sum_parts(p1, p2, p3, p4, p5, shrink_pow, result);
    }
    s21_set_sign(result, res_sign);
    pow -= dpow;
    s21_set_power(result, pow);
    if (pow < 0) {
      if (res_sign) {
        out = 2;
      } else {
        out = 1;
      }
    }
  }
  return out;
}

void s21_product_parts(s21_decimal *value_1, s21_decimal *value_2,
                       s21_decimal *p1, s21_decimal *p2, s21_decimal *p3,
                       s21_decimal *p4, s21_decimal *p5) {
  s21_decimal h_del = s21_m_pow(s21_ten(), 20);
  s21_decimal m_del = s21_m_pow(s21_ten(), 10);
  s21_decimal a, d;
  s21_decimal b = s21_m_div(*value_1, h_del, &a);
  s21_decimal c = s21_m_div(b, m_del, &b);
  s21_decimal e = s21_m_div(*value_2, h_del, &d);
  s21_decimal f = s21_m_div(e, m_del, &e);
  s21_m_mul(a, d, p1);

  s21_m_mul(a, e, p2);
  s21_m_mul(b, d, p5);
  s21_m_add(*p2, *p5, p2);

  s21_m_mul(b, e, p3);
  s21_m_mul(c, d, p5);
  s21_m_add(*p3, *p5, p3);
  s21_m_mul(a, f, p5);
  s21_m_add(*p3, *p5, p3);

  s21_m_mul(b, f, p4);
  s21_m_mul(c, e, p5);
  s21_m_add(*p4, *p5, p4);

  s21_m_mul(c, f, p5);
}

int s21_sum_parts(s21_decimal p1, s21_decimal p2, s21_decimal p3,
                  s21_decimal p4, s21_decimal p5, int dpow, s21_decimal *res) {
  return s21_part_to_term(&p5, 0, dpow, 0) ||
         s21_part_to_term(&p4, 10, dpow, !s21_is_zero(&p5)) ||
         s21_part_to_term(&p3, 20, dpow, !s21_is_zero(&p4)) ||
         s21_part_to_term(&p2, 30, dpow, !s21_is_zero(&p3)) ||
         s21_part_to_term(&p1, 40, dpow, !s21_is_zero(&p2)) ||
         s21_m_add(p1, p2, res) || s21_m_add(*res, p3, res) ||
         s21_m_add(*res, p4, res) || s21_m_add(*res, p5, res);
}

int s21_part_to_term(s21_decimal *value, int pow, int dpow, int cont) {
  int out = 0;
  int rpow = s21_abs(dpow - pow);
  if (!s21_is_zero(value)) {
    if (dpow > pow) {
      if (rpow < 22) {
        s21_bank_round(value, rpow, cont);
      } else {
        *value = s21_zero();
      }
    } else if (rpow > 20) {
      out = 1;
    } else {
      out = s21_m_mul(*value, s21_m_pow(s21_ten(), rpow), value);
    }
  }
  return out;
}

int s21_m_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int out = 0;
  s21_decimal square = s21_zero(), result_tmp = s21_zero();
  for (; !(out || s21_is_zero(&value_2));
       s21_m_sub(value_2, square, &value_2)) {
    int pow = s21_dec_log2(&value_2, &square, s21_one());
    s21_decimal member = value_1;
    out = s21_dec_lshift(&member, pow) ||
          s21_m_add(result_tmp, member, &result_tmp);
  }
  *result = result_tmp;
  return out;
}
