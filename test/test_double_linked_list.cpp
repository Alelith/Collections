#include <iostream>
#include <cassert>
#include <stdexcept>
#include "test_colors.hpp"
#include "double_linked_list.hpp"

void test_double_linked_list_constructor() {
    TEST_GROUP("DoubleLinkedList constructors");
    
    // Default constructor
    DoubleLinkedList<int> l1;
    assert(l1.size() == 0);
    assert(l1.empty());
    assert(l1.head() == nullptr);
    assert(l1.tail() == nullptr);
    
    // Constructor with count and value
    DoubleLinkedList<int> l2(5, 10);
    assert(l2.size() == 5);
    for (size_t i = 0; i < 5; ++i) {
        assert(l2[i] == 10);
    }
    
    // Copy constructor
    DoubleLinkedList<int> l3(l2);
    assert(l3.size() == l2.size());
    for (size_t i = 0; i < l3.size(); ++i) {
        assert(l3[i] == l2[i]);
    }
    
    // Move constructor
    DoubleLinkedList<int> l4(std::move(l3));
    assert(l4.size() == 5);
    assert(l3.size() == 0);
    
    TEST_PASS("DoubleLinkedList constructors");
}

void test_double_linked_list_operators() {
    TEST_GROUP("DoubleLinkedList operators");
    
    DoubleLinkedList<int> l1(3, 5);
    
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
    DoubleLinkedList<int> l2;
    l2 = l1;
    assert(l2.size() == l1.size());
    assert(l2[1] == 10);
    
    // Move assignment
    DoubleLinkedList<int> l3;
    l3 = std::move(l2);
    assert(l3.size() == 3);
    assert(l2.size() == 0);
    
    TEST_PASS("DoubleLinkedList operators");
}

void test_double_linked_list_add_insert() {
    TEST_GROUP("DoubleLinkedList add and insert");
    
    DoubleLinkedList<int> l;
    
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
    
    TEST_PASS("DoubleLinkedList add and insert");
}

void test_double_linked_list_erase() {
    TEST_GROUP("DoubleLinkedList erase");
    
    DoubleLinkedList<int> l;
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
    
    TEST_PASS("DoubleLinkedList erase");
}

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
        // Expected
    }
    
    TEST_PASS("DoubleLinkedList at");
}

void test_double_linked_list_bidirectional() {
    TEST_GROUP("DoubleLinkedList bidirectional access");
    
    DoubleLinkedList<int> l;
    l.add(1);
    l.add(2);
    l.add(3);
    l.add(4);
    l.add(5);
    
    // Verify prev pointers
    auto node = l.tail();
    int expected = 5;
    while (node) {
        assert(node->data == expected);
        node = node->prev;
        expected--;
    }
    
    // Test access optimization (should use backward traversal for indices > size/2)
    assert(l[4] == 5);
    assert(l[3] == 4);
    
    TEST_PASS("DoubleLinkedList bidirectional access");
}

void test_double_linked_list_edge_cases() {
    TEST_GROUP("DoubleLinkedList edge cases");
    
    // Empty list operations
    DoubleLinkedList<int> l;
    assert(l.empty());
    assert(l.size() == 0);
    
    // Single element operations
    l.add(42);
    assert(l.size() == 1);
    assert(l.head() == l.tail());
    assert(l.head()->prev == nullptr);
    assert(l.head()->next == nullptr);
    
    int val = l.erase(0);
    assert(val == 42);
    assert(l.empty());
    
    // Large number of additions
    DoubleLinkedList<int> l2;
    for (int i = 0; i < 1000; ++i) {
        l2.add(i);
    }
    assert(l2.size() == 1000);
    assert(l2[999] == 999);
    assert(l2[0] == 0);
    
    // Self-assignment
    DoubleLinkedList<int> l3;
    l3.add(1);
    l3 = l3;
    assert(l3.size() == 1);
    assert(l3[0] == 1);
    
    // Zero-size constructor
    DoubleLinkedList<int> l4(0, 5);
    assert(l4.size() == 0);
    assert(l4.empty());
    
    TEST_PASS("DoubleLinkedList edge cases");
}

void test_double_linked_list_stress() {
    TEST_GROUP("DoubleLinkedList stress tests");
    
    DoubleLinkedList<int> l;
    
    // Add many elements
    for (int i = 0; i < 5000; ++i) {
        l.add(i);
    }
    
    // Access from both ends repeatedly
    for (int i = 0; i < 100; ++i) {
        assert(l[i] == i);
        assert(l[4999 - i] == 4999 - i);
    }
    
    // Erase from both ends
    for (int i = 0; i < 500; ++i) {
        l.erase(0);
        l.erase(l.size() - 1);
    }
    assert(l.size() == 4000);
    
    // Verify middle elements
    assert(l[0] == 500);
    assert(l[l.size() - 1] == 4499);
    
    TEST_PASS("DoubleLinkedList stress tests");
}

void test_double_linked_list_bidirectional_iteration() {
    TEST_GROUP("DoubleLinkedList bidirectional iteration");
    
    DoubleLinkedList<int> l;
    for (int i = 0; i < 100; ++i) {
        l.add(i);
    }
    
    // Forward iteration
    auto node = l.head();
    int count = 0;
    while (node) {
        assert(node->data == count);
        node = node->next;
        count++;
    }
    assert(count == 100);
    
    // Backward iteration
    node = l.tail();
    count = 99;
    while (node) {
        assert(node->data == count);
        node = node->prev;
        count--;
    }
    assert(count == -1);
    
    // Verify prev/next consistency
    node = l.head();
    while (node->next) {
        assert(node->next->prev == node);
        node = node->next;
    }
    
    TEST_PASS("DoubleLinkedList bidirectional iteration");
}

void test_double_linked_list_access_optimization() {
    TEST_GROUP("DoubleLinkedList access optimization");
    
    DoubleLinkedList<int> l;
    for (int i = 0; i < 1000; ++i) {
        l.add(i);
    }
    
    // Access elements near end (should use backward traversal)
    for (int i = 900; i < 1000; ++i) {
        assert(l[i] == i);
        assert(l.at(i) == i);
    }
    
    // Access elements near beginning (should use forward traversal)
    for (int i = 0; i < 100; ++i) {
        assert(l[i] == i);
        assert(l.at(i) == i);
    }
    
    // Access middle elements
    for (int i = 400; i < 600; ++i) {
        assert(l[i] == i);
    }
    
    TEST_PASS("DoubleLinkedList access optimization");
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
        
        TEST_SUCCESS("DoubleLinkedList");
        return 0;
    } catch (const std::exception& e) {
        TEST_FAIL(e.what());
        return 1;
    }
}
