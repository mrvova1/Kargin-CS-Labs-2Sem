#include <iostream>
#include "Polynomial.h"

int main() {
    Polynomial p1;
    Polynomial p2;
    std::cout << "Введите первый многочлен: ";
    std::cin >> p1;
    std::cout << "Первый: " << p1 << "\n";
    std::cout << "Введите второй многочлен: ";
    std::cin >> p2;
    std::cout << "Второй: " << p2 << "\n";
    Polynomial sum = p1 + p2;
    std::cout << "Сумма: " << sum << "\n";
    Polynomial prod = p1 * p2;
    std::cout << "Произведение: " << prod << "\n";
    Polynomial raz = p1 - p2;
    std::cout << "Разность: " << raz << "\n";
    return 0;
}
