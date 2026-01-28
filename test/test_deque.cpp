/**
 * @file test_deque.cpp
 * @brief Unit tests for Deque container
 * 
 * @details Comprehensive test suite that validates all Deque
 * double-ended operations including constructors, push/pop from both
 * ends, circular buffer behavior, capacity management, and edge case
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
 * @brief Tests Deque constructors
 * 
 * @details Verifies default constructor, fill constructor, copy
 * constructor, and move constructor. Validates proper initialization
 * of size and capacity.
 * 
 * @ingroup testing
 */
void test_deque_constructor() {
	TEST_GROUP("Deque constructors");
	
	Deque<int> d1;
	assert(d1.size() == 0);
	assert(d1.capacity() == 0);
	assert(d1.empty());
	
	Deque<int> d2(5, 10);
	assert(d2.size() == 5);
	assert(d2.capacity() == 5);
	for (size_t i = 0; i < 5; ++i)
		assert(d2[i] == 10);
	
	Deque<int> d3(d2);
	assert(d3.size() == d2.size());
	for (size_t i = 0; i < d3.size(); ++i)
		assert(d3[i] == d2[i]);
	
	Deque<int> d4(std::move(d3));
	assert(d4.size() == 5);
	assert(d3.size() == 0);
	
	TEST_PASS("Deque constructors");
}

/**
 * @brief Tests Deque operators
 * 
 * @details Verifies subscript operator, copy assignment, and move
 * assignment. Tests bounds checking and proper data transfer during
 * assignments.
 * 
 * @ingroup testing
 */
void test_deque_operators() {
	TEST_GROUP("Deque operators");
	
	Deque<int> d1(3, 5);
	
	assert(d1[0] == 5);
	d1[1] = 10;
	assert(d1[1] == 10);
	
	try {
		d1[10];
		assert(false && "Should throw exception");
	} catch (const std::out_of_range&) {
	}
	
	Deque<int> d2;
	d2 = d1;
	assert(d2.size() == d1.size());
	assert(d2[1] == 10);
	
	Deque<int> d3;
	d3 = std::move(d2);
	assert(d3.size() == 3);
	assert(d2.size() == 0);
	
	TEST_PASS("Deque operators");
}

/**
 * @brief Tests Deque push and pop operations
 * 
 * @details Verifies double-ended operations with push_back(),
 * push_front(), pop_back(), and pop_front(). Tests proper element
 * ordering and index adjustment.
 * 
 * @ingroup testing
 */
void test_deque_push_pop() {
	TEST_GROUP("Deque push and pop operations");
	
	Deque<int> d;
	
	d.push_back(1);
	d.push_back(2);
	d.push_back(3);
	assert(d.size() == 3);
	assert(d[0] == 1);
	assert(d[1] == 2);
	assert(d[2] == 3);
	
	d.push_front(0);
	assert(d.size() == 4);
	assert(d[0] == 0);
	assert(d[1] == 1);
	
	int val = d.pop_back();
	assert(val == 3);
	assert(d.size() == 3);
	
	val = d.pop_front();
	assert(val == 0);
	assert(d.size() == 2);
	assert(d[0] == 1);
	assert(d[1] == 2);
	
	TEST_PASS("Deque push and pop operations");
}

/**
 * @brief Tests Deque empty operations
 * 
 * @details Verifies exception handling when attempting to pop from
 * empty deque (both front and back).
 * 
 * @ingroup testing
 */
void test_deque_empty_operations() {
	TEST_GROUP("Deque empty operations");
	
	Deque<int> d;
	
	try {
		d.pop_back();
		assert(false && "Should throw exception");
	} catch (const std::out_of_range&) {
	}
	
	try {
		d.pop_front();
		assert(false && "Should throw exception");
	} catch (const std::out_of_range&) {
	}
	
	TEST_PASS("Deque empty operations");
}

/**
 * @brief Tests Deque clear operation
 * 
 * @details Verifies clear() method properly resets deque to empty
 * state with size zero.
 * 
 * @ingroup testing
 */
void test_deque_clear() {
	TEST_GROUP("Deque clear");
	
	Deque<int> d;
	d.push_back(1);
	d.push_back(2);
	d.push_back(3);
	
	d.clear();
	assert(d.size() == 0);
	assert(d.empty());
	
	TEST_PASS("Deque clear");
}

/**
 * @brief Tests Deque at() method
 * 
 * @details Verifies bounds-checked element access with exception
 * throwing for invalid indices.
 * 
 * @ingroup testing
 */
void test_deque_at() {
	TEST_GROUP("Deque at");
	
	Deque<int> d;
	d.push_back(10);
	d.push_back(20);
	d.push_back(30);
	
	assert(d.at(0) == 10);
	assert(d.at(2) == 30);
	
	try {
		d.at(100);
		assert(false && "Should throw exception");
	} catch (const std::out_of_range&) {
	}
	
	TEST_PASS("Deque at");
}

/**
 * @brief Tests Deque circular buffer behavior
 * 
 * @details Verifies correct circular buffer implementation with
 * wraparound behavior when pushing/popping from both ends.
 * 
 * @ingroup testing
 */
void test_deque_circular_buffer() {
	TEST_GROUP("Deque circular buffer behavior");
	
	Deque<int> d;
	
	for (int i = 0; i < 5; ++i)
		d.push_back(i);
	
	d.pop_front();
	d.push_back(5);
	assert(d.size() == 5);
	assert(d[0] == 1);
	assert(d[4] == 5);
	
	d.pop_back();
	d.push_front(0);
	assert(d.size() == 5);
	assert(d[0] == 0);
	assert(d[1] == 1);
	
	TEST_PASS("Deque circular buffer behavior");
}

/**
 * @brief Tests Deque edge cases
 * 
 * @details Verifies correct behavior for empty deque operations,
 * single element scenarios, alternating push operations from both
 * ends, self-assignment, and symmetric push/pop patterns.
 * 
 * @ingroup testing
 */
void test_deque_edge_cases() {
	TEST_GROUP("Deque edge cases");
	
	Deque<int> d;
	assert(d.empty());
	assert(d.size() == 0);
	
	d.push_back(42);
	assert(d.size() == 1);
	int val = d.pop_back();
	assert(val == 42);
	assert(d.empty());
	
	d.push_front(10);
	assert(d.size() == 1);
	assert(d[0] == 10);
	
	Deque<int> d2;
	for (int i = 0; i < 100; ++i) {
		if (i % 2 == 0)
			d2.push_back(i);
		else
			d2.push_front(i);
	}
	assert(d2.size() == 100);
	
	Deque<int> d3;
	for (int i = 0; i < 50; ++i) {
		d3.push_back(i);
		d3.push_front(-i);
	}
	for (int i = 0; i < 50; ++i) {
		d3.pop_back();
		d3.pop_front();
	}
	assert(d3.empty());
	
	Deque<int> d4;
	d4.push_back(1);
	d4 = d4;
	assert(d4.size() == 1);
	assert(d4[0] == 1);
	
	Deque<int> d5(0, 5);
	assert(d5.size() == 0);
	assert(d5.empty());
	
	TEST_PASS("Deque edge cases");
}

/**
 * @brief Tests Deque under stress conditions
 * 
 * @details Performs high-volume push/pop operations from both ends
 * with thousands of elements, verifying circular buffer behavior and
 * capacity management at scale.
 * 
 * @ingroup testing
 */
void test_deque_stress() {
	TEST_GROUP("Deque stress tests");
	
	Deque<int> d;
	
	for (int i = 0; i < 5000; ++i) {
		d.push_back(i);
		assert(d.size() == static_cast<size_t>(i + 1));
	}
	
	for (int i = 0; i < 5000; ++i)
		d.push_front(-i - 1);
	assert(d.size() == 10000);
	
	for (int i = 0; i < 5000; ++i)
		assert(d[i] == -5000 + i);
	
	for (int i = 0; i < 2500; ++i) {
		d.pop_front();
		d.pop_back();
	}
	assert(d.size() == 5000);
	
	TEST_PASS("Deque stress tests");
}

/**
 * @brief Tests Deque wraparound behavior
 * 
 * @details Verifies correct circular buffer wraparound when front
 * index wraps around array boundaries during pop_front/push_back
 * sequences.
 * 
 * @ingroup testing
 */
void test_deque_wraparound() {
	TEST_GROUP("Deque wraparound behavior");
	
	Deque<int> d;
	
	for (int i = 0; i < 10; ++i)
		d.push_back(i);
	
	for (int i = 0; i < 20; ++i) {
		d.pop_front();
		d.push_back(i + 10);
	}
	
	assert(d.size() == 10);
	
	for (size_t i = 0; i < d.size(); ++i)
		assert(d[i] == static_cast<int>(i + 20));
	
	TEST_PASS("Deque wraparound behavior");
}

/**
 * @brief Tests Deque capacity growth and dynamic resizing
 * 
 * @details Verifies automatic capacity expansion during push
 * operations from both ends, ensuring capacity is always sufficient
 * for current size.
 * 
 * @ingroup testing
 */
void test_deque_capacity_growth() {
	TEST_GROUP("Deque capacity growth");
	
	Deque<int> d;
	size_t prev_capacity = 0;
	
	for (int i = 0; i < 100; ++i) {
		if (i % 2 == 0)
			d.push_back(i);
		else
			d.push_front(i);
		
		if (d.capacity() != prev_capacity) {
			assert(d.capacity() >= d.size());
			prev_capacity = d.capacity();
		}
	}
	
	assert(d.size() == 100);
	
	TEST_PASS("Deque capacity growth");
}

/**
 * @brief Tests Deque with mixed operations from both ends
 * 
 * @details Verifies correct element ordering and index management
 * when randomly mixing push_back, push_front, pop_back, and
 * pop_front operations.
 * 
 * @ingroup testing
 */
void test_deque_mixed_operations() {
	TEST_GROUP("Deque mixed operations");
	
	Deque<int> d;
	
	d.push_back(1);
	d.push_front(0);
	d.push_back(2);
	assert(d[0] == 0 && d[1] == 1 && d[2] == 2);
	
	d.pop_front();
	assert(d[0] == 1 && d[1] == 2);
	
	d.push_front(-1);
	d.push_back(3);
	assert(d.size() == 4);
	assert(d[0] == -1 && d[1] == 1 && d[2] == 2 && d[3] == 3);
	
	d.pop_back();
	d.pop_back();
	assert(d.size() == 2);
	assert(d[0] == -1 && d[1] == 1);
	
	TEST_PASS("Deque mixed operations");
}

/**
 * @brief Tests Deque construction from other collection types
 * 
 * @details Verifies copy construction from Vector, Stack, LinkedList,
 * DoubleLinkedList, and Queue. Tests proper element copying and size
 * preservation.
 * 
 * @ingroup testing
 */
void test_deque_from_other_collections() {
	TEST_GROUP("Deque from other collections");
	
	Vector<int> v;
	for (int i = 0; i < 10; ++i)
		v.add(i);
	Deque<int> d1(v);
	assert(d1.size() == v.size());
	for (size_t i = 0; i < d1.size(); ++i)
		assert(d1[i] == v[i]);
	
	Stack<int> s;
	for (int i = 0; i < 10; ++i)
		s.push(i * 2);
	Deque<int> d2(s);
	assert(d2.size() == s.size());
	for (size_t i = 0; i < d2.size(); ++i)
		assert(d2[i] == s[i]);
	
	LinkedList<int> ll;
	for (int i = 0; i < 10; ++i)
		ll.add(i * 3);
	Deque<int> d3(ll);
	assert(d3.size() == ll.size());
	for (size_t i = 0; i < d3.size(); ++i)
		assert(d3[i] == ll[i]);
	
	DoubleLinkedList<int> dll;
	for (int i = 0; i < 10; ++i)
		dll.add(i * 4);
	Deque<int> d4(dll);
	assert(d4.size() == dll.size());
	for (size_t i = 0; i < d4.size(); ++i)
		assert(d4[i] == dll[i]);
	
	Queue<int> q;
	for (int i = 0; i < 10; ++i)
		q.enqueue(i * 5);
	Deque<int> d5(q);
	assert(d5.size() == q.size());
	for (size_t i = 0; i < d5.size(); ++i)
		assert(d5[i] == q[i]);
	
	TEST_PASS("Deque from other collections");
}

/**
 * @brief Tests Deque iterator functionality
 * 
 * @details Verifies begin() and end() iterators, iterator arithmetic,
 * range-based for loops, dereferencing, and iterator modification of
 * elements with circular buffer.
 * 
 * @ingroup testing
 */
void test_deque_iterators() {
	TEST_GROUP("Deque iterators");
	
	Deque<int> d;
	for (int i = 0; i < 10; ++i)
		d.push_back(i);
	
	int sum = 0;
	for (auto it = d.begin(); it != d.end(); ++it)
		sum += *it;
	assert(sum == 45);
	
	auto it = d.begin();
	for (int i = 0; i < 10; ++i) {
		assert(*it == i);
		++it;
	}
	assert(it == d.end());
	
	int count = 0;
	for (const auto& val : d) {
		assert(val == count);
		count++;
	}
	assert(count == 10);
	
	for (auto it = d.begin(); it != d.end(); ++it)
		*it *= 2;
	
	for (int i = 0; i < 10; ++i)
		assert(d[i] == i * 2);
	
	TEST_PASS("Deque iterators");
}

/**
 * @brief Tests Deque iterator behavior with circular buffer
 * 
 * @details Verifies iterator correctness when front index has wrapped
 * around, ensuring iteration follows logical element order despite
 * physical wraparound.
 * 
 * @ingroup testing
 */
void test_deque_circular_buffer_iteration() {
	TEST_GROUP("Deque circular buffer iteration");
	
	Deque<int> d;
	
	for (int i = 0; i < 10; ++i)
		d.push_back(i);
	
	for (int i = 0; i < 5; ++i) {
		d.pop_front();
		d.push_back(i + 10);
	}
	
	
	int expected = 5;
	for (const auto& val : d) {
		assert(val == expected);
		expected++;
	}
	assert(expected == 15);
	
	auto it = d.begin();
	expected = 5;
	while (it != d.end()) {
		assert(*it == expected);
		++it;
		expected++;
	}
	
	TEST_PASS("Deque circular buffer iteration");
}

/**
 * @brief Tests Deque iterator edge cases
 * 
 * @details Verifies iterator behavior with empty deque, single
 * element, push_front operations, and mixed push patterns. Tests
 * proper element ordering.
 * 
 * @ingroup testing
 */
void test_deque_iterator_edge_cases() {
	TEST_GROUP("Deque iterator edge cases");
	
	Deque<int> d1;
	assert(d1.begin() == d1.end());
	int count = 0;
	for (const auto& val : d1) {
		(void)val;
		count++;
	}
	assert(count == 0);
	
	Deque<int> d2;
	d2.push_back(42);
	count = 0;
	for (const auto& val : d2) {
		assert(val == 42);
		count++;
	}
	assert(count == 1);
	
	Deque<int> d3;
	for (int i = 0; i < 5; ++i)
		d3.push_front(i);
	
	auto it = d3.begin();
	for (int i = 4; i >= 0; --i) {
		assert(*it == i);
		++it;
	}
	
	Deque<int> d4;
	d4.push_back(1);
	d4.push_front(0);
	d4.push_back(2);
	d4.push_front(-1);
	
	int expected[] = {-1, 0, 1, 2};
	int idx = 0;
	for (const auto& val : d4) {
		assert(val == expected[idx]);
		idx++;
	}
	
	TEST_PASS("Deque iterator edge cases");
}

int main() {
	TEST_HEADER("Deque");
	
	try {
		test_deque_constructor();
		test_deque_operators();
		test_deque_push_pop();
		test_deque_empty_operations();
		test_deque_clear();
		test_deque_at();
		test_deque_circular_buffer();
		test_deque_edge_cases();
		test_deque_stress();
		test_deque_wraparound();
		test_deque_capacity_growth();
		test_deque_mixed_operations();
		test_deque_from_other_collections();
		test_deque_iterators();
		test_deque_circular_buffer_iteration();
		test_deque_iterator_edge_cases();
		
		TEST_SUCCESS("Deque");
		return 0;
	} catch (const std::exception& e) {
		TEST_FAIL(e.what());
		return 1;
	}
}
