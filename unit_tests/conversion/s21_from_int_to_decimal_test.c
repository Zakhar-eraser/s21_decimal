#include "common_test.h"

static int pos_args[] = {0, -0, 12909, INT32_MAX};
static int neg_args[] = {-328976, INT32_MIN};

START_TEST(s21_from_int_to_decimal_pos) {
  s21_decimal val;
  ck_assert(!s21_from_int_to_decimal(pos_args[_i], &val));
  ck_assert(val.bits[0] == pos_args[_i]);
  ck_assert(!s21_get_sign(&val));
}
END_TEST

START_TEST(s21_from_int_to_decimal_neg) {
  s21_decimal val;
  ck_assert(!s21_from_int_to_decimal(neg_args[_i], &val));
  ck_assert(val.bits[0] == -neg_args[_i]);
  ck_assert(s21_get_sign(&val));
}
END_TEST

Suite *s21_from_int_to_decimal_suite() {
  Suite *s = suite_create("s21_from_int_to_decimal");

  TCase *tc = tcase_create("DEFAULT");
  tcase_add_loop_test(tc, s21_from_int_to_decimal_pos, 0, LENGTH(pos_args));
  tcase_add_loop_test(tc, s21_from_int_to_decimal_neg, 0, LENGTH(neg_args));
  suite_add_tcase(s, tc);

  return s;
}
