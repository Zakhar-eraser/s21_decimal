#include "common_test.h"

static int t_pos_v[][3] = {
    {1, 0, 0},
    {0, 0, 0},
    {1879048191, -1291644761, -500259693},  // 69999999999.999999999999999999
    {-1, -1, -1}};
static int t_pos_p[] = {28, 22, 18, 0};
static int t_pos_r[][3] = {{0, 0, 0},
                           {0, 0, 0},
                           {1280523263, 16, 0},  // 69999999999
                           {-1, -1, -1}};

START_TEST(pos) {
  s21_decimal value = s21_ints_to_decimal(t_pos_v[_i], t_pos_p[_i], 0);
  s21_decimal tresult = s21_ints_to_decimal(t_pos_r[_i], 0, 0);
  s21_decimal result;
  ck_assert(!s21_truncate(value, &result));
  ck_assert(s21_is_m_equal(&result, &tresult));
  ck_assert(!s21_get_power(&result));
  ck_assert(!s21_get_sign(&result));
}
END_TEST

START_TEST(neg) {
  s21_decimal value = s21_ints_to_decimal(t_pos_v[_i], t_pos_p[_i], 1);
  s21_decimal tresult = s21_ints_to_decimal(t_pos_r[_i], 0, 1);
  s21_decimal result;
  ck_assert(!s21_truncate(value, &result));
  ck_assert(s21_is_m_equal(&result, &tresult));
  ck_assert(!s21_get_power(&result));
  ck_assert(s21_get_sign(&result));
}
END_TEST

Suite *s21_truncate_suite() {
  Suite *s = suite_create("s21_truncate");

  TCase *tc_pos = tcase_create("POS");
  tcase_add_loop_test(tc_pos, pos, 0, LENGTH(t_pos_p));
  suite_add_tcase(s, tc_pos);

  TCase *tc_neg = tcase_create("NEG");
  tcase_add_loop_test(tc_neg, neg, 0, LENGTH(t_pos_p));
  suite_add_tcase(s, tc_neg);

  return s;
}