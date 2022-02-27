//тесты для полинома
#include <gtest.h>
#include "arithmetic.h"

TEST(polinom, can_create_polinom) {
	EXPECT_NO_THROW(polinom p);
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