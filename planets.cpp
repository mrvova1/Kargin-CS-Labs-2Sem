#include "planets.h"
#include <iostream>
#include <fstream>
#include <cstring>

void resize_planets(Planet*& planets, int n_planet, int &capacity) {
    int new_capacity = capacity * 2;
    Planet* new_planets = new Planet[new_capacity];
    for (int i = 0; i < n_planet; i++){
        new_planets[i] = planets[i];
    }
    delete[] planets;
    planets = new_planets;
    capacity = new_capacity;
}

Planet::Planet() : planet_(new char[1]), diameter_(0), life_(0), satellite_(0) {
    planet_[0] = '\0';
}

Planet::Planet(char* planet, int diameter, int life, int satellite) {
    planet_ = new char[strlen(planet) + 1];
    strcpy(planet_, planet);
    diameter_ = diameter;
    life_ = life;
    satellite_ = satellite;
}

Planet::Planet(const Planet &p) {
    planet_ = new char[strlen(p.planet_) + 1];
    strcpy(planet_, p.planet_);
    diameter_ = p.diameter_;
    life_ = p.life_;
    satellite_ = p.satellite_;
}

Planet& Planet::operator=(const Planet &other){
    if (this != &other) {
        delete[] planet_;
        planet_ = new char[strlen(other.planet_) + 1];
        strcpy(planet_, other.planet_);
        diameter_ = other.diameter_;
        life_ = other.life_;
        satellite_ = other.satellite_;
    }
    return *this;
}

Planet::~Planet() {
    delete[] planet_;
}

char* Planet::getPlanet() const {
    return planet_;
}

int Planet::getDiameter() const {
    return diameter_;
}

int Planet::getLife() const {
    return life_;
}

int Planet::getSatellite() const {
    return satellite_;
}

void Planet::clear() {
    delete[] planet_;
    planet_ = new char[1];
    planet_[0] = '\0';
    diameter_ = 0;
    life_ = 0;
    satellite_ = 0;
}

void Planet::add_planet(Planet*& planets, int &n_planet, int &capacity){
    if (n_planet >= capacity) {
        resize_planets(planets, n_planet, capacity);
    }
    Planet new_planet;
    std::cin >> new_planet;
    planets[n_planet] = new_planet;
    n_planet++;
}

void Planet::delete_planet(Planet* planets, int &n_planet, int planet_index){
    if (planet_index < 0 || planet_index >= n_planet) return;
    for (int i = planet_index; i < n_planet - 1; i++){
        planets[i] = planets[i+1];
    }
    planets[n_planet - 1].clear();
    n_planet--;
}

int Planet::read_db(char* file_name, Planet*& planets, int &n_planet, int &capacity) {
    char name[100];
    int diameter = 0, life = 0, satellite = 0;
    n_planet = 0;
    std::ifstream file(file_name);
    if (file) {
        while (file >> name >> diameter >> life >> satellite) {
            if(n_planet >= capacity) {
                resize_planets(planets, n_planet, capacity);
            }
            planets[n_planet] = Planet(name, diameter, life, satellite);
            n_planet++;
        }
    }
    return n_planet;
}

int Planet::menu() {
    std::cout << "Введите, что бы вы хотели сделать:" << '\n'
              << "1. Прочитать планеты из файла" << '\n'
              << "2. Записать планеты в файл" << '\n'
              << "3. Изменить данные планеты" << '\n'
              << "4. Вывести имеющиеся планеты" << '\n'
              << "5. Отсортировать планеты по диаметру" << '\n'
              << "6. Отсортировать планеты по названию" << '\n'
              << "7. Добавить планету" << '\n'
              << "8. Удалить планету" << '\n'
              << "9. Выйти" << '\n';
    int choice = 0;
    std::cin >> choice;
    return choice;
}

void Planet::print_db(Planet* planets, int n_planet) {
    for (int i = 0; i < n_planet; i++) {
        std::cout << planets[i] << std::endl;
    }
}

int Planet::write_db(char* file_name, Planet* planets, int n_planet) {
    std::ofstream file(file_name);
    if (file) {
        for (int i = 0; i < n_planet; i++) {
            file << planets[i] << std::endl;
        }
    }
    return 0;
}

int Planet::find(Planet* planets, int n_planet) {
    std::cout << "Введите название планеты: ";
    char name[100];
    std::cin >> name;
    for (int i = 0; i < n_planet; i++) {
        if (strcmp(name, planets[i].getPlanet()) == 0) {
            return i;
        }
    }
    return -1;
}

void Planet::sort_db(Planet* planets, int n_planet) {
    for (int i = 0; i < n_planet - 1; i++) {
        for (int j = i + 1; j < n_planet; j++) {
            if (planets[i].getDiameter() < planets[j].getDiameter()) {
                Planet temp = planets[i];
                planets[i] = planets[j];
                planets[j] = temp;
            }
        }
    }
}

void Planet::sort_by_name(Planet* planets, int n_planet) {
    for (int i = 0; i < n_planet - 1; i++) {
        for (int j = i + 1; j < n_planet; j++) {
            if (strcmp(planets[i].getPlanet(), planets[j].getPlanet()) > 0) {
                Planet temp = planets[i];
                planets[i] = planets[j];
                planets[j] = temp;
            }
        }
    }
}

std::ostream& operator << (std::ostream &os, const Planet &planet)
{
    os << planet.planet_ << " "
       << planet.diameter_ << " "
       << planet.life_ << " "
       << planet.satellite_;
    return os;
}

std::istream& operator >> (std::istream& in, Planet& planet)
{
    std::cout << "Введите новые данные" << '\n';
    std::cout << "Название: ";
    char temp_name[100];
    in >> temp_name;
    int diameter = 0, life = 0, satellite = 0;
    std::cout << "Диаметр: ";
    in >> diameter;
    std::cout << "Жизнь: ";
    in >> life;
    std::cout << "Спутники: ";
    in >> satellite;
    planet = Planet(temp_name, diameter, life, satellite);
    return in;
}
