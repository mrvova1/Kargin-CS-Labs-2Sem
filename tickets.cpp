#include "tickets.h"
#include <iostream>
#include <fstream>
#include <cstring>

void resize_tickets(Flight*& tickets, int n_tickets, int &capacity) {
    int new_capacity = capacity * 2;
    Flight* new_tickets = new Flight[new_capacity];
    for (int i = 0; i < n_tickets; i++){
        new_tickets[i] = tickets[i];
    }
    delete[] tickets;
    tickets = new_tickets;
    capacity = new_capacity;
}

Flight::Flight() : date_(new char[1]), time_(new char[1]), price_(0), airplane_(new char[1]), first_name_(new char[1]), last_name_(new char[1]) {
    date_[0] = '\0';
    time_[0] = '\0';
    airplane_[0] = '\0';
    first_name_[0] = '\0';
    last_name_[0] = '\0';
}

Flight::Flight(const char* date, const char* time, int price, const char* airplane, const char* first_name, const char* last_name) {
    date_ = new char[strlen(date) + 1];
    strcpy(date_, date);

    time_ = new char[strlen(time) + 1];
    strcpy(time_, time);

    price_ = price;

    airplane_ = new char[strlen(airplane) + 1];
    strcpy(airplane_, airplane);

    first_name_ = new char[strlen(first_name) + 1];
    strcpy(first_name_, first_name);

    last_name_ = new char[strlen(last_name) + 1];
    strcpy(last_name_, last_name);
}

Flight::Flight(const Flight &f) {
    date_ = new char[strlen(f.date_) + 1];
    strcpy(date_, f.date_);

    time_ = new char[strlen(f.time_) + 1];
    strcpy(time_, f.time_);

    price_ = f.price_;

    airplane_ = new char[strlen(f.airplane_) + 1];
    strcpy(airplane_, f.airplane_);

    first_name_ = new char[strlen(f.first_name_) + 1];
    strcpy(first_name_, f.first_name_);

    last_name_ = new char[strlen(f.last_name_) + 1];
    strcpy(last_name_, f.last_name_);
}

Flight& Flight::operator=(const Flight &other) {
    if (this != &other) {
        delete[] date_;
        delete[] time_;
        delete[] airplane_;
        delete[] first_name_;
        delete[] last_name_;

        date_ = new char[strlen(other.date_) + 1];
        strcpy(date_, other.date_);

        time_ = new char[strlen(other.time_) + 1];
        strcpy(time_, other.time_);

        price_ = other.price_;

        airplane_ = new char[strlen(other.airplane_) + 1];
        strcpy(airplane_, other.airplane_);

        first_name_ = new char[strlen(other.first_name_) + 1];
        strcpy(first_name_, other.first_name_);

        last_name_ = new char[strlen(other.last_name_) + 1];
        strcpy(last_name_, other.last_name_);
    }
    return *this;
}

Flight::~Flight() {
    delete[] date_;
    delete[] time_;
    delete[] airplane_;
    delete[] first_name_;
    delete[] last_name_;
}

char* Flight::getDate() const {
    return date_;
}

char* Flight::getTime() const {
    return time_;
}

int Flight::getPrice() const {
    return price_;
}

char* Flight::getAirplane() const {
    return airplane_;
}

char* Flight::getFirstName() const {
    return first_name_;
}

char* Flight::getLastName() const {
    return last_name_;
}

void Flight::clear() {
    delete[] date_;
    date_ = new char[1];
    date_[0] = '\0';

    delete[] time_;
    time_ = new char[1];
    time_[0] = '\0';

    price_ = 0;

    delete[] airplane_;
    airplane_ = new char[1];
    airplane_[0] = '\0';

    delete[] first_name_;
    first_name_ = new char[1];
    first_name_[0] = '\0';

    delete[] last_name_;
    last_name_ = new char[1];
    last_name_[0] = '\0';
}

void Flight::add_ticket(Flight*& tickets, int &n_tickets, int &capacity) {
    if(n_tickets >= capacity) {
        resize_tickets(tickets, n_tickets, capacity);
    }
    Flight new_ticket;
    std::cin >> new_ticket;
    tickets[n_tickets] = new_ticket;
    n_tickets++;
}

void Flight::delete_ticket(Flight* tickets, int &n_tickets, int ticket_index) {
    if(ticket_index < 0 || ticket_index >= n_tickets) return;
    tickets[ticket_index].clear();
    for (int i = ticket_index; i < n_tickets - 1; i++) {
        tickets[i] = tickets[i + 1];
    }
    tickets[n_tickets - 1].clear();
    n_tickets--;
}

int Flight::read_db(char* file_name, Flight*& tickets, int &n_tickets, int &capacity) {
    char date[100], time[100], airplane[100], first_name[100], last_name[100];
    int price = 0;
    n_tickets = 0;

    std::ifstream file(file_name);
    if (file) {
        while (file >> date >> time >> price >> airplane >> first_name >> last_name) {
            if(n_tickets >= capacity) {
                resize_tickets(tickets, n_tickets, capacity);
            }
            tickets[n_tickets] = Flight(date, time, price, airplane, first_name, last_name);
            n_tickets++;
        }
    }
    return n_tickets;
}

int Flight::menu() {
    std::cout << "Введите, что бы вы хотели сделать:" << '\n'
              << "1. Прочитать билеты из файла" << '\n'
              << "2. Записать билеты в файл" << '\n'
              << "3. Изменить данные билета" << '\n'
              << "4. Вывести имеющиеся билеты" << '\n'
              << "5. Отсортировать билеты по цене" << '\n'
              << "6. Отсортировать билеты по имени владельца" << '\n'
              << "7. Добавить билет" << '\n'
              << "8. Удалить билет" << '\n'
              << "9. Выйти" << '\n';
    int choice = 0;
    std::cin >> choice;
    return choice;
}

void Flight::print_db(Flight* tickets, int n_tickets) {
    for (int i = 0; i < n_tickets; i++) {
        std::cout << tickets[i] << std::endl;
    }
}

int Flight::write_db(char* file_name, Flight* tickets, int n_tickets) {
    std::ofstream file(file_name);
    if (file) {
        for (int i = 0; i < n_tickets; i++) {
            file << tickets[i] << std::endl;
        }
    }
    return 0;
}

int Flight::find(Flight* tickets, int n_tickets) {
    std::cout << "Введите имя владельца: ";
    char name[100];
    std::cin >> name;
    for (int i = 0; i < n_tickets; i++) {
        if (strcmp(name, tickets[i].getFirstName()) == 0) {
            return i;
        }
    }
    return -1;
}

void Flight::sort_by_price(Flight* tickets, int n_tickets) {
    for (int i = 0; i < n_tickets - 1; i++) {
        for (int j = i + 1; j < n_tickets; j++) {
            if (tickets[i].getPrice() > tickets[j].getPrice()) {
                Flight temp = tickets[i];
                tickets[i] = tickets[j];
                tickets[j] = temp;
            }
        }
    }
}

void Flight::sort_by_name(Flight* tickets, int n_tickets) {
    for (int i = 0; i < n_tickets - 1; i++) {
        for (int j = i + 1; j < n_tickets; j++) {
            if (strcmp(tickets[i].getFirstName(), tickets[j].getFirstName()) > 0) {
                Flight temp = tickets[i];
                tickets[i] = tickets[j];
                tickets[j] = temp;
            }
        }
    }
}

std::ostream& operator<<(std::ostream &os, const Flight &flight) {
    os << flight.date_ << " "
       << flight.time_ << " "
       << flight.price_ << " "
       << flight.airplane_ << " "
       << flight.first_name_ << " "
       << flight.last_name_;
    return os;
}

std::istream& operator>>(std::istream& in, Flight& flight) {
    std::cout << "Введите новые данные" << '\n';
    std::cout << "Дата: ";
    char temp_date[100];
    in >> temp_date;

    std::cout << "Время: ";
    char temp_time[100];
    in >> temp_time;

    int price = 0;
    std::cout << "Цена: ";
    in >> price;

    std::cout << "Самолет: ";
    char temp_airplane[100];
    in >> temp_airplane;

    std::cout << "Имя владельца: ";
    char temp_first_name[100];
    in >> temp_first_name;

    std::cout << "Фамилия владельца: ";
    char temp_last_name[100];
    in >> temp_last_name;

    flight = Flight(temp_date, temp_time, price, temp_airplane, temp_first_name, temp_last_name);
    return in;
}
