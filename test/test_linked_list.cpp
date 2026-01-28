/**
 * @file test_linked_list.cpp
 * @brief Unit tests for LinkedList container
 * 
 * @details Comprehensive test suite that validates all LinkedList
 * operations including constructors, element access, insertion,
 * deletion, iterators, and edge case handling.
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
 * @brief Tests LinkedList constructors
 * 
 * @details Verifies default constructor, fill constructor, copy
 * constructor, and move constructor. Validates proper initialization
 * of size, head, and tail pointers.
 * 
 * @ingroup testing
 */
void test_linked_list_constructor() {
	TEST_GROUP("LinkedList constructors");
	
	LinkedList<int> l1;
	assert(l1.size() == 0);
	assert(l1.empty());
	assert(l1.head() == nullptr);
	assert(l1.tail() == nullptr);
	
	LinkedList<int> l2(5, 10);
	assert(l2.size() == 5);
	for (size_t i = 0; i < 5; ++i)
		assert(l2[i] == 10);
	
	LinkedList<int> l3(l2);
	assert(l3.size() == l2.size());
	for (size_t i = 0; i < l3.size(); ++i)
		assert(l3[i] == l2[i]);
	
	LinkedList<int> l4(std::move(l3));
	assert(l4.size() == 5);
	assert(l3.size() == 0);
	
	TEST_PASS("LinkedList constructors");
}

/**
 * @brief Tests LinkedList operators
 * 
 * @details Verifies subscript operator, copy assignment, and move
 * assignment. Tests bounds checking and proper data transfer during
 * assignments.
 * 
 * @ingroup testing
 */
void test_linked_list_operators() {
	TEST_GROUP("LinkedList operators");
	
	LinkedList<int> l1(3, 5);
	
	assert(l1[0] == 5);
	l1[1] = 10;
	assert(l1[1] == 10);
	
	try {
		l1[10];
		assert(false && "Should throw exception");
	} catch (const std::out_of_range&) {
	}
	
	LinkedList<int> l2;
	l2 = l1;
	assert(l2.size() == l1.size());
	assert(l2[1] == 10);
	
	LinkedList<int> l3;
	l3 = std::move(l2);
	assert(l3.size() == 3);
	assert(l2.size() == 0);
	
	TEST_PASS("LinkedList operators");
}

/**
 * @brief Tests LinkedList add and insert operations
 * 
 * @details Verifies add() method for appending elements and insert()
 * method for inserting elements at specific positions. Tests
 * boundary conditions and exception handling.
 * 
 * @ingroup testing
 */
void test_linked_list_add_insert() {
	TEST_GROUP("LinkedList add and insert");
	
	LinkedList<int> l;
	
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
	
	TEST_PASS("LinkedList add and insert");
}

/**
 * @brief Tests LinkedList erase operation
 * 
 * @details Verifies erase() method for removing elements at various
 * positions (beginning, middle, end). Tests return value and proper
 * list adjustment.
 * 
 * @ingroup testing
 */
void test_linked_list_erase() {
	TEST_GROUP("LinkedList erase");
	
	LinkedList<int> l;
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
	
	TEST_PASS("LinkedList erase");
}

/**
 * @brief Tests LinkedList clear operation
 * 
 * @details Verifies clear() method properly deallocates all nodes
 * and resets size, head, and tail pointers.
 * 
 * @ingroup testing
 */
void test_linked_list_clear() {
	TEST_GROUP("LinkedList clear");
	
	LinkedList<int> l;
	l.add(1);
	l.add(2);
	l.add(3);
	
	l.clear();
	assert(l.size() == 0);
	assert(l.empty());
	assert(l.head() == nullptr);
	assert(l.tail() == nullptr);
	
	TEST_PASS("LinkedList clear");
}

/**
 * @brief Tests LinkedList at() method
 * 
 * @details Verifies bounds-checked element access with exception
 * throwing for invalid indices.
 * 
 * @ingroup testing
 */
void test_linked_list_at() {
	TEST_GROUP("LinkedList at");
	
	LinkedList<int> l;
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
	
	TEST_PASS("LinkedList at");
}

/**
 * @brief Tests LinkedList head and tail pointer access
 * 
 * @details Verifies head() and tail() methods return correct node
 * pointers in various list states (empty, single element, multiple
 * elements).
 * 
 * @ingroup testing
 */
void test_linked_list_head_tail() {
	TEST_GROUP("LinkedList head and tail");
	
	LinkedList<int> l;
	
	assert(l.head() == nullptr);
	assert(l.tail() == nullptr);
	
	l.add(1);
	assert(l.head() != nullptr);
	assert(l.tail() != nullptr);
	assert(l.head() == l.tail());
	assert(l.head()->data == 1);
	
	l.add(2);
	l.add(3);
	assert(l.head()->data == 1);
	assert(l.tail()->data == 3);
	
	TEST_PASS("LinkedList head and tail");
}

/**
 * @brief Tests LinkedList edge cases
 * 
 * @details Verifies correct behavior for empty list operations,
 * single element scenarios, self-assignment, and large lists.
 * 
 * @ingroup testing
 */
void test_linked_list_edge_cases() {
	TEST_GROUP("LinkedList edge cases");
	
	LinkedList<int> l;
	assert(l.empty());
	assert(l.size() == 0);
	
	l.add(42);
	assert(l.size() == 1);
	int val = l.erase(0);
	assert(val == 42);
	assert(l.empty());
	
	LinkedList<int> l2;
	for (int i = 0; i < 1000; ++i)
		l2.add(i);
	assert(l2.size() == 1000);
	assert(l2[999] == 999);
	
	LinkedList<int> l3;
	l3.add(1);
	l3 = l3;
	assert(l3.size() == 1);
	assert(l3[0] == 1);
	
	LinkedList<int> l4(0, 5);
	assert(l4.size() == 0);
	assert(l4.empty());
	
	TEST_PASS("LinkedList edge cases");
}

/**
 * @brief Tests LinkedList under stress conditions
 * 
 * @details Performs high-volume operations with thousands of elements,
 * verifying correctness of insertions, deletions, and element access
 * at scale.
 * 
 * @ingroup testing
 */
void test_linked_list_stress() {
	TEST_GROUP("LinkedList stress tests");
	
	LinkedList<int> l;
	
	for (int i = 0; i < 5000; ++i) {
		l.add(i);
		assert(l.size() == static_cast<size_t>(i + 1));
	}
	
	for (int i = 0; i < 5000; ++i)
		assert(l[i] == i);
	
	for (int i = 0; i < 1000; ++i) {
		size_t mid = l.size() / 2;
		l.erase(mid);
	}
	assert(l.size() == 4000);
	
	for (int i = 0; i < 100; ++i)
		l.insert(0, -i);
	assert(l.size() == 4100);
	assert(l[0] == -99);
	
	TEST_PASS("LinkedList stress tests");
}

/**
 * @brief Tests LinkedList node-level iteration
 * 
 * @details Verifies manual iteration through nodes using head(),
 * tail(), and next pointers. Tests sequential access and node
 * integrity.
 * 
 * @ingroup testing
 */
void test_linked_list_iteration() {
	TEST_GROUP("LinkedList node iteration");
	
	LinkedList<int> l;
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
	
	assert(l.tail()->data == 99);
	assert(l.tail()->next == nullptr);
	
	TEST_PASS("LinkedList node iteration");
}

/**
 * @brief Tests LinkedList with alternating operations
 * 
 * @details Verifies correct behavior when mixing add(), insert(),
 * and erase() operations in alternating patterns.
 * 
 * @ingroup testing
 */
void test_linked_list_alternating_ops() {
	TEST_GROUP("LinkedList alternating operations");
	
	LinkedList<int> l;
	
	for (int i = 0; i < 50; ++i) {
		l.add(i * 2);
		if (l.size() > 1)
			l.insert(l.size() - 1, i * 2 + 1);
	}
	
	assert(l.size() == 99);
	
	for (int i = 0; i < 30; ++i) {
		l.erase(0);
		if (l.size() > 0)
			l.erase(l.size() - 1);
	}
	
	assert(l.size() == 39);
	
	TEST_PASS("LinkedList alternating operations");
}

/**
 * @brief Tests LinkedList iterator functionality
 * 
 * @details Verifies begin() and end() iterators, iterator arithmetic,
 * range-based for loops, dereferencing, and iterator modification of
 * elements.
 * 
 * @ingroup testing
 */
void test_linked_list_iterators() {
	TEST_GROUP("LinkedList iterators");
	
	LinkedList<int> l;
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
	
	for (auto it = l.begin(); it != l.end(); ++it)
		*it *= 2;
	
	for (int i = 0; i < 10; ++i)
		assert(l[i] == i * 2);
	
	TEST_PASS("LinkedList iterators");
}

/**
 * @brief Tests LinkedList construction from other collection types
 * 
 * @details Verifies copy construction from Vector, Stack, Queue,
 * DoubleLinkedList, and Deque. Tests proper element copying and size
 * preservation.
 * 
 * @ingroup testing
 */
void test_linked_list_from_other_collections() {
	TEST_GROUP("LinkedList from other collections");
	
	Vector<int> v;
	for (int i = 0; i < 10; ++i)
		v.add(i);
	LinkedList<int> l1(v);
	assert(l1.size() == v.size());
	for (size_t i = 0; i < l1.size(); ++i)
		assert(l1[i] == v[i]);
	
	Stack<int> s;
	for (int i = 0; i < 10; ++i)
		s.push(i * 2);
	LinkedList<int> l2(s);
	assert(l2.size() == s.size());
	for (size_t i = 0; i < l2.size(); ++i)
		assert(l2[i] == s[i]);
	
	Queue<int> q;
	for (int i = 0; i < 10; ++i)
		q.enqueue(i * 3);
	LinkedList<int> l3(q);
	assert(l3.size() == q.size());
	for (size_t i = 0; i < l3.size(); ++i)
		assert(l3[i] == q[i]);
	
	DoubleLinkedList<int> dll;
	for (int i = 0; i < 10; ++i)
		dll.add(i * 4);
	LinkedList<int> l4(dll);
	assert(l4.size() == dll.size());
	for (size_t i = 0; i < l4.size(); ++i)
		assert(l4[i] == dll[i]);
	
	Deque<int> d;
	for (int i = 0; i < 10; ++i)
		d.push_back(i * 5);
	LinkedList<int> l5(d);
	assert(l5.size() == d.size());
	for (size_t i = 0; i < l5.size(); ++i)
		assert(l5[i] == d[i]);
	
	TEST_PASS("LinkedList from other collections");
}

int main() {
	TEST_HEADER("LinkedList");
	
	try {
		test_linked_list_constructor();
		test_linked_list_operators();
		test_linked_list_add_insert();
		test_linked_list_erase();
		test_linked_list_clear();
		test_linked_list_at();
		test_linked_list_head_tail();
		test_linked_list_edge_cases();
		test_linked_list_stress();
		test_linked_list_iteration();
		test_linked_list_alternating_ops();
		test_linked_list_iterators();
		test_linked_list_from_other_collections();
		
		TEST_SUCCESS("LinkedList");
		return 0;
	} catch (const std::exception& e) {
		TEST_FAIL(e.what());
		return 1;
	}
}
