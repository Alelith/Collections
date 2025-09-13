#include "../include/deque.hpp"
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
    Deque<int> d;
    print_result("Deque empty at start", d.empty() && d.size() == 0);
    d.push_back(10);
    print_result("push_back: size==1", d.size() == 1);
    print_result("push_back: value==10", d[0] == 10);
    d.push_front(20);
    print_result("push_front: size==2", d.size() == 2);
    print_result("push_front: value==20", d[0] == 20);
    int popped = d.pop_back();
    print_result("pop_back: returns last", popped == 10 && d.size() == 1);
    popped = d.pop_front();
    print_result("pop_front: returns first", popped == 20 && d.size() == 0);
    d.push_back(1); d.push_back(2); d.push_back(3); d.push_front(0);
    d.clear();
    print_result("clear leaves deque empty", d.empty());
    // Test push after clear
    d.push_back(99);
    print_result("push_back after clear", d.size() == 1 && d[0] == 99);
    d.clear();
    // Test push many elements
    for (int i = 0; i < 100; ++i) d.push_back(i);
    print_result("push_back 100 elements", d.size() == 100 && d[99] == 99);
    // Test pop all
    for (int i = 0; i < 100; ++i) d.pop_front();
    print_result("pop_front all elements", d.empty());
}

void test_strict() {
    Deque<int> d;
    bool except = false;
    try { d.pop_back(); } catch (const std::out_of_range&) { except = true; }
    print_result("pop_back on empty deque throws exception", except);
    except = false;
    try { d.pop_front(); } catch (const std::out_of_range&) { except = true; }
    print_result("pop_front on empty deque throws exception", except);
    except = false;
    try { d[0]; } catch (const std::out_of_range&) { except = true; }
    print_result("operator[] out of range throws exception", except);
    // Test copy constructor
    d.push_back(1); d.push_back(2); d.push_back(3);
    Deque<int> d2(d);
    print_result("copy constructor copies values", d2.size() == d.size() && d2[0] == d[0]);
    // Test assignment operator
    Deque<int> d3;
    d3 = d;
    print_result("assignment operator copies values", d3.size() == d.size() && d3[0] == d[0]);
    // Test move constructor
    Deque<int> d4(std::move(d3));
    print_result("move constructor moves values", d4.size() == d2.size() && d4[0] == d2[0]);
    // Test move assignment
    Deque<int> d5;
    d5 = std::move(d4);
    print_result("move assignment moves values", d5.size() == d2.size() && d5[0] == d2[0]);
}

int main() {
    std::cout << "\n--- Basic Deque Test ---\n";
    test_basic();
    std::cout << "\n--- Strict Deque Test ---\n";
    test_strict();
    std::cout << "\nAll Deque tests completed.\n";
    return 0;
}
