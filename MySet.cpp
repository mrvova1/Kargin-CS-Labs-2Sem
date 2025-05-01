#define MYSTACK_H
#include <iostream>
#include "MySet.h"

int main() {
    std::cout << "Введите первый многочлен: ";
    Term p1;
    Polynomial p2;
    std::cin >> p1;
    std::cout << "Первый: " << p1 << "\n";
    std::cout << "Введите второй многочлен: ";
    std::cin >> p2;
    std::cout << "Второй: " << p2 << "\n";

    // std::cout << "Второй: " << p2 << "\n";
    // Term sum = p1 + p2;
    // std::cout << "Сумма: " << sum << "\n";
    // Term prod = p1 * p2;
    // std::cout << "Произведение: " << prod << "\n";
    return 0;
}
