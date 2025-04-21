#include <iostream>
#include "MySet.h"

int main() {
    MySet<int> set;
    int choice, element;

    std::cout << "Демонстрация работы MySet<int>" << std::endl;

    bool running = true;
    while(running) {
        std::cout << "\nТекущее множество: " << set;
        std::cout << "Меню:\n";
        std::cout << "1) Добавить элемент\n";
        std::cout << "2) Удалить элемент\n";
        std::cout << "3) Показать множество\n";
        std::cout << "0) Выход\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch(choice) {
            case 1:
                std::cin.ignore();
                std::cout << "Введите элемент для добавления: ";
                std::cin >> element;
                // std::cout << "Введите элемент для добавления: ";

                if (set.add_element(element)) {
                    std::cout << "Элемент " << element << " добавлен" << std::endl;
                } else {
                    std::cout << "Элемент " << element << " уже в массиве" << std::endl;
                }
                // std::cout << "Введите элемент для добавления: ";

                break;
            case 2:
                std::cin.ignore();
                std::cout << "Введите элемент для удаления: ";
                std::cin >> element;
                if (set.delete_element(element)) {
                    std::cout << "Элемент " << element << " удалён" << std::endl;
                } else {
                    std::cout << "Элемент " << element << " не присутствовал в массиве" << std::endl;
                }
                break;
            case 3:
                std::cin.ignore();
                std::cout << "Множество: " << set;
                break;
            case 0:
                std::cin.ignore();
                running = false;
                break;
            default:
                std::cin.ignore();
                std::cout << "Неверный выбор. Повторите ввод." << std::endl;
                break;
        }
    }
    std::cout << "Завершение работы программы." << std::endl;
    return 0;
}
