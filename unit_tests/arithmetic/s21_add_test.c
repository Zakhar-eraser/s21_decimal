#include "common_test.h"

static void common_add_test(int m1[3], int p1, int m2[3], int p2, int mr[3],
                            int pr);
static void common_sub_test(int m1[3], int p1, int m2[3], int p2, int mr[3],
                            int pr, int sr);
static void common_error_test(int m1[3], int p1, int m2[3], int p2);

START_TEST(full_mantissa_0) {
  int mvs[] = {-1, -1, -1};
  int mr[] = {858993459, 858993459, 858993459};
  common_add_test(mvs, 1, mvs, 1, mr, 0);
}
END_TEST

START_TEST(non_scalable) {
  int mv1[] = {-1726311213, 565465366,
               458420333};  // 84563625634643644536467.34547
  int mv2[] = {1911306582, 1425302170,
               1758170728};  // 3243252546342523423423.5435350
  int mr[] = {783882884, 1782309231,
              476002040};  // 87806878180986167959890.88900
  common_add_test(mv1, 5, mv2, 7, mr, 5);
}
END_TEST

START_TEST(full_mantissa_1) {
  int mv1[] = {837546, 0, 0};
  int mv2[] = {-1, -1, -1};
  int mr[] = {-1634232318, -1717986919, 429496729};
  common_add_test(mv1, 4, mv2, 7, mr, 6);
}
END_TEST

START_TEST(full_m_non_s_0) {
  int mv1[] = {837546, 0, 0};
  int mv2[] = {-1, -1, -1};
  int mr[] = {-1717986835, -1717986919,
              429496729};  // 7922816251426433759354395117
  common_add_test(mv1, 4, mv2, 1, mr, 0);
}
END_TEST

START_TEST(full_m_non_s_1) {
  int mv1[] = {830546, 0, 0};
  int mv2[] = {-2, -1, -1};
  int mr[] = {-1717986836, -1717986919,
              429496729};  // 7922816251426433759354395116
  common_add_test(mv1, 4, mv2, 1, mr, 0);
}
END_TEST

START_TEST(zeros_sum) {
  int vs[] = {0, 0, 0};
  common_add_test(vs, 5, vs, 28, vs, 0);
}
END_TEST

START_TEST(same_values) {
  int mvs[] = {-1, -1, -1};
  int mr[] = {0, 0, 0};
  common_sub_test(mvs, 4, mvs, 4, mr, 0, 0);
}

START_TEST(zeros_sub) {
  int vs[] = {0, 0, 0};
  common_sub_test(vs, 28, vs, 0, vs, 5, 1);
}
END_TEST

START_TEST(low_great_0) {
  int mv1[] = {832546, 0, 0};
  int mv2[] = {1879048230, -1291644761,
               -500259693};  // 700000000000000000000000000.38
  int mr[] = {1879039905, -1291644761,
              -500259693};  // -699999999999999999999999917.13
  common_sub_test(mv1, 4, mv2, 2, mr, 2, 1);
}
END_TEST

START_TEST(low_great_1) {
  int mv1[] = {345251, 0, 0};
  int mv2[] = {-885420103, 2031826949, 28};  // 700000000000000000000000000.38
  int mr[] = {-885765354, 2031826949, 28};   // -699999999999999999999999917.13
  common_sub_test(mv1, 0, mv2, 0, mr, 0, 1);
}
END_TEST

START_TEST(ovf_0) {
  int mv1[] = {-1, -1, -1};
  int mv2[] = {1, 0, 0};
  common_error_test(mv1, 0, mv2, 0);
}
END_TEST

START_TEST(ovf_1) {
  int mv1[] = {-2, -1, -1};
  int mv2[] = {15, 0, 0};
  common_error_test(mv1, 0, mv2, 1);
}
END_TEST

Suite *s21_add_suite() {
  Suite *s = suite_create("s21_add");

  TCase *tc_add = tcase_create("ADD");
  tcase_add_test(tc_add, full_mantissa_0);
  tcase_add_test(tc_add, full_mantissa_1);
  tcase_add_test(tc_add, non_scalable);
  tcase_add_test(tc_add, full_m_non_s_0);
  tcase_add_test(tc_add, full_m_non_s_1);
  tcase_add_test(tc_add, zeros_sum);
  suite_add_tcase(s, tc_add);

  TCase *tc_sub = tcase_create("SUB");
  tcase_add_test(tc_sub, same_values);
  tcase_add_test(tc_sub, zeros_sub);
  tcase_add_test(tc_sub, low_great_0);
  tcase_add_test(tc_sub, low_great_1);
  suite_add_tcase(s, tc_sub);

  TCase *tc_fail = tcase_create("FAIL");
  tcase_add_test(tc_fail, ovf_0);
  tcase_add_test(tc_fail, ovf_1);
  suite_add_tcase(s, tc_fail);

  return s;
}

static void common_error_test(int m1[3], int p1, int m2[3], int p2) {
  s21_decimal vals[] = {s21_ints_to_decimal(m1, p1, 0),
                        s21_ints_to_decimal(m2, p2, 0)};
  for (int i = 0; i < 2; i++) {
    s21_set_sign(vals, i);
    s21_set_sign(vals + 1, i);
    for (int j = 0; j < 2; j++) {
      s21_decimal tmp;
      int out = s21_add(vals[j], vals[(j + 1) % 2], &tmp);
      if (i) {
        ck_assert(out == 2);
      } else {
        ck_assert(out == 1);
      }
    }
  }
}

static void common_add_test(int m1[3], int p1, int m2[3], int p2, int mr[3],
                            int pr) {
  s21_decimal vals[] = {s21_ints_to_decimal(m1, p1, 0),
                        s21_ints_to_decimal(m2, p2, 0)};
  s21_decimal tresult = s21_ints_to_decimal(mr, pr, 0);
  for (int j = 0; j < 2; j++) {
    for (int i = 0; i < 2; i++) {
      s21_set_sign(vals + j, i);
      s21_set_sign(vals + (j + 1) % 2, i);
      s21_decimal result;
      ck_assert(!s21_add(vals[j], vals[(j + 1) % 2], &result));
      ck_assert(s21_is_m_equal(&result, &tresult));
      if (!s21_is_zero(&result)) {
        ck_assert(s21_get_power(&result) == pr);
        ck_assert(s21_get_sign(&result) == i);
      }
    }
  }
}

static void common_sub_test(int m1[3], int p1, int m2[3], int p2, int mr[3],
                            int pr, int sr) {
  s21_decimal vals[] = {s21_ints_to_decimal(m1, p1, 0),
                        s21_ints_to_decimal(m2, p2, 0)};
  s21_decimal tresult = s21_ints_to_decimal(mr, pr, sr);
  for (int i = 0; i < 2; i++) {
    s21_decimal result;
    s21_set_sign(vals, i);
    s21_set_sign(vals + 1, (i + 1) % 2);
    ck_assert(!s21_add(vals[0], vals[1], &result));
    ck_assert(s21_is_m_equal(&result, &tresult));
    if (!s21_is_zero(&result)) {
      ck_assert(s21_get_power(&result) == pr);
      ck_assert(s21_get_sign(&result) == (sr ^ i));
    }
  }
}