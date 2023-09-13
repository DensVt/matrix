
#include <check.h>
#include <time.h>
#include <unistd.h>

#include "s21_matrix.h"

void matrix_filling(double number, matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; number += 1.0, j++)
      A->matrix[i][j] = number;
  }
}

START_TEST(create_m_1) {
  matrix_t matrix;
  int err = 0;

  err = s21_create_matrix(5, 5, &matrix);
  if (!err) s21_remove_matrix(&matrix);
  ck_assert_int_eq(0, err);

  err = s21_create_matrix(5, 10, &matrix);
  if (!err) s21_remove_matrix(&matrix);
  ck_assert_int_eq(0, err);

  err = s21_create_matrix(10, 5, &matrix);
  if (!err) s21_remove_matrix(&matrix);
  ck_assert_int_eq(0, err);

  err = s21_create_matrix(0, 0, &matrix);
  ck_assert_int_eq(1, err);

  err = s21_create_matrix(0, 3, &matrix);
  ck_assert_int_eq(1, err);

  err = s21_create_matrix(-4, -4, &matrix);
  ck_assert_int_eq(1, err);

  err = s21_create_matrix(-4, 5, &matrix);
  ck_assert_int_eq(1, err);

  err = s21_create_matrix(4, -5, &matrix);
  ck_assert_int_eq(1, err);

  err = s21_create_matrix(2, 2, NULL);
  ck_assert_int_eq(1, err);
}
END_TEST

START_TEST(create_m_2) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = 0;
      ck_assert_ldouble_eq_tol(0, m.matrix[i][j], 1e-07);
    }
  }
  ck_assert_int_eq(m.rows, rows);
  ck_assert_int_eq(m.columns, cols);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_m_3) {
  const int rows = 0;
  const int cols = 10;
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), ERR_INVALID_MATRIX);
}
END_TEST

START_TEST(create_m_4) {
  const int rows = 10;
  const int cols = 0;

  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), ERR_INVALID_MATRIX);
}
END_TEST

START_TEST(remove_m) {
  matrix_t matrix_r;
  int err = 0;

  err = s21_create_matrix(3, 3, &matrix_r);
  s21_remove_matrix(&matrix_r);
  if (matrix_r.matrix != NULL) err = ERR_INVALID_MATRIX;

  ck_assert_int_eq(err, OK);
}
END_TEST

// s21_eq_matrix

START_TEST(eq_m_1) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(2, 3, &A);
  matrix_filling(2.0, &A);

  s21_create_matrix(2, 3, &B);
  matrix_filling(2.0, &B);

  res = s21_eq_matrix(&A, &B);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(eq_m_2) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(2, 2, &A);
  matrix_filling(3.0, &A);

  s21_create_matrix(2, 2, &B);
  matrix_filling(1.0, &B);

  res = s21_eq_matrix(&A, &B);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(eq_m_3) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(3, 4, &A);
  matrix_filling(1.0, &A);

  s21_create_matrix(3, 4, &B);
  matrix_filling(-2.0, &B);

  res = s21_eq_matrix(&A, &B);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(eq_m_4) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(3, 2, &A);
  matrix_filling(7.0, &A);

  s21_create_matrix(2, 3, &B);
  matrix_filling(-5.0, &B);

  res = s21_eq_matrix(&A, &B);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(eq_m_5) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(1, 3, &A);
  matrix_filling(3.0, &A);
  s21_create_matrix(3, 1, &B);
  matrix_filling(3.0, &B);
  res = s21_eq_matrix(&A, &B);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(eq_m_6) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(7, 7, &A);
  matrix_filling(1.0, &A);

  s21_create_matrix(7, 7, &B);
  matrix_filling(1.0, &B);

  res = s21_eq_matrix(&A, &B);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

// Суммирование матриц

START_TEST(sum_m_1) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};

  s21_create_matrix(4, 4, &A);
  matrix_filling(1.0, &A);

  s21_create_matrix(4, 4, &B);
  matrix_filling(1.0, &B);

  s21_sum_matrix(&A, &B, &C);

  s21_create_matrix(4, 4, &D);

  D.matrix[0][0] = 2.0;
  D.matrix[0][1] = 4.0;
  D.matrix[0][2] = 6.0;
  D.matrix[0][3] = 8.0;

  D.matrix[1][0] = 10.0;
  D.matrix[1][1] = 12.0;
  D.matrix[1][2] = 14.0;
  D.matrix[1][3] = 16.0;

  D.matrix[2][0] = 18.0;
  D.matrix[2][1] = 20.0;
  D.matrix[2][2] = 22.0;
  D.matrix[2][3] = 24.0;

  D.matrix[3][0] = 26.0;
  D.matrix[3][1] = 28.0;
  D.matrix[3][2] = 30.0;
  D.matrix[3][3] = 32.0;

  res = s21_eq_matrix(&D, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(sum_m_2) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};

  s21_create_matrix(4, 4, &A);
  matrix_filling(0.0, &A);

  s21_create_matrix(4, 4, &B);
  matrix_filling(2.0, &B);

  s21_sum_matrix(&A, &B, &C);

  s21_create_matrix(4, 4, &D);

  D.matrix[0][0] = 2.0;
  D.matrix[0][1] = 4.0;
  D.matrix[0][2] = 6.0;
  D.matrix[0][3] = 8.0;

  D.matrix[1][0] = 10.0;
  D.matrix[1][1] = 12.0;
  D.matrix[1][2] = 14.0;
  D.matrix[1][3] = 16.0;

  D.matrix[2][0] = 18.0;
  D.matrix[2][1] = 20.0;
  D.matrix[2][2] = 22.0;
  D.matrix[2][3] = 24.0;

  D.matrix[3][0] = 26.0;
  D.matrix[3][1] = 28.0;
  D.matrix[3][2] = 30.0;
  D.matrix[3][3] = 32.0;

  res = s21_eq_matrix(&D, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(sum_m_3) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};

  s21_create_matrix(3, 3, &A);
  matrix_filling(-3.0, &A);

  s21_create_matrix(3, 3, &B);
  matrix_filling(5.0, &B);

  s21_sum_matrix(&A, &B, &C);

  s21_create_matrix(3, 3, &D);

  D.matrix[0][0] = 2.0;
  D.matrix[0][1] = 4.0;
  D.matrix[0][2] = 6.0;

  D.matrix[1][0] = 8.0;
  D.matrix[1][1] = 10.0;
  D.matrix[1][2] = 12.0;

  D.matrix[2][0] = 14.0;
  D.matrix[2][1] = 16.0;
  D.matrix[2][2] = 18.0;

  res = s21_eq_matrix(&D, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(sum_m_4) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};

  s21_create_matrix(4, 4, &A);
  matrix_filling(5.0, &A);

  s21_create_matrix(4, 4, &B);
  matrix_filling(-3.0, &B);

  s21_sum_matrix(&A, &B, &C);

  s21_create_matrix(4, 4, &D);

  D.matrix[0][0] = 2.0;
  D.matrix[0][1] = 4.0;
  D.matrix[0][2] = 6.0;
  D.matrix[0][3] = 8.0;

  D.matrix[1][0] = 10.0;
  D.matrix[1][1] = 12.0;
  D.matrix[1][2] = 14.0;
  D.matrix[1][3] = 16.0;

  D.matrix[2][0] = 18.0;
  D.matrix[2][1] = 20.0;
  D.matrix[2][2] = 22.0;
  D.matrix[2][3] = 24.0;

  D.matrix[3][0] = 26.0;
  D.matrix[3][1] = 28.0;
  D.matrix[3][2] = 30.0;
  D.matrix[3][3] = 32.0;

  res = s21_eq_matrix(&D, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(sum_m_5) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};

  s21_create_matrix(4, 2, &A);
  matrix_filling(1.0, &A);

  s21_create_matrix(4, 2, &B);
  matrix_filling(1.0, &B);

  s21_sum_matrix(&A, &B, &C);

  s21_create_matrix(4, 2, &D);

  D.matrix[0][0] = 2.0;
  D.matrix[0][1] = 4.0;

  D.matrix[1][0] = 6.0;
  D.matrix[1][1] = 8.0;

  D.matrix[2][0] = 10.0;
  D.matrix[2][1] = 12.0;

  D.matrix[3][0] = 14.0;
  D.matrix[3][1] = 16.0;

  res = s21_eq_matrix(&D, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(sum_m_6) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};

  s21_create_matrix(4, 2, &A);
  matrix_filling(-1.0, &A);

  s21_create_matrix(4, 2, &B);
  matrix_filling(3.0, &B);

  s21_sum_matrix(&A, &B, &C);

  s21_create_matrix(4, 2, &D);

  D.matrix[0][0] = 2.0;
  D.matrix[0][1] = 4.0;

  D.matrix[1][0] = 6.0;
  D.matrix[1][1] = 8.0;

  D.matrix[2][0] = 10.0;
  D.matrix[2][1] = 12.0;

  D.matrix[3][0] = 14.0;
  D.matrix[3][1] = 16.0;

  res = s21_eq_matrix(&D, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(sum_m_7) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};

  s21_create_matrix(4, 2, &A);
  matrix_filling(4.0, &A);

  s21_create_matrix(4, 2, &B);
  matrix_filling(-2.0, &B);

  s21_sum_matrix(&A, &B, &C);

  s21_create_matrix(4, 2, &D);

  D.matrix[0][0] = 2.0;
  D.matrix[0][1] = 4.0;

  D.matrix[1][0] = 6.0;
  D.matrix[1][1] = 8.0;

  D.matrix[2][0] = 10.0;
  D.matrix[2][1] = 12.0;

  D.matrix[3][0] = 14.0;
  D.matrix[3][1] = 16.0;

  res = s21_eq_matrix(&D, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(sum_m_8) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};

  s21_create_matrix(4, 2, &A);

  s21_create_matrix(4, 3, &B);

  res = s21_sum_matrix(&A, &B, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  ck_assert_int_eq(res, ERR_COMPUTATION);
}
END_TEST

// Вычетание матриц

START_TEST(sub_m_1) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};

  s21_create_matrix(4, 4, &A);
  matrix_filling(1.0, &A);

  s21_create_matrix(4, 4, &B);
  matrix_filling(1.0, &B);

  s21_sub_matrix(&A, &B, &C);

  s21_create_matrix(4, 4, &D);

  D.matrix[0][0] = 0.0;
  D.matrix[0][1] = 0.0;
  D.matrix[0][2] = 0.0;
  D.matrix[0][3] = 0.0;

  D.matrix[1][0] = 0.0;
  D.matrix[1][1] = 0.0;
  D.matrix[1][2] = 0.0;
  D.matrix[1][3] = 0.0;

  D.matrix[2][0] = 0.0;
  D.matrix[2][1] = 0.0;
  D.matrix[2][2] = 0.0;
  D.matrix[2][3] = 0.0;

  D.matrix[3][0] = 0.0;
  D.matrix[3][1] = 0.0;
  D.matrix[3][2] = 0.0;
  D.matrix[3][3] = 0.0;

  res = s21_eq_matrix(&D, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(sub_m_2) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};

  s21_create_matrix(4, 4, &A);
  matrix_filling(0.0, &A);

  s21_create_matrix(4, 4, &B);
  matrix_filling(2.0, &B);

  s21_sub_matrix(&A, &B, &C);

  s21_create_matrix(4, 4, &D);

  D.matrix[0][0] = -2.0;
  D.matrix[0][1] = -2.0;
  D.matrix[0][2] = -2.0;
  D.matrix[0][3] = -2.0;

  D.matrix[1][0] = -2.0;
  D.matrix[1][1] = -2.0;
  D.matrix[1][2] = -2.0;
  D.matrix[1][3] = -2.0;

  D.matrix[2][0] = -2.0;
  D.matrix[2][1] = -2.0;
  D.matrix[2][2] = -2.0;
  D.matrix[2][3] = -2.0;

  D.matrix[3][0] = -2.0;
  D.matrix[3][1] = -2.0;
  D.matrix[3][2] = -2.0;
  D.matrix[3][3] = -2.0;

  res = s21_eq_matrix(&D, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(sub_m_3) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};

  s21_create_matrix(4, 4, &A);
  matrix_filling(-3.0, &A);

  s21_create_matrix(4, 4, &B);
  matrix_filling(5.0, &B);

  s21_sub_matrix(&A, &B, &C);

  s21_create_matrix(4, 4, &D);

  D.matrix[0][0] = -8.0;
  D.matrix[0][1] = -8.0;
  D.matrix[0][2] = -8.0;
  D.matrix[0][3] = -8.0;

  D.matrix[1][0] = -8.0;
  D.matrix[1][1] = -8.0;
  D.matrix[1][2] = -8.0;
  D.matrix[1][3] = -8.0;

  D.matrix[2][0] = -8.0;
  D.matrix[2][1] = -8.0;
  D.matrix[2][2] = -8.0;
  D.matrix[2][3] = -8.0;

  D.matrix[3][0] = -8.0;
  D.matrix[3][1] = -8.0;
  D.matrix[3][2] = -8.0;
  D.matrix[3][3] = -8.0;

  res = s21_eq_matrix(&D, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(sub_m_4) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};

  s21_create_matrix(4, 4, &A);
  matrix_filling(5.0, &A);

  s21_create_matrix(4, 4, &B);
  matrix_filling(-3.0, &B);

  s21_sub_matrix(&A, &B, &C);

  s21_create_matrix(4, 4, &D);

  D.matrix[0][0] = 8.0;
  D.matrix[0][1] = 8.0;
  D.matrix[0][2] = 8.0;
  D.matrix[0][3] = 8.0;

  D.matrix[1][0] = 8.0;
  D.matrix[1][1] = 8.0;
  D.matrix[1][2] = 8.0;
  D.matrix[1][3] = 8.0;

  D.matrix[2][0] = 8.0;
  D.matrix[2][1] = 8.0;
  D.matrix[2][2] = 8.0;
  D.matrix[2][3] = 8.0;

  D.matrix[3][0] = 8.0;
  D.matrix[3][1] = 8.0;
  D.matrix[3][2] = 8.0;
  D.matrix[3][3] = 8.0;

  res = s21_eq_matrix(&D, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(sub_m_5) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};

  s21_create_matrix(4, 2, &A);
  matrix_filling(1.0, &A);

  s21_create_matrix(4, 2, &B);
  matrix_filling(1.0, &B);

  s21_sub_matrix(&A, &B, &C);

  s21_create_matrix(4, 2, &D);

  D.matrix[0][0] = 0.0;
  D.matrix[0][1] = 0.0;

  D.matrix[1][0] = 0.0;
  D.matrix[1][1] = 0.0;

  D.matrix[2][0] = 0.0;
  D.matrix[2][1] = 0.0;

  D.matrix[3][0] = 0.0;
  D.matrix[3][1] = 0.0;

  res = s21_eq_matrix(&D, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(sub_m_6) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};

  s21_create_matrix(4, 2, &A);
  matrix_filling(-1.0, &A);

  s21_create_matrix(4, 2, &B);
  matrix_filling(3.0, &B);

  s21_sub_matrix(&A, &B, &C);

  s21_create_matrix(4, 2, &D);

  D.matrix[0][0] = -4.0;
  D.matrix[0][1] = -4.0;

  D.matrix[1][0] = -4.0;
  D.matrix[1][1] = -4.0;

  D.matrix[2][0] = -4.0;
  D.matrix[2][1] = -4.0;

  D.matrix[3][0] = -4.0;
  D.matrix[3][1] = -4.0;

  res = s21_eq_matrix(&D, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(sub_m_7) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};

  s21_create_matrix(4, 2, &A);
  matrix_filling(4.0, &A);

  s21_create_matrix(4, 2, &B);
  matrix_filling(-2.0, &B);

  s21_sub_matrix(&A, &B, &C);

  s21_create_matrix(4, 2, &D);

  D.matrix[0][0] = 6.0;
  D.matrix[0][1] = 6.0;

  D.matrix[1][0] = 6.0;
  D.matrix[1][1] = 6.0;

  D.matrix[2][0] = 6.0;
  D.matrix[2][1] = 6.0;

  D.matrix[3][0] = 6.0;
  D.matrix[3][1] = 6.0;

  res = s21_eq_matrix(&D, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(sub_m_8) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};

  s21_create_matrix(4, 2, &A);

  s21_create_matrix(4, 3, &B);

  res = s21_sub_matrix(&A, &B, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  ck_assert_int_eq(res, ERR_COMPUTATION);
}
END_TEST

//Умножение матрицы на число

START_TEST(mult_n_1) {
  int res = 0;
  double number = 3.0;
  matrix_t A = {0};
  matrix_t C = {0};
  matrix_t B = {0};

  s21_create_matrix(4, 4, &A);

  matrix_filling(1.0, &A);

  s21_mult_number(&A, number, &C);

  s21_create_matrix(4, 4, &B);

  B.matrix[0][0] = 3.0;
  B.matrix[0][1] = 6.0;
  B.matrix[0][2] = 9.0;
  B.matrix[0][3] = 12.0;

  B.matrix[1][0] = 15.0;
  B.matrix[1][1] = 18.0;
  B.matrix[1][2] = 21.0;
  B.matrix[1][3] = 24.0;

  B.matrix[2][0] = 27.0;
  B.matrix[2][1] = 30.0;
  B.matrix[2][2] = 33.0;
  B.matrix[2][3] = 36.0;

  B.matrix[3][0] = 39.0;
  B.matrix[3][1] = 42.0;
  B.matrix[3][2] = 45.0;
  B.matrix[3][3] = 48.0;

  res = s21_eq_matrix(&B, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(mult_n_2) {
  int res = 0;
  double number = 5.0;
  matrix_t A = {0};
  matrix_t C = {0};
  matrix_t B = {0};

  s21_create_matrix(4, 4, &A);
  matrix_filling(1.0, &A);

  s21_mult_number(&A, number, &C);

  s21_create_matrix(4, 4, &B);

  B.matrix[0][0] = 5.0;
  B.matrix[0][1] = 10.0;
  B.matrix[0][2] = 15.0;
  B.matrix[0][3] = 20.0;

  B.matrix[1][0] = 25.0;
  B.matrix[1][1] = 30.0;
  B.matrix[1][2] = 35.0;
  B.matrix[1][3] = 40.0;

  B.matrix[2][0] = 45.0;
  B.matrix[2][1] = 50.0;
  B.matrix[2][2] = 55.0;
  B.matrix[2][3] = 60.0;

  B.matrix[3][0] = 65.0;
  B.matrix[3][1] = 70.0;
  B.matrix[3][2] = 75.0;
  B.matrix[3][3] = 80.0;

  res = s21_eq_matrix(&B, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(mult_n_3) {
  int res = 0;
  double number = 2.0;
  matrix_t A = {0};
  matrix_t C = {0};
  matrix_t B = {0};

  s21_create_matrix(4, 2, &A);
  matrix_filling(2.0, &A);

  s21_mult_number(&A, number, &C);

  s21_create_matrix(4, 2, &B);

  B.matrix[0][0] = 4.0;
  B.matrix[0][1] = 6.0;

  B.matrix[1][0] = 8.0;
  B.matrix[1][1] = 10.0;

  B.matrix[2][0] = 12.0;
  B.matrix[2][1] = 14.0;

  B.matrix[3][0] = 16.0;
  B.matrix[3][1] = 18.0;

  res = s21_eq_matrix(&B, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(mult_n_4) {
  int res = 0;
  double number = -2.0;
  matrix_t A = {0};
  matrix_t C = {0};
  matrix_t B = {0};

  s21_create_matrix(4, 2, &A);
  matrix_filling(2.0, &A);

  s21_mult_number(&A, number, &C);

  s21_create_matrix(4, 2, &B);

  B.matrix[0][0] = -4.0;
  B.matrix[0][1] = -6.0;

  B.matrix[1][0] = -8.0;
  B.matrix[1][1] = -10.0;

  B.matrix[2][0] = -12.0;
  B.matrix[2][1] = -14.0;

  B.matrix[3][0] = -16.0;
  B.matrix[3][1] = -18.0;

  res = s21_eq_matrix(&B, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(mult_n_5) {
  int res = 0;
  double number = 2.0;
  matrix_t A = {0};
  matrix_t C = {0};
  matrix_t B = {0};

  s21_create_matrix(1, 1, &A);
  matrix_filling(2.0, &A);

  s21_mult_number(&A, number, &C);

  s21_create_matrix(1, 1, &B);

  B.matrix[0][0] = 4.0;

  res = s21_eq_matrix(&B, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(mult_n_6) {
  int res = 0;
  double number = 2.0;
  matrix_t A = {0};
  matrix_t C = {0};

  s21_create_matrix(0, 0, &A);

  res = s21_mult_number(&A, number, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&C);

  ck_assert_int_eq(res, ERR_INVALID_MATRIX);
}
END_TEST

// Умножение матриц

START_TEST(mult_m_1) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};

  s21_create_matrix(4, 4, &A);
  matrix_filling(1.0, &A);

  s21_create_matrix(4, 4, &B);
  matrix_filling(1.0, &B);

  s21_mult_matrix(&A, &B, &C);

  s21_create_matrix(4, 4, &D);

  D.matrix[0][0] = 90.0;
  D.matrix[0][1] = 100.0;
  D.matrix[0][2] = 110.0;
  D.matrix[0][3] = 120.0;

  D.matrix[1][0] = 202.0;
  D.matrix[1][1] = 228.0;
  D.matrix[1][2] = 254.0;
  D.matrix[1][3] = 280.0;

  D.matrix[2][0] = 314.0;
  D.matrix[2][1] = 356.0;
  D.matrix[2][2] = 398.0;
  D.matrix[2][3] = 440.0;

  D.matrix[3][0] = 426.0;
  D.matrix[3][1] = 484.0;
  D.matrix[3][2] = 542.0;
  D.matrix[3][3] = 600.0;

  res = s21_eq_matrix(&D, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(mult_m_2) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};

  s21_create_matrix(4, 4, &A);
  matrix_filling(1.0, &A);

  s21_create_matrix(4, 4, &B);
  matrix_filling(-5.0, &B);

  s21_mult_matrix(&A, &B, &C);

  s21_create_matrix(4, 4, &D);

  D.matrix[0][0] = 30.0;
  D.matrix[0][1] = 40.0;
  D.matrix[0][2] = 50.0;
  D.matrix[0][3] = 60.0;

  D.matrix[1][0] = 46.0;
  D.matrix[1][1] = 72.0;
  D.matrix[1][2] = 98.0;
  D.matrix[1][3] = 124.0;

  D.matrix[2][0] = 62.0;
  D.matrix[2][1] = 104.0;
  D.matrix[2][2] = 146.0;
  D.matrix[2][3] = 188.0;

  D.matrix[3][0] = 78.0;
  D.matrix[3][1] = 136.0;
  D.matrix[3][2] = 194.0;
  D.matrix[3][3] = 252.0;

  res = s21_eq_matrix(&D, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(mult_m_3) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};

  s21_create_matrix(4, 4, &A);
  matrix_filling(-5.0, &A);

  s21_create_matrix(4, 4, &B);
  matrix_filling(1.0, &B);

  s21_mult_matrix(&A, &B, &C);

  s21_create_matrix(4, 4, &D);

  D.matrix[0][0] = -78.0;
  D.matrix[0][1] = -92.0;
  D.matrix[0][2] = -106.0;
  D.matrix[0][3] = -120.0;

  D.matrix[1][0] = 34.0;
  D.matrix[1][1] = 36.0;
  D.matrix[1][2] = 38.0;
  D.matrix[1][3] = 40.0;

  D.matrix[2][0] = 146.0;
  D.matrix[2][1] = 164.0;
  D.matrix[2][2] = 182.0;
  D.matrix[2][3] = 200.0;

  D.matrix[3][0] = 258.0;
  D.matrix[3][1] = 292.0;
  D.matrix[3][2] = 326.0;
  D.matrix[3][3] = 360.0;

  res = s21_eq_matrix(&D, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(mult_m_4) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};

  s21_create_matrix(4, 2, &A);
  matrix_filling(-5.0, &A);

  s21_create_matrix(2, 4, &B);
  matrix_filling(1.0, &B);

  s21_mult_matrix(&A, &B, &C);

  s21_create_matrix(4, 4, &D);

  D.matrix[0][0] = -25.0;
  D.matrix[0][1] = -34.0;
  D.matrix[0][2] = -43.0;
  D.matrix[0][3] = -52.0;

  D.matrix[1][0] = -13.0;
  D.matrix[1][1] = -18.0;
  D.matrix[1][2] = -23.0;
  D.matrix[1][3] = -28.0;

  D.matrix[2][0] = -1.0;
  D.matrix[2][1] = -2.0;
  D.matrix[2][2] = -3.0;
  D.matrix[2][3] = -4.0;

  D.matrix[3][0] = 11.0;
  D.matrix[3][1] = 14.0;
  D.matrix[3][2] = 17.0;
  D.matrix[3][3] = 20.0;

  res = s21_eq_matrix(&D, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(mult_m_5) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};

  s21_create_matrix(1, 1, &A);
  matrix_filling(-5.0, &A);

  s21_create_matrix(1, 1, &B);
  matrix_filling(1.0, &B);

  s21_mult_matrix(&A, &B, &C);

  s21_create_matrix(1, 1, &D);

  D.matrix[0][0] = -5.0;

  res = s21_eq_matrix(&D, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(mult_m_6) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};

  res = s21_mult_matrix(&A, &B, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  ck_assert_int_eq(res, ERR_INVALID_MATRIX);
}
END_TEST

START_TEST(mult_m_7) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};

  s21_create_matrix(2, 3, &A);
  matrix_filling(-5.0, &A);

  s21_create_matrix(2, 2, &B);
  matrix_filling(1.0, &B);

  res = s21_mult_matrix(&A, &B, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  ck_assert_int_eq(res, ERR_COMPUTATION);
}
END_TEST

// Tранспонирование матрицы

// START_TEST(transp_1) {
//   int res = 0;
//   matrix_t A = {0};

//   res = s21_transpose(&A, &A);
//   ck_assert_int_eq(res, ERR_INVALID_MATRIX);
//   s21_remove_matrix(&A);
// }
// END_TEST

START_TEST(transp_2) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(3, 4, &A);
  matrix_filling(1.0, &A);
  res = s21_transpose(&A, &B);
  res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(transp_3) {
  int res = 0;
  matrix_t A = {0};
  matrix_t T = {0};
  matrix_t B = {0};

  s21_create_matrix(2, 3, &A);
  matrix_filling(1.0, &A);
  s21_create_matrix(3, 2, &B);

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 4.0;

  B.matrix[1][0] = 2.0;
  B.matrix[1][1] = 5.0;

  B.matrix[2][0] = 3.0;
  B.matrix[2][1] = 6.0;

  res = s21_transpose(&A, &T);
  res = s21_eq_matrix(&T, &B);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&T);
  s21_remove_matrix(&B);
}
END_TEST

// Вычисление матрицы алгебраических дополнений

START_TEST(calc_compl_1) {
  int res = 0;
  matrix_t A = {0};
  matrix_t C = {0};
  matrix_t B = {0};

  s21_create_matrix(4, 4, &A);

  A.matrix[0][0] = 112.0;
  A.matrix[0][1] = 243.0;
  A.matrix[0][2] = 3.0;
  A.matrix[0][3] = -8.0;

  A.matrix[1][0] = 47.0;
  A.matrix[1][1] = 51.0;
  A.matrix[1][2] = -66.0;
  A.matrix[1][3] = 99.0;

  A.matrix[2][0] = -74.0;
  A.matrix[2][1] = 85.0;
  A.matrix[2][2] = 97.0;
  A.matrix[2][3] = 63.0;

  A.matrix[3][0] = -13.0;
  A.matrix[3][1] = 79.0;
  A.matrix[3][2] = -99.0;
  A.matrix[3][3] = -121.0;

  s21_calc_complements(&A, &C);

  s21_create_matrix(4, 4, &B);

  B.matrix[0][0] = -2879514.0;
  B.matrix[0][1] = -1236631.0;
  B.matrix[0][2] = -1685096.0;
  B.matrix[0][3] = 880697.0;

  B.matrix[1][0] = 1162090.0;
  B.matrix[1][1] = -714015.0;
  B.matrix[1][2] = 4046255.0;
  B.matrix[1][3] = -3901600.0;

  B.matrix[2][0] = 4362897.0;
  B.matrix[2][1] = -2049432.0;
  B.matrix[2][2] = -532912.0;
  B.matrix[2][3] = -1370781.0;

  B.matrix[3][0] = 3412773.0;
  B.matrix[3][1] = -1569493.0;
  B.matrix[3][2] = 3144517.0;
  B.matrix[3][3] = 1284666.0;

  res = s21_eq_matrix(&B, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(calc_compl_2) {
  int res = 0;
  matrix_t A = {0};
  matrix_t C = {0};
  matrix_t B = {0};

  s21_create_matrix(4, 4, &A);

  A.matrix[0][0] = 65.0;
  A.matrix[0][1] = -3.0;
  A.matrix[0][2] = 90.0;
  A.matrix[0][3] = 1.0;

  A.matrix[1][0] = 75.0;
  A.matrix[1][1] = 38.0;
  A.matrix[1][2] = -539.0;
  A.matrix[1][3] = 42.0;

  A.matrix[2][0] = 23.0;
  A.matrix[2][1] = 0.0;
  A.matrix[2][2] = 99.0;
  A.matrix[2][3] = 32.0;

  A.matrix[3][0] = -16.0;
  A.matrix[3][1] = 56.0;
  A.matrix[3][2] = 43.0;
  A.matrix[3][3] = 6.0;

  s21_calc_complements(&A, &C);

  s21_create_matrix(4, 4, &B);

  B.matrix[0][0] = -1228452.0;
  B.matrix[0][1] = -399766.0;
  B.matrix[0][2] = -105004.0;
  B.matrix[0][3] = 1207806.0;

  B.matrix[1][0] = -158082.0;
  B.matrix[1][1] = -106757.0;
  B.matrix[1][2] = 113242.0;
  B.matrix[1][3] = -236721.0;

  B.matrix[2][0] = 238098.0;
  B.matrix[2][1] = 433979.0;
  B.matrix[2][2] = -129886.0;
  B.matrix[2][3] = -2484693.0;

  B.matrix[3][0] = 41460.0;
  B.matrix[3][1] = -1500628.0;
  B.matrix[3][2] = -82468.0;
  B.matrix[3][3] = 225336.0;

  res = s21_eq_matrix(&B, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(calc_compl_3) {
  int res = 0;
  matrix_t A = {0};
  matrix_t C = {0};

  s21_create_matrix(4, 3, &A);

  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 7.0;

  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 0.0;
  A.matrix[1][2] = 0.0;

  A.matrix[2][0] = 47.0;
  A.matrix[2][1] = 13.0;
  A.matrix[2][2] = 17.0;

  A.matrix[3][0] = 22.0;
  A.matrix[3][1] = 7.0;
  A.matrix[3][2] = 1.0;

  res = s21_calc_complements(&A, &C);

  s21_remove_matrix(&A);

  ck_assert_int_eq(res, ERR_COMPUTATION);
}
END_TEST

START_TEST(calc_compl_4) {
  int res = 0;
  matrix_t A = {0};
  matrix_t C = {0};

  s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);

  res = s21_calc_complements(&A, &C);

  ck_assert_int_eq(res, ERR_INVALID_MATRIX);
}
END_TEST

//Вычисление определителя

// START_TEST(determ_1) {
//   int res = 0;
//   double determinant = 0.0;
//   matrix_t A = {NULL, 0, 0};

//   res = s21_determinant(&A, &determinant);
//   ck_assert_int_eq(res, ERR_INVALID_MATRIX);
//   s21_remove_matrix(&A);
// }
// END_TEST

START_TEST(determ_2) {
  int res = 0;
  double determinant = 0.0;
  matrix_t A = {0};
  s21_create_matrix(1, 2, &A);

  res = s21_determinant(&A, &determinant);
  ck_assert_int_eq(res, ERR_COMPUTATION);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determ_3) {
  double determinant = 0.0;
  matrix_t A = {0};

  s21_create_matrix(1, 1, &A);
  matrix_filling(1.0, &A);

  s21_determinant(&A, &determinant);
  ck_assert_double_eq(determinant, 1.0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determ_4) {
  double determinant = 0.0;
  matrix_t A = {0};

  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 4000.87;
  A.matrix[0][1] = 454.0;
  A.matrix[0][2] = 4.0;

  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 1.897;
  A.matrix[1][2] = 3.0;

  A.matrix[2][0] = 0.000087;
  A.matrix[2][1] = 2.5668;
  A.matrix[2][2] = 1.0;

  s21_determinant(&A, &determinant);
  ck_assert_double_eq_tol(determinant, -24105.996724156,
                          0.00001);  // Изменение здесь
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determ_5) {
  double determinant = 0.0;
  matrix_t A = {0};

  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = -677700.0;
  A.matrix[0][1] = 654.0;

  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = -0.00001;

  s21_determinant(&A, &determinant);
  ck_assert_double_eq(determinant, -1301.223);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determ_6) {
  double determinant = 0.0;
  matrix_t A = {0};

  s21_create_matrix(8, 8, &A);
  matrix_filling(1.0, &A);

  s21_determinant(&A, &determinant);
  ck_assert_double_eq(determinant, 0.0);
  s21_remove_matrix(&A);
}
END_TEST

// START_TEST(determ_7) {
//   double determinant = 0.0;
//   matrix_t A = {0};

//   s21_create_matrix(3, 3, &A);

//   A.matrix[0][0] = 0.0;
//   A.matrix[0][1] = 454.0;
//   A.matrix[0][2] = 13.0;

//   A.matrix[1][0] = 2.0;
//   A.matrix[1][1] = 68.7;
//   A.matrix[1][2] = 8.0;

//   A.matrix[2][0] = 38.0;
//   A.matrix[2][1] = 65.3;
//   A.matrix[2][2] = 8.4;

//   s21_determinant(&A, &determinant);
//   ck_assert_int_eq((int)determinant * 10, (int)-98148.8 * 10);
//   s21_remove_matrix(&A);
// }
// END_TEST

// Поиск обратной матрицы

START_TEST(inverse_m_1) {
  int res = 0;
  matrix_t A = {0};
  matrix_t C = {0};
  matrix_t B = {0};

  s21_create_matrix(4, 4, &A);

  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 7.0;
  A.matrix[0][3] = 9.0;

  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 0.0;
  A.matrix[1][2] = 0.0;
  A.matrix[1][3] = 0.0;

  A.matrix[2][0] = 47.0;
  A.matrix[2][1] = 13.0;
  A.matrix[2][2] = 17.0;
  A.matrix[2][3] = 21.0;

  A.matrix[3][0] = 22.0;
  A.matrix[3][1] = 7.0;
  A.matrix[3][2] = 1.0;
  A.matrix[3][3] = 3.0;

  s21_inverse_matrix(&A, &C);

  s21_create_matrix(4, 4, &B);

  B.matrix[0][0] = 0.0;
  B.matrix[0][1] = 1.0;
  B.matrix[0][2] = 0.0;
  B.matrix[0][3] = 0.0;

  B.matrix[1][0] = -5.0 / 23.0;
  B.matrix[1][1] = -121.0 / 23.0;
  B.matrix[1][2] = 2.0 / 23.0;
  B.matrix[1][3] = 1.0 / 23.0;

  B.matrix[2][0] = -18.0 / 23.0;
  B.matrix[2][1] = -379.0 / 46.0;
  B.matrix[2][2] = 19.0 / 46.0;
  B.matrix[2][3] = -25.0 / 46.0;

  B.matrix[3][0] = 53.0 / 69.0;
  B.matrix[3][1] = 1061.0 / 138.0;
  B.matrix[3][2] = -47.0 / 138.0;
  B.matrix[3][3] = 19.0 / 46.0;

  res = s21_eq_matrix(&B, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(inverse_m_2) {
  int res;
  matrix_t A = {0};
  matrix_t C = {0};

  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 2;

  res = s21_inverse_matrix(&A, &C);

  ck_assert_int_eq(C.matrix[0][0] == (1.0 / A.matrix[0][0]), 1);
  ck_assert_int_eq(res, OK);

  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(inverse_m_3) {
  int res = 0;
  matrix_t A = {0};
  matrix_t C = {0};

  s21_create_matrix(3, 3, &A);
  matrix_filling(1.0, &A);

  res = s21_inverse_matrix(&A, &C);
  ck_assert_int_eq(res, ERR_COMPUTATION);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_m_4) {
  int res = 0;
  matrix_t A = {0};
  matrix_t C = {0};

  s21_create_matrix(3, 2, &A);
  matrix_filling(1.0, &A);

  res = s21_inverse_matrix(&A, &C);
  ck_assert_int_eq(res, ERR_COMPUTATION);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_m_5) {
  int res = 0;
  matrix_t A = {0};
  matrix_t C = {0};

  s21_create_matrix(3, 3, &A);
  matrix_filling(1.0, &A);
  s21_remove_matrix(&A);

  res = s21_inverse_matrix(&A, &C);

  ck_assert_int_eq(res, ERR_INVALID_MATRIX);
}
END_TEST

START_TEST(inverse_m_6) {
  int res = 0;
  matrix_t A = {0};
  matrix_t C = {0};
  matrix_t B = {0};

  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;

  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;

  A.matrix[2][0] = 8.0;
  A.matrix[2][1] = 6.0;
  A.matrix[2][2] = 9.0;

  s21_inverse_matrix(&A, &C);

  s21_create_matrix(3, 3, &B);

  B.matrix[0][0] = -3.0 / 5.0;
  B.matrix[0][1] = 0.0;
  B.matrix[0][2] = 1.0 / 5.0;

  B.matrix[1][0] = -4.0 / 5.0;
  B.matrix[1][1] = 1.0;
  B.matrix[1][2] = -2.0 / 5.0;

  B.matrix[2][0] = 16.0 / 15.0;
  B.matrix[2][1] = -2.0 / 3.0;
  B.matrix[2][2] = 1.0 / 5.0;

  res = s21_eq_matrix(&B, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

Suite *s21_matrix_suite(void) {
  Suite *suite;

  suite = suite_create("s21_matrix");
  TCase *tcase_core = tcase_create("Core");

  // Добавление теста в группу тестов.

  tcase_add_test(tcase_core, create_m_1);
  tcase_add_test(tcase_core, create_m_2);
  tcase_add_test(tcase_core, create_m_3);
  tcase_add_test(tcase_core, create_m_4);

  tcase_add_test(tcase_core, remove_m);

  tcase_add_test(tcase_core, eq_m_1);
  tcase_add_test(tcase_core, eq_m_2);
  tcase_add_test(tcase_core, eq_m_3);
  tcase_add_test(tcase_core, eq_m_4);
  tcase_add_test(tcase_core, eq_m_5);
  tcase_add_test(tcase_core, eq_m_6);

  tcase_add_test(tcase_core, sum_m_1);
  tcase_add_test(tcase_core, sum_m_2);
  tcase_add_test(tcase_core, sum_m_3);
  tcase_add_test(tcase_core, sum_m_4);
  tcase_add_test(tcase_core, sum_m_5);
  tcase_add_test(tcase_core, sum_m_6);
  tcase_add_test(tcase_core, sum_m_7);
  tcase_add_test(tcase_core, sum_m_8);

  tcase_add_test(tcase_core, sub_m_1);
  tcase_add_test(tcase_core, sub_m_2);
  tcase_add_test(tcase_core, sub_m_3);
  tcase_add_test(tcase_core, sub_m_4);
  tcase_add_test(tcase_core, sub_m_5);
  tcase_add_test(tcase_core, sub_m_6);
  tcase_add_test(tcase_core, sub_m_7);
  tcase_add_test(tcase_core, sub_m_8);

  tcase_add_test(tcase_core, mult_n_1);
  tcase_add_test(tcase_core, mult_n_2);
  tcase_add_test(tcase_core, mult_n_3);
  tcase_add_test(tcase_core, mult_n_4);
  tcase_add_test(tcase_core, mult_n_5);
  tcase_add_test(tcase_core, mult_n_6);

  tcase_add_test(tcase_core, mult_m_1);
  tcase_add_test(tcase_core, mult_m_2);
  tcase_add_test(tcase_core, mult_m_3);
  tcase_add_test(tcase_core, mult_m_4);
  tcase_add_test(tcase_core, mult_m_5);
  tcase_add_test(tcase_core, mult_m_6);
  tcase_add_test(tcase_core, mult_m_7);

  //   tcase_add_test(tcase_core, transp_1);
  tcase_add_test(tcase_core, transp_2);
  tcase_add_test(tcase_core, transp_3);

  tcase_add_test(tcase_core, calc_compl_1);
  tcase_add_test(tcase_core, calc_compl_2);
  tcase_add_test(tcase_core, calc_compl_3);
  tcase_add_test(tcase_core, calc_compl_4);

  //   tcase_add_test(tcase_core, determ_1);
  tcase_add_test(tcase_core, determ_2);
  tcase_add_test(tcase_core, determ_3);
  tcase_add_test(tcase_core, determ_4);
  tcase_add_test(tcase_core, determ_5);
  tcase_add_test(tcase_core, determ_6);
  //   tcase_add_test(tcase_core, determ_7);

  tcase_add_test(tcase_core, inverse_m_1);
  tcase_add_test(tcase_core, inverse_m_2);
  tcase_add_test(tcase_core, inverse_m_3);
  tcase_add_test(tcase_core, inverse_m_4);
  tcase_add_test(tcase_core, inverse_m_5);
  tcase_add_test(tcase_core, inverse_m_6);

  // Добавление теста в тестовый набор.

  suite_add_tcase(suite, tcase_core);

  return suite;
}

int main(void) {
  Suite *suite = s21_matrix_suite();
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_VERBOSE);

  // Получаем количество проваленных тестов.

  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  // Сигнализируем о том, что тестирование прошло успешно/неуспешно.

  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}