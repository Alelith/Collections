#include "../include/stack.hpp"
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
    Stack<int> s;
    print_result("Stack empty at start", s.empty() && s.size() == 0);
    s.push(10);
    print_result("push: size==1", s.size() == 1);
    print_result("push: value==10", s[0] == 10);
    s.push(20);
    print_result("push: size==2", s.size() == 2);
    print_result("push: value==20", s[1] == 20);
    int popped = s.pop();
    print_result("pop: returns last", popped == 20 && s.size() == 1);
    s.push(30);
    s.push(40);
    int popped_idx = s.pop();
    print_result("pop(): removes and returns correct value", popped_idx == 40 && s.size() == 2 && s[1] == 30);
    s.clear();
    print_result("clear leaves stack empty", s.empty());
    // Test push after clear
    s.push(99);
    print_result("push after clear", s.size() == 1 && s[0] == 99);
    s.clear();
    // Test push many elements
    for (int i = 0; i < 100; ++i) s.push(i);
    print_result("push 100 elements", s.size() == 100 && s[99] == 99);
    // Test pop all
    for (int i = 0; i < 100; ++i) s.pop();
    print_result("pop all elements", s.empty());
}


void test_strict() {
    Stack<int> s;
    bool except = false;
    try { s.pop(); } catch (const std::out_of_range&) { except = true; }
    print_result("pop on empty stack throws exception", except);
    except = false;
    try { s[0]; } catch (const std::out_of_range&) { except = true; }
    print_result("operator[] out of range throws exception", except);
    // Test copy constructor
    s.push(1); s.push(2); s.push(3);
    Stack<int> s2(s);
    print_result("copy constructor copies values", s2.size() == s.size() && s2[0] == s[0]);
    // Test assignment operator
    Stack<int> s3;
    s3 = s;
    print_result("assignment operator copies values", s3.size() == s.size() && s3[0] == s[0]);
    // Test move constructor
    Stack<int> s4(std::move(s3));
    print_result("move constructor moves values", s4.size() == s2.size() && s4[0] == s2[0]);
    // Test move assignment
    Stack<int> s5;
    s5 = std::move(s4);
    print_result("move assignment moves values", s5.size() == s2.size() && s5[0] == s2[0]);
}


int main() {
    std::cout << "\n--- Basic Stack Test ---\n";
    test_basic();
    std::cout << "\n--- Strict Stack Test ---\n";
    test_strict();
    std::cout << "\nAll Stack tests completed.\n";
    return 0;
}
