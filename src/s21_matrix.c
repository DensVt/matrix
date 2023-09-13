#include "s21_matrix.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows <= 0 || columns <= 0 || result == NULL) {
    return 1;  // возвращаем ошибку, если матрица не корректна
  }

  result->rows = rows;
  result->columns = columns;
  result->matrix = malloc(rows * sizeof(double *));
  if (result->matrix == NULL) {
    return 1;  // возвращаем ошибку, если выделение памяти не удалось
  }

  for (int i = 0; i < rows; i++) {
    result->matrix[i] = malloc(columns * sizeof(double));
    if (result->matrix[i] == NULL) {
      // если выделение памяти не удалось, освобождаем то, что уже выделили
      for (int j = 0; j < i; j++) {
        free(result->matrix[j]);
      }
      free(result->matrix);
      return 1;  // возвращаем ошибку
    }
  }

  return 0;  // если все прошло успешно, возвращаем 0
}

void s21_remove_matrix(matrix_t *A) {
  if (A == NULL || A->matrix == NULL) {
    return;  // ничего не делаем, если матрица не корректна
  }

  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);  // освобождаем каждую строку матрицы
  }

  free(A->matrix);  // затем освобождаем массив строк

  A->rows = 0;
  A->columns = 0;
  A->matrix = NULL;  // устанавливаем все поля структуры в нули
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *C) {
  // Проверяем, что матрицы имеют одинаковые размеры
  if (A->rows != B->rows || A->columns != B->columns) return ERR_COMPUTATION;

  // Выделяем память для результирующей матрицы
  C->rows = A->rows;
  C->columns = A->columns;
  C->matrix = (double **)malloc(C->rows * sizeof(double *));
  for (int i = 0; i < C->rows; ++i)
    C->matrix[i] = (double *)malloc(C->columns * sizeof(double));

  // Вычитаем матрицы
  for (int i = 0; i < A->rows; ++i)
    for (int j = 0; j < A->columns; ++j)
      C->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];

  return SUCCESS;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  // Проверяем, что матрицы имеют одинаковые размеры
  if (A->rows != B->rows || A->columns != B->columns) return 0;

  // Проверяем, что все элементы матриц равны
  for (int i = 0; i < A->rows; ++i)
    for (int j = 0; j < A->columns; ++j)
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) >
          1e-6)  // Используем проверку равенства с учетом погрешности
        return 0;

  // Если все элементы равны, возвращаем SUCCESS
  return 1;
}

// Функция для суммирования двух матриц.
// Они должны иметь одинаковые размеры, чтобы операция могла быть выполнена.
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  // Проверяем, совпадают ли размеры двух матриц.
  if (A->rows != B->rows || A->columns != B->columns) return ERR_COMPUTATION;
  // Создаем матрицу result с теми же размерами, что и матрицы A и B.
  if (s21_create_matrix(A->rows, A->columns, result) != OK)
    return ERR_INVALID_MATRIX;
  // Проходим по каждому элементу матрицы и добавляем соответствующие элементы
  // из матриц A и B.
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }

  return OK;
}

// Функция для умножения матрицы на число.
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  // Создаем матрицу result с теми же размерами, что и матрица A.
  if (s21_create_matrix(A->rows, A->columns, result) != OK)
    return ERR_INVALID_MATRIX;
  // Проходим по каждому элементу матрицы и умножаем его на заданное число.
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }

  return OK;
}

// Функция для умножения двух матриц.
// Количество столбцов первой матрицы должно быть равно количеству строк второй
// матрицы, чтобы операция могла быть выполнена.
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  // Проверяем, совпадают ли размеры для умножения матриц.
  if (A->columns != B->rows) return ERR_COMPUTATION;
  // Создаем матрицу result с количеством строк, равным количеству строк матрицы
  // A, и количеством столбцов, равным количеству столбцов матрицы B.
  if (s21_create_matrix(A->rows, B->columns, result) != OK)
    return ERR_INVALID_MATRIX;
  // Выполняем умножение матриц.
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      // Суммируем произведения соответствующих элементов строки матрицы A и
      // столбца матрицы B.
      result->matrix[i][j] = 0;
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }

  return OK;
}

// Функция для транспонирования матрицы.
// Размеры исходной и результатирующей матрицы будут иметь противоположное
// отношение (столбцы становятся строками и наоборот).
int s21_transpose(matrix_t *A, matrix_t *result) {
  // Создаем матрицу result с количеством строк, равным количеству столбцов
  // матрицы A, и количеством столбцов, равным количеству строк матрицы A.
  if (s21_create_matrix(A->columns, A->rows, result) != OK)
    return ERR_INVALID_MATRIX;
  // Проходим по каждому элементу матрицы и присваиваем его транспонированной
  // позиции в результате.
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }

  return OK;
}
// Вспомогательная функция для перестановки строк матрицы
void s21_swap_rows(matrix_t *A, int i, int j) {
  double *temp = A->matrix[i];
  A->matrix[i] = A->matrix[j];
  A->matrix[j] = temp;
}

// Вспомогательная функция для вычисления определителя с помощью метода Гаусса
double s21_calc_determinant(matrix_t *A) {
  double det = 1.0;

  // Приводим матрицу к верхнетреугольному виду
  for (int i = 0; i < A->rows; ++i) {
    // Ищем максимальный элемент в текущем столбце
    int max_row = i;
    for (int j = i + 1; j < A->rows; ++j) {
      if (fabs(A->matrix[j][i]) > fabs(A->matrix[max_row][i])) {
        max_row = j;
      }
    }

    // Если максимальный элемент равен нулю, то определитель равен нулю
    if (fabs(A->matrix[max_row][i]) < 1e-6) {
      return 0.0;
    }

    // Меняем местами строки, если необходимо
    if (i != max_row) {
      s21_swap_rows(A, i, max_row);
      det *= -1;  // Меняем знак определителя при перестановке строк
    }

    // Нормализуем строку
    double div = A->matrix[i][i];
    for (int j = 0; j < A->columns; ++j) {
      A->matrix[i][j] /= div;
    }
    det *= div;

    // Обнуляем элементы ниже главной диагонали
    for (int j = i + 1; j < A->rows; ++j) {
      double mult = A->matrix[j][i];
      for (int k = i; k < A->columns; ++k) {
        A->matrix[j][k] -= mult * A->matrix[i][k];
      }
    }
  }

  return det;
}

int s21_determinant(matrix_t *A, double *result) {
  if (A->rows != A->columns) return ERR_COMPUTATION;

  // Клонируем матрицу, так как метод Гаусса модифицирует исходную матрицу
  matrix_t clone;
  s21_create_matrix(A->rows, A->columns, &clone);
  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < A->columns; ++j) {
      clone.matrix[i][j] = A->matrix[i][j];
    }
  }

  *result = s21_calc_determinant(&clone);
  s21_remove_matrix(&clone);
  return OK;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (A->rows != A->columns) return ERR_COMPUTATION;

  // Инициализация выходной матрицы
  if (s21_create_matrix(A->rows, A->columns, result) != OK)
    return ERR_INVALID_MATRIX;

  matrix_t minor;
  if (s21_create_matrix(A->rows - 1, A->columns - 1, &minor) != OK)
    return ERR_INVALID_MATRIX;

  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < A->columns; ++j) {
      // Создаем минорную матрицу для элемента A[i][j]
      int row_offset = 0;
      for (int x = 0; x < A->rows; ++x) {
        if (x == i) {
          row_offset = 1;
          continue;
        }

        int column_offset = 0;
        for (int y = 0; y < A->columns; ++y) {
          if (y == j) {
            column_offset = 1;
            continue;
          }
          // Добавление условия для предотвращения выхода за пределы массива
          if ((x - row_offset) < minor.rows &&
              (y - column_offset) < minor.columns)
            minor.matrix[x - row_offset][y - column_offset] = A->matrix[x][y];
        }
      }

      // Вычисляем определитель минорной матрицы
      double minor_det;
      if (s21_determinant(&minor, &minor_det) != OK) {
        s21_remove_matrix(&minor);
        return ERR_COMPUTATION;
      }

      // Элемент матрицы алгебраических дополнений - это определитель минорной
      // матрицы, умноженный на (-1)^(i+j)
      result->matrix[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * minor_det;
    }
  }
  s21_remove_matrix(&minor);
  return OK;
}

// Функция проверяет, является ли матрица A недействительной.
int error_matrix(const matrix_t *A) {
  // Если матрица A не существует (то есть указатель на нее равен NULL), она
  // является недействительной.
  if (A == NULL) return ERR_INVALID_MATRIX;
  // Если сама матрица, количество строк или столбцов в матрице равны NULL или
  // меньше 0, матрица также является недействительной.
  if (A->matrix == NULL || A->rows <= 0 || A->columns <= 0)
    return ERR_INVALID_MATRIX;
  // Если все проверки пройдены, матрица считается действительной.
  return OK;
}

// Функция  вычисляет обратную матрицу для матрицы A и сохраняет ее в результат.
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = ERR_INVALID_MATRIX;
  // Если матрица A не является квадратной, вычисление обратной матрицы
  // невозможно.
  if (A->rows != A->columns) res = ERR_COMPUTATION;
  // Если матрица A является матрицей 1x1, обратная матрица является просто
  // обратным числом элемента матрицы.
  if (A->rows == 1 && A->columns == 1) {
    s21_create_matrix(A->rows, A->columns, result);
    result->matrix[0][0] = 1 / A->matrix[0][0];
    res = OK;
  }
  // Если матрица A не содержит ошибок, является квадратной и имеет размерность
  // больше 1, мы продолжаем вычисления.
  if (!error_matrix(A) && A->rows == A->columns && A->rows > 1) {
    double determinant = 0.0;
    // Вычисляем определитель матрицы A.
    res = s21_determinant(A, &determinant);
    // Если определитель близок к нулю, обратной матрицы не существует.
    if (fabs(determinant) > 1e-7 && !res) {
      matrix_t calc_complements = {0};
      matrix_t transpose = {0};
      res = s21_calc_complements(A, &calc_complements);
      if (!res) {
        s21_transpose(&calc_complements, &transpose);
        s21_create_matrix(A->rows, A->columns, result);
        // Затем каждый элемент результатирующей матрицы вычисляется как
        // соответствующий элемент транспонированной матрицы, деленный на
        // определитель.
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            // Заполняем элементы матрицы результатов путем деления каждого
            // элемента транспонированной матрицы на определитель.
            result->matrix[i][j] = (1 / determinant) * transpose.matrix[i][j];
            res = OK;
          }
        }
      }
      // Удаляем вспомогательные матрицы calc_complements и transpose, чтобы
      // освободить память.
      s21_remove_matrix(&calc_complements);
      s21_remove_matrix(&transpose);
    } else {
      // Если определитель близок к нулю или вычисление определителя завершилось
      // ошибкой, возвращаем ошибку вычисления.
      res = ERR_COMPUTATION;
    }
  }
  // Возвращаем результат операции: либо OK, если обратная матрица была успешно
  // вычислена, либо код ошибки в противном случае.
  return res;
}
