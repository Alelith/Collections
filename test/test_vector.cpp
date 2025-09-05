#include "vector.hpp"
#include <iostream>
#include <string>
#include <cassert>

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

void print_result(const std::string& test, bool ok) {
    std::cout << test << ": " << (ok ? GREEN "OK" RESET : RED "KO" RESET) << std::endl;
}

int main() {
    // Default constructor
    Vector<int> v;
    print_result("Default constructor: empty", v.empty() && v.size() == 0 && v.capacity() == 0);

    // push_back
    v.push_back(42);
    print_result("push_back: size==1", v.size() == 1);
    print_result("push_back: value==42", v[0] == 42);
    size_t cap_after_first = v.capacity();
    v.push_back(7);
    print_result("push_back: size==2", v.size() == 2);
    print_result("push_back: value==7", v[1] == 7);
    print_result("push_back: capacity not decreased", v.capacity() >= cap_after_first);

    // pop_back
    v.pop_back();
    print_result("pop_back: size==1", v.size() == 1);
    print_result("pop_back: value==42", v[0] == 42);
    v.pop_back();
    print_result("pop_back: size==0", v.size() == 0);
    print_result("pop_back: empty==true", v.empty());

    // clear
    v.push_back(1); v.push_back(2); v.push_back(3);
    v.clear();
    print_result("clear: size==0", v.size() == 0);
    print_result("clear: empty==true", v.empty());
    print_result("clear: capacity==0 after shrink_to_fit", v.capacity() == 0);

    // at()
    v.push_back(10); v.push_back(20);
    bool at_ok = true;
    try { at_ok = (v.at(1) == 20); } catch (...) { at_ok = false; }
    print_result("at: valid index", at_ok);
    bool at_throw = false;
    try { v.at(10); } catch (const std::out_of_range&) { at_throw = true; }
    print_result("at: out_of_range throws", at_throw);

    // Copy constructor
    Vector<int> v2(v);
    print_result("Copy constructor: size", v2.size() == v.size());
    print_result("Copy constructor: value", v2[0] == 10 && v2[1] == 20);

    // Move constructor
    Vector<int> v3(std::move(v2));
    print_result("Move constructor: size", v3.size() == 2);
    print_result("Move constructor: value", v3[1] == 20);

    // Copy assignment
    Vector<int> v4;
    v4 = v3;
    print_result("Copy assignment: size", v4.size() == v3.size());
    print_result("Copy assignment: value", v4[0] == 10 && v4[1] == 20);

    // Move assignment
    Vector<int> v5;
    v5 = std::move(v4);
    print_result("Move assignment: size", v5.size() == 2);
    print_result("Move assignment: value", v5[1] == 20);

    // reserve
    v5.reserve(10);
    print_result("reserve: capacity >= 10", v5.capacity() >= 10);
    size_t old_cap = v5.capacity();
    v5.reserve(5);
    print_result("reserve: capacity not reduced", v5.capacity() == old_cap);

    // shrink_to_fit
    v5.shrink_to_fit();
    print_result("shrink_to_fit: capacity==size", v5.capacity() == v5.size());

    // data()
    int* data_ptr = v5.data();
    print_result("data() not null if not empty", data_ptr != nullptr);
    v5.clear();
    print_result("data() null if empty", v5.data() == nullptr);

    // Iterators
    v5.push_back(1); v5.push_back(2); v5.push_back(3);
    int sum = 0;
    for (auto it = v5.begin(); it != v5.end(); ++it) sum += *it;
    print_result("iterator sum == 6", sum == 6);
    print_result("begin() == data()", v5.begin() == v5.data());
    print_result("end() - begin() == size", v5.end() - v5.begin() == (int)v5.size());

    // Const correctness
    const Vector<int>& cv = v5;
    print_result("const begin() == data()", cv.begin() == cv.data());
    print_result("const end() - begin() == size", cv.end() - cv.begin() == (int)cv.size());

    return 0;
}
