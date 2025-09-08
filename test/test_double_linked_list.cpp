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

void test_basic() {
    DoubleLinkedList<int> d;
    print_result("DoubleLinkedList vacía al inicio", d.empty() && d.size() == 0);
    d.add(10);
    print_result("add: size==1", d.size() == 1);
    print_result("add: valor==10", d[0] == 10);
    d.add(20);
    print_result("add: size==2", d.size() == 2);
    print_result("add: valor==20", d[1] == 20);
    int erased = d.erase(0);
    print_result("erase(0): elimina y devuelve el valor correcto", erased == 10 && d.size() == 1 && d[0] == 20);
    d.insert(1, 42);
    print_result("insert(1,42): inserta al final", d[1] == 42 && d.size() == 2);
    d.clear();
    print_result("clear deja la lista vacía", d.empty());
}

void test_strict() {
    DoubleLinkedList<int> d;
    bool except = false;
    try { d[0]; } catch (const std::out_of_range&) { except = true; }
    print_result("operator[] fuera de rango lanza excepción", except);
    d.add(1); d.add(2); d.add(3);
    d.insert(0, 0);
    print_result("insert(0,0): inserta al principio", d[0] == 0);
    d.erase(1);
    print_result("erase(1): elimina el valor correcto", d[1] == 2);
}

int main() {
    std::cout << "\n--- Test básico DoubleLinkedList ---\n";
    test_basic();
    std::cout << "\n--- Test estricto DoubleLinkedList ---\n";
    test_strict();
    return 0;
}
