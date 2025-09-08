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
    print_result("LinkedList vacía al inicio", l.empty() && l.size() == 0);
    l.add(10);
    print_result("add: size==1", l.size() == 1);
    print_result("add: valor==10", l[0] == 10);
    l.add(20);
    print_result("add: size==2", l.size() == 2);
    print_result("add: valor==20", l[1] == 20);
    int erased = l.erase(0);
    print_result("erase(0): elimina y devuelve el valor correcto", erased == 10 && l.size() == 1 && l[0] == 20);
    l.insert(1, 42);
    print_result("insert(1,42): inserta al final", l[1] == 42 && l.size() == 2);
    l.clear();
    print_result("clear deja la lista vacía", l.empty());
}

void test_strict() {
    LinkedList<int> l;
    bool except = false;
    try { l[0]; } catch (const std::out_of_range&) { except = true; }
    print_result("operator[] fuera de rango lanza excepción", except);
    l.add(1); l.add(2); l.add(3);
    l.insert(0, 0);
    print_result("insert(0,0): inserta al principio", l[0] == 0);
    l.erase(1);
    print_result("erase(1): elimina el valor correcto", l[1] == 2);
}

int main() {
    std::cout << "\n--- Test básico LinkedList ---\n";
    test_basic();
    std::cout << "\n--- Test estricto LinkedList ---\n";
    test_strict();
    return 0;
}
