#include <iostream>
#include <cassert>
#include <stdexcept>
#include "test_colors.hpp"
#include "deque.hpp"

void test_deque_constructor() {
    TEST_GROUP("Deque constructors");
    
    // Default constructor
    Deque<int> d1;
    assert(d1.size() == 0);
    assert(d1.capacity() == 0);
    assert(d1.empty());
    
    // Constructor with count and value
    Deque<int> d2(5, 10);
    assert(d2.size() == 5);
    assert(d2.capacity() == 5);
    for (size_t i = 0; i < 5; ++i) {
        assert(d2[i] == 10);
    }
    
    // Copy constructor
    Deque<int> d3(d2);
    assert(d3.size() == d2.size());
    for (size_t i = 0; i < d3.size(); ++i) {
        assert(d3[i] == d2[i]);
    }
    
    // Move constructor
    Deque<int> d4(std::move(d3));
    assert(d4.size() == 5);
    assert(d3.size() == 0);
    
    TEST_PASS("Deque constructors");
}

void test_deque_operators() {
    TEST_GROUP("Deque operators");
    
    Deque<int> d1(3, 5);
    
    // operator[]
    assert(d1[0] == 5);
    d1[1] = 10;
    assert(d1[1] == 10);
    
    // operator[] out of range
    try {
        d1[10];
        assert(false && "Should throw exception");
    } catch (const std::out_of_range&) {
        // Expected
    }
    
    // Copy assignment
    Deque<int> d2;
    d2 = d1;
    assert(d2.size() == d1.size());
    assert(d2[1] == 10);
    
    // Move assignment
    Deque<int> d3;
    d3 = std::move(d2);
    assert(d3.size() == 3);
    assert(d2.size() == 0);
    
    TEST_PASS("Deque operators");
}

void test_deque_push_pop() {
    TEST_GROUP("Deque push and pop operations");
    
    Deque<int> d;
    
    // Push back
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    assert(d.size() == 3);
    assert(d[0] == 1);
    assert(d[1] == 2);
    assert(d[2] == 3);
    
    // Push front
    d.push_front(0);
    assert(d.size() == 4);
    assert(d[0] == 0);
    assert(d[1] == 1);
    
    // Pop back
    int val = d.pop_back();
    assert(val == 3);
    assert(d.size() == 3);
    
    // Pop front
    val = d.pop_front();
    assert(val == 0);
    assert(d.size() == 2);
    assert(d[0] == 1);
    assert(d[1] == 2);
    
    TEST_PASS("Deque push and pop operations");
}

void test_deque_empty_operations() {
    TEST_GROUP("Deque empty operations");
    
    Deque<int> d;
    
    // Pop from empty deque
    try {
        d.pop_back();
        assert(false && "Should throw exception");
    } catch (const std::out_of_range&) {
        // Expected
    }
    
    try {
        d.pop_front();
        assert(false && "Should throw exception");
    } catch (const std::out_of_range&) {
        // Expected
    }
    
    TEST_PASS("Deque empty operations");
}

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
        // Expected
    }
    
    TEST_PASS("Deque at");
}

void test_deque_circular_buffer() {
    TEST_GROUP("Deque circular buffer behavior");
    
    Deque<int> d;
    
    // Fill deque
    for (int i = 0; i < 5; ++i) {
        d.push_back(i);
    }
    
    // Remove from front and add to back
    d.pop_front();
    d.push_back(5);
    assert(d.size() == 5);
    assert(d[0] == 1);
    assert(d[4] == 5);
    
    // Remove from back and add to front
    d.pop_back();
    d.push_front(0);
    assert(d.size() == 5);
    assert(d[0] == 0);
    assert(d[1] == 1);
    
    TEST_PASS("Deque circular buffer behavior");
}

void test_deque_edge_cases() {
    TEST_GROUP("Deque edge cases");
    
    // Empty deque operations
    Deque<int> d;
    assert(d.empty());
    assert(d.size() == 0);
    
    // Single element operations
    d.push_back(42);
    assert(d.size() == 1);
    int val = d.pop_back();
    assert(val == 42);
    assert(d.empty());
    
    // Push front on empty
    d.push_front(10);
    assert(d.size() == 1);
    assert(d[0] == 10);
    
    // Large number of operations (test reallocation)
    Deque<int> d2;
    for (int i = 0; i < 100; ++i) {
        if (i % 2 == 0)
            d2.push_back(i);
        else
            d2.push_front(i);
    }
    assert(d2.size() == 100);
    
    // Alternating push/pop
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
    
    // Self-assignment
    Deque<int> d4;
    d4.push_back(1);
    d4 = d4;
    assert(d4.size() == 1);
    assert(d4[0] == 1);
    
    // Zero-size constructor
    Deque<int> d5(0, 5);
    assert(d5.size() == 0);
    assert(d5.empty());
    
    TEST_PASS("Deque edge cases");
}

void test_deque_stress() {
    TEST_GROUP("Deque stress tests");
    
    Deque<int> d;
    
    // Push many to back
    for (int i = 0; i < 5000; ++i) {
        d.push_back(i);
        assert(d.size() == static_cast<size_t>(i + 1));
    }
    
    // Push many to front
    for (int i = 0; i < 5000; ++i) {
        d.push_front(-i - 1);
    }
    assert(d.size() == 10000);
    
    // Verify elements
    for (int i = 0; i < 5000; ++i) {
        assert(d[i] == -5000 + i);
    }
    
    // Pop from both ends
    for (int i = 0; i < 2500; ++i) {
        d.pop_front();
        d.pop_back();
    }
    assert(d.size() == 5000);
    
    TEST_PASS("Deque stress tests");
}

void test_deque_wraparound() {
    TEST_GROUP("Deque wraparound behavior");
    
    Deque<int> d;
    
    // Fill deque
    for (int i = 0; i < 10; ++i) {
        d.push_back(i);
    }
    
    // Remove from front and add to back multiple times
    for (int i = 0; i < 20; ++i) {
        d.pop_front();
        d.push_back(i + 10);
    }
    
    assert(d.size() == 10);
    
    // Verify circular buffer worked correctly
    for (size_t i = 0; i < d.size(); ++i) {
        assert(d[i] == static_cast<int>(i + 20));
    }
    
    TEST_PASS("Deque wraparound behavior");
}

void test_deque_capacity_growth() {
    TEST_GROUP("Deque capacity growth");
    
    Deque<int> d;
    size_t prev_capacity = 0;
    
    // Monitor capacity changes
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

void test_deque_mixed_operations() {
    TEST_GROUP("Deque mixed operations");
    
    Deque<int> d;
    
    // Complex sequence of operations
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
        
        TEST_SUCCESS("Deque");
        return 0;
    } catch (const std::exception& e) {
        TEST_FAIL(e.what());
        return 1;
    }
}
