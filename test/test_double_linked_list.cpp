#include "../include/double_linked_list.hpp"
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
    DoubleLinkedList<int> d;
    print_result("DoubleLinkedList empty at start", d.empty() && d.size() == 0);
    d.add(10);
    print_result("add: size==1", d.size() == 1);
    print_result("add: value==10", d[0] == 10);
    d.add(20);
    print_result("add: size==2", d.size() == 2);
    print_result("add: value==20", d[1] == 20);
    int erased = d.erase(0);
    print_result("erase(0): removes and returns correct value", erased == 10 && d.size() == 1 && d[0] == 20);
    d.insert(1, 42);
    print_result("insert(1,42): inserts at end", d[1] == 42 && d.size() == 2);
    d.clear();
    print_result("clear leaves list empty", d.empty());
    // Test add after clear
    d.add(99);
    print_result("add after clear", d.size() == 1 && d[0] == 99);
    d.clear();
    // Test insert at beginning
    d.insert(0, 123);
    print_result("insert at beginning on empty list", d.size() == 1 && d[0] == 123);
    d.clear();
    // Test add many elements
    for (int i = 0; i < 100; ++i) d.add(i);
    print_result("add 100 elements", d.size() == 100 && d[99] == 99);
    // Test erase all
    for (int i = 0; i < 100; ++i) d.erase(0);
    print_result("erase all elements", d.empty());
}

void test_strict() {
    DoubleLinkedList<int> d;
    bool except = false;
    try { d[0]; } catch (const std::out_of_range&) { except = true; }
    print_result("operator[] out of range throws exception", except);
    except = false;
    try { d.erase(0); } catch (const std::out_of_range&) { except = true; }
    print_result("erase on empty list throws exception", except);
    except = false;
    try { d.insert(2, 5); } catch (const std::out_of_range&) { except = true; }
    print_result("insert out of range throws exception", except);
    d.add(1); d.add(2); d.add(3);
    d.insert(0, 0);
    print_result("insert(0,0): inserts at beginning", d[0] == 0);
    d.erase(1);
    print_result("erase(1): removes correct value", d[1] == 2);
    // Test copy constructor
    DoubleLinkedList<int> d2(d);
    print_result("copy constructor copies values", d2.size() == d.size() && d2[0] == d[0]);
    // Test assignment operator
    DoubleLinkedList<int> d3;
    d3 = d;
    print_result("assignment operator copies values", d3.size() == d.size() && d3[0] == d[0]);
    // Test move constructor
    DoubleLinkedList<int> d4(std::move(d3));
    print_result("move constructor moves values", d4.size() == d2.size() && d4[0] == d2[0]);
    // Test move assignment
    DoubleLinkedList<int> d5;
    d5 = std::move(d4);
    print_result("move assignment moves values", d5.size() == d2.size() && d5[0] == d2[0]);
}

int main() {
    std::cout << "\n--- Basic DoubleLinkedList Test ---\n";
    test_basic();
    std::cout << "\n--- Strict DoubleLinkedList Test ---\n";
    test_strict();
    std::cout << "\nAll DoubleLinkedList tests completed.\n";
    return 0;
}
