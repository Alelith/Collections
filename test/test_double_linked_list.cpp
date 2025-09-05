#include "../include/double_linked_list.cpp"
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
    DoubleLinkedList<int> l;
    print_result("Default constructor: empty", l.empty() && l.size() == 0);

    // push_back
    l.push_back(42);
    print_result("push_back: size==1", l.size() == 1);
    print_result("push_back: value==42", l[0] == 42);
    l.push_back(7);
    print_result("push_back: size==2", l.size() == 2);
    print_result("push_back: value==7", l[1] == 7);
    print_result("push_back: prev pointer", l.tail()->prev == l.head());

    // pop_back
    l.pop_back();
    print_result("pop_back: size==1", l.size() == 1);
    print_result("pop_back: value==42", l[0] == 42);
    l.pop_back();
    print_result("pop_back: size==0", l.size() == 0);
    print_result("pop_back: empty==true", l.empty());
    print_result("pop_back: head==nullptr", l.head() == nullptr);
    print_result("pop_back: tail==nullptr", l.tail() == nullptr);

    // clear
    l.push_back(1); l.push_back(2); l.push_back(3);
    l.clear();
    print_result("clear: size==0", l.size() == 0);
    print_result("clear: empty==true", l.empty());
    print_result("clear: head==nullptr", l.head() == nullptr);
    print_result("clear: tail==nullptr", l.tail() == nullptr);

    // at()
    l.push_back(10); l.push_back(20);
    bool at_ok = true;
    try { at_ok = (l.at(1) == 20); } catch (...) { at_ok = false; }
    print_result("at: valid index", at_ok);
    bool at_throw = false;
    try { l.at(10); } catch (const std::out_of_range&) { at_throw = true; }
    print_result("at: out_of_range throws", at_throw);

    // Copy constructor
    DoubleLinkedList<int> l2(l);
    print_result("Copy constructor: size", l2.size() == l.size());
    print_result("Copy constructor: value", l2[0] == 10 && l2[1] == 20);
    print_result("Copy constructor: prev pointer", l2.tail()->prev == l2.head());

    // Move constructor
    DoubleLinkedList<int> l3(std::move(l2));
    print_result("Move constructor: size", l3.size() == 2);
    print_result("Move constructor: value", l3[1] == 20);
    print_result("Move constructor: prev pointer", l3.tail()->prev == l3.head());

    // Copy assignment
    DoubleLinkedList<int> l4;
    l4 = l3;
    print_result("Copy assignment: size", l4.size() == l3.size());
    print_result("Copy assignment: value", l4[0] == 10 && l4[1] == 20);
    print_result("Copy assignment: prev pointer", l4.tail()->prev == l4.head());

    // Move assignment
    DoubleLinkedList<int> l5;
    l5 = std::move(l4);
    print_result("Move assignment: size", l5.size() == 2);
    print_result("Move assignment: value", l5[1] == 20);
    print_result("Move assignment: prev pointer", l5.tail()->prev == l5.head());

    // head/tail
    print_result("head() not null if not empty", l5.head() != nullptr);
    print_result("tail() not null if not empty", l5.tail() != nullptr);
    print_result("head()->data == 10", l5.head()->data == 10);
    print_result("tail()->data == 20", l5.tail()->data == 20);

    return 0;
}
