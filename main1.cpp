#include <iostream>
#include "tickets.h"
#include <cstring>

int main(int argc, char* argv[]) {
    const int INITIAL_CAPACITY = 120;
    const int MAX_NAME_LENGTH = 100;
    char file_name[MAX_NAME_LENGTH];

    Flight* tickets = new Flight[INITIAL_CAPACITY];
    int capacity = INITIAL_CAPACITY;
    int n_tickets = 0;
    int ind;

    if (argc > 1 && strcmp(argv[1], "i") == 0) {
        while (true) {
            MenuOption choice = static_cast<MenuOption>(Flight::menu());
            switch (choice) {
                case READ_FROM_FILE:
                    std::cout << "Введите название файла" << '\n';
                    std::cin >> file_name;
                    n_tickets = Flight::read_db(file_name, tickets, n_tickets, capacity);
                    break;
                case WRITE_TO_FILE:
                    std::cout << "Введите название файла" << '\n';
                    std::cin >> file_name;
                    Flight::write_db(file_name, tickets, n_tickets);
                    break;
                case EDIT_TICKET:
                    if ((ind = Flight::find(tickets, n_tickets)) >= 0)
                        std::cin >> tickets[ind];
                    else
                        std::cout << "Такого билета нет" << std::endl;
                    break;
                case PRINT_TICKETS:
                    Flight::print_db(tickets, n_tickets);
                    break;
                case SORT_BY_PRICE:
                    Flight::sort_by_price(tickets, n_tickets);
                    break;
                case SORT_BY_NAME:
                    Flight::sort_by_name(tickets, n_tickets);
                    break;
                case ADD_TICKET:
                    Flight::add_ticket(tickets, n_tickets, capacity);
                    break;
                case DELETE_TICKET:
                    if ((ind = Flight::find(tickets, n_tickets)) >= 0)
                        Flight::delete_ticket(tickets, n_tickets, ind);
                    else
                        std::cout << "Такого билета нет" << std::endl;
                    break;
                case EXIT_PROGRAM:
                    delete[] tickets;
                    return 0;
                default:
                    std::cout << "Неправильный ввод" << std::endl;
                    break;
            }
        }
    } else if (argc > 1 && strcmp(argv[1], "d") == 0) {
        std::strcpy(file_name, "tickets.txt");
        n_tickets = Flight::read_db(file_name, tickets, n_tickets, capacity);
        Flight::print_db(tickets, n_tickets);
        std::cout << '\n';

        std::cin >> tickets[2];
        std::cout << tickets[2] << std::endl;
        Flight::sort_by_name(tickets, n_tickets);
        Flight::print_db(tickets, n_tickets);
        std::cout << '\n';

        Flight::sort_by_price(tickets, n_tickets);
        Flight::print_db(tickets, n_tickets);
        std::cout << '\n';

        Flight::add_ticket(tickets, n_tickets, capacity);
        Flight::delete_ticket(tickets, n_tickets, 2);
        Flight::print_db(tickets, n_tickets);
    }
    delete[] tickets;
    return 0;
}
