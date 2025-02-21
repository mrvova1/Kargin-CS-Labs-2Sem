#ifndef PLANET_H
#define PLANET_H

#include <iostream>
#include <fstream>
#include <cstring>

enum MenuOption {
    READ_FROM_FILE = 1,
    WRITE_TO_FILE,
    EDIT_PLANET,
    PRINT_PLANETS,
    SORT_BY_DIAMETER,
    SORT_BY_NAME,
    ADD_PLANET,
    DELETE_PLANET,
    EXIT_PROGRAM
};

class Planet {
private:
    char* planet_;
    int diameter_, life_, satellite_;
public:
    Planet();
    Planet(char* planet, int diameter, int life, int satellite);
    Planet(const Planet &p);
    Planet& operator=(const Planet & other);
    ~Planet();

    // Друзья для перегрузки операторов ввода/вывода
    friend std::istream& operator >> (std::istream&, Planet&);
    friend std::ostream& operator << (std::ostream &os, const Planet &planet);

    // Геттеры
    char* getPlanet() const;
    int getDiameter() const;
    int getLife() const;
    int getSatellite() const;

    // Статические методы для работы с базой планет
    static void add_planet(Planet* planets, int &n_planet);
    static void delete_planet(Planet* planets, int &n_planet, int planet_index);
    static int read_db(char* file_name, Planet* planets, const int Size);
    static int menu();
    static void print_db(Planet* planets, int n_planet);
    static int write_db(char* file_name, Planet* planets, int n_planet);
    static int find(Planet* planets, int n_planet);
    static void sort_db(Planet* planets, int n_planet);
    static void sort_by_name(Planet* planets, int n_planet);
};

#endif // PLANET_H
