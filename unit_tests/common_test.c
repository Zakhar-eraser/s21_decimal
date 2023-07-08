#include "common_test.h"

s21_decimal s21_ints_to_decimal(int *value, int power, int sign) {
  s21_decimal out = {
      {value[0], value[1], value[2], (power << 16) | (sign << 31)}};
  return out;
}

s21_decimal s21_long_to_decimal(long long value, int power, int sign) {
  s21_decimal out = {{0, 0, 0, (power << 16) | (sign << 31)}};
  *(long long *)out.bits = value;
  return out;
}

float Rand_R(float a, float b) {
  float m = (float)rand() / RAND_MAX;
  float num = a + m * (b - a);
  return num;
}
