#include <iostream>
#include <cassert>
#include <stdexcept>
#include "test_colors.hpp"
#include "super_lib.hpp"

void test_vector_constructor() {
    TEST_GROUP("Vector constructors");
    
    // Default constructor
    Vector<int> v1;
    assert(v1.size() == 0);
    assert(v1.capacity() == 0);
    assert(v1.empty());
    
    // Constructor with count and value
    Vector<int> v2(5, 10);
    assert(v2.size() == 5);
    assert(v2.capacity() == 5);
    for (size_t i = 0; i < 5; ++i) {
        assert(v2[i] == 10);
    }
    
    // Copy constructor
    Vector<int> v3(v2);
    assert(v3.size() == v2.size());
    for (size_t i = 0; i < v3.size(); ++i) {
        assert(v3[i] == v2[i]);
    }
    
    // Move constructor
    Vector<int> v4(std::move(v3));
    assert(v4.size() == 5);
    assert(v3.size() == 0);
    
    TEST_PASS("Vector constructors");
}

void test_vector_operators() {
    TEST_GROUP("Vector operators");
    
    Vector<int> v1(3, 5);
    
    // operator[]
    assert(v1[0] == 5);
    v1[1] = 10;
    assert(v1[1] == 10);
    
    // operator[] out of range
    try {
        v1[10];
        assert(false && "Should throw exception");
    } catch (const std::out_of_range&) {
        // Expected
    }
    
    // Copy assignment
    Vector<int> v2;
    v2 = v1;
    assert(v2.size() == v1.size());
    assert(v2[1] == 10);
    
    // Move assignment
    Vector<int> v3;
    v3 = std::move(v2);
    assert(v3.size() == 3);
    assert(v2.size() == 0);
    
    TEST_PASS("Vector operators");
}

void test_vector_add_insert() {
    TEST_GROUP("Vector add and insert");
    
    Vector<int> v;
    
    // Add elements
    v.add(1);
    v.add(2);
    v.add(3);
    assert(v.size() == 3);
    assert(v[0] == 1);
    assert(v[1] == 2);
    assert(v[2] == 3);
    
    // Insert at beginning
    v.insert(0, 0);
    assert(v.size() == 4);
    assert(v[0] == 0);
    assert(v[1] == 1);
    
    // Insert in middle
    v.insert(2, 99);
    assert(v.size() == 5);
    assert(v[2] == 99);
    
    // Insert at end
    v.insert(v.size(), 100);
    assert(v[v.size() - 1] == 100);
    
    // Insert out of range
    try {
        v.insert(100, 1);
        assert(false && "Should throw exception");
    } catch (const std::out_of_range&) {
        // Expected
    }
    
    TEST_PASS("Vector add and insert");
}

void test_vector_erase() {
    TEST_GROUP("Vector erase");
    
    Vector<int> v;
    v.add(1);
    v.add(2);
    v.add(3);
    v.add(4);
    v.add(5);
    
    // Erase from middle
    int erased = v.erase(2);
    assert(erased == 3);
    assert(v.size() == 4);
    assert(v[2] == 4);
    
    // Erase from beginning
    erased = v.erase(0);
    assert(erased == 1);
    assert(v.size() == 3);
    
    // Erase from end
    erased = v.erase(v.size() - 1);
    assert(erased == 5);
    assert(v.size() == 2);
    
    // Erase out of range
    try {
        v.erase(100);
        assert(false && "Should throw exception");
    } catch (const std::out_of_range&) {
        // Expected
    }
    
    TEST_PASS("Vector erase");
}

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
        // Expected
    }
    
    TEST_PASS("Vector at");
}

void test_vector_iterators() {
    TEST_GROUP("Vector iterators");
    
    Vector<int> v;
    v.add(1);
    v.add(2);
    v.add(3);
    
    int sum = 0;
    for (auto it = v.begin(); it != v.end(); ++it) {
        sum += *it;
    }
    assert(sum == 6);
    
    TEST_PASS("Vector iterators");
}

void test_vector_edge_cases() {
    TEST_GROUP("Vector edge cases");
    
    // Empty vector operations
    Vector<int> v;
    assert(v.empty());
    assert(v.size() == 0);
    
    // Large number of additions (test reallocation)
    Vector<int> v2;
    for (int i = 0; i < 1000; ++i) {
        v2.add(i);
    }
    assert(v2.size() == 1000);
    assert(v2[999] == 999);
    
    // Self-assignment
    Vector<int> v3;
    v3.add(1);
    v3 = v3;
    assert(v3.size() == 1);
    assert(v3[0] == 1);
    
    // Zero-size constructor
    Vector<int> v4(0, 5);
    assert(v4.size() == 0);
    assert(v4.empty());
    
    TEST_PASS("Vector edge cases");
}

void test_vector_stress() {
    TEST_GROUP("Vector stress tests");
    
    // Test many reallocations
    Vector<int> v;
    for (int i = 0; i < 10000; ++i) {
        v.add(i);
        assert(v.size() == static_cast<size_t>(i + 1));
        assert(v[i] == i);
    }
    
    // Verify all elements
    for (int i = 0; i < 10000; ++i) {
        assert(v[i] == i);
        assert(v.at(i) == i);
    }
    
    // Test many erasures
    for (int i = 0; i < 5000; ++i) {
        int val = v.erase(0);
        assert(val == i);
        assert(v.size() == static_cast<size_t>(10000 - i - 1));
    }
    
    // Verify remaining elements
    for (int i = 0; i < 5000; ++i) {
        assert(v[i] == i + 5000);
    }
    
    TEST_PASS("Vector stress tests");
}

void test_vector_insert_positions() {
    TEST_GROUP("Vector insert at all positions");
    
    Vector<int> v;
    v.add(0);
    v.add(2);
    v.add(4);
    v.add(6);
    v.add(8);
    
    // Insert at various positions
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
    
    // Verify all elements in order
    for (int i = 0; i < 9; ++i) {
        assert(v[i] == i);
    }
    
    TEST_PASS("Vector insert at all positions");
}

void test_vector_copy_semantics() {
    TEST_GROUP("Vector copy semantics");
    
    Vector<int> v1;
    for (int i = 0; i < 100; ++i) {
        v1.add(i);
    }
    
    // Copy constructor
    Vector<int> v2(v1);
    assert(v2.size() == v1.size());
    assert(v2.capacity() == v1.capacity());
    
    // Verify deep copy
    for (size_t i = 0; i < v1.size(); ++i) {
        assert(v2[i] == v1[i]);
    }
    
    // Modify original
    v1[50] = 999;
    assert(v2[50] == 50); // Copy should be unchanged
    
    // Copy assignment
    Vector<int> v3;
    v3 = v1;
    assert(v3.size() == v1.size());
    assert(v3[50] == 999);
    
    TEST_PASS("Vector copy semantics");
}

void test_vector_move_semantics() {
    TEST_GROUP("Vector move semantics");
    
    Vector<int> v1;
    for (int i = 0; i < 100; ++i) {
        v1.add(i);
    }
    
    size_t old_size = v1.size();
    size_t old_capacity = v1.capacity();
    
    // Move constructor
    Vector<int> v2(std::move(v1));
    assert(v2.size() == old_size);
    assert(v2.capacity() == old_capacity);
    assert(v1.size() == 0);
    assert(v1.capacity() == 0);
    assert(v1.empty());
    
    // Move assignment
    Vector<int> v3;
    v3.add(1);
    v3 = std::move(v2);
    assert(v3.size() == old_size);
    assert(v2.size() == 0);
    
    TEST_PASS("Vector move semantics");
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
        
        TEST_SUCCESS("Vector");
        return 0;
    } catch (const std::exception& e) {
        TEST_FAIL(e.what());
        return 1;
    }
}
