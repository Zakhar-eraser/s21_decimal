#include "common_test.h"

static long long t_zero_args1_values[] = {0, 10, 0, 1, 10000000000000, 1};
static int t_zero_args1_powers[] = {0, 0, 0, 28, 28, 28};
static long long t_zero_args2_values[] = {10, 0, 0, 5, 100000000000000, 1};
static int t_zero_args2_powers[] = {0, 0, 0, 1, 28, 28};

static int t_default_args1_values[][3] = {
    {0, 0, -2147483648},  //                      0
    {15, 0, 0},           //                               1
    {25, 0, 0},           //                               2
    {24, 0, 0},           //                               3
    {26, 0, 0},           //                               4
    {-1, -1, -1},         //                             5   79E27
    {1073741824, -124515964, -2126562952},  //    6   4E28
    {1073741824, -124515964, -2126562952},  //    7   4E28
    {1342177280, 918096869, -1584461865},   //     8   5E28
    {805306368, -1167128797, 1626303258},   //     9   3E28
    {1073741824, -124515964, -2126562952},  //   10   4E28
    {-1, -1, -1},   //                            11   79E27
    {-1, -1, -1}};  //                           12   79E27
//                                     0  1   2   3   4   5  6   7   8   9   10
//                                     11  12
static int t_default_args1_powers[] = {0,  28, 28, 28, 28, 0, 14,
                                       14, 14, 14, 14, 28, 15};

static int t_default_args2_values[][3] = {
    {5, 0, 0},                              //                                0
    {1, 0, 0},                              //                                1
    {1, 0, 0},                              //                                2
    {1, 0, 0},                              //                                3
    {1, 0, 0},                              //                                4
    {268435456, 1042612833, 542101086},     //       5  1E28
    {1073741824, -124515964, -2126562952},  //    6  4E28
    {536870926, 2085225666, 1084202172},    //      7  2E28 + 14
    {536870917, 2085225666, 1084202172},    //      8  2E28 + 5
    {1073741824, -124515964, -2126562952},  //    9  4E28 + 5
    {805306371, -1167128797, 1626303258},   //     10  3E28 + 3
    {-1, -1, -1},   //                             11  79E27
    {-1, -1, -1}};  //                            12  79E27
//                                     0  1  2  3  4  5   6   7   8   9   10  11
//                                     12
static int t_default_args2_powers[] = {1,  1,  1,  1,  1,  28, 15,
                                       15, 15, 15, 15, 28, 14};

static int t_default_res_values[][3] = {
    {0, 0, 1073741824},  //                       0
    {2, 0, 0},           //                                1
    {2, 0, 0},           //                                2
    {2, 0, 0},           //                                3
    {3, 0, 0},           //                                4
    {-1, -1, -1},        //                             5  79E27
    {-2147483648, -49806386, 867361737},  //      6  16E27
    {1073741830, -24903193, 433680868},   //       7  8E27 + 6
    {268435458, 1042612833, 542101086},   //       8  10E27 + 2
    {-536870912, 2110128858, 650521303},  //      9  12E27 + 2
    {-536870911, 2110128858, 650521303},  //      10  12E27 + 1
    {158262358, 899300158, -892143627},   //       11  67.77
    {158262358, 899300158, -892143627}};  //      12  67E27
//                                   0  1   2   3   4   5  6  7  8  9  10 11  0
static int t_default_res_powers[] = {0, 28, 28, 28, 28, 0, 0,
                                     0, 0,  0,  0,  27, 0};

static int t_err_args1_values[][3] = {
    {1105788928, 93132, 0},              //              0   4E14
    {268435456, 1042612833, 542101086},  // 1   1E28
    {-1, -1, -1}};
//                               0
static int t_err_args1_pows[] = {0, 0};
static int t_err_args2_values[][3] = {
    {552894464, 46566, 0},  //               0   2E14
    {100000000, 0, 0},      //                  1   1E8
    {-1, -1, -1}};
//                               0  1
static int t_err_args2_pows[] = {0, 7};

START_TEST(s21_mul_zero) {
  s21_decimal value1 =
      s21_long_to_decimal(t_zero_args1_values[_i], t_zero_args1_powers[_i], 0);
  s21_decimal value2 =
      s21_long_to_decimal(t_zero_args2_values[_i], t_zero_args2_powers[_i], 0);
  s21_decimal result;
  ck_assert(!s21_mul(value1, value2, &result));
  ck_assert(s21_is_zero(&result));
}
END_TEST

START_TEST(s21_mul_default) {
  int *val_args[2] = {(int *)t_default_args1_values,
                      (int *)t_default_args2_values};
  int *pow_args[2] = {(int *)t_default_args1_powers,
                      (int *)t_default_args2_powers};
  for (int i = 0; i < 2; i++) {
    int *val_arg1 = val_args[i];
    int *pow_arg1 = pow_args[i];
    int *val_arg2 = val_args[(i + 1) % 2];
    int *pow_arg2 = pow_args[(i + 1) % 2];
    for (int j = 0; j < 4; j++) {
      int s1 = s21_get_bit(j, 0);
      int s2 = s21_get_bit(j, 1);
      int sr = s1 ^ s2;
      s21_decimal value1 =
          s21_ints_to_decimal(val_arg1 + 3 * _i, pow_arg1[_i], s1);
      s21_decimal value2 =
          s21_ints_to_decimal(val_arg2 + 3 * _i, pow_arg2[_i], s2);
      s21_decimal tresult = s21_ints_to_decimal(t_default_res_values[_i],
                                                t_default_res_powers[_i], sr);
      s21_decimal result;
      ck_assert(!s21_mul(value1, value2, &result));
      ck_assert(s21_is_m_equal(&result, &tresult));
      ck_assert(s21_get_power(&result) == t_default_res_powers[_i]);
      ck_assert(s21_get_sign(&result) == sr);
    }
  }
}
END_TEST

START_TEST(s21_mul_error) {
  int *val_args[2] = {(int *)t_err_args1_values, (int *)t_err_args2_values};
  int *pow_args[2] = {(int *)t_err_args1_pows, (int *)t_err_args2_pows};
  for (int i = 0; i < 2; i++) {
    int *val_arg1 = val_args[i];
    int *pow_arg1 = pow_args[i];
    int *val_arg2 = val_args[(i + 1) % 2];
    int *pow_arg2 = pow_args[(i + 1) % 2];
    for (int j = 0; j < 4; j++) {
      int s1 = s21_get_bit(j, 0);
      int s2 = s21_get_bit(j, 1);
      int sr = s1 ^ s2;
      s21_decimal value1 =
          s21_ints_to_decimal(val_arg1 + 3 * _i, pow_arg1[_i], s1);
      s21_decimal value2 =
          s21_ints_to_decimal(val_arg2 + 3 * _i, pow_arg2[_i], s2);
      s21_decimal tmp;
      int result = s21_mul(value1, value2, &tmp);
      if (sr) {
        ck_assert(result == 2);
      } else {
        ck_assert(result == 1);
      }
    }
  }
}
END_TEST

Suite *s21_mul_suite() {
  Suite *s = suite_create("s21_mul");

  TCase *tc_zero = tcase_create("ZERO");
  tcase_add_loop_test(tc_zero, s21_mul_zero, 0, LENGTH(t_zero_args1_powers));
  suite_add_tcase(s, tc_zero);

  TCase *tc_default = tcase_create("DEFAULT");
  tcase_add_loop_test(tc_default, s21_mul_default, 0,
                      LENGTH(t_default_args1_powers));
  suite_add_tcase(s, tc_default);

  TCase *tc_error = tcase_create("ERROR");
  tcase_add_loop_test(tc_error, s21_mul_error, 0, LENGTH(t_err_args1_pows));
  suite_add_tcase(s, tc_error);

  return s;
}