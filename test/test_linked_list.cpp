#include "../include/linked_list.hpp"
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
    LinkedList<int> l;
    print_result("LinkedList empty at start", l.empty() && l.size() == 0);
    l.add(10);
    print_result("add: size==1", l.size() == 1);
    print_result("add: value==10", l[0] == 10);
    l.add(20);
    print_result("add: size==2", l.size() == 2);
    print_result("add: value==20", l[1] == 20);
    int erased = l.erase(0);
    print_result("erase(0): removes and returns correct value", erased == 10 && l.size() == 1 && l[0] == 20);
    l.insert(1, 42);
    print_result("insert(1,42): inserts at end", l[1] == 42 && l.size() == 2);
    l.clear();
    print_result("clear leaves list empty", l.empty());
    // Test add after clear
    l.add(99);
    print_result("add after clear", l.size() == 1 && l[0] == 99);
    l.clear();
    // Test insert at beginning
    l.insert(0, 123);
    print_result("insert at beginning on empty list", l.size() == 1 && l[0] == 123);
    l.clear();
    // Test add many elements
    for (int i = 0; i < 100; ++i) l.add(i);
    print_result("add 100 elements", l.size() == 100 && l[99] == 99);
    // Test erase all
    for (int i = 0; i < 100; ++i) l.erase(0);
    print_result("erase all elements", l.empty());
}


void test_strict() {
    LinkedList<int> l;
    bool except = false;
    try { l[0]; } catch (const std::out_of_range&) { except = true; }
    print_result("operator[] out of range throws exception", except);
    except = false;
    try { l.erase(0); } catch (const std::out_of_range&) { except = true; }
    print_result("erase on empty list throws exception", except);
    except = false;
    try { l.insert(2, 5); } catch (const std::out_of_range&) { except = true; }
    print_result("insert out of range throws exception", except);
    l.add(1); l.add(2); l.add(3);
    l.insert(0, 0);
    print_result("insert(0,0): inserts at beginning", l[0] == 0);
    l.erase(1);
    print_result("erase(1): removes correct value", l[1] == 2);
    // Test copy constructor
    LinkedList<int> l2(l);
    print_result("copy constructor copies values", l2.size() == l.size() && l2[0] == l[0]);
    // Test assignment operator
    LinkedList<int> l3;
    l3 = l;
    print_result("assignment operator copies values", l3.size() == l.size() && l3[0] == l[0]);
    // Test move constructor
    LinkedList<int> l4(std::move(l3));
    print_result("move constructor moves values", l4.size() == l2.size() && l4[0] == l2[0]);
    // Test move assignment
    LinkedList<int> l5;
    l5 = std::move(l4);
    print_result("move assignment moves values", l5.size() == l2.size() && l5[0] == l2[0]);
}


int main() {
    std::cout << "\n--- Basic LinkedList Test ---\n";
    test_basic();
    std::cout << "\n--- Strict LinkedList Test ---\n";
    test_strict();
    std::cout << "\nAll LinkedList tests completed.\n";
    return 0;
}
