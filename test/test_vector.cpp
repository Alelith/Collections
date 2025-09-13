#include "../include/vector.hpp"
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
    Vector<int> v;
    print_result("Vector empty at start", v.empty() && v.size() == 0 && v.capacity() == 0);
    v.add(10);
    print_result("add: size==1", v.size() == 1);
    print_result("add: value==10", v[0] == 10);
    v.add(20);
    print_result("add: size==2", v.size() == 2);
    print_result("add: value==20", v[1] == 20);
    int erased = v.erase(0);
    print_result("erase(0): removes and returns correct value", erased == 10 && v.size() == 1 && v[0] == 20);
    v.insert(1, 42);
    print_result("insert(1,42): inserts at end", v[1] == 42 && v.size() == 2);
    v.clear();
    print_result("clear leaves vector empty", v.empty() && v.size() == 0);
    // Test add after clear
    v.add(99);
    print_result("add after clear", v.size() == 1 && v[0] == 99);
    v.clear();
    // Test insert at beginning
    v.insert(0, 123);
    print_result("insert at beginning on empty vector", v.size() == 1 && v[0] == 123);
    v.clear();
    // Test add many elements
    for (int i = 0; i < 100; ++i) v.add(i);
    print_result("add 100 elements", v.size() == 100 && v[99] == 99);
    // Test erase all
    for (int i = 0; i < 100; ++i) v.erase(0);
    print_result("erase all elements", v.empty());
}


void test_strict() {
    Vector<int> v;
    bool except = false;
    try { v[0]; } catch (const std::out_of_range&) { except = true; }
    print_result("operator[] out of range throws exception", except);
    except = false;
    try { v.erase(0); } catch (const std::out_of_range&) { except = true; }
    print_result("erase on empty vector throws exception", except);
    except = false;
    try { v.insert(2, 5); } catch (const std::out_of_range&) { except = true; }
    print_result("insert out of range throws exception", except);
    v.add(1); v.add(2); v.add(3);
    v.insert(0, 0);
    print_result("insert(0,0): inserts at beginning", v[0] == 0);
    v.erase(1);
    print_result("erase(1): removes correct value", v[1] == 2);
    // Test at() const correctness
    const Vector<int>& cv = v;
    except = false;
    try { cv.at(100); } catch (const std::out_of_range&) { except = true; }
    print_result("const at() out of range throws exception", except);
    print_result("const at() returns correct value", cv.at(0) == 0);
    // Test copy constructor
    Vector<int> v2(v);
    print_result("copy constructor copies values", v2.size() == v.size() && v2[0] == v[0]);
    // Test assignment operator
    Vector<int> v3;
    v3 = v;
    print_result("assignment operator copies values", v3.size() == v.size() && v3[0] == v[0]);
    // Test move constructor
    Vector<int> v4(std::move(v3));
    print_result("move constructor moves values", v4.size() == v2.size() && v4[0] == v2[0]);
    // Test move assignment
    Vector<int> v5;
    v5 = std::move(v4);
    print_result("move assignment moves values", v5.size() == v2.size() && v5[0] == v2[0]);
    // Test data() and iterators
    v5.add(100);
    int* data_ptr = v5.data();
    print_result("data() returns pointer to first element", *data_ptr == v5[0]);
    int sum = 0;
    for (auto it = v5.begin(); it != v5.end(); ++it) sum += *it;
    print_result("iterator range sums correctly", sum == v5[0] + v5[1]);
}


int main() {
    std::cout << "\n--- Basic Vector Test ---\n";
    test_basic();
    std::cout << "\n--- Strict Vector Test ---\n";
    test_strict();
    std::cout << "\nAll Vector tests completed.\n";
    return 0;
}
