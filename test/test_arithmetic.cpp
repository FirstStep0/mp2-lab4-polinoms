//тесты для полинома
#include <gtest.h>
#include "arithmetic.h"

TEST(polinom, can_create_polinom) {
	EXPECT_NO_THROW(polinom p);
}

TEST(polinom, size_not_change_if_monom_is_equal_zero) {
	polinom p;
	int max_rand = 10;
	int count = rand() % max_rand;
	for (int i = 0; i < count; i++) {
		p += monom(rand() % 10, rand() % 10, rand() % 10, rand() % 10);
	}
	int size1 = p.size();
	p += monom(0, 3, 3, 3);
	int size2 = p.size();
	EXPECT_EQ(size1, size2);
}

TEST(polinom, size_change_if_monom_is_not_equal_zero) {
	polinom p;
	int max_rand = 10;
	int count = rand() % max_rand;
	for (int i = 0; i < count; i++) {
		p += monom(rand() % 10, rand() % 10, rand() % 10, rand() % 10);
	}
	int size1 = p.size();
	p += monom(3, 3, 3, 3);
	int size2 = p.size();
	EXPECT_EQ(size1 + 1, size2);
}

TEST(polinom, multiply_is_correct) {
	polinom a;
	a += monom(1, 2);
	a += monom(2, 4);
	polinom b;
	b += monom(3, 2);
	polinom r = a * b;
	polinom d;
	d += monom(3, 4);
	d += monom(6, 6);
	EXPECT_EQ(r, d);
}

TEST(polinom, add_operator_is_correct) {
	polinom a;
	a += monom(-1, 2, 0, 0);
	a += monom(2, 4, 0, 0);
	polinom b;
	b += monom(3, 2, 0, 0);
	b += monom(3, 2, 3, 0);
	polinom r = a + b;
	polinom d;
	d += monom(2, 4, 0, 0);
	d += monom(3, 2, 3, 0);
	d += monom(2, 2, 0, 0);
	EXPECT_EQ(r, d);
}

TEST(polinom, sub_operator_is_correct) {
	polinom a;
	a += monom(-1, 2, 0, 0);
	a += monom(2, 4, 0, 0);
	a += monom(2, 2, 3, 0);
	a += monom(1, 0, 7, 0);
	polinom b;
	b += monom(3, 2, 0, 0);
	b += monom(3, 2, 3, 0);
	b += monom(1, 0, 7, 0);
	polinom r = a - b;
	polinom d;
	d += monom(2, 4, 0, 0);
	d += monom(-1, 2, 3, 0);
	d += monom(-4, 2, 0, 0);
	EXPECT_EQ(r, d);
}

TEST(polinom, add_operator_combines_the_same_monom) {
	polinom a, b;
	a += monom(1, 1);
	b += monom(5, 1);
	polinom r = a + b;
	polinom d;
	d += monom(6, 1);
	EXPECT_EQ(r, d);
}

TEST(polinom, sub_operator_combines_the_same_monom) {
	polinom a, b;
	a += monom(1, 1);
	b += monom(2, 1);
	polinom r = a - b;
	polinom d;
	d += monom(-1, 1);
	EXPECT_EQ(r, d);
}
TEST(polinom, add_operator_delete_zero_monom) {
	polinom a, b;
	a += monom(1, 1);
	b += monom(-1, 1);
	polinom r = a + b;
	polinom d;
	EXPECT_EQ(r, d);
}
TEST(polinom, sub_operator_delete_zero_monom) {
	polinom a, b;
	a += monom(1, 1);
	b += monom(1, 1);
	polinom r = a - b;
	polinom d;
	EXPECT_EQ(r, d);
}