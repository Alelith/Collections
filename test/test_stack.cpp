/**
 * @file test_stack.cpp
 * @brief Unit tests for Stack container
 * 
 * @details Comprehensive test suite that validates all Stack LIFO
 * operations including constructors, push/pop, element access,
 * capacity management, and edge case handling.
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
 * @brief Tests Stack constructors
 * 
 * @details Verifies default constructor, fill constructor, copy
 * constructor, and move constructor. Validates proper initialization
 * of size and capacity.
 * 
 * @ingroup testing
 */
void test_stack_constructor() {
	TEST_GROUP("Stack constructors");
	
	Stack<int> s1;
	assert(s1.size() == 0);
	assert(s1.capacity() == 0);
	assert(s1.empty());
	
	Stack<int> s2(5, 10);
	assert(s2.size() == 5);
	assert(s2.capacity() == 5);
	for (size_t i = 0; i < 5; ++i)
		assert(s2[i] == 10);
	
	Stack<int> s3(s2);
	assert(s3.size() == s2.size());
	for (size_t i = 0; i < s3.size(); ++i)
		assert(s3[i] == s2[i]);
	
	Stack<int> s4(std::move(s3));
	assert(s4.size() == 5);
	assert(s3.size() == 0);
	
	TEST_PASS("Stack constructors");
}

/**
 * @brief Tests Stack operators
 * 
 * @details Verifies subscript operator, copy assignment, and move
 * assignment. Tests bounds checking and proper data transfer during
 * assignments.
 * 
 * @ingroup testing
 */
void test_stack_operators() {
	TEST_GROUP("Stack operators");
	
	Stack<int> s1(3, 5);
	
	assert(s1[0] == 5);
	s1[1] = 10;
	assert(s1[1] == 10);
	
	try {
		s1[10];
		assert(false && "Should throw exception");
	} catch (const std::out_of_range&) {
	}
	
	Stack<int> s2;
	s2 = s1;
	assert(s2.size() == s1.size());
	assert(s2[1] == 10);
	
	Stack<int> s3;
	s3 = std::move(s2);
	assert(s3.size() == 3);
	assert(s2.size() == 0);
	
	TEST_PASS("Stack operators");
}

/**
 * @brief Tests Stack push and pop operations
 * 
 * @details Verifies LIFO behavior with push() adding elements to
 * top and pop() removing from top. Tests exception handling for
 * popping from empty stack.
 * 
 * @ingroup testing
 */
void test_stack_push_pop() {
	TEST_GROUP("Stack push and pop");
	
	Stack<int> s;
	
	s.push(1);
	s.push(2);
	s.push(3);
	assert(s.size() == 3);
	assert(s[2] == 3);
	
	int val = s.pop();
	assert(val == 3);
	assert(s.size() == 2);
	
	val = s.pop();
	assert(val == 2);
	assert(s.size() == 1);
	
	val = s.pop();
	assert(val == 1);
	assert(s.size() == 0);
	assert(s.empty());
	
	try {
		s.pop();
		assert(false && "Should throw exception");
	} catch (const std::out_of_range&) {
	}
	
	TEST_PASS("Stack push and pop");
}

/**
 * @brief Tests Stack clear operation
 * 
 * @details Verifies clear() method properly resets stack to empty
 * state with size zero.
 * 
 * @ingroup testing
 */
void test_stack_clear() {
	TEST_GROUP("Stack clear");
	
	Stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	
	s.clear();
	assert(s.size() == 0);
	assert(s.empty());
	
	TEST_PASS("Stack clear");
}

/**
 * @brief Tests Stack at() method
 * 
 * @details Verifies bounds-checked element access with exception
 * throwing for invalid indices.
 * 
 * @ingroup testing
 */
void test_stack_at() {
	TEST_GROUP("Stack at");
	
	Stack<int> s;
	s.push(10);
	s.push(20);
	s.push(30);
	
	assert(s.at(0) == 10);
	assert(s.at(2) == 30);
	
	try {
		s.at(100);
		assert(false && "Should throw exception");
	} catch (const std::out_of_range&) {
	}
	
	TEST_PASS("Stack at");
}

/**
 * @brief Tests Stack iterators
 * 
 * @details Verifies iterator-based traversal from bottom to top of
 * stack using begin() and end() methods.
 * 
 * @ingroup testing
 */
void test_stack_iterators() {
	TEST_GROUP("Stack iterators");
	
	Stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	
	int sum = 0;
	for (auto it = s.begin(); it != s.end(); ++it)
		sum += *it;
	assert(sum == 6);
	
	TEST_PASS("Stack iterators");
}

/**
 * @brief Tests Stack edge cases
 * 
 * @details Verifies correct behavior for empty stack operations
 * and boundary conditions.
 * 
 * @ingroup testing
 */
void test_stack_edge_cases() {
	TEST_GROUP("Stack edge cases");
	
	Stack<int> s;
	assert(s.empty());
	assert(s.size() == 0);
	
	s.push(42);
	assert(s.size() == 1);
	int val = s.pop();
	assert(val == 42);
	assert(s.empty());
	
	Stack<int> s2;
	for (int i = 0; i < 1000; ++i)
		s2.push(i);
	assert(s2.size() == 1000);
	
	for (int i = 999; i >= 0; --i) {
		int popped = s2.pop();
		assert(popped == i);
	}
	assert(s2.empty());
	
	Stack<int> s3;
	s3.push(1);
	s3 = s3;
	assert(s3.size() == 1);
	assert(s3[0] == 1);
	
	Stack<int> s4(0, 5);
	assert(s4.size() == 0);
	assert(s4.empty());
	
	TEST_PASS("Stack edge cases");
}

/**
 * @brief Tests Stack under stress conditions
 * 
 * @details Performs high-volume push/pop operations with thousands of
 * elements, verifying LIFO correctness and capacity management at
 * scale.
 * 
 * @ingroup testing
 */
void test_stack_stress() {
	TEST_GROUP("Stack stress tests");
	
	Stack<int> s;
	
	for (int i = 0; i < 10000; ++i) {
		s.push(i);
		assert(s.size() == static_cast<size_t>(i + 1));
	}
	
	assert(s[9999] == 9999);
	assert(s.at(9999) == 9999);
	
	for (int i = 0; i < 5000; ++i) {
		int val = s.pop();
		assert(val == 9999 - i);
	}
	assert(s.size() == 5000);
	
	for (int i = 0; i < 3000; ++i)
		s.push(i + 10000);
	assert(s.size() == 8000);
	
	TEST_PASS("Stack stress tests");
}

/**
 * @brief Tests Stack LIFO (Last-In-First-Out) behavior
 * 
 * @details Verifies strict LIFO ordering in various scenarios,
 * ensuring last pushed element is always first to be popped.
 * 
 * @ingroup testing
 */
void test_stack_lifo_behavior() {
	TEST_GROUP("Stack LIFO behavior");
	
	Stack<int> s;
	
	for (int i = 0; i < 100; ++i)
		s.push(i);
	
	for (int i = 99; i >= 0; --i) {
		assert(s[s.size() - 1] == i);
		int val = s.pop();
		assert(val == i);
	}
	
	assert(s.empty());
	
	s.push(1);
	s.push(2);
	assert(s.pop() == 2);
	s.push(3);
	assert(s.pop() == 3);
	assert(s.pop() == 1);
	
	TEST_PASS("Stack LIFO behavior");
}

/**
 * @brief Tests Stack capacity management and dynamic growth
 * 
 * @details Verifies automatic capacity expansion during push
 * operations, ensuring capacity is always sufficient for current
 * size.
 * 
 * @ingroup testing
 */
void test_stack_capacity_management() {
	TEST_GROUP("Stack capacity management");
	
	Stack<int> s;
	
	size_t prev_capacity = 0;
	for (int i = 0; i < 100; ++i) {
		s.push(i);
		if (s.capacity() != prev_capacity) {
			assert(s.capacity() >= s.size());
			prev_capacity = s.capacity();
		}
	}
	
	s.clear();
	assert(s.size() == 0);
	assert(s.empty());
	
	TEST_PASS("Stack capacity management");
}

/**
 * @brief Tests Stack construction from other collection types
 * 
 * @details Verifies copy construction from Vector, LinkedList,
 * DoubleLinkedList, Queue, and Deque. Tests proper element copying
 * and size preservation.
 * 
 * @ingroup testing
 */
void test_stack_from_other_collections() {
	TEST_GROUP("Stack from other collections");
	
	Vector<int> v;
	for (int i = 0; i < 10; ++i)
		v.add(i);
	Stack<int> s1(v);
	assert(s1.size() == v.size());
	for (size_t i = 0; i < s1.size(); ++i)
		assert(s1[i] == v[i]);
	
	LinkedList<int> ll;
	for (int i = 0; i < 10; ++i)
		ll.add(i * 2);
	Stack<int> s2(ll);
	assert(s2.size() == ll.size());
	for (size_t i = 0; i < s2.size(); ++i)
		assert(s2[i] == ll[i]);
	
	DoubleLinkedList<int> dll;
	for (int i = 0; i < 10; ++i)
		dll.add(i * 3);
	Stack<int> s3(dll);
	assert(s3.size() == dll.size());
	for (size_t i = 0; i < s3.size(); ++i)
		assert(s3[i] == dll[i]);
	
	Queue<int> q;
	for (int i = 0; i < 10; ++i)
		q.enqueue(i * 4);
	Stack<int> s4(q);
	assert(s4.size() == q.size());
	for (size_t i = 0; i < s4.size(); ++i)
		assert(s4[i] == q[i]);
	
	Deque<int> d;
	for (int i = 0; i < 10; ++i)
		d.push_back(i * 5);
	Stack<int> s5(d);
	assert(s5.size() == d.size());
	for (size_t i = 0; i < s5.size(); ++i)
		assert(s5[i] == d[i]);
	
	TEST_PASS("Stack from other collections");
}

int main() {
	TEST_HEADER("Stack");
	
	try {
		test_stack_constructor();
		test_stack_operators();
		test_stack_push_pop();
		test_stack_clear();
		test_stack_at();
		test_stack_iterators();
		test_stack_edge_cases();
		test_stack_stress();
		test_stack_lifo_behavior();
		test_stack_capacity_management();
		test_stack_from_other_collections();
		
		TEST_SUCCESS("Stack");
		return 0;
	} catch (const std::exception& e) {
		TEST_FAIL(e.what());
		return 1;
	}
}
