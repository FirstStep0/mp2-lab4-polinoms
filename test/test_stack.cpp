// тесты для списка

#include "stack.h"
#include <gtest.h>

TEST(list, can_create_list) {
	ASSERT_NO_THROW(list<int> l);
}

TEST(list, new_list_is_empty) {
	list<int> l;
	EXPECT_EQ(l.empty(), true);
}

TEST(list, push_back_correctly_add_element) {
	list<int> l;
	for (int i = 0; i < 10; i++) {
		l.push_back(i);
		EXPECT_EQ(l.back(), i);
	}
}
TEST(list, push_back_change_size) {
	list<int> l;
	for (int i = 1; i <= 10; i++) {
		l.push_back(i);
		EXPECT_EQ(l.size(), i);
	}
}

TEST(list, pop_back_change_size) {
	list<int> l;
	for (int i = 1; i <= 10; i++) {
		l.push_back(i);
	}
	for (int i = 1; i <= 10; i++) {
		l.pop_back();
		EXPECT_EQ(l.size(), 10 - i);
	}
}

TEST(list, pop_back_throw_exception_if_list_is_empty) {
	list<int> l;
	EXPECT_ANY_THROW(l.pop_back());
}

TEST(list, push_front_change_size) {
	list<int> l;
	for (int i = 1; i <= 10; i++) {
		l.push_front(i);
		EXPECT_EQ(l.size(), i);
	}
}

TEST(list, pop_front_change_size) {
	list<int> l;
	for (int i = 1; i <= 10; i++) {
		l.push_front(i);
	}
	for (int i = 1; i <= 10; i++) {
		l.pop_front();
		EXPECT_EQ(l.size(), 10 - i);
	}
}
TEST(list, push_front_correctly_add_element) {
	list<int> l;
	for (int i = 1; i <= 10; i++) {
		l.push_front(i);
		EXPECT_EQ(l.front(), i);
	}
	auto it = l.begin();
	int i = 10;
	while (it != l.end()) {
		EXPECT_EQ((*it), i);
		++it;
		--i;
	}
}

TEST(list, pop_front_throw_exception_if_list_is_empty) {
	list<int> l;
	EXPECT_ANY_THROW(l.pop_front());
}

TEST(list, can_create_list_from_other_list) {
	list<int> l1;
	EXPECT_NO_THROW(list<int> l2(l1));
}

TEST(list, list_and_the_copied_list_are_equal) {
	list<int> l1;
	for (int i = 0; i < 10; i++) {
		l1.push_back(i);
	}
	list<int> l2(l1);
	auto it = l2.begin();
	int i = 0;
	while (it != l2.end()) {
		EXPECT_EQ((*it), i);
		++it;
		++i;
	}
}

TEST(list, clear_list_is_empty) {
	list<int> l;
	for (int i = 1; i <= 10; i++) {
		l.push_back(i);
	}
	l.clear();
	EXPECT_EQ(l.size(), 0);
	EXPECT_EQ(l.begin(), l.end());
}
TEST(list, merge_is_correctly) {
	list<int> l1, l2;
	l1.push_back(1);
	l1.push_back(3);
	l1.push_back(5);

	l2.push_back(2);
	l2.push_back(4);

	l1.merge(l2);
	int i = 1;
	auto it = l1.begin();
	while (it != l1.end()) {
		EXPECT_EQ((*it), i);
		++it;
		++i;
	}
}
TEST(list, sort_is_correctly) {
	list<int> l1;
	srand(time(0));
	for (int j = 0; j < 25; j++) {
		for (int i = 0; i < 20; i++) {
			l1.push_back(rand());
		}
		l1.sort();
		auto it2 = l1.begin();
		auto itLast = l1.end();
		--itLast;
		while (it2 != itLast) {
			auto it1 = it2++;
			EXPECT_TRUE((*it1 <= *it2));
		}
		l1.clear();
	}
}