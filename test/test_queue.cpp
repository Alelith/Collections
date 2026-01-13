#include <iostream>
#include <cassert>
#include <stdexcept>
#include "test_colors.hpp"
#include "super_lib.hpp"

void test_queue_constructor() {
    TEST_GROUP("Queue constructors");
    
    // Default constructor
    Queue<int> q1;
    assert(q1.size() == 0);
    assert(q1.empty());
    assert(q1.head() == nullptr);
    assert(q1.tail() == nullptr);
    
    // Constructor with count and value
    Queue<int> q2(5, 10);
    assert(q2.size() == 5);
    for (size_t i = 0; i < 5; ++i) {
        assert(q2[i] == 10);
    }
    
    // Copy constructor
    Queue<int> q3(q2);
    assert(q3.size() == q2.size());
    for (size_t i = 0; i < q3.size(); ++i) {
        assert(q3[i] == q2[i]);
    }
    
    // Move constructor
    Queue<int> q4(std::move(q3));
    assert(q4.size() == 5);
    assert(q3.size() == 0);
    
    TEST_PASS("Queue constructors");
}

void test_queue_operators() {
    TEST_GROUP("Queue operators");
    
    Queue<int> q1(3, 5);
    
    // operator[]
    assert(q1[0] == 5);
    q1[1] = 10;
    assert(q1[1] == 10);
    
    // operator[] out of range
    try {
        q1[10];
        assert(false && "Should throw exception");
    } catch (const std::out_of_range&) {
        // Expected
    }
    
    // Copy assignment
    Queue<int> q2;
    q2 = q1;
    assert(q2.size() == q1.size());
    assert(q2[1] == 10);
    
    // Move assignment
    Queue<int> q3;
    q3 = std::move(q2);
    assert(q3.size() == 3);
    assert(q2.size() == 0);
    
    TEST_PASS("Queue operators");
}

void test_queue_enqueue_dequeue() {
    TEST_GROUP("Queue enqueue and dequeue");
    
    Queue<int> q;
    
    // Enqueue elements
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    assert(q.size() == 3);
    assert(q[0] == 1);
    assert(q[1] == 2);
    assert(q[2] == 3);
    
    // Dequeue elements (FIFO - First In First Out)
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
    
    // Dequeue from empty queue
    try {
        q.dequeue();
        assert(false && "Should throw exception");
    } catch (const std::out_of_range&) {
        // Expected
    }
    
    TEST_PASS("Queue enqueue and dequeue");
}

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
        // Expected
    }
    
    TEST_PASS("Queue at");
}

void test_queue_head_tail() {
    TEST_GROUP("Queue head and tail");
    
    Queue<int> q;
    
    // Empty queue
    assert(q.head() == nullptr);
    assert(q.tail() == nullptr);
    
    // Single element
    q.enqueue(1);
    assert(q.head() != nullptr);
    assert(q.tail() != nullptr);
    assert(q.head() == q.tail());
    assert(q.head()->data == 1);
    
    // Multiple elements
    q.enqueue(2);
    q.enqueue(3);
    assert(q.head()->data == 1);
    assert(q.tail()->data == 3);
    
    TEST_PASS("Queue head and tail");
}

void test_queue_edge_cases() {
    TEST_GROUP("Queue edge cases");
    
    // Empty queue operations
    Queue<int> q;
    assert(q.empty());
    assert(q.size() == 0);
    
    // Single element operations
    q.enqueue(42);
    assert(q.size() == 1);
    int val = q.dequeue();
    assert(val == 42);
    assert(q.empty());
    
    // Large number of enqueues
    Queue<int> q2;
    for (int i = 0; i < 1000; ++i) {
        q2.enqueue(i);
    }
    assert(q2.size() == 1000);
    
    // Dequeue all in FIFO order
    for (int i = 0; i < 1000; ++i) {
        int dequeued = q2.dequeue();
        assert(dequeued == i);
    }
    assert(q2.empty());
    
    // Self-assignment
    Queue<int> q3;
    q3.enqueue(1);
    q3 = q3;
    assert(q3.size() == 1);
    assert(q3[0] == 1);
    
    // Zero-size constructor
    Queue<int> q4(0, 5);
    assert(q4.size() == 0);
    assert(q4.empty());
    
    // Mixed enqueue and dequeue operations
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

void test_queue_stress() {
    TEST_GROUP("Queue stress tests");
    
    Queue<int> q;
    
    // Enqueue many elements
    for (int i = 0; i < 10000; ++i) {
        q.enqueue(i);
        assert(q.size() == static_cast<size_t>(i + 1));
    }
    
    // Dequeue half, enqueue more
    for (int i = 0; i < 5000; ++i) {
        int val = q.dequeue();
        assert(val == i);
    }
    
    for (int i = 0; i < 3000; ++i) {
        q.enqueue(i + 10000);
    }
    
    assert(q.size() == 8000);
    
    TEST_PASS("Queue stress tests");
}

void test_queue_fifo_behavior() {
    TEST_GROUP("Queue FIFO behavior");
    
    Queue<int> q;
    
    // Enqueue sequence
    for (int i = 0; i < 100; ++i) {
        q.enqueue(i);
    }
    
    // Verify FIFO order (dequeue from head which was enqueued first)
    for (int i = 0; i < 100; ++i) {
        int val = q.dequeue();
        assert(val == i);
    }
    
    assert(q.empty());
    
    // Mixed operations maintaining FIFO
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

void test_queue_pointer_integrity() {
    TEST_GROUP("Queue pointer integrity");
    
    Queue<int> q;
    
    // Build queue
    for (int i = 0; i < 50; ++i) {
        q.enqueue(i);
    }
    
    // Verify head and tail pointers
    assert(q.head() != nullptr);
    assert(q.tail() != nullptr);
    assert(q.head()->data == 0);
    assert(q.tail()->data == 49);
    
    // Check next/prev consistency
    auto node = q.head();
    int count = 0;
    while (node) {
        assert(node->data == count);
        if (node->next) {
            assert(node->next->prev == node);
        }
        node = node->next;
        count++;
    }
    assert(count == 50);
    
    TEST_PASS("Queue pointer integrity");
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
        
        TEST_SUCCESS("Queue");
        return 0;
    } catch (const std::exception& e) {
        TEST_FAIL(e.what());
        return 1;
    }
}
