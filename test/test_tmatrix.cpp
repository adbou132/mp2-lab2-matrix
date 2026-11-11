#include "tmatrix.h"
#include <gtest/gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length) // можно ли создать матрицу 
{
    ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix) // если матрица больше макс
{
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length) // отрицатеьный размер
{
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix) // копирование
{
    TDynamicMatrix<int> m(5);
    ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one) // скопированная матрицв равна исходной
{
    TDynamicMatrix<int> m(3);
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
            m[i][j] = static_cast<int>(i * 3 + j);

    TDynamicMatrix<int> copy(m);
    EXPECT_TRUE(m == copy);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory) // копмия имеет свою память
{
    TDynamicMatrix<int> m(3);
    m[0][0] = 42;

    TDynamicMatrix<int> copy(m);
    copy[0][0] = 100;

    EXPECT_EQ(m[0][0], 42);
    EXPECT_EQ(copy[0][0], 100);
}


TEST(TDynamicMatrix, throws_when_set_element_with_negative_index) // отриц индекс
{
    TDynamicMatrix<int> m(3);
    EXPECT_ANY_THROW(m.at(static_cast<size_t>(-1)));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index) // выход за границы по индексу
{
    TDynamicMatrix<int> m(3);
    EXPECT_ANY_THROW(m.at(10));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself) // самоприсваивание
{
    TDynamicMatrix<int> m(3);
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
            m[i][j] = static_cast<int>(i + j);

    TDynamicMatrix<int>& ref = m;
    m = ref;

    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
            EXPECT_EQ(m[i][j], static_cast<int>(i + j));
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size) // копирование матриц одного размера
{
    TDynamicMatrix<int> a(3), b(3);
    a[0][0] = 42; a[2][2] = 99;
    b = a;

    EXPECT_EQ(b[0][0], 42);
    EXPECT_EQ(b[2][2], 99);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size) // меняем размер левой матрицы
{
    TDynamicMatrix<int> a(3), b(7);
    b = a;
    EXPECT_EQ(b.size(), 3u);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size) // полная проверка
{
    TDynamicMatrix<int> a(3), b(7);
    a[1][1] = 5;
    b = a;
    EXPECT_EQ(b.size(), 3u);
    EXPECT_EQ(b[1][1], 5);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true) // true для одинаковвых матриц
{
    TDynamicMatrix<int> a(3), b(3);
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j) {
            a[i][j] = static_cast<int>(i + j);
            b[i][j] = static_cast<int>(i + j);
        }

    EXPECT_TRUE(a == b);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true) // сравнение матрицы с собой же
{
    TDynamicMatrix<int> m(3);
    EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal) // матрицы разного размера не р
{
    TDynamicMatrix<int> a(3), b(4);
    EXPECT_FALSE(a == b);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size) // сложение матриц по элементу
{
    TDynamicMatrix<int> a(3), b(3);
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j) {
            a[i][j] = 1;
            b[i][j] = 2;
        }

    TDynamicMatrix<int> r = a + b;
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
            EXPECT_EQ(r[i][j], 3);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size) // исключенме при разных размерах
{
    TDynamicMatrix<int> a(3), b(4);
    EXPECT_ANY_THROW(a + b);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size) // вычитание по элементу
{
    TDynamicMatrix<int> a(3), b(3);
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j) {
            a[i][j] = 5;
            b[i][j] = 2;
        }

    TDynamicMatrix<int> r = a - b;
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
            EXPECT_EQ(r[i][j], 3);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size) // исключенме
{
    TDynamicMatrix<int> a(3), b(4);
    EXPECT_ANY_THROW(a - b);
}