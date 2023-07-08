#include <check.h>

// Add unit test`s suites here
Suite *s21_from_int_to_decimal_suite();
Suite *s21_round_suite();
Suite *s21_mul_suite();
Suite *s21_div_suite();
Suite *s21_from_decimal_to_int_suite();
Suite *s21_from_decimal_to_float_suite();
Suite *s21_is_equal_suite();
Suite *s21_is_not_equal_suite();
Suite *s21_is_less_suite();
Suite *s21_is_less_or_equal_suite();
Suite *s21_is_greater_suite();
Suite *s21_is_greater_or_equal_suite();
Suite *s21_add_suite();
Suite *s21_sub_suite();
Suite *s21_floor_suite();
Suite *s21_truncate_suite();
Suite *s21_negate_suite();

int main() {
  int result = 0;
  SRunner *runner = srunner_create(suite_create("s21_decimal"));
#ifdef S21_NOFORK
  srunner_set_fork_status(runner, CK_NOFORK);
#endif
  // And here
  srunner_add_suite(runner, s21_from_decimal_to_float_suite());
  srunner_add_suite(runner, s21_from_int_to_decimal_suite());
  srunner_add_suite(runner, s21_round_suite());
  srunner_add_suite(runner, s21_mul_suite());
  srunner_add_suite(runner, s21_div_suite());
  srunner_add_suite(runner, s21_from_decimal_to_int_suite());
  srunner_add_suite(runner, s21_is_equal_suite());
  srunner_add_suite(runner, s21_is_not_equal_suite());
  srunner_add_suite(runner, s21_is_less_suite());
  srunner_add_suite(runner, s21_is_less_or_equal_suite());
  srunner_add_suite(runner, s21_is_greater_suite());
  srunner_add_suite(runner, s21_is_greater_or_equal_suite());
  srunner_add_suite(runner, s21_add_suite());
  srunner_add_suite(runner, s21_sub_suite());
  srunner_add_suite(runner, s21_floor_suite());
  srunner_add_suite(runner, s21_truncate_suite());
  srunner_add_suite(runner, s21_negate_suite());

  srunner_run_all(runner, CK_NORMAL);

  result = srunner_ntests_failed(runner) > 0;
  srunner_free(runner);
  return result;
}