#include <iostream>
#include <cassert>
#include <stdexcept>
#include "test_colors.hpp"
#include "super_lib.hpp"

void test_stack_constructor() {
    TEST_GROUP("Stack constructors");
    
    // Default constructor
    Stack<int> s1;
    assert(s1.size() == 0);
    assert(s1.capacity() == 0);
    assert(s1.empty());
    
    // Constructor with count and value
    Stack<int> s2(5, 10);
    assert(s2.size() == 5);
    assert(s2.capacity() == 5);
    for (size_t i = 0; i < 5; ++i) {
        assert(s2[i] == 10);
    }
    
    // Copy constructor
    Stack<int> s3(s2);
    assert(s3.size() == s2.size());
    for (size_t i = 0; i < s3.size(); ++i) {
        assert(s3[i] == s2[i]);
    }
    
    // Move constructor
    Stack<int> s4(std::move(s3));
    assert(s4.size() == 5);
    assert(s3.size() == 0);
    
    TEST_PASS("Stack constructors");
}

void test_stack_operators() {
    TEST_GROUP("Stack operators");
    
    Stack<int> s1(3, 5);
    
    // operator[]
    assert(s1[0] == 5);
    s1[1] = 10;
    assert(s1[1] == 10);
    
    // operator[] out of range
    try {
        s1[10];
        assert(false && "Should throw exception");
    } catch (const std::out_of_range&) {
        // Expected
    }
    
    // Copy assignment
    Stack<int> s2;
    s2 = s1;
    assert(s2.size() == s1.size());
    assert(s2[1] == 10);
    
    // Move assignment
    Stack<int> s3;
    s3 = std::move(s2);
    assert(s3.size() == 3);
    assert(s2.size() == 0);
    
    TEST_PASS("Stack operators");
}

void test_stack_push_pop() {
    TEST_GROUP("Stack push and pop");
    
    Stack<int> s;
    
    // Push elements
    s.push(1);
    s.push(2);
    s.push(3);
    assert(s.size() == 3);
    assert(s[2] == 3);  // Top element
    
    // Pop elements (LIFO - Last In First Out)
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
    
    // Pop from empty stack
    try {
        s.pop();
        assert(false && "Should throw exception");
    } catch (const std::out_of_range&) {
        // Expected
    }
    
    TEST_PASS("Stack push and pop");
}

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
        // Expected
    }
    
    TEST_PASS("Stack at");
}

void test_stack_iterators() {
    TEST_GROUP("Stack iterators");
    
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    
    int sum = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
        sum += *it;
    }
    assert(sum == 6);
    
    TEST_PASS("Stack iterators");
}

void test_stack_edge_cases() {
    TEST_GROUP("Stack edge cases");
    
    // Empty stack operations
    Stack<int> s;
    assert(s.empty());
    assert(s.size() == 0);
    
    // Single element operations
    s.push(42);
    assert(s.size() == 1);
    int val = s.pop();
    assert(val == 42);
    assert(s.empty());
    
    // Large number of pushes (test reallocation)
    Stack<int> s2;
    for (int i = 0; i < 1000; ++i) {
        s2.push(i);
    }
    assert(s2.size() == 1000);
    
    // Pop all in reverse order
    for (int i = 999; i >= 0; --i) {
        int popped = s2.pop();
        assert(popped == i);
    }
    assert(s2.empty());
    
    // Self-assignment
    Stack<int> s3;
    s3.push(1);
    s3 = s3;
    assert(s3.size() == 1);
    assert(s3[0] == 1);
    
    // Zero-size constructor
    Stack<int> s4(0, 5);
    assert(s4.size() == 0);
    assert(s4.empty());
    
    TEST_PASS("Stack edge cases");
}

void test_stack_stress() {
    TEST_GROUP("Stack stress tests");
    
    Stack<int> s;
    
    // Push many elements
    for (int i = 0; i < 10000; ++i) {
        s.push(i);
        assert(s.size() == static_cast<size_t>(i + 1));
    }
    
    // Verify top elements without popping
    assert(s[9999] == 9999);
    assert(s.at(9999) == 9999);
    
    // Pop half
    for (int i = 0; i < 5000; ++i) {
        int val = s.pop();
        assert(val == 9999 - i);
    }
    assert(s.size() == 5000);
    
    // Push more
    for (int i = 0; i < 3000; ++i) {
        s.push(i + 10000);
    }
    assert(s.size() == 8000);
    
    TEST_PASS("Stack stress tests");
}

void test_stack_lifo_behavior() {
    TEST_GROUP("Stack LIFO behavior");
    
    Stack<int> s;
    
    // Push sequence
    for (int i = 0; i < 100; ++i) {
        s.push(i);
    }
    
    // Verify LIFO order
    for (int i = 99; i >= 0; --i) {
        assert(s[s.size() - 1] == i);
        int val = s.pop();
        assert(val == i);
    }
    
    assert(s.empty());
    
    // Mixed operations
    s.push(1);
    s.push(2);
    assert(s.pop() == 2);
    s.push(3);
    assert(s.pop() == 3);
    assert(s.pop() == 1);
    
    TEST_PASS("Stack LIFO behavior");
}

void test_stack_capacity_management() {
    TEST_GROUP("Stack capacity management");
    
    Stack<int> s;
    
    // Track capacity growth
    size_t prev_capacity = 0;
    for (int i = 0; i < 100; ++i) {
        s.push(i);
        if (s.capacity() != prev_capacity) {
            assert(s.capacity() >= s.size());
            prev_capacity = s.capacity();
        }
    }
    
    // Verify shrinking on clear
    s.clear();
    assert(s.size() == 0);
    assert(s.empty());
    
    TEST_PASS("Stack capacity management");
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
        
        TEST_SUCCESS("Stack");
        return 0;
    } catch (const std::exception& e) {
        TEST_FAIL(e.what());
        return 1;
    }
}
