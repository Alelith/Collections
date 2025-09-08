#include "../include/stack.cpp"
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
    print_result("Stack vacío al inicio", s.empty() && s.size() == 0);
    s.push(10);
    print_result("push: size==1", s.size() == 1);
    print_result("push: valor==10", s[0] == 10);
    s.push(20);
    print_result("push: size==2", s.size() == 2);
    print_result("push: valor==20", s[1] == 20);
    int popped = s.pop();
    print_result("pop: devuelve el último", popped == 20 && s.size() == 1);
    s.push(30);
    s.push(40);
    int popped_idx = s.pop();
    print_result("pop(): elimina y devuelve el valor correcto", popped_idx == 40 && s.size() == 2 && s[1] == 30);
    s.clear();
    print_result("clear deja el stack vacío", s.empty());
}

void test_strict() {
    Stack<int> s;
    bool except = false;
    try { s.pop(); } catch (const std::out_of_range&) { except = true; }
    print_result("pop en stack vacío lanza excepción", except);
    except = false;
    try { s[0]; } catch (const std::out_of_range&) { except = true; }
    print_result("operator[] fuera de rango lanza excepción", except);
}

int main() {
    std::cout << "\n--- Test básico Stack ---\n";
    test_basic();
    std::cout << "\n--- Test estricto Stack ---\n";
    test_strict();
    return 0;
}
