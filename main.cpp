#include <iostream>
#include <cstring>
#include "fractions.h"

int interactive() {
    setlocale(LC_ALL, "Russian");
    std::cout << "Интерактивный режим.\n";
    while (true) {
        MenuOption choice = static_cast<MenuOption>(Fractions::menu());
        switch (choice) {
            case INPUT_FRACTION: {
                std::cin.ignore();
                Fractions f;
                std::cout << "Введите дробь:" << std::endl;
                std::cin >> f;
                std::cout << "Введённая дробь: " << f << std::endl;
                break;
            }
            case ADD_FRACTIONS: {
                std::cin.ignore();
                Fractions a, b;
                std::cout << "Введите первую дробь:" << std::endl;
                std::cin >> a;
                std::cout << "Введите вторую дробь:" << std::endl;
                std::cin >> b;
                Fractions res = a + b;
                std::cout << "Результат сложения: " << res << std::endl;
                break;
            }
            case SUBTRACT_FRACTIONS: {
                std::cin.ignore();
                Fractions a, b;
                std::cout << "Введите первую дробь:" << std::endl;
                std::cin >> a;
                std::cout << "Введите вторую дробь:" << std::endl;
                std::cin >> b;
                Fractions res = a - b;
                std::cout << "Результат вычитания: " << res << std::endl;
                break;
            }
            case MULTIPLY_FRACTIONS: {
                std::cin.ignore();
                Fractions a, b;
                std::cout << "Введите первую дробь:" << std::endl;
                std::cin >> a;
                std::cout << "Введите вторую дробь:" << std::endl;
                std::cin >> b;
                Fractions res = a * b;
                std::cout << "Результат умножения: " << res << std::endl;
                break;
            }
            case DIVIDE_FRACTIONS: {
                std::cin.ignore();
                Fractions a, b;
                std::cout << "Введите первую дробь:" << std::endl;
                std::cin >> a;
                std::cout << "Введите вторую дробь:" << std::endl;
                std::cin >> b;
                Fractions res = a / b;
                std::cout << "Результат деления: " << res << std::endl;
                break;
            }
            case EXIT_PROGRAM: {
                return 0;
            }
            default:
                std::cout << "Неправильный ввод" << std::endl;
                break;
        }
    }
    return 0;
}

int demo() {
    setlocale(LC_ALL, "Russian");
    std::cout << "Демо режим\n";
    // ввод дроби с клавиатуры
    std::cout << "Введите дробь: \n";
    Fractions z;
    std::cin >> z;
    std::cout << "z=" << z << std::endl;
    // проверка конструкторов
    Fractions fr1(0, 10, 14), fr2;
    std::cout << "fr2=" << fr2 << std::endl;
    std::cout << "fr1=" << fr1 << std::endl;
    Fractions fr = "-1 4/8";
    std::cout << "fr=" << fr << std::endl;
    Fractions x(z), y;
    std::cout << "x=" << x << std::endl;
    double dbl = -1.25;
    Fractions f = dbl;
    std::cout << "f=" << f << std::endl;
    // проверка перегруженной операции "+"
    y = x + z;
    std::cout << "y=" << y << std::endl;
    y += x;
    f += dbl / 2.0;
    std::cout << "f=" << f << std::endl;
    y = x + dbl;
    std::cout << "y=" << y << std::endl;
    y = dbl + y;
    std::cout << "y=" << y << std::endl;
    y += dbl;
    std::cout << "y=" << y << std::endl;
    int i = 5;
    y += i;
    std::cout << "y=" << y << std::endl;
    y = i + x;
    std::cout << "y=" << y << std::endl;
    y = x + i;
    std::cout << "y=" << y << std::endl;
    y += dbl + i + x;
    std::cout << "y=" << y << std::endl;
    y = dbl - i - x;
    std::cout << "y=" << y << std::endl;

    return 0;
}

int main(int argc, char *argv[]) {
    bool isInteractive = false;
    if (argc == 2 && std::strcmp(argv[1], "i") == 0) {
        isInteractive = true;
    }
    if (isInteractive) {
        return interactive();
    } else {
        return demo();
    }
}
