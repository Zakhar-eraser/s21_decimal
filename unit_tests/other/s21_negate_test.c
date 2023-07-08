#include "common_test.h"

static int t_v[][3] = {
    {0, 0, 0}, {-1, -1, -1}, {1073741824, -24903193, 433680868}};
static int t_p[] = {14, 0, 0};

START_TEST(tdefault) {
  s21_decimal val = s21_ints_to_decimal(t_v[_i], t_p[_i], 0);
  s21_decimal result;
  for (int i = 0; i < 2; i++) {
    s21_set_sign(&val, i);
    ck_assert(!s21_negate(val, &result));
    ck_assert(s21_is_m_equal(&val, &result));
    ck_assert(s21_get_power(&val) == s21_get_power(&result));
    ck_assert(s21_get_sign(&result) != i);
  }
}
END_TEST

Suite *s21_negate_suite() {
  Suite *s = suite_create("s21_negate");

  TCase *tc_def = tcase_create("DEFAULT");
  tcase_add_loop_test(tc_def, tdefault, 0, LENGTH(t_p));
  suite_add_tcase(s, tc_def);

  return s;
}