#include "../include/deque.cpp"
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
    Deque<int> d;
    print_result("Deque vacío al inicio", d.empty() && d.size() == 0);
    d.push_back(10);
    print_result("push_back: size==1", d.size() == 1);
    print_result("push_back: valor==10", d[0] == 10);
    d.push_front(20);
    print_result("push_front: size==2", d.size() == 2);
    print_result("push_front: valor==20", d[0] == 20);
    int popped = d.pop_back();
    print_result("pop_back: devuelve el último", popped == 10 && d.size() == 1);
    popped = d.pop_front();
    print_result("pop_front: devuelve el primero", popped == 20 && d.size() == 0);
    d.push_back(1); d.push_back(2); d.push_back(3); d.push_front(0);
    d.clear();
    print_result("clear deja el deque vacío", d.empty());
}

void test_strict() {
    Deque<int> d;
    bool except = false;
    try { d.pop_back(); } catch (const std::out_of_range&) { except = true; }
    print_result("pop_back en deque vacío lanza excepción", except);
    except = false;
    try { d.pop_front(); } catch (const std::out_of_range&) { except = true; }
    print_result("pop_front en deque vacío lanza excepción", except);
    except = false;
    try { d[0]; } catch (const std::out_of_range&) { except = true; }
    print_result("operator[] fuera de rango lanza excepción", except);
}

int main() {
    std::cout << "\n--- Test básico Deque ---\n";
    test_basic();
    std::cout << "\n--- Test estricto Deque ---\n";
    test_strict();
    return 0;
}
