/**
 * @file test_double_linked_list.cpp
 * @brief Unit tests for DoubleLinkedList container
 * 
 * @details Comprehensive test suite that validates all
 * DoubleLinkedList operations including constructors, bidirectional
 * traversal, element access, insertion, deletion, and edge case
 * handling.
 * 
 * @ingroup testing
 * @author Super Library Team
 * @date 2024
 */

#include <iostream>
#include <cassert>
#include <stdexcept>
#include "test_colors.hpp"
#include "super_lib.hpp"

/**
 * @brief Tests DoubleLinkedList constructors
 * 
 * @details Verifies default constructor, fill constructor, copy
 * constructor, and move constructor. Validates proper initialization
 * of size, head, and tail pointers.
 * 
 * @ingroup testing
 */
void test_double_linked_list_constructor() {
	TEST_GROUP("DoubleLinkedList constructors");
	
	DoubleLinkedList<int> l1;
	assert(l1.size() == 0);
	assert(l1.empty());
	assert(l1.head() == nullptr);
	assert(l1.tail() == nullptr);
	
	DoubleLinkedList<int> l2(5, 10);
	assert(l2.size() == 5);
	for (size_t i = 0; i < 5; ++i)
		assert(l2[i] == 10);
	
	DoubleLinkedList<int> l3(l2);
	assert(l3.size() == l2.size());
	for (size_t i = 0; i < l3.size(); ++i)
		assert(l3[i] == l2[i]);
	
	DoubleLinkedList<int> l4(std::move(l3));
	assert(l4.size() == 5);
	assert(l3.size() == 0);
	
	TEST_PASS("DoubleLinkedList constructors");
}

/**
 * @brief Tests DoubleLinkedList operators
 * 
 * @details Verifies subscript operator, copy assignment, and move
 * assignment. Tests bounds checking and proper data transfer during
 * assignments.
 * 
 * @ingroup testing
 */
void test_double_linked_list_operators() {
	TEST_GROUP("DoubleLinkedList operators");
	
	DoubleLinkedList<int> l1(3, 5);
	
	assert(l1[0] == 5);
	l1[1] = 10;
	assert(l1[1] == 10);
	
	try {
		l1[10];
		assert(false && "Should throw exception");
	} catch (const std::out_of_range&) {
	}
	
	DoubleLinkedList<int> l2;
	l2 = l1;
	assert(l2.size() == l1.size());
	assert(l2[1] == 10);
	
	DoubleLinkedList<int> l3;
	l3 = std::move(l2);
	assert(l3.size() == 3);
	assert(l2.size() == 0);
	
	TEST_PASS("DoubleLinkedList operators");
}

/**
 * @brief Tests DoubleLinkedList add and insert operations
 * 
 * @details Verifies add() method for appending elements and insert()
 * method for inserting elements at specific positions. Tests
 * boundary conditions and exception handling.
 * 
 * @ingroup testing
 */
void test_double_linked_list_add_insert() {
	TEST_GROUP("DoubleLinkedList add and insert");
	
	DoubleLinkedList<int> l;
	
	l.add(1);
	l.add(2);
	l.add(3);
	assert(l.size() == 3);
	assert(l[0] == 1);
	assert(l[1] == 2);
	assert(l[2] == 3);
	
	l.insert(0, 0);
	assert(l.size() == 4);
	assert(l[0] == 0);
	assert(l[1] == 1);
	
	l.insert(2, 99);
	assert(l.size() == 5);
	assert(l[2] == 99);
	
	l.insert(l.size(), 100);
	assert(l[l.size() - 1] == 100);
	
	try {
		l.insert(100, 1);
		assert(false && "Should throw exception");
	} catch (const std::out_of_range&) {
	}
	
	TEST_PASS("DoubleLinkedList add and insert");
}

/**
 * @brief Tests DoubleLinkedList erase operation
 * 
 * @details Verifies erase() method for removing elements at various
 * positions (beginning, middle, end). Tests return value and proper
 * bidirectional link adjustment.
 * 
 * @ingroup testing
 */
void test_double_linked_list_erase() {
	TEST_GROUP("DoubleLinkedList erase");
	
	DoubleLinkedList<int> l;
	l.add(1);
	l.add(2);
	l.add(3);
	l.add(4);
	l.add(5);
	
	int erased = l.erase(2);
	assert(erased == 3);
	assert(l.size() == 4);
	assert(l[2] == 4);
	
	erased = l.erase(0);
	assert(erased == 1);
	assert(l.size() == 3);
	
	erased = l.erase(l.size() - 1);
	assert(erased == 5);
	assert(l.size() == 2);
	
	try {
		l.erase(100);
		assert(false && "Should throw exception");
	} catch (const std::out_of_range&) {
	}
	
	TEST_PASS("DoubleLinkedList erase");
}

/**
 * @brief Tests DoubleLinkedList clear operation
 * 
 * @details Verifies clear() method properly deallocates all nodes
 * and resets size, head, and tail pointers.
 * 
 * @ingroup testing
 */
void test_double_linked_list_clear() {
	TEST_GROUP("DoubleLinkedList clear");
	
	DoubleLinkedList<int> l;
	l.add(1);
	l.add(2);
	l.add(3);
	
	l.clear();
	assert(l.size() == 0);
	assert(l.empty());
	assert(l.head() == nullptr);
	assert(l.tail() == nullptr);
	
	TEST_PASS("DoubleLinkedList clear");
}

/**
 * @brief Tests DoubleLinkedList at() method
 * 
 * @details Verifies bounds-checked element access with exception
 * throwing for invalid indices.
 * 
 * @ingroup testing
 */
void test_double_linked_list_at() {
	TEST_GROUP("DoubleLinkedList at");
	
	DoubleLinkedList<int> l;
	l.add(10);
	l.add(20);
	l.add(30);
	
	assert(l.at(0) == 10);
	assert(l.at(2) == 30);
	
	try {
		l.at(100);
		assert(false && "Should throw exception");
	} catch (const std::out_of_range&) {
	}
	
	TEST_PASS("DoubleLinkedList at");
}

/**
 * @brief Tests DoubleLinkedList bidirectional access
 * 
 * @details Verifies traversal in both forward and backward directions
 * using next and prev pointers. Tests that data can be accessed from
 * both ends.
 * 
 * @ingroup testing
 */
void test_double_linked_list_bidirectional() {
	TEST_GROUP("DoubleLinkedList bidirectional access");
	
	DoubleLinkedList<int> l;
	l.add(1);
	l.add(2);
	l.add(3);
	l.add(4);
	l.add(5);
	
	auto node = l.tail();
	int expected = 5;
	while (node) {
		assert(node->data == expected);
		node = node->prev;
		expected--;
	}
	
	assert(l[4] == 5);
	assert(l[3] == 4);
	
	TEST_PASS("DoubleLinkedList bidirectional access");
}

/**
 * @brief Tests DoubleLinkedList edge cases
 * 
 * @details Verifies correct behavior for empty list operations,
 * single element with bidirectional links, self-assignment, and large
 * lists.
 * 
 * @ingroup testing
 */
void test_double_linked_list_edge_cases() {
	TEST_GROUP("DoubleLinkedList edge cases");
	
	DoubleLinkedList<int> l;
	assert(l.empty());
	assert(l.size() == 0);
	
	l.add(42);
	assert(l.size() == 1);
	assert(l.head() == l.tail());
	assert(l.head()->prev == nullptr);
	assert(l.head()->next == nullptr);
	
	int val = l.erase(0);
	assert(val == 42);
	assert(l.empty());
	
	DoubleLinkedList<int> l2;
	for (int i = 0; i < 1000; ++i)
		l2.add(i);
	assert(l2.size() == 1000);
	assert(l2[999] == 999);
	assert(l2[0] == 0);
	
	DoubleLinkedList<int> l3;
	l3.add(1);
	l3 = l3;
	assert(l3.size() == 1);
	assert(l3[0] == 1);
	
	DoubleLinkedList<int> l4(0, 5);
	assert(l4.size() == 0);
	assert(l4.empty());
	
	TEST_PASS("DoubleLinkedList edge cases");
}

/**
 * @brief Tests DoubleLinkedList under stress conditions
 * 
 * @details Performs high-volume operations with thousands of elements,
 * verifying bidirectional access, insertions, deletions from both
 * ends at scale.
 * 
 * @ingroup testing
 */
void test_double_linked_list_stress() {
	TEST_GROUP("DoubleLinkedList stress tests");
	
	DoubleLinkedList<int> l;
	
	for (int i = 0; i < 5000; ++i)
		l.add(i);
	
	for (int i = 0; i < 100; ++i) {
		assert(l[i] == i);
		assert(l[4999 - i] == 4999 - i);
	}
	
	for (int i = 0; i < 500; ++i) {
		l.erase(0);
		l.erase(l.size() - 1);
	}
	assert(l.size() == 4000);
	
	assert(l[0] == 500);
	assert(l[l.size() - 1] == 4499);
	
	TEST_PASS("DoubleLinkedList stress tests");
}

/**
 * @brief Tests DoubleLinkedList bidirectional iteration
 * 
 * @details Verifies manual iteration through nodes in both forward
 * (next) and backward (prev) directions, ensuring bidirectional link
 * consistency.
 * 
 * @ingroup testing
 */
void test_double_linked_list_bidirectional_iteration() {
	TEST_GROUP("DoubleLinkedList bidirectional iteration");
	
	DoubleLinkedList<int> l;
	for (int i = 0; i < 100; ++i)
		l.add(i);
	
	auto node = l.head();
	int count = 0;
	while (node) {
		assert(node->data == count);
		node = node->next;
		count++;
	}
	assert(count == 100);
	
	node = l.tail();
	count = 99;
	while (node) {
		assert(node->data == count);
		node = node->prev;
		count--;
	}
	assert(count == -1);
	
	node = l.head();
	while (node->next) {
		assert(node->next->prev == node);
		node = node->next;
	}
	
	TEST_PASS("DoubleLinkedList bidirectional iteration");
}

/**
 * @brief Tests DoubleLinkedList access optimization
 * 
 * @details Verifies optimized element access by choosing forward or
 * backward traversal based on target index proximity to head or tail.
 * 
 * @ingroup testing
 */
void test_double_linked_list_access_optimization() {
	TEST_GROUP("DoubleLinkedList access optimization");
	
	DoubleLinkedList<int> l;
	for (int i = 0; i < 1000; ++i)
		l.add(i);
	
	for (int i = 900; i < 1000; ++i) {
		assert(l[i] == i);
		assert(l.at(i) == i);
	}
	
	for (int i = 0; i < 100; ++i) {
		assert(l[i] == i);
		assert(l.at(i) == i);
	}
	
	for (int i = 400; i < 600; ++i)
		assert(l[i] == i);
	
	TEST_PASS("DoubleLinkedList access optimization");
}

/**
 * @brief Tests DoubleLinkedList iterator functionality
 * 
 * @details Verifies begin() and end() iterators, forward/backward
 * iteration, range-based for loops, dereferencing, and iterator
 * modification of elements.
 * 
 * @ingroup testing
 */
void test_double_linked_list_iterators() {
	TEST_GROUP("DoubleLinkedList iterators");
	
	DoubleLinkedList<int> l;
	for (int i = 0; i < 10; ++i)
		l.add(i);
	
	int sum = 0;
	for (auto it = l.begin(); it != l.end(); ++it)
		sum += *it;
	assert(sum == 45);
	
	auto it = l.begin();
	for (int i = 0; i < 10; ++i) {
		assert(*it == i);
		++it;
	}
	assert(it == l.end());
	
	int count = 0;
	for (const auto& val : l) {
		assert(val == count);
		count++;
	}
	assert(count == 10);
	
	auto tail_it = l.begin();
	for (int i = 0; i < 9; ++i)
		++tail_it;
	
	for (int i = 9; i >= 1; --i) {
		assert(*tail_it == i);
		--tail_it;
	}
	assert(*tail_it == 0);
	
	for (auto it = l.begin(); it != l.end(); ++it)
		*it *= 2;
	
	for (int i = 0; i < 10; ++i)
		assert(l[i] == i * 2);
	
	TEST_PASS("DoubleLinkedList iterators");
}

/**
 * @brief Tests DoubleLinkedList construction from other collection types
 * 
 * @details Verifies copy construction from Vector, Stack, LinkedList,
 * Queue, and Deque. Tests proper element copying and bidirectional
 * link creation.
 * 
 * @ingroup testing
 */
void test_double_linked_list_from_other_collections() {
	TEST_GROUP("DoubleLinkedList from other collections");
	
	Vector<int> v;
	for (int i = 0; i < 10; ++i)
		v.add(i);
	DoubleLinkedList<int> l1(v);
	assert(l1.size() == v.size());
	for (size_t i = 0; i < l1.size(); ++i)
		assert(l1[i] == v[i]);
	
	Stack<int> s;
	for (int i = 0; i < 10; ++i)
		s.push(i * 2);
	DoubleLinkedList<int> l2(s);
	assert(l2.size() == s.size());
	for (size_t i = 0; i < l2.size(); ++i)
		assert(l2[i] == s[i]);
	
	LinkedList<int> ll;
	for (int i = 0; i < 10; ++i)
		ll.add(i * 3);
	DoubleLinkedList<int> l3(ll);
	assert(l3.size() == ll.size());
	for (size_t i = 0; i < l3.size(); ++i)
		assert(l3[i] == ll[i]);
	
	Queue<int> q;
	for (int i = 0; i < 10; ++i)
		q.enqueue(i * 4);
	DoubleLinkedList<int> l4(q);
	assert(l4.size() == q.size());
	for (size_t i = 0; i < l4.size(); ++i)
		assert(l4[i] == q[i]);
	
	Deque<int> d;
	for (int i = 0; i < 10; ++i)
		d.push_back(i * 5);
	DoubleLinkedList<int> l5(d);
	assert(l5.size() == d.size());
	for (size_t i = 0; i < l5.size(); ++i)
		assert(l5[i] == d[i]);
	
	TEST_PASS("DoubleLinkedList from other collections");
}

int main() {
	TEST_HEADER("DoubleLinkedList");
	
	try {
		test_double_linked_list_constructor();
		test_double_linked_list_operators();
		test_double_linked_list_add_insert();
		test_double_linked_list_erase();
		test_double_linked_list_clear();
		test_double_linked_list_at();
		test_double_linked_list_bidirectional();
		test_double_linked_list_edge_cases();
		test_double_linked_list_stress();
		test_double_linked_list_bidirectional_iteration();
		test_double_linked_list_access_optimization();
		test_double_linked_list_iterators();
		test_double_linked_list_from_other_collections();
		
		TEST_SUCCESS("DoubleLinkedList");
		return 0;
	} catch (const std::exception& e) {
		TEST_FAIL(e.what());
		return 1;
	}
}
