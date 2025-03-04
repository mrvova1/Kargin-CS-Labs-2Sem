#ifndef FLIGHT_H
#define FLIGHT_H

#include <iostream>
#include <fstream>
#include <cstring>

enum MenuOption {
    READ_FROM_FILE = 1,
    WRITE_TO_FILE,
    EDIT_TICKET,
    PRINT_TICKETS,
    SORT_BY_PRICE,
    SORT_BY_NAME,
    ADD_TICKET,
    DELETE_TICKET,
    EXIT_PROGRAM
};

class Flight {
private:
    char* date_;
    char* time_;
    int price_;
    char* airplane_;
    char* first_name_;
    char* last_name_;
public:
    Flight();
    Flight(const char* date, const char* time, int price, const char* airplane, const char* first_name, const char* last_name);
    Flight(const Flight &f);
    Flight& operator=(const Flight & other);
    ~Flight();

    void clear();

    friend std::istream& operator>>(std::istream&, Flight&);
    friend std::ostream& operator<<(std::ostream &os, const Flight &flight);

    char* getDate() const;
    char* getTime() const;
    int getPrice() const;
    char* getAirplane() const;
    char* getFirstName() const;
    char* getLastName() const;

    static void add_ticket(Flight*& tickets, int &n_tickets, int &capacity);
    static void delete_ticket(Flight* tickets, int &n_tickets, int ticket_index);
    static int read_db(char* file_name, Flight*& tickets, int &n_tickets, int &capacity);
    static int menu();
    static void print_db(Flight* tickets, int n_tickets);
    static int write_db(char* file_name, Flight* tickets, int n_tickets);
    static int find(Flight* tickets, int n_tickets);
    static void sort_by_price(Flight* tickets, int n_tickets);
    static void sort_by_name(Flight* tickets, int n_tickets);
};

#endif // FLIGHT_H
