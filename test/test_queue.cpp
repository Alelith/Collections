#include "../include/queue.cpp"
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
    Queue<int> q;
    print_result("Queue vacía al inicio", q.empty() && q.size() == 0);
    q.enqueue(10);
    print_result("enqueue: size==1", q.size() == 1);
    print_result("enqueue: valor==10", q[0] == 10);
    q.enqueue(20);
    print_result("enqueue: size==2", q.size() == 2);
    print_result("enqueue: valor==20", q[1] == 20);
    int dq = q.dequeue();
    print_result("dequeue: devuelve el último", dq == 20 && q.size() == 1);
    q.enqueue(30);
    q.enqueue(40);
    print_result("enqueue: size==3", q.size() == 3);
    q.clear();
    print_result("clear deja la queue vacía", q.empty());
}

void test_strict() {
    Queue<int> q;
    bool except = false;
    try { q.dequeue(); } catch (const std::out_of_range&) { except = true; }
    print_result("dequeue en queue vacía lanza excepción", except);
    except = false;
    try { q[0]; } catch (const std::out_of_range&) { except = true; }
    print_result("operator[] fuera de rango lanza excepción", except);
    q.enqueue(1); q.enqueue(2); q.enqueue(3);
    print_result("enqueue múltiple: valores correctos", q[0] == 1 && q[2] == 3);
}

int main() {
    std::cout << "\n--- Test básico Queue ---\n";
    test_basic();
    std::cout << "\n--- Test estricto Queue ---\n";
    test_strict();
    return 0;
}
