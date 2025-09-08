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
    print_result("Vector vacío al inicio", v.empty() && v.size() == 0);
    v.add(10);
    print_result("add: size==1", v.size() == 1);
    print_result("add: valor==10", v[0] == 10);
    v.add(20);
    print_result("add: size==2", v.size() == 2);
    print_result("add: valor==20", v[1] == 20);
    int erased = v.erase(0);
    print_result("erase(0): elimina y devuelve el valor correcto", erased == 10 && v.size() == 1 && v[0] == 20);
    v.insert(1, 42);
    print_result("insert(1,42): inserta al final", v[1] == 42 && v.size() == 2);
    v.clear();
    print_result("clear deja el vector vacío", v.empty());
}

void test_strict() {
    Vector<int> v;
    bool except = false;
    try { v[0]; } catch (const std::out_of_range&) { except = true; }
    print_result("operator[] fuera de rango lanza excepción", except);
    v.add(1); v.add(2); v.add(3);
    v.insert(0, 0);
    print_result("insert(0,0): inserta al principio", v[0] == 0);
    v.erase(1);
    print_result("erase(1): elimina el valor correcto", v[1] == 2);
}

int main() {
    std::cout << "\n--- Test básico Vector ---\n";
    test_basic();
    std::cout << "\n--- Test estricto Vector ---\n";
    test_strict();
    return 0;
}
