#include <iostream>
#include <cassert>
#include <stdexcept>
#include "test_colors.hpp"
#include "linked_list.hpp"

void test_linked_list_constructor() {
    TEST_GROUP("LinkedList constructors");
    
    // Default constructor
    LinkedList<int> l1;
    assert(l1.size() == 0);
    assert(l1.empty());
    assert(l1.head() == nullptr);
    assert(l1.tail() == nullptr);
    
    // Constructor with count and value
    LinkedList<int> l2(5, 10);
    assert(l2.size() == 5);
    for (size_t i = 0; i < 5; ++i) {
        assert(l2[i] == 10);
    }
    
    // Copy constructor
    LinkedList<int> l3(l2);
    assert(l3.size() == l2.size());
    for (size_t i = 0; i < l3.size(); ++i) {
        assert(l3[i] == l2[i]);
    }
    
    // Move constructor
    LinkedList<int> l4(std::move(l3));
    assert(l4.size() == 5);
    assert(l3.size() == 0);
    
    TEST_PASS("LinkedList constructors");
}

void test_linked_list_operators() {
    TEST_GROUP("LinkedList operators");
    
    LinkedList<int> l1(3, 5);
    
    // operator[]
    assert(l1[0] == 5);
    l1[1] = 10;
    assert(l1[1] == 10);
    
    // operator[] out of range
    try {
        l1[10];
        assert(false && "Should throw exception");
    } catch (const std::out_of_range&) {
        // Expected
    }
    
    // Copy assignment
    LinkedList<int> l2;
    l2 = l1;
    assert(l2.size() == l1.size());
    assert(l2[1] == 10);
    
    // Move assignment
    LinkedList<int> l3;
    l3 = std::move(l2);
    assert(l3.size() == 3);
    assert(l2.size() == 0);
    
    TEST_PASS("LinkedList operators");
}

void test_linked_list_add_insert() {
    TEST_GROUP("LinkedList add and insert");
    
    LinkedList<int> l;
    
    // Add elements
    l.add(1);
    l.add(2);
    l.add(3);
    assert(l.size() == 3);
    assert(l[0] == 1);
    assert(l[1] == 2);
    assert(l[2] == 3);
    
    // Insert at beginning
    l.insert(0, 0);
    assert(l.size() == 4);
    assert(l[0] == 0);
    assert(l[1] == 1);
    
    // Insert in middle
    l.insert(2, 99);
    assert(l.size() == 5);
    assert(l[2] == 99);
    
    // Insert at end
    l.insert(l.size(), 100);
    assert(l[l.size() - 1] == 100);
    
    // Insert out of range
    try {
        l.insert(100, 1);
        assert(false && "Should throw exception");
    } catch (const std::out_of_range&) {
        // Expected
    }
    
    TEST_PASS("LinkedList add and insert");
}

void test_linked_list_erase() {
    TEST_GROUP("LinkedList erase");
    
    LinkedList<int> l;
    l.add(1);
    l.add(2);
    l.add(3);
    l.add(4);
    l.add(5);
    
    // Erase from middle
    int erased = l.erase(2);
    assert(erased == 3);
    assert(l.size() == 4);
    assert(l[2] == 4);
    
    // Erase from beginning
    erased = l.erase(0);
    assert(erased == 1);
    assert(l.size() == 3);
    
    // Erase from end
    erased = l.erase(l.size() - 1);
    assert(erased == 5);
    assert(l.size() == 2);
    
    // Erase out of range
    try {
        l.erase(100);
        assert(false && "Should throw exception");
    } catch (const std::out_of_range&) {
        // Expected
    }
    
    TEST_PASS("LinkedList erase");
}

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
        // Expected
    }
    
    TEST_PASS("LinkedList at");
}

void test_linked_list_head_tail() {
    TEST_GROUP("LinkedList head and tail");
    
    LinkedList<int> l;
    
    // Empty list
    assert(l.head() == nullptr);
    assert(l.tail() == nullptr);
    
    // Single element
    l.add(1);
    assert(l.head() != nullptr);
    assert(l.tail() != nullptr);
    assert(l.head() == l.tail());
    assert(l.head()->data == 1);
    
    // Multiple elements
    l.add(2);
    l.add(3);
    assert(l.head()->data == 1);
    assert(l.tail()->data == 3);
    
    TEST_PASS("LinkedList head and tail");
}

void test_linked_list_edge_cases() {
    TEST_GROUP("LinkedList edge cases");
    
    // Empty list operations
    LinkedList<int> l;
    assert(l.empty());
    assert(l.size() == 0);
    
    // Single element operations
    l.add(42);
    assert(l.size() == 1);
    int val = l.erase(0);
    assert(val == 42);
    assert(l.empty());
    
    // Large number of additions
    LinkedList<int> l2;
    for (int i = 0; i < 1000; ++i) {
        l2.add(i);
    }
    assert(l2.size() == 1000);
    assert(l2[999] == 999);
    
    // Self-assignment
    LinkedList<int> l3;
    l3.add(1);
    l3 = l3;
    assert(l3.size() == 1);
    assert(l3[0] == 1);
    
    // Zero-size constructor
    LinkedList<int> l4(0, 5);
    assert(l4.size() == 0);
    assert(l4.empty());
    
    TEST_PASS("LinkedList edge cases");
}

void test_linked_list_stress() {
    TEST_GROUP("LinkedList stress tests");
    
    LinkedList<int> l;
    
    // Add many elements
    for (int i = 0; i < 5000; ++i) {
        l.add(i);
        assert(l.size() == static_cast<size_t>(i + 1));
    }
    
    // Verify all elements
    for (int i = 0; i < 5000; ++i) {
        assert(l[i] == i);
    }
    
    // Erase from middle repeatedly
    for (int i = 0; i < 1000; ++i) {
        size_t mid = l.size() / 2;
        l.erase(mid);
    }
    assert(l.size() == 4000);
    
    // Insert many at beginning
    for (int i = 0; i < 100; ++i) {
        l.insert(0, -i);
    }
    assert(l.size() == 4100);
    assert(l[0] == -99);
    
    TEST_PASS("LinkedList stress tests");
}

void test_linked_list_iteration() {
    TEST_GROUP("LinkedList node iteration");
    
    LinkedList<int> l;
    for (int i = 0; i < 100; ++i) {
        l.add(i);
    }
    
    // Iterate through nodes
    auto node = l.head();
    int count = 0;
    while (node) {
        assert(node->data == count);
        node = node->next;
        count++;
    }
    assert(count == 100);
    
    // Verify tail
    assert(l.tail()->data == 99);
    assert(l.tail()->next == nullptr);
    
    TEST_PASS("LinkedList node iteration");
}

void test_linked_list_alternating_ops() {
    TEST_GROUP("LinkedList alternating operations");
    
    LinkedList<int> l;
    
    // Alternating add and insert
    for (int i = 0; i < 50; ++i) {
        l.add(i * 2);
        if (l.size() > 1) {
            l.insert(l.size() - 1, i * 2 + 1);
        }
    }
    
    // Verify pattern
    assert(l.size() == 99);
    
    // Alternating erase operations
    for (int i = 0; i < 30; ++i) {
        l.erase(0);
        if (l.size() > 0) {
            l.erase(l.size() - 1);
        }
    }
    
    assert(l.size() == 39);
    
    TEST_PASS("LinkedList alternating operations");
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
        
        TEST_SUCCESS("LinkedList");
        return 0;
    } catch (const std::exception& e) {
        TEST_FAIL(e.what());
        return 1;
    }
}
