#include "../include/queue.hpp"
#include <iostream>
#include <string>
#include <cassert>

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"


void print_result(const std::string& test, bool ok) {
    std::cout << test << ": " << (ok ? GREEN "OK" RESET : RED "KO" RESET) << std::endl;
}


void test_basic() {
    Queue<int> q;
    print_result("Queue empty at start", q.empty() && q.size() == 0);
    q.enqueue(10);
    print_result("enqueue: size==1", q.size() == 1);
    print_result("enqueue: value==10", q[0] == 10);
    q.enqueue(20);
    print_result("enqueue: size==2", q.size() == 2);
    print_result("enqueue: value==20", q[1] == 20);
    int dq = q.dequeue();
    print_result("dequeue: returns last", dq == 20 && q.size() == 1);
    q.enqueue(30);
    q.enqueue(40);
    print_result("enqueue: size==3", q.size() == 3);
    q.clear();
    print_result("clear leaves queue empty", q.empty());
    // Test enqueue after clear
    q.enqueue(99);
    print_result("enqueue after clear", q.size() == 1 && q[0] == 99);
    q.clear();
    // Test enqueue many elements
    for (int i = 0; i < 100; ++i) q.enqueue(i);
    print_result("enqueue 100 elements", q.size() == 100 && q[99] == 99);
    // Test dequeue all
    for (int i = 0; i < 100; ++i) q.dequeue();
    print_result("dequeue all elements", q.empty());
}


void test_strict() {
    Queue<int> q;
    bool except = false;
    try { q.dequeue(); } catch (const std::out_of_range&) { except = true; }
    print_result("dequeue on empty queue throws exception", except);
    except = false;
    try { q[0]; } catch (const std::out_of_range&) { except = true; }
    print_result("operator[] out of range throws exception", except);
    // Test copy constructor
    q.enqueue(1); q.enqueue(2); q.enqueue(3);
    Queue<int> q2(q);
    print_result("copy constructor copies values", q2.size() == q.size() && q2[0] == q[0]);
    // Test assignment operator
    Queue<int> q3;
    q3 = q;
    print_result("assignment operator copies values", q3.size() == q.size() && q3[0] == q[0]);
    // Test move constructor
    Queue<int> q4(std::move(q3));
    print_result("move constructor moves values", q4.size() == q2.size() && q4[0] == q2[0]);
    // Test move assignment
    Queue<int> q5;
    q5 = std::move(q4);
    print_result("move assignment moves values", q5.size() == q2.size() && q5[0] == q2[0]);
}


int main() {
    std::cout << "\n--- Basic Queue Test ---\n";
    test_basic();
    std::cout << "\n--- Strict Queue Test ---\n";
    test_strict();
    std::cout << "\nAll Queue tests completed.\n";
    return 0;
}
