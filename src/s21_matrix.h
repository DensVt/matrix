#ifndef S21_MATRIX_H
#define S21_MATRIX_H
#include <stdlib.h>

// Определение структуры матрицы
typedef struct matrix_struct {
  double **matrix;  // Двумерный массив, представляющий матрицу
  int rows;     // Количество строк матрицы
  int columns;  // Количество столбцов матрицы
} matrix_t;

// Определение констант ошибок
#define OK 0
#define ERR_INVALID_MATRIX 1
#define ERR_COMPUTATION 2

// Определение констант успешного выполнения и неуспеха
#define SUCCESS 1
#define FAILURE 0

// Прототипы функций работы с матрицами
int s21_create_matrix(int rows, int columns,
                      matrix_t *result);  // Создает матрицу с заданным
                                          // количеством строк и столбцов
void s21_remove_matrix(
    matrix_t *A);  // Удаляет матрицу, освобождая выделенную под нее память
int s21_eq_matrix(matrix_t *A,
                  matrix_t *B);  // Сравнивает две матрицы на равенство
int s21_sum_matrix(matrix_t *A, matrix_t *B,
                   matrix_t *result);  // Складывает две матрицы
int s21_sub_matrix(matrix_t *A, matrix_t *B,
                   matrix_t *result);  // Вычитает матрицу B из матрицы A
int s21_mult_number(matrix_t *A, double number,
                    matrix_t *result);  // Умножает матрицу на число
int s21_mult_matrix(matrix_t *A, matrix_t *B,
                    matrix_t *result);  // Умножает матрицу A на матрицу B
int s21_transpose(matrix_t *A,
                  matrix_t *result);  // Вычисляет транспонированную матрицу
int s21_calc_complements(
    matrix_t *A,
    matrix_t *result);  // Вычисляет матрицу алгебраических дополнений
int s21_determinant(matrix_t *A,
                    double *result);  // Вычисляет определитель матрицы
int s21_inverse_matrix(matrix_t *A,
                       matrix_t *result);  // Вычисляет обратную матрицу

#endif