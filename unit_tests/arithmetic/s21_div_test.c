#include "common_test.h"

static int t_zero_1_values[][3] = {
    {0}, {1, 0, 0}, {8, 0, 0}, {5, 0, 0}, {50000, 0, 0}, {1, 0, 0}, {2, 0, 0}};
static int t_zero_1_powers[] = {0, 0, 1, 28, 5, 28, 28};

static int t_zero_2_values[][3] = {
    {6, 0, 0},
    {-1, -1, -1},
    {1073741824, -124515964, -2126562952},  // 4E28
    {10, 0, 0},
    {268435456, 1042612833, 542101086},  // 1E28
    {3, 0, 0},
    {30, 0, 0}};
static int t_zero_2_powers[] = {0, 0, 0, 0, 0, 0, 0};

static int t_default_1_values[][3] = {
    {55356, 0, 0},
    {55356, 0, 0},
    {55346, 0, 0},
    {45346, 0, 0},
    {8, 0, 0},
    {1, 0, 0},
    {2, 0, 0},
    {3, 0, 0},
    {-1, -1, -1},
    {1751957861, -914647108, -580881030},  // 68512798831099901989224235365
    {25, 0, 0},
    {8, 0, 0},
    {2, 0, 0},
    {5, 0, 0},
    {16, 0, 0},
    {14, 0, 0},
    {-1, -1, -1},
    {50, 0, 0},
    {5, 0, 0},
    {-805306366, 1067516025, 108420217}};
static int t_default_1_powers[] = {4, 3, 1,  4, 3, 0, 0, 0, 0, 0,
                                   0, 0, 28, 0, 0, 0, 0, 0, 0, 28};

static int t_default_2_values[][3] = {
    {268435456, 1042612833, 542101086},     // 1E28
    {268435456, 1042612833, 542101086},     // 1E28
    {268435456, 1042612833, 542101086},     // 1E28
    {268435456, 1042612833, 542101086},     // 1E28
    {1073741824, -124515964, -2126562952},  // 4E28
    {3, 0, 0},
    {3, 0, 0},
    {7, 0, 0},
    {-1, -1, -1},
    {94310055, 0, 0},
    {500, 0, 0},
    {1073741824, -124515964, -2126562952},  // 4E28
    {3, 0, 0},
    {1, 0, 0},
    {2, 0, 0},
    {2, 0, 0},
    {268435456, 1042612833, 542101086},  // 1E28
    {11, 0, 0},
    {11, 0, 0},
    {4, 0, 0}};
static int t_default_2_powers[] = {0, 0,  0, 0, 3,  0,  0,  0, 0, 0,
                                   0, 14, 0, 4, 27, 28, 28, 0, 0, 0};

static int t_default_res_values[][3] = {
    {6, 0, 0},
    {55, 0, 0},
    {5535, 0, 0},
    {5, 0, 0},
    {2, 0, 0},
    {89478485, 347537611, 180700362},      // (3)
    {178956971, 695075222, 361400724},     // (6)
    {-1112089746, -166732686, 232329036},  // 3/7
    {1, 0, 0},
    {-1244373741, 1639205659, 39},
    {5, 0, 0},
    {2, 0, 0},
    {1, 0, 0},
    {50000, 0, 0},
    {1073741824, -24903193, 433680868},     // 8E27
    {1879048192, -1291644761, -500259693},  // 7E28
    {-1, -1, -1},
    {48806447, -1898527489, -1830871450},
    {1293370833, -1478342938, 246409584},
    {5, 0, 0}};
static int t_default_res_powers[] = {28, 28, 28, 28, 28, 28, 28, 28, 0,  0,
                                     2,  14, 28, 0,  0,  0,  0,  28, 28, 2};

static int t_err_1_values[][3] = {
    {-1, -1, -1},
    {16, 0, 0},
    {0},
    {-1, -1, -1},
    {1211279220, 806217, 0}  // 3462676859758452
};
static int t_err_1_powers[] = {28, 0, 0, 0, 0};

static int t_err_2_values[][3] = {{0},
                                  {2, 0, 0},
                                  {0},
                                  {268435455, 1042612833, 542101086},  // (9)E27
                                  {2, 0, 0}};
static int t_err_2_powers[] = {5, 28, 28, 28, 14};

START_TEST(s21_div_zero) {
  s21_decimal value1 =
      s21_ints_to_decimal(t_zero_1_values[_i], t_zero_1_powers[_i], 0);
  s21_decimal value2 =
      s21_ints_to_decimal(t_zero_2_values[_i], t_zero_2_powers[_i], 0);
  s21_decimal result;
  ck_assert(!s21_div(value1, value2, &result));
  ck_assert(s21_is_zero(&result));
}
END_TEST

START_TEST(s21_div_default) {
  s21_decimal value1 =
      s21_ints_to_decimal(t_default_1_values[_i], t_default_1_powers[_i], 0);
  s21_decimal value2 =
      s21_ints_to_decimal(t_default_2_values[_i], t_default_2_powers[_i], 0);
  s21_decimal tresult = s21_ints_to_decimal((int *)t_default_res_values[_i],
                                            t_default_res_powers[_i], 0);
  for (int i = 0; i < 2; i++) {
    s21_set_sign(&value1, i);
    int rs = (i + 1) % 2;
    s21_set_sign(&value2, rs);
    rs ^= i;
    s21_decimal result;
    ck_assert(!s21_div(value1, value2, &result));
    ck_assert(s21_is_m_equal(&result, &tresult));
    ck_assert(s21_get_power(&result) == s21_get_power(&tresult));
    ck_assert(s21_get_sign(&result) == rs);
  }
}
END_TEST

START_TEST(s21_div_err) {
  s21_decimal value1 =
      s21_ints_to_decimal(t_err_1_values[_i], t_err_1_powers[_i], 0);
  s21_decimal value2 =
      s21_ints_to_decimal(t_err_2_values[_i], t_err_2_powers[_i], 0);
  for (int i = 0; i < 4; i++) {
    int s1 = s21_get_bit(i, 0);
    int s2 = s21_get_bit(i, 1);
    s21_set_sign(&value1, s1);
    s21_set_sign(&value2, s2);
    int rs = s1 ^ s2;
    s21_decimal result;
    int out;
    ck_assert((out = s21_div(value1, value2, &result)));
    if (s21_is_zero(&value2)) {
      ck_assert(out == 3);
    } else if (rs) {
      ck_assert(out == 2);
    } else {
      ck_assert(out == 1);
    }
  }
}
END_TEST

Suite *s21_div_suite() {
  Suite *s = suite_create("s21_div");

  TCase *tc_zero = tcase_create("ZERO");
  tcase_add_loop_test(tc_zero, s21_div_zero, 0, LENGTH(t_zero_1_powers));
  suite_add_tcase(s, tc_zero);

  TCase *tc_default = tcase_create("DEFAULT");
  tcase_add_loop_test(tc_default, s21_div_default, 0,
                      LENGTH(t_default_1_powers) - 1);
  suite_add_tcase(s, tc_default);

  TCase *tc_error = tcase_create("ERROR");
  tcase_add_loop_test(tc_error, s21_div_err, 0, LENGTH(t_err_1_powers));
  suite_add_tcase(s, tc_error);

  return s;
}