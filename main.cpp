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
                std::cout << "Введите элемент для добавления: ";

                set.add_element(element);
                std::cout << "Введите элемент для добавления: ";

                std::cout << "Элемент " << element << " добавлен (если ранее отсутствовал)." << std::endl;
                break;
            case 2:
                std::cin.ignore();
                std::cout << "Введите элемент для удаления: ";
                std::cin >> element;
                set.delete_element(element);
                std::cout << "Элемент " << element << " удалён (если присутствовал)." << std::endl;
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
