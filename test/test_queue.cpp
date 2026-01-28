/**
 * @file test_queue.cpp
 * @brief Unit tests for Queue container
 * 
 * @details Comprehensive test suite that validates all Queue FIFO
 * operations including constructors, enqueue/dequeue, element
 * access, node pointers, and edge case handling.
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
 * @brief Tests Queue constructors
 * 
 * @details Verifies default constructor, fill constructor, copy
 * constructor, and move constructor. Validates proper initialization
 * of size, head, and tail pointers.
 * 
 * @ingroup testing
 */
void test_queue_constructor() {
	TEST_GROUP("Queue constructors");
	
	Queue<int> q1;
	assert(q1.size() == 0);
	assert(q1.empty());
	assert(q1.head() == nullptr);
	assert(q1.tail() == nullptr);
	
	Queue<int> q2(5, 10);
	assert(q2.size() == 5);
	for (size_t i = 0; i < 5; ++i)
		assert(q2[i] == 10);
	
	Queue<int> q3(q2);
	assert(q3.size() == q2.size());
	for (size_t i = 0; i < q3.size(); ++i)
		assert(q3[i] == q2[i]);
	
	Queue<int> q4(std::move(q3));
	assert(q4.size() == 5);
	assert(q3.size() == 0);
	
	TEST_PASS("Queue constructors");
}

/**
 * @brief Tests Queue operators
 * 
 * @details Verifies subscript operator, copy assignment, and move
 * assignment. Tests bounds checking and proper data transfer during
 * assignments.
 * 
 * @ingroup testing
 */
void test_queue_operators() {
	TEST_GROUP("Queue operators");
	
	Queue<int> q1(3, 5);
	
	assert(q1[0] == 5);
	q1[1] = 10;
	assert(q1[1] == 10);
	
	try {
		q1[10];
		assert(false && "Should throw exception");
	} catch (const std::out_of_range&) {
	}
	
	Queue<int> q2;
	q2 = q1;
	assert(q2.size() == q1.size());
	assert(q2[1] == 10);
	
	Queue<int> q3;
	q3 = std::move(q2);
	assert(q3.size() == 3);
	assert(q2.size() == 0);
	
	TEST_PASS("Queue operators");
}

/**
 * @brief Tests Queue enqueue and dequeue operations
 * 
 * @details Verifies FIFO behavior with enqueue() adding elements to
 * rear and dequeue() removing from front. Tests exception handling
 * for dequeuing from empty queue.
 * 
 * @ingroup testing
 */
void test_queue_enqueue_dequeue() {
	TEST_GROUP("Queue enqueue and dequeue");
	
	Queue<int> q;
	
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	assert(q.size() == 3);
	assert(q[0] == 1);
	assert(q[1] == 2);
	assert(q[2] == 3);
	
	int val = q.dequeue();
	assert(val == 1);
	assert(q.size() == 2);
	
	val = q.dequeue();
	assert(val == 2);
	assert(q.size() == 1);
	
	val = q.dequeue();
	assert(val == 3);
	assert(q.size() == 0);
	assert(q.empty());
	
	try {
		q.dequeue();
		assert(false && "Should throw exception");
	} catch (const std::out_of_range&) {
	}
	
	TEST_PASS("Queue enqueue and dequeue");
}

/**
 * @brief Tests Queue clear operation
 * 
 * @details Verifies clear() method properly deallocates all nodes
 * and resets size, head, and tail pointers.
 * 
 * @ingroup testing
 */
void test_queue_clear() {
	TEST_GROUP("Queue clear");
	
	Queue<int> q;
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	
	q.clear();
	assert(q.size() == 0);
	assert(q.empty());
	assert(q.head() == nullptr);
	assert(q.tail() == nullptr);
	
	TEST_PASS("Queue clear");
}

/**
 * @brief Tests Queue at() method
 * 
 * @details Verifies bounds-checked element access with exception
 * throwing for invalid indices.
 * 
 * @ingroup testing
 */
void test_queue_at() {
	TEST_GROUP("Queue at");
	
	Queue<int> q;
	q.enqueue(10);
	q.enqueue(20);
	q.enqueue(30);
	
	assert(q.at(0) == 10);
	assert(q.at(2) == 30);
	
	try {
		q.at(100);
		assert(false && "Should throw exception");
	} catch (const std::out_of_range&) {
	}
	
	TEST_PASS("Queue at");
}

/**
 * @brief Tests Queue head and tail pointers
 * 
 * @details Verifies head() and tail() methods return correct node
 * pointers in various queue states (empty, single element, multiple
 * elements).
 * 
 * @ingroup testing
 */
void test_queue_head_tail() {
	TEST_GROUP("Queue head and tail");
	
	Queue<int> q;
	
	assert(q.head() == nullptr);
	assert(q.tail() == nullptr);
	
	q.enqueue(1);
	assert(q.head() != nullptr);
	assert(q.tail() != nullptr);
	assert(q.head() == q.tail());
	assert(q.head()->data == 1);
	
	q.enqueue(2);
	q.enqueue(3);
	assert(q.head()->data == 1);
	assert(q.tail()->data == 3);
	
	TEST_PASS("Queue head and tail");
}

/**
 * @brief Tests Queue edge cases
 * 
 * @details Verifies correct behavior for empty queue operations,
 * single element scenarios, self-assignment, mixed enqueue/dequeue
 * patterns, and large queues.
 * 
 * @ingroup testing
 */
void test_queue_edge_cases() {
	TEST_GROUP("Queue edge cases");
	
	Queue<int> q;
	assert(q.empty());
	assert(q.size() == 0);
	
	q.enqueue(42);
	assert(q.size() == 1);
	int val = q.dequeue();
	assert(val == 42);
	assert(q.empty());
	
	Queue<int> q2;
	for (int i = 0; i < 1000; ++i)
		q2.enqueue(i);
	assert(q2.size() == 1000);
	
	for (int i = 0; i < 1000; ++i) {
		int dequeued = q2.dequeue();
		assert(dequeued == i);
	}
	assert(q2.empty());
	
	Queue<int> q3;
	q3.enqueue(1);
	q3 = q3;
	assert(q3.size() == 1);
	assert(q3[0] == 1);
	
	Queue<int> q4(0, 5);
	assert(q4.size() == 0);
	assert(q4.empty());
	
	Queue<int> q5;
	q5.enqueue(1);
	q5.enqueue(2);
	assert(q5.dequeue() == 1);
	q5.enqueue(3);
	q5.enqueue(4);
	assert(q5.dequeue() == 2);
	assert(q5.size() == 2);
	
	TEST_PASS("Queue edge cases");
}

/**
 * @brief Tests Queue under stress conditions
 * 
 * @details Performs high-volume enqueue/dequeue operations with
 * thousands of elements, verifying FIFO correctness and node
 * management at scale.
 * 
 * @ingroup testing
 */
void test_queue_stress() {
	TEST_GROUP("Queue stress tests");
	
	Queue<int> q;
	
	for (int i = 0; i < 10000; ++i) {
		q.enqueue(i);
		assert(q.size() == static_cast<size_t>(i + 1));
	}
	
	for (int i = 0; i < 5000; ++i) {
		int val = q.dequeue();
		assert(val == i);
	}
	
	for (int i = 0; i < 3000; ++i)
		q.enqueue(i + 10000);
	
	assert(q.size() == 8000);
	
	TEST_PASS("Queue stress tests");
}

/**
 * @brief Tests Queue FIFO (First-In-First-Out) behavior
 * 
 * @details Verifies strict FIFO ordering in various scenarios,
 * ensuring first enqueued element is always first to be dequeued.
 * 
 * @ingroup testing
 */
void test_queue_fifo_behavior() {
	TEST_GROUP("Queue FIFO behavior");
	
	Queue<int> q;
	
	for (int i = 0; i < 100; ++i)
		q.enqueue(i);
	
	for (int i = 0; i < 100; ++i) {
		int val = q.dequeue();
		assert(val == i);
	}
	
	assert(q.empty());
	
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	assert(q.dequeue() == 1);
	q.enqueue(4);
	assert(q.dequeue() == 2);
	assert(q.dequeue() == 3);
	assert(q.dequeue() == 4);
	
	TEST_PASS("Queue FIFO behavior");
}

/**
 * @brief Tests Queue internal pointer integrity
 * 
 * @details Verifies bidirectional links between nodes remain
 * consistent, with prev/next pointers properly maintained throughout
 * operations.
 * 
 * @ingroup testing
 */
void test_queue_pointer_integrity() {
	TEST_GROUP("Queue pointer integrity");
	
	Queue<int> q;
	
	for (int i = 0; i < 50; ++i)
		q.enqueue(i);
	
	assert(q.head() != nullptr);
	assert(q.tail() != nullptr);
	assert(q.head()->data == 0);
	assert(q.tail()->data == 49);
	
	auto node = q.head();
	int count = 0;
	while (node) {
		assert(node->data == count);
		if (node->next)
			assert(node->next->prev == node);
		node = node->next;
		count++;
	}
	assert(count == 50);
	
	TEST_PASS("Queue pointer integrity");
}

/**
 * @brief Tests Queue iterator functionality
 * 
 * @details Verifies begin() and end() iterators, iterator arithmetic,
 * range-based for loops, and proper sequential access from front to
 * rear.
 * 
 * @ingroup testing
 */
void test_queue_iterators() {
	TEST_GROUP("Queue iterators");
	
	Queue<int> q;
	for (int i = 0; i < 10; ++i)
		q.enqueue(i);
	
	int sum = 0;
	for (auto it = q.begin(); it != q.end(); ++it)
		sum += *it;
	assert(sum == 45);
	
	auto it = q.begin();
	for (int i = 0; i < 10; ++i) {
		assert(*it == i);
		++it;
	}
	assert(it == q.end());
	
	int count = 0;
	for (const auto& val : q) {
		assert(val == count);
		count++;
	}
	assert(count == 10);
	
	TEST_PASS("Queue iterators");
}

/**
 * @brief Tests Queue construction from other collection types
 * 
 * @details Verifies copy construction from Vector, Stack, LinkedList,
 * DoubleLinkedList, and Deque. Tests proper element copying and size
 * preservation.
 * 
 * @ingroup testing
 */
void test_queue_from_other_collections() {
	TEST_GROUP("Queue from other collections");
	
	Vector<int> v;
	for (int i = 0; i < 10; ++i)
		v.add(i);
	Queue<int> q1(v);
	assert(q1.size() == v.size());
	for (size_t i = 0; i < q1.size(); ++i)
		assert(q1[i] == v[i]);
	
	Stack<int> s;
	for (int i = 0; i < 10; ++i)
		s.push(i * 2);
	Queue<int> q2(s);
	assert(q2.size() == s.size());
	for (size_t i = 0; i < q2.size(); ++i)
		assert(q2[i] == s[i]);
	
	LinkedList<int> ll;
	for (int i = 0; i < 10; ++i)
		ll.add(i * 3);
	Queue<int> q3(ll);
	assert(q3.size() == ll.size());
	for (size_t i = 0; i < q3.size(); ++i)
		assert(q3[i] == ll[i]);
	
	DoubleLinkedList<int> dll;
	for (int i = 0; i < 10; ++i)
		dll.add(i * 4);
	Queue<int> q4(dll);
	assert(q4.size() == dll.size());
	for (size_t i = 0; i < q4.size(); ++i)
		assert(q4[i] == dll[i]);
	
	Deque<int> d;
	for (int i = 0; i < 10; ++i)
		d.push_back(i * 5);
	Queue<int> q5(d);
	assert(q5.size() == d.size());
	for (size_t i = 0; i < q5.size(); ++i)
		assert(q5[i] == d[i]);
	
	TEST_PASS("Queue from other collections");
}

int main() {
	TEST_HEADER("Queue");
	
	try {
		test_queue_constructor();
		test_queue_operators();
		test_queue_enqueue_dequeue();
		test_queue_clear();
		test_queue_at();
		test_queue_head_tail();
		test_queue_edge_cases();
		test_queue_stress();
		test_queue_fifo_behavior();
		test_queue_pointer_integrity();
		test_queue_iterators();
		test_queue_from_other_collections();
		
		TEST_SUCCESS("Queue");
		return 0;
	} catch (const std::exception& e) {
		TEST_FAIL(e.what());
		return 1;
	}
}
