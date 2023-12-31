# Реализация функции библиотеки matrix.h

### Обзор
- Библиотека matrix.h предоставляет набор функций для выполнения основных операций с матрицами.

Основные функции
- create_matrix: Создание матрицы.
- remove_matrix: Очистка и уничтожение матрицы.
- eq_matrix: Сравнение двух матриц на равенство.
- sum_matrix: Сложение двух матриц.
- sub_matrix: Вычитание одной матрицы из другой.
- s21_mult_matrix: Умножение матриц.
- s21_mult_number: Умножение матрицы на число.
- s21_transpose: Транспонирование матрицы.
- s21_determinant: Вычисление определителя матрицы.
- s21_calc_complements: Вычисление матрицы алгебраических дополнений.
- s21_inverse_matrix: Поиск обратной матрицы.


### Требования
- Язык программирования: C стандарта C11.
- Компилятор: gcc.
- Стиль кодирования: Google Style.
- Префикс функций: s21_.
- Тестирование: unit-тесты с помощью библиотеки Check, покрытие не менее 80% для каждой функции.
- Сборка: Makefile с целями all, clean, test, s21_matrix.a, gcov_report.

### Особенности реализации
- Не использовать устаревшие и выведенные из употребления конструкции и функции. Следовать стандарту POSIX.1-2017.
- Библиотека должна быть статической и содержать заголовочный файл s21_matrix.h.
- Реализация в соответствии с принципами структурного программирования.
- Точность дробной части: максимум 6 знаков после запятой.
