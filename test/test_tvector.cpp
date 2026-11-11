#include "tmatrix.h"
#include <gtest/gtest.h>

TEST(TDynamicVector, copied_vector_is_equal_to_source_one) //конструктор копирования
{
    TDynamicVector<int> v(10);
    for (int i = 0; i < 10; ++i) v[i] = i;
    TDynamicVector<int> v1(v);
    EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory) // копия не делит память с исходным вектором
{
    TDynamicVector<int> v(10);
    TDynamicVector<int> v1(v);
    v[0] = 20;
    EXPECT_NE(v1[0], 20);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index) // выход за границу снизу
{
    TDynamicVector<int> v(5);
    EXPECT_ANY_THROW(v.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index) // выход за границу сверху
{
    TDynamicVector<int> v(5);
    EXPECT_ANY_THROW(v.at(10));
}

TEST(TDynamicVector, can_assign_vector_to_itself) // самоприсваивание
{
    TDynamicVector<int> v(5);
    for (int i = 0; i < 5; ++i) v[i] = i;
    v = v;
    for (int i = 0; i < 5; ++i) EXPECT_EQ(v[i], i);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size) // присваивание разных по размеру
{
    TDynamicVector<int> a(3), b(3);
    a[0] = 1; a[1] = 2; a[2] = 3;
    b = a;
    EXPECT_EQ(a, b);
}

TEST(TDynamicVector, assign_operator_change_vector_size) // изменение размера при присваивании 
{
    TDynamicVector<int> a(3), b(7);
    b = a;
    EXPECT_EQ(b.size(), 3);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size) // присваивание разных размеров
{
    TDynamicVector<int> a(3), b(7);
    a[0] = 1; a[1] = 2; a[2] = 3;
    b = a;
    EXPECT_EQ(b.size(), 3u);
    EXPECT_EQ(b[0], 1);
}

TEST(TDynamicVector, compare_equal_vectors_return_true) // сравнение равных векторов
{
    TDynamicVector<int> a(3), b(3);
    a[0] = 1; a[1] = 2; a[2] = 3;
    b[0] = 1; b[1] = 2; b[2] = 3;
    EXPECT_TRUE(a == b);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true) // сравнение с самим собой
{
    TDynamicVector<int> a(3);
    EXPECT_TRUE(a == a);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal) // не равные из за разных размеров
{
    TDynamicVector<int> a(3), b(4);
    EXPECT_TRUE(a != b);
}

TEST(TDynamicVector, can_add_scalar_to_vector) // сложение с числом
{
    TDynamicVector<int> a(3); a[0] = 1; a[1] = 2; a[2] = 3;
    TDynamicVector<int> r = a + 10;
    EXPECT_EQ(r[0], 11); EXPECT_EQ(r[1], 12); EXPECT_EQ(r[2], 13);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector) // вычитание числа
{
    TDynamicVector<int> a(3); a[0] = 10; a[1] = 20; a[2] = 30;
    TDynamicVector<int> r = a - 5;
    EXPECT_EQ(r[0], 5); EXPECT_EQ(r[1], 15); EXPECT_EQ(r[2], 25);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector) // умножение вектора на число
{
    TDynamicVector<int> a(3); a[0] = 1; a[1] = 2; a[2] = 3;
    TDynamicVector<int> r = a * 2;
    EXPECT_EQ(r[0], 2); EXPECT_EQ(r[1], 4); EXPECT_EQ(r[2], 6);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size) // сложение векторов
{
    TDynamicVector<int> a(3), b(3);
    a[0] = 1; a[1] = 2; a[2] = 3;
    b[0] = 4; b[1] = 5; b[2] = 6;
    TDynamicVector<int> r = a + b;
    EXPECT_EQ(r[0], 5); EXPECT_EQ(r[1], 7); EXPECT_EQ(r[2], 9);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size) // разные размеры
{
    TDynamicVector<int> a(3), b(4);
    EXPECT_ANY_THROW(a + b);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size) // вычитание векторов
{
    TDynamicVector<int> a(3), b(3);
    a[0] = 5; a[1] = 7; a[2] = 9;
    b[0] = 1; b[1] = 2; b[2] = 3;
    TDynamicVector<int> r = a - b;
    EXPECT_EQ(r[0], 4); EXPECT_EQ(r[1], 5); EXPECT_EQ(r[2], 6);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size) // разные размервы
{
    TDynamicVector<int> a(3), b(4);
    EXPECT_ANY_THROW(a - b);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size) // скалярное произведение
{
    TDynamicVector<int> a(3), b(3);
    a[0] = 1; a[1] = 2; a[2] = 3;
    b[0] = 4; b[1] = 5; b[2] = 6;
    int r = a * b;
    EXPECT_EQ(r, 1 * 4 + 2 * 5 + 3 * 6);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size) // разные размеры
{
    TDynamicVector<int> a(3), b(4);
    EXPECT_ANY_THROW(a * b);
}