/**
 * @file test_vector.cpp
 * @brief Unit tests for Vector container class
 * 
 * @author Lilith Estévez Boeta
 * @date 2025-01-28
 * 
 * @details This file contains comprehensive unit tests for the Vector
 * class, including constructors, operators, element access, insertion,
 * deletion, capacity management, and iterator functionality.
 */

#include <iostream>
#include <cassert>
#include <stdexcept>
#include "test_colors.hpp"
#include "super_lib.hpp"

/**
 * @brief Tests Vector constructors
 * 
 * @details Verifies default constructor, fill constructor, copy
 * constructor, and move constructor functionality.
 * 
 * @ingroup test_utilities
 */
void test_vector_constructor() {
	TEST_GROUP("Vector constructors");
	
	Vector<int> v1;
	assert(v1.size() == 0);
	assert(v1.capacity() == 0);
	assert(v1.empty());
	
	Vector<int> v2(5, 10);
	assert(v2.size() == 5);
	assert(v2.capacity() == 5);
	for (size_t i = 0; i < 5; ++i)
		assert(v2[i] == 10);
	
	Vector<int> v3(v2);
	assert(v3.size() == v2.size());
	for (size_t i = 0; i < v3.size(); ++i)
		assert(v3[i] == v2[i]);
	
	Vector<int> v4(std::move(v3));
	assert(v4.size() == 5);
	assert(v3.size() == 0);
	
	TEST_PASS("Vector constructors");
}

/**
 * @brief Tests Vector operators
 * 
 * @details Verifies subscript operator, copy assignment operator, and
 * move assignment operator. Tests bounds checking and exception
 * throwing.
 * 
 * @ingroup test_utilities
 */
void test_vector_operators() {
	TEST_GROUP("Vector operators");
	
	Vector<int> v1(3, 5);
	
	assert(v1[0] == 5);
	v1[1] = 10;
	assert(v1[1] == 10);
	
	try {
		v1[10];
		assert(false && "Should throw exception");
	} catch (const std::out_of_range&) {
	}
	
	Vector<int> v2;
	v2 = v1;
	assert(v2.size() == v1.size());
	assert(v2[1] == 10);
	
	Vector<int> v3;
	v3 = std::move(v2);
	assert(v3.size() == 3);
	assert(v2.size() == 0);
	
	TEST_PASS("Vector operators");
}

/**
 * @brief Tests Vector add and insert operations
 * 
 * @details Verifies add() method for appending elements and insert()
 * method for inserting elements at specific positions. Tests automatic
 * capacity growth.
 * 
 * @ingroup test_utilities
 */
void test_vector_add_insert() {
	TEST_GROUP("Vector add and insert");
	
	Vector<int> v;
	
	v.add(1);
	v.add(2);
	v.add(3);
	assert(v.size() == 3);
	assert(v[0] == 1);
	assert(v[1] == 2);
	assert(v[2] == 3);
	
	v.insert(0, 0);
	assert(v.size() == 4);
	assert(v[0] == 0);
	assert(v[1] == 1);
	
	v.insert(2, 99);
	assert(v.size() == 5);
	assert(v[2] == 99);
	
	v.insert(v.size(), 100);
	assert(v[v.size() - 1] == 100);
	
	try {
		v.insert(100, 1);
		assert(false && "Should throw exception");
	} catch (const std::out_of_range&) {
	}
	
	TEST_PASS("Vector add and insert");
}

/**
 * @brief Tests Vector erase operation
 * 
 * @details Verifies erase() method for removing elements at various
 * positions (beginning, middle, end). Tests return value and proper
 * vector size adjustment.
 * 
 * @ingroup testing
 */
void test_vector_erase() {
	TEST_GROUP("Vector erase");
	
	Vector<int> v;
	v.add(1);
	v.add(2);
	v.add(3);
	v.add(4);
	v.add(5);
	
	int erased = v.erase(2);
	assert(erased == 3);
	assert(v.size() == 4);
	assert(v[2] == 4);
	
	erased = v.erase(0);
	assert(erased == 1);
	assert(v.size() == 3);
	
	erased = v.erase(v.size() - 1);
	assert(erased == 5);
	assert(v.size() == 2);
	
	try {
		v.erase(100);
		assert(false && "Should throw exception");
	} catch (const std::out_of_range&) {
	}
	
	TEST_PASS("Vector erase");
}

/**
 * @brief Tests Vector clear operation
 * 
 * @details Verifies clear() method properly resets vector to empty
 * state with size zero.
 * 
 * @ingroup testing
 */
void test_vector_clear() {
	TEST_GROUP("Vector clear");
	
	Vector<int> v;
	v.add(1);
	v.add(2);
	v.add(3);
	
	v.clear();
	assert(v.size() == 0);
	assert(v.empty());
	
	TEST_PASS("Vector clear");
}

/**
 * @brief Tests Vector at() method
 * 
 * @details Verifies bounds-checked element access with exception
 * throwing for invalid indices.
 * 
 * @ingroup testing
 */
void test_vector_at() {
	TEST_GROUP("Vector at");
	
	Vector<int> v;
	v.add(10);
	v.add(20);
	v.add(30);
	
	assert(v.at(0) == 10);
	assert(v.at(2) == 30);
	
	try {
		v.at(100);
		assert(false && "Should throw exception");
	} catch (const std::out_of_range&) {
	}
	
	TEST_PASS("Vector at");
}

/**
 * @brief Tests Vector iterators
 * 
 * @details Verifies iterator-based traversal using begin() and end()
 * methods with range-based operations.
 * 
 * @ingroup testing
 */
void test_vector_iterators() {
	TEST_GROUP("Vector iterators");
	
	Vector<int> v;
	v.add(1);
	v.add(2);
	v.add(3);
	
	int sum = 0;
	for (auto it = v.begin(); it != v.end(); ++it)
		sum += *it;
	assert(sum == 6);
	
	TEST_PASS("Vector iterators");
}

/**
 * @brief Tests Vector edge cases
 * 
 * @details Verifies correct behavior for empty vectors, large
 * vectors, self-assignment, and zero-size construction.
 * 
 * @ingroup testing
 */
void test_vector_edge_cases() {
	TEST_GROUP("Vector edge cases");
	
	Vector<int> v;
	assert(v.empty());
	assert(v.size() == 0);
	
	Vector<int> v2;
	for (int i = 0; i < 1000; ++i)
		v2.add(i);
	assert(v2.size() == 1000);
	assert(v2[999] == 999);
	
	Vector<int> v3;
	v3.add(1);
	v3 = v3;
	assert(v3.size() == 1);
	assert(v3[0] == 1);
	
	Vector<int> v4(0, 5);
	assert(v4.size() == 0);
	assert(v4.empty());
	
	TEST_PASS("Vector edge cases");
}

/**
 * @brief Tests Vector stress operations
 * 
 * @details Performs high-volume operations (10000+ elements) to
 * verify correct behavior under heavy load, including mass
 * insertion, access, and deletion.
 * 
 * @ingroup testing
 */
void test_vector_stress() {
	TEST_GROUP("Vector stress tests");
	
	Vector<int> v;
	for (int i = 0; i < 10000; ++i) {
		v.add(i);
		assert(v.size() == static_cast<size_t>(i + 1));
		assert(v[i] == i);
	}
	
	for (int i = 0; i < 10000; ++i) {
		assert(v[i] == i);
		assert(v.at(i) == i);
	}
	
	for (int i = 0; i < 5000; ++i) {
		int val = v.erase(0);
		assert(val == i);
		assert(v.size() == static_cast<size_t>(10000 - i - 1));
	}
	
	for (int i = 0; i < 5000; ++i)
		assert(v[i] == i + 5000);
	
	TEST_PASS("Vector stress tests");
}

/**
 * @brief Tests Vector insert at multiple positions
 * 
 * @details Verifies insert() method at various positions throughout
 * the vector, ensuring correct element placement and ordering.
 * 
 * @ingroup testing
 */
void test_vector_insert_positions() {
	TEST_GROUP("Vector insert at all positions");
	
	Vector<int> v;
	v.add(0);
	v.add(2);
	v.add(4);
	v.add(6);
	v.add(8);
	
	v.insert(1, 1);
	assert(v.size() == 6);
	assert(v[0] == 0 && v[1] == 1 && v[2] == 2);
	
	v.insert(3, 3);
	assert(v.size() == 7);
	assert(v[3] == 3 && v[4] == 4);
	
	v.insert(5, 5);
	assert(v.size() == 8);
	assert(v[5] == 5 && v[6] == 6);
	
	v.insert(7, 7);
	assert(v.size() == 9);
	assert(v[7] == 7 && v[8] == 8);
	
	for (int i = 0; i < 9; ++i)
		assert(v[i] == i);
	
	TEST_PASS("Vector insert at all positions");
}

/**
 * @brief Tests Vector copy semantics
 * 
 * @details Verifies deep copy behavior with copy constructor and
 * copy assignment operator. Ensures independent copies with no
 * shared state.
 * 
 * @ingroup testing
 */
void test_vector_copy_semantics() {
	TEST_GROUP("Vector copy semantics");
	
	Vector<int> v1;
	for (int i = 0; i < 100; ++i)
		v1.add(i);
	
	Vector<int> v2(v1);
	assert(v2.size() == v1.size());
	assert(v2.capacity() == v1.capacity());
	
	for (size_t i = 0; i < v1.size(); ++i)
		assert(v2[i] == v1[i]);
	
	v1[50] = 999;
	assert(v2[50] == 50);
	
	Vector<int> v3;
	v3 = v1;
	assert(v3.size() == v1.size());
	assert(v3[50] == 999);
	
	TEST_PASS("Vector copy semantics");
}

/**
 * @brief Tests Vector move semantics
 * 
 * @details Verifies efficient move operations with move constructor
 * and move assignment operator. Ensures proper resource transfer
 * with source left in valid empty state.
 * 
 * @ingroup testing
 */
void test_vector_move_semantics() {
	TEST_GROUP("Vector move semantics");
	
	Vector<int> v1;
	for (int i = 0; i < 100; ++i)
		v1.add(i);
	
	size_t old_size = v1.size();
	size_t old_capacity = v1.capacity();
	
	Vector<int> v2(std::move(v1));
	assert(v2.size() == old_size);
	assert(v2.capacity() == old_capacity);
	assert(v1.size() == 0);
	assert(v1.capacity() == 0);
	assert(v1.empty());
	
	Vector<int> v3;
	v3.add(1);
	v3 = std::move(v2);
	assert(v3.size() == old_size);
	assert(v2.size() == 0);
	
	TEST_PASS("Vector move semantics");
}

/**
 * @brief Tests Vector construction from other collection types
 * 
 * @details Verifies Vector can be constructed from Stack,
 * LinkedList, DoubleLinkedList, Queue, and Deque containers,
 * preserving element order and values.
 * 
 * @ingroup testing
 */
void test_vector_from_other_collections() {
	TEST_GROUP("Vector from other collections");
	
	Stack<int> s;
	for (int i = 0; i < 10; ++i)
		s.push(i);
	Vector<int> v1(s);
	assert(v1.size() == s.size());
	for (size_t i = 0; i < v1.size(); ++i)
		assert(v1[i] == s[i]);
	
	LinkedList<int> ll;
	for (int i = 0; i < 10; ++i)
		ll.add(i * 2);
	Vector<int> v2(ll);
	assert(v2.size() == ll.size());
	for (size_t i = 0; i < v2.size(); ++i)
		assert(v2[i] == ll[i]);
	
	DoubleLinkedList<int> dll;
	for (int i = 0; i < 10; ++i)
		dll.add(i * 3);
	Vector<int> v3(dll);
	assert(v3.size() == dll.size());
	for (size_t i = 0; i < v3.size(); ++i)
		assert(v3[i] == dll[i]);
	
	Queue<int> q;
	for (int i = 0; i < 10; ++i)
		q.enqueue(i * 4);
	Vector<int> v4(q);
	assert(v4.size() == q.size());
	for (size_t i = 0; i < v4.size(); ++i)
		assert(v4[i] == q[i]);
	
	Deque<int> d;
	for (int i = 0; i < 10; ++i)
		d.push_back(i * 5);
	Vector<int> v5(d);
	assert(v5.size() == d.size());
	for (size_t i = 0; i < v5.size(); ++i)
		assert(v5[i] == d[i]);
	
	TEST_PASS("Vector from other collections");
}

int main() {
	TEST_HEADER("Vector");
	
	try {
		test_vector_constructor();
		test_vector_operators();
		test_vector_add_insert();
		test_vector_erase();
		test_vector_clear();
		test_vector_at();
		test_vector_iterators();
		test_vector_edge_cases();
		test_vector_stress();
		test_vector_insert_positions();
		test_vector_copy_semantics();
		test_vector_move_semantics();
		test_vector_from_other_collections();
		
		TEST_SUCCESS("Vector");
		return 0;
	} catch (const std::exception& e) {
		TEST_FAIL(e.what());
		return 1;
	}
}
