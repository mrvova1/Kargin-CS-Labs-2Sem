#include <iostream>
#include "MySet.h"

// int main() {
//     MySet<char*> set;

//     // int choice, element;

//     int choice;
//     char element[100];

//     std::cout << "Демонстрация работы MySet<int>" << std::endl;

//     bool running = true;
//     while(running) {
//         std::cout << "\nТекущее множество: " << set;
//         std::cout << "Меню:\n";
//         std::cout << "1) Добавить элемент\n";
//         std::cout << "2) Удалить элемент\n";
//         std::cout << "3) Показать множество\n";
//         std::cout << "0) Выход\n";
//         std::cout << "Ваш выбор: ";
//         std::cin >> choice;

//         switch(choice) {
//             case 1:
//                 std::cin.ignore();
//                 std::cout << "Введите элемент для добавления: ";
//                 std::cin >> element;
//                 // std::cout << "Введите элемент для добавления: ";

//                 if (set.add_element(element)) {
//                     std::cout << "Элемент " << element << " добавлен" << std::endl;
//                 } else {
//                     std::cout << "Элемент " << element << " уже в массиве" << std::endl;
//                 }
//                 // std::cout << "Введите элемент для добавления: ";

//                 break;
//             case 2:
//                 std::cin.ignore();
//                 std::cout << "Введите элемент для удаления: ";
//                 std::cin >> element;
//                 if (set.delete_element(element)) {
//                     std::cout << "Элемент " << element << " удалён" << std::endl;
//                 } else {
//                     std::cout << "Элемент " << element << " не присутствовал в массиве" << std::endl;
//                 }
//                 break;
//             case 3:
//                 std::cin.ignore();
//                 std::cout << "Множество: " << set;
//                 break;
//             case 0:
//                 std::cin.ignore();
//                 running = false;
//                 break;
//             default:
//                 std::cin.ignore();
//                 std::cout << "Неверный выбор. Повторите ввод." << std::endl;
//                 break;
//         }
//     }
//     std::cout << "Завершение работы программы." << std::endl;
//     return 0;
// }

// #include <iostream>
// #include "containers/myvector.h"
// #include "containers/myset.h"

int main() {
    int MAX_SIZE = 128;
    setlocale(LC_ALL, "Russian");

    MyVector<char *> v;
    v.add_element("Привет!");
    v.add_element("Привет!");
    v.add_element("Привет!");
    v.add_element("Привет!");
    v.add_element("Привет!");
    std::cout << "Вектор v: " << v << std::endl;
    v.add_element("Привет!");
    v.add_element("Привет!");
    v.add_element("Привет!");
    std::cout << "Вектор v: " << v << std::endl;
    MyVector v1 = v;
    std::cout << "Вектор v1: " << v1 << std::endl;
    for (int i = 0; i < MAX_SIZE; i++)
        v1.delete_element(0);
    std::cout << "Вектор v1: " << v1 << std::endl;
    MySet<char *> s, s1, s2;
    s.add_element("Привет!");
    s.add_element("No");
    char *str = "Hello!";
    s.add_element(str);
    std::cout << "Множество s: " << s << std::endl;
    s1.add_element("Cat");
    s1.add_element("No");
    s1.add_element("Привет!");
    std::cout << "Множество s1: " << s1 << std::endl;
    s2 = s1 - s;
    std::cout << "Множество s2=s1-s: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    s2 = s - s1;
    std::cout << "Множество s2=s-s1: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    s2 = s1 + s;
    std::cout << "Множество s2=s1+s: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    s2 = s1 * s;
    std::cout << "Множество s2=s1*s: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    MySet s3 = s2;
    std::cout << "Множество s3=s2: " << s3 << std::endl;
    if (s3 == s2)
        std::cout << "Множество s3=s2\n";
    else
        std::cout << "Множество s3!=s2\n";
    if (s3 == s1)
        std::cout << "Множество s3=s1\n";
    else
        std::cout << "Множество s3!=s1\n";
    if (s1 == s3)
        std::cout << "Множество s1=s3\n";
    else
        std::cout << "Множество s1!=s3\n";
    return 0;
}
