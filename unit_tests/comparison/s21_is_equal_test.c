#include "common_test.h"

static int t_false_1_val[][3] = {
    {-1, -1, -1}, {1}, {-1986853888, -1569605072, 718}, {1}};
static int t_false_1_pow[] = {0, 0, 8, 14};

static int t_false_2_val[][3] = {{-1, -1, -1},
                                 {268435456, 1042612833, 542101086},
                                 {-2016870400, -683204809, 718634547},
                                 {1}};
static int t_false_2_pow[] = {0, 28, 14, 14};

static int t_true_1_ne_s_v[][3] = {{1}, {-1986853888, -1569605072, 718}};
static int t_true_1_ne_s_p[] = {4, 8};

static int t_true_2_ne_s_v[][3] = {{1}, {-2016870400, -683204809, 718634547}};
static int t_true_2_ne_s_p[] = {4, 14};

static int t_true_1_ne_p_v[][3] = {{1253261375, -278597179, -1408087420}, {1}};
static int t_true_1_ne_p_p[] = {15, 1};

static int t_true_2_ne_p_v[][3] = {{1253261375, -278597179, -1408087420},
                                   {268435456, 1042612833, 542101086}};
static int t_true_2_ne_p_p[] = {14, 28};

static int t_true_1_ne_o_v[][3] = {
    {10}, {-1, -1, -1}, {4, 4, 4}, {-134217728, -571112803, 596311194}};
static int t_true_1_ne_o_p[] = {0, 0, 15, 28};
static int t_true_1_ne_o_s[] = {0, 0, 0, 1};

static int t_true_2_ne_o_v[][3] = {
    {268435456, 1042612833, 542101086}, {-1, -1, -2}, {2, 2, 2}, {1}};
static int t_true_2_ne_o_p[] = {28, 0, 1, 0};
static int t_true_2_ne_o_s[] = {0, 0, 1, 1};

START_TEST(s21_is_equal_eq) {
  s21_decimal vals[2] = {
      s21_ints_to_decimal(t_false_1_val[_i], t_false_1_pow[_i], 0),
      s21_ints_to_decimal(t_false_2_val[_i], t_false_2_pow[_i], 0)};
  for (int j = 0; j < 2; j++) {
    for (int i = 0; i < 2; i++) {
      s21_set_sign(vals, i);
      s21_set_sign(vals + 1, i);
      ck_assert(s21_is_equal(vals[j], vals[(j + 1) % 2]));
    }
  }
}
END_TEST

START_TEST(s21_is_equal_zeros) {
  s21_decimal val1 = s21_zero();
  s21_decimal val2 = s21_zero();
  for (int i = 0; i < 4; i++) {
    s21_set_sign(&val1, s21_get_bit(i, 0));
    s21_set_sign(&val2, s21_get_bit(i, 1));
    for (int j = 0; j < 29; j++) {
      s21_set_power(&val1, j);
      s21_set_power(&val2, 28 - j);
      ck_assert(s21_is_equal(val1, val2));
    }
  }
}
END_TEST

START_TEST(s21_is_equal_ne_s) {
  s21_decimal vals[2] = {
      s21_ints_to_decimal(t_true_1_ne_s_v[_i], t_true_1_ne_s_p[_i], 0),
      s21_ints_to_decimal(t_true_2_ne_s_v[_i], t_true_2_ne_s_p[_i], 0)};
  for (int j = 0; j < 2; j++) {
    for (int i = 0; i < 2; i++) {
      s21_set_sign(vals, i);
      s21_set_sign(vals + 1, (i + 1) % 2);
      ck_assert(!s21_is_equal(vals[j], vals[(j + 1) % 2]));
    }
  }
}
END_TEST

START_TEST(s21_is_equal_ne_p) {
  s21_decimal vals[2] = {
      s21_ints_to_decimal(t_true_1_ne_p_v[_i], t_true_1_ne_p_p[_i], 0),
      s21_ints_to_decimal(t_true_2_ne_p_v[_i], t_true_2_ne_p_p[_i], 0)};
  for (int j = 0; j < 2; j++) {
    for (int i = 0; i < 2; i++) {
      s21_set_sign(vals, i);
      s21_set_sign(vals + 1, i);
      ck_assert(!s21_is_equal(vals[j], vals[(j + 1) % 2]));
    }
  }
}
END_TEST

START_TEST(s21_is_equal_ne_zero) {
  s21_decimal val1 = s21_zero();
  s21_set_power(&val1, 28);
  s21_set_sign(&val1, 1);
  s21_decimal val2 = s21_one();
  s21_set_power(&val2, 28);
  s21_set_sign(&val2, 1);
  ck_assert(!s21_is_equal(val1, val2));
  ck_assert(!s21_is_equal(val2, val1));
}
END_TEST

START_TEST(s21_is_equal_ne_o) {
  s21_decimal val1 = s21_ints_to_decimal(
      t_true_1_ne_o_v[_i], t_true_1_ne_o_p[_i], t_true_1_ne_o_s[_i]);
  s21_decimal val2 = s21_ints_to_decimal(
      t_true_2_ne_o_v[_i], t_true_2_ne_o_p[_i], t_true_2_ne_o_s[_i]);
  ck_assert(!s21_is_equal(val1, val2));
  ck_assert(!s21_is_equal(val2, val1));
}
END_TEST

Suite *s21_is_equal_suite() {
  Suite *s = suite_create("s21_is_equal");

  TCase *tc_true = tcase_create("TRUE");
  tcase_add_loop_test(tc_true, s21_is_equal_eq, 0, LENGTH(t_false_1_pow));
  tcase_add_test(tc_true, s21_is_equal_zeros);
  suite_add_tcase(s, tc_true);

  TCase *tc_false = tcase_create("FALSE");
  tcase_add_loop_test(tc_false, s21_is_equal_ne_s, 0, LENGTH(t_true_1_ne_s_p));
  tcase_add_loop_test(tc_false, s21_is_equal_ne_p, 0, LENGTH(t_true_1_ne_p_p));
  tcase_add_test(tc_false, s21_is_equal_ne_zero);
  tcase_add_loop_test(tc_false, s21_is_equal_ne_o, 0, LENGTH(t_true_1_ne_o_p));
  suite_add_tcase(s, tc_false);

  return s;
}