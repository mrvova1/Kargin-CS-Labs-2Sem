#include <iostream>
#include "planets.h"

int main(int argc, char* argv[]) {
    const int MAX_PLANETS = 120;
    const int MAX_NAME_LENGTH = 100;
    char file_name[MAX_NAME_LENGTH];
    Planet planets[MAX_PLANETS];
    int n_planet = 0;
    int ind;

    if (argc > 1 && strcmp(argv[1], "i") == 0) {
    while (true) {
        MenuOption choice = static_cast<MenuOption>(Planet::menu());
        switch (choice) {
            case READ_FROM_FILE:
                std::cout << "Введите название файла" << '\n';
                std::cin >> file_name;
                n_planet = Planet::read_db(file_name, planets, MAX_PLANETS);
                break;
            case WRITE_TO_FILE:
                std::cout << "Введите название файла" << '\n';
                std::cin >> file_name;
                Planet::write_db(file_name, planets, n_planet);
                break;
            case EDIT_PLANET:
                if ((ind = Planet::find(planets, n_planet)) >= 0)
                    std::cin >> planets[ind];
                else
                    std::cout << "Такой планеты нет" << std::endl;
                break;
            case PRINT_PLANETS:
                Planet::print_db(planets, n_planet);
                break;
            case SORT_BY_DIAMETER:
                Planet::sort_db(planets, n_planet);
                break;
            case SORT_BY_NAME:
                Planet::sort_by_name(planets, n_planet);
                break;
            case ADD_PLANET:
                Planet::add_planet(planets, n_planet);
                break;
            case DELETE_PLANET:
                if ((ind = Planet::find(planets, n_planet)) >= 0)
                    Planet::delete_planet(planets, n_planet, ind);
                else
                    std::cout << "Такой планеты нет" << std::endl;
                break;
            case EXIT_PROGRAM:
                return 0;
            default:
                std::cout << "Неправильный ввод" << std::endl;
                break;
        }
    }
} else if (argc > 1 && strcmp(argv[1], "d") == 0) {
    std::strcpy(file_name, "Sun.txt");
    n_planet = Planet::read_db(file_name, planets, MAX_PLANETS);
    Planet::print_db(planets, n_planet);
    std::cout << '\n';

    std::cin >> planets[2];
    std::cout << planets[2];
    Planet::sort_by_name(planets, n_planet);
    Planet::print_db(planets, n_planet);
    std::cout << '\n';

    Planet::sort_db(planets, n_planet);
    Planet::print_db(planets, n_planet);
    std::cout << '\n';

    Planet::add_planet(planets, n_planet);
    Planet::delete_planet(planets, n_planet, 2);
    Planet::print_db(planets, n_planet);

}
    return 0;
}
