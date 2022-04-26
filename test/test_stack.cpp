// тесты для списка

#include "stack.h"
#include <gtest.h>
#include <algorithm>

TEST(list, can_create_list) {
	ASSERT_NO_THROW(list<int> l);
}

TEST(list, new_list_is_empty) {
	list<int> l;
	EXPECT_EQ(l.empty(), true);
}

TEST(list, can_create_list_from_other_list) {
	list<int> l1;
	for (int i = 0; i <= 10; i += 2) {
		l1.push_back(i);
	}
	list<int> l2(l1);
	auto it = l2.begin();
	int i = 0;
	while (it != l2.end()) {
		EXPECT_EQ((*it), i);
		++it;
		i += 2;
	}
}

TEST(list, push_back_correctly_add_element) {
	list<int> l;
	const int siz = 10;
	int arr[siz];
	for (int i = 0; i < siz; i++) {
		arr[i] = rand();
		l.push_back(arr[i]);
		auto it = l.begin();
		for (int j = 0; it != l.end(); ++it, j++) {
			EXPECT_EQ((*it), arr[j]);
		}
	}
}

TEST(list, insert_correctly_add_element) {
	list<int> l;
	const int siz = 10;
	int arr[siz];
	for (int i = 0; i < siz; i++)arr[i] = rand();
	int pos = rand() % siz;
	auto it = l.begin();
	for (int i = 0; i < siz; i++) {
		if (i != pos)l.push_back(arr[i]);
		else {
			it = l.end();
			--it;
		}
	}
	l.insert(it, arr[pos]);
	int index = 0;
	it = l.begin();
	while (it != l.end()) {
		EXPECT_EQ((*it), arr[index]);
		++it;
		++index;
	}
}

TEST(list, insert_change_size) {
	list<int> l;
	for (int i = 1; i <= 10; i++) {
		l.insert(l.begin(), rand());
		EXPECT_EQ(l.size(), i);
	}
}

TEST(list, push_back_change_size) {
	list<int> l;
	for (int i = 1; i <= 10; i++) {
		l.push_back(rand());
		EXPECT_EQ(l.size(), i);
	}
}

TEST(list, pop_back_change_size) {
	list<int> l;
	for (int i = 1; i <= 10; i++) {
		l.push_back(rand());
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
		l.push_front(rand());
		EXPECT_EQ(l.size(), i);
	}
}

TEST(list, pop_front_change_size) {
	list<int> l;
	for (int i = 1; i <= 10; i++) {
		l.push_front(rand());
	}
	for (int i = 1; i <= 10; i++) {
		l.pop_front();
		EXPECT_EQ(l.size(), 10 - i);
	}
}
TEST(list, push_front_correctly_add_element) {
	list<int> l;
	const int siz = 10;
	int arr[siz];
	for (int i = siz - 1; i >= 0; i--) {
		arr[i] = rand();
		l.push_front(arr[i]);
		auto it = l.begin();
		for (int j = i; it != l.end(); ++it, j++) {
			EXPECT_EQ((*it), arr[j]);
		}
	}
}

TEST(list, pop_front_throw_exception_if_list_is_empty) {
	list<int> l;
	EXPECT_ANY_THROW(l.pop_front());
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
	const int siz = 10;
	int arr[siz];
	for (int i = 0; i < siz; i++) {
		arr[i] = rand();
	}
	sort(arr, arr + siz);
	for (int i = 0; i < siz; i++) {
		if (i % 2) {
			l1.push_back(arr[i]);
		}
		else {
			l2.push_back(arr[i]);
		}
	}
	l1.merge(l2);
	int index = 0;
	auto it = l1.begin();
	while (it != l1.end()) {
		EXPECT_EQ((*it), arr[index]);
		++it;
		++index;
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

TEST(list, clear_change_size) {
	list<int> l;
	l.clear();
	EXPECT_EQ(l.size(), 0);
}