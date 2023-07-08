#include "common.h"

int s21_dec_log2(s21_decimal *value, s21_decimal *closest_square,
                 s21_decimal init) {
  *closest_square = init;
  int pow = 0;
  for (s21_decimal square = init;
       !s21_dec_s_lshift(&square, 0) && s21_is_m_less_or_equal(&square, value);
       pow++, *closest_square = square)
    ;
  return pow;
}

int s21_dec_lshift(s21_decimal *value, int shift) {
  int out = 0;
  for (; shift && !(out = s21_dec_s_lshift(value, 0)); shift--)
    ;
  return out;
}

int s21_dec_s_lshift(s21_decimal *value, int ign_loss) {
  int out = s21_get_bit(value->bits[2], 31);
  if (ign_loss || !out) {
    char bit1 = s21_get_bit(value->bits[0], 31);
    char bit2 = s21_get_bit(value->bits[1], 31);
    value->bits[0] <<= 1;
    value->bits[1] <<= 1;
    value->bits[2] <<= 1;
    s21_set_bit(value->bits + 1, 0, bit1);
    s21_set_bit(value->bits + 2, 0, bit2);
  }
  return out;
}

void s21_set_sign(s21_decimal *dst, int bit) {
  s21_set_bit(dst->bits + 3, 31, bit);
}

int s21_get_power(s21_decimal *value) {
  int power = value->bits[3] << 1;
  return power >> 17;
}

void s21_set_power(s21_decimal *value, int power) {
  value->bits[3] = (power << 16) | (s21_get_sign(value) << 31);
}

int s21_is_zero(s21_decimal *value) {
  return !(value->bits[0] || value->bits[1] || value->bits[2]);
}

int s21_get_sign(s21_decimal *value) { return s21_get_bit(value->bits[3], 31); }

s21_decimal s21_inverse(s21_decimal *value) {
  s21_decimal result = *value;
  result.bits[0] = ~result.bits[0];
  result.bits[1] = ~result.bits[1];
  result.bits[2] = ~result.bits[2];
  s21_m_add(result, s21_one(), &result);
  return result;
}

int s21_add_with_ovf(int value_1, int value_2, int *result) {
  int high = s21_get_bit(value_1, 31) + s21_get_bit(value_2, 31);
  s21_set_bit(&value_1, 31, 0);
  s21_set_bit(&value_2, 31, 0);
  *result = value_1 + value_2;
  high += s21_get_bit(*result, 31);
  s21_set_bit(result, 31, s21_get_bit(high, 0));
  return s21_get_bit(high, 1);
}

int s21_get_bit(int value, int bit_order) {
  return ((1 << bit_order) & value) && 1;
}

void s21_set_bit(int *value, int bit_order, int is_set) {
  if (is_set) {
    *value |= (1 << bit_order);
  } else {
    *value &= ~(1 << bit_order);
  }
}

void s21_dec_set_bit(s21_decimal *value, int bit_order, int bit) {
  if ((bit_order >= 0) && (bit_order < 32)) {
    s21_set_bit(value->bits, bit_order, bit);
  } else if ((bit_order >= 32) && (bit_order < 32 * 2)) {
    s21_set_bit(value->bits + 1, bit_order - 32, bit);
  } else if ((bit_order >= 32 * 2) && (bit_order < 32 * 3)) {
    s21_set_bit(value->bits + 2, bit_order - 32 * 2, bit);
  }
}

int s21_dec_get_bit(s21_decimal *value, int bit_order) {
  int num_int = bit_order / 32;
  int num_bit = bit_order % 32;
  return (value->bits[num_int] & (1u << num_bit)) >> num_bit;
}

s21_decimal s21_zero() {
  s21_decimal zero = {0};
  return zero;
}

s21_decimal s21_one() {
  s21_decimal one = {0};
  one.bits[0] = 1;
  return one;
}

s21_decimal s21_ten() {
  s21_decimal ten = {0};
  ten.bits[0] = 10;
  return ten;
}

s21_decimal s21_m_pow(s21_decimal value, int pow) {
  s21_decimal result = s21_one();
  while (pow) {
    if (pow % 2) {
      s21_m_mul(result, value, &result);
      pow--;
    } else {
      s21_m_mul(value, value, &value);
      pow /= 2;
    }
  }
  return result;
}

int s21_log(s21_decimal value) {
  int pow = 0;
  s21_decimal del = s21_ten();
  for (; s21_is_m_greater_or_equal(&value, &del);
       pow++, s21_m_div(value, del, &value))
    ;
  return pow;
}

void s21_bank_round(s21_decimal *value, int pow, int cont) {
  if (pow) {
    s21_decimal rem;
    if (pow == 29) {
      pow = 1;
      rem = s21_m_div(*value, s21_m_pow(s21_ten(), 28), value);
      if (!s21_is_zero(&rem)) cont = 1;
      rem = *value;
      *value = s21_zero();
    } else {
      rem = s21_m_div(*value, s21_m_pow(s21_ten(), pow), value);
    }
    if (s21_bank_round_cond(value, rem, pow, cont))
      s21_m_add(*value, s21_one(), value);
  }
}

int s21_bank_round_cond(s21_decimal *high, s21_decimal low, int pow, int cont) {
  int out = 0;
  s21_decimal rem1 = s21_m_div(low, s21_m_pow(s21_ten(), pow - 1), &low);
  if (low.bits[0] > 4) {
    if (low.bits[0] == 5) {
      if (!s21_is_zero(&rem1) || (pow == 1 && cont) ||
          s21_get_bit(high->bits[0], 0))
        out = 1;
    } else {
      out = 1;
    }
  }
  return out;
}

int s21_abs(int x) {
  if (x < 0) x = -x;
  return x;
}

void s21_neg_swap(s21_decimal *val_1, s21_decimal *val_2) {
  if (s21_get_sign(val_1) && s21_get_sign(val_2)) {
    s21_decimal tmp = *val_1;
    *val_1 = *val_2;
    *val_2 = tmp;
  }
}

int s21_comparator(s21_decimal *val_1, s21_decimal *val_2, int is_greater,
                   int (*f_comp)(s21_decimal *, s21_decimal *)) {
  s21_clean_zero(val_1);
  s21_clean_zero(val_2);
  s21_neg_swap(val_1, val_2);
  int s1 = s21_get_sign(val_1);
  int s2 = s21_get_sign(val_2);
  int out;
  if (s1 == s2) {
    s21_decimal *lp, *gp;
    if (s21_normalize(val_1, val_2, &lp, &gp)) {
      if (lp == val_2) {
        out = 1 - is_greater;
      } else {
        out = is_greater;
      }
    } else {
      out = f_comp(val_1, val_2);
    }
  } else {
    if (s1 && !s2) {
      out = 1 - is_greater;
    } else {
      out = is_greater;
    }
  }
  return out;
}

int s21_normalize(s21_decimal *val_1, s21_decimal *val_2, s21_decimal **lp,
                  s21_decimal **gp) {
  int pl = s21_get_power(val_1);
  int pg = s21_get_power(val_2);
  int out = 0;
  *lp = val_1;
  *gp = val_2;
  if (pl != pg) {
    if (pl > pg) {
      pl += pg;
      pg = pl - pg;
      pl -= pg;
      *lp = val_2;
      *gp = val_1;
    }
    int s = s21_get_sign(*lp);
    int dp_avai = 28 - s21_log(**lp);
    int dp = pg - pl;
    out = dp - dp_avai;
    if (out < 0) {
      out = 0;
      s21_m_mul(**lp, s21_m_pow(s21_ten(), dp), *lp);
      s21_set_power(*lp, pg);
    } else {
      s21_decimal tmp;
      if (s21_m_mul(**lp, s21_m_pow(s21_ten(), dp_avai), &tmp)) {
        out++;
        dp_avai--;
        s21_m_mul(**lp, s21_m_pow(s21_ten(), dp_avai), &tmp);
      }
      s21_set_power(&tmp, pl + dp_avai);
      **lp = tmp;
    }
    s21_set_sign(*lp, s);
  }
  return out;
}
