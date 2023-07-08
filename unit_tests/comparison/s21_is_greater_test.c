#include "common_test.h"

static int t_less_v1[][3] = {{0},
                             {-1, -1, -1},
                             {1198760915, -265923153, 1318580950},
                             {1198760916, -265923153, 1318580950},
                             {5},
                             {-1, -1, -1},
                             {-2342, 234235, 23423455},
                             {1, 2, 3},
                             {12, 34, 56},
                             {6578}};
static int t_less_p1[] = {0, 28, 21, 21, 0, 28, 15, 14, 1, 2};
static int t_less_s1[] = {1, 1, 0, 1, 1, 0, 0, 1, 1, 0};
static int t_less_v2[][3] = {{1},
                             {0},
                             {1198760916, -265923153, 1318580950},
                             {1198760915, -265923153, 1318580950},
                             {5},
                             {1073741824, -24903193, 433680868},
                             {-2342, 234235, 23423455},
                             {1, 2, 3},
                             {123, 344, 565},
                             {657845}};
static int t_less_p2[] = {28, 15, 21, 21, 0, 27, 14, 15, 0, 3};
static int t_less_s2[] = {0, 0, 0, 1, 0, 0, 0, 1, 0, 0};

static int t_equal_v1[][3] = {
    {101000}, {3, 235342, 53525425}, {1073741824, -24903193, 433680868}};
static int t_equal_p1[] = {4, 0, 27};
static int t_equal_v2[][3] = {{101}, {3, 235342, 53525425}, {800000}};
static int t_equal_p2[] = {1, 0, 5};

START_TEST(less) {
  s21_decimal val1 =
      s21_ints_to_decimal(t_less_v1[_i], t_less_p1[_i], t_less_s1[_i]);
  s21_decimal val2 =
      s21_ints_to_decimal(t_less_v2[_i], t_less_p2[_i], t_less_s2[_i]);
  ck_assert(s21_is_less(val1, val2));
}
END_TEST

START_TEST(equal) {
  s21_decimal val1 = s21_ints_to_decimal(t_equal_v1[_i], t_equal_p1[_i], 0);
  s21_decimal val2 = s21_ints_to_decimal(t_equal_v2[_i], t_equal_p2[_i], 0);
  ck_assert(!s21_is_less(val1, val2));
  ck_assert(!s21_is_less(val2, val1));
  s21_set_sign(&val1, 1);
  s21_set_sign(&val2, 1);
  ck_assert(!s21_is_less(val1, val2));
  ck_assert(!s21_is_less(val2, val1));
}
END_TEST

START_TEST(equal_zero) {
  s21_decimal val1 = s21_zero();
  s21_decimal val2 = s21_zero();
  for (int i = 0; i < 4; i++) {
    s21_set_sign(&val1, s21_get_bit(i, 0));
    s21_set_sign(&val2, s21_get_bit(i, 1));
    for (int j = 0; j < 29; j++) {
      s21_set_power(&val1, j);
      s21_set_power(&val2, 28 - j);
      ck_assert(!s21_is_less(val1, val2));
    }
  }
}
END_TEST

START_TEST(greater) {
  s21_decimal val1 =
      s21_ints_to_decimal(t_less_v1[_i], t_less_p1[_i], t_less_s1[_i]);
  s21_decimal val2 =
      s21_ints_to_decimal(t_less_v2[_i], t_less_p2[_i], t_less_s2[_i]);
  ck_assert(!s21_is_less(val2, val1));
}
END_TEST

Suite *s21_is_greater_suite() {
  Suite *s = suite_create("s21_is_greater");

  TCase *tc_true = tcase_create("TRUE");
  tcase_add_loop_test(tc_true, greater, 0, LENGTH(t_less_p1));
  suite_add_tcase(s, tc_true);

  TCase *tc_false = tcase_create("FALSE");
  tcase_add_loop_test(tc_false, equal, 0, LENGTH(t_equal_p1));
  tcase_add_test(tc_false, equal_zero);
  tcase_add_loop_test(tc_false, less, 0, LENGTH(t_less_p1));
  suite_add_tcase(s, tc_false);

  return s;
}