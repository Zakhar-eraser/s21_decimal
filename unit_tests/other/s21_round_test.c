#include "common_test.h"

static long long input_values[] = {1234567845665300009, 234545568, 243443294676,
                                   25, 245};
static int input_power[] = {5, 2, 4, 1, 2};
static int input_signs[] = {1, 0, 1, 0, 0};

static long long output_values[] = {12345678456653, 2345456, 24344329, 3, 2};

START_TEST(s21_round_zero) {
  s21_decimal result;
  s21_round(s21_zero(), &result);
  ck_assert(s21_is_zero(&result));
}
END_TEST

START_TEST(s21_round_zero_with_power) {
  s21_decimal result;
  s21_decimal input = s21_zero();
  s21_set_power(&input, 28);
  s21_round(s21_zero(), &result);
  ck_assert(s21_is_zero(&result));
  ck_assert(!s21_get_power(&result));
}
END_TEST

START_TEST(s21_round_zero_power) {
  s21_decimal input = s21_zero();
  *(long long *)input.bits = 123456784566534364;
  s21_decimal result;
  s21_round(input, &result);
  ck_assert(s21_is_m_equal(&result, &input));
  ck_assert(!s21_get_power(&result));
}
END_TEST

START_TEST(s21_round_default) {
  s21_decimal input = s21_zero(), match = s21_zero();
  *(long long *)input.bits = input_values[_i];
  *(long long *)match.bits = output_values[_i];
  s21_set_power(&input, input_power[_i]);
  s21_set_sign(&input, input_signs[_i]);
  s21_decimal result;
  s21_round(input, &result);
  ck_assert(s21_is_m_equal(&result, &match));
  ck_assert(!s21_get_power(&result));
  ck_assert(s21_get_sign(&result) == input_signs[_i]);
}
END_TEST

Suite *s21_round_suite() {
  Suite *s = suite_create("s21_round");

  TCase *tc = tcase_create("ZERO");
  tcase_add_test(tc, s21_round_zero);
  tcase_add_test(tc, s21_round_zero_with_power);
  suite_add_tcase(s, tc);

  TCase *tc_no_round = tcase_create("NO ROUND");
  tcase_add_test(tc_no_round, s21_round_zero_power);
  suite_add_tcase(s, tc_no_round);

  TCase *tc_default = tcase_create("DEFAULT");
  tcase_add_loop_test(tc_default, s21_round_default, 0, LENGTH(input_values));
  suite_add_tcase(s, tc_default);

  return s;
}