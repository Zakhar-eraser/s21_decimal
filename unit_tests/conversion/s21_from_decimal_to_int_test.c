#include "common_test.h"

static int t_default_vals[][3] = {
    {0},
    {0},
    {0},
    {0},
    {0x7FFFFFFF},
    {0x80000000},
    {123452345},
    {123452345},
    {268435455, 1042612833, 542101086},     // 0.9999999999999999999999999999
    {-1, 1156841471, 1164153218},           // 2147483647.9999999999999999999
    {-1981284353, -809819388, 1164153218},  // 2147483648.9999999999999999999
    {1}};
static int t_default_pows[] = {0, 28, 0, 28, 0, 0, 0, 0, 28, 19, 19, 0};
static int t_default_signs[] = {0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1};
static int t_default_res[] = {0,          0,          0,          0,
                              0x7FFFFFFF, 0x80000000, 123452345,  -123452345,
                              0,          0x7FFFFFFF, 0x80000000, 0xFFFFFFFF};

static int t_err_vals[][3] = {{0x80000000}, {0x80000001}, {-1, -1, -1}};
static int t_err_pows[] = {0, 0, 19};
static int t_err_signs[] = {0, 1, 1};

START_TEST(s21_from_decimal_to_int_default) {
  s21_decimal val = s21_ints_to_decimal(t_default_vals[_i], t_default_pows[_i],
                                        t_default_signs[_i]);
  int result;
  ck_assert(!s21_from_decimal_to_int(val, &result));
  ck_assert(result == t_default_res[_i]);
}
END_TEST

START_TEST(s21_from_decimal_to_int_err) {
  s21_decimal val =
      s21_ints_to_decimal(t_err_vals[_i], t_err_pows[_i], t_err_signs[_i]);
  int result;
  ck_assert(s21_from_decimal_to_int(val, &result));
}
END_TEST

Suite *s21_from_decimal_to_int_suite() {
  Suite *s = suite_create("s21_from_decimal_to_int");

  TCase *tc_default = tcase_create("DEFAULT");
  tcase_add_loop_test(tc_default, s21_from_decimal_to_int_default, 0,
                      LENGTH(t_default_pows));
  suite_add_tcase(s, tc_default);

  TCase *tc_err = tcase_create("ERROR");
  tcase_add_loop_test(tc_err, s21_from_decimal_to_int_err, 0,
                      LENGTH(t_err_pows));
  suite_add_tcase(s, tc_err);

  return s;
}