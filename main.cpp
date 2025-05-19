#include "engine.h"

int main() {
    MyStack<Engine*> container;

    std::cout << "Демонстрация работы" << std::endl;
    int choice;
    bool running = true;
    while(running) {
        std::cout << "Меню:\n";
        std::cout << "1) Добавить InternalCombustionEngine\n";
        std::cout << "2) Добавить DieselEngine\n";
        std::cout << "3) Добавить TurbojetEngine\n";
        std::cout << "4) Удалить элемент\n";
        std::cout << "5) Показать множество\n";
        std::cout << "0) Выход\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;
        std::cout << "\n";


        switch(choice) {
            case 1:
                std::cin.ignore();
                container.push(new InternalCombustionEngine(2.5, 180));
                break;
            case 2:
                std::cin.ignore();
                container.push(new DieselEngine(3.0, 220, 17.5));
                break;
            case 3:
                std::cin.ignore();
                container.push(new TurbojetEngine(150.0));
                break;
            case 4:
                std::cin.ignore();
                int index;
                std::cin >> index;
                container.delete_el(index);
                break;
            case 5:
                std::cin.ignore();
                for (size_t i=0; i < container.len(); i++){
                    std::cout << i << ") ";
                    container[i]->show();
                }
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
        std::cout << "\n";
    }
    std::cout << "Завершение работы программы." << std::endl;
    for (size_t i=0; i < container.len(); i++){
        container.pop();
    }
    return 0;
}
