#include <iostream>
#include <fstream>
#include <cstring>

class Planet {
private:
    char* planet_;
    int diameter_, life_, satellite_;
public:
    Planet() : planet_(nullptr), diameter_(0), life_(0), satellite_(0) {}

    Planet(char* planet, int diameter, int life, int satellite) {
        this->planet_ = new char[strlen(planet) + 1];
        strcpy(planet_, planet);
        this->diameter_ = diameter;
        this->life_ = life;
        this->satellite_ = satellite;
    }

    Planet& operator=(const Planet & other){
        planet_ = new char[strlen(other.planet_) + 1];
        strcpy(planet_, other.planet_);
        diameter_ = other.diameter_;
        life_ = other.life_;
        satellite_ = other.satellite_;
        return *this;
    };

    Planet(const Planet &p)
    {
        planet_ = new char[strlen(p.planet_) + 1];
        strcpy(planet_, p.planet_);
        diameter_ = p.diameter_;
        life_ = p.life_;
        satellite_ = p.satellite_;
    }

    ~Planet() {
        delete[] planet_;
    }

    // void edit() {
    //     std::cin >>
    // }

    char* getPlanet() const {
        return planet_;
    }

    int getDiameter() const {
        return diameter_;
    }

    int getLife() const {
        return life_;
    }

    int getSatellite() const {
        return satellite_;
    }

    static void add_planet(Planet* planets, int &n_planet){
        Planet new_planet;
        std::cin >> new_planet;
        planets[n_planet] = new_planet;
        n_planet++;
    }

    static void delete_planet(Planet* planets, int &n_planet, int planet_index){
        for (int i=planet_index; i<n_planet; i++){
            planets[i] = planets[i++];
        }
        n_planet--;
    }

    static int read_db(char* file_name, Planet* planets, const int Size) {
        char name[100];
        int diameter = 0, life = 0, satellite = 0;
        int n_planet = 0;

        std::ifstream file(file_name);
        if (file) {
            while (file >> name >> diameter >> life >> satellite && n_planet < Size) {
                planets[n_planet] = Planet(name, diameter, life, satellite);
                n_planet++;

            }
        }
        return n_planet;
    }

    static int menu() {
        std::cout << "Введите что бы вы хотели сделать:" << '\n' << "1. Прочитать планеты из файла" << '\n'
                  << "2. Записать планеты в файл" << '\n' << "3. Изменить данные планеты" << '\n'
                  << "4. Вывести имеющиеся планеты" << '\n' << "5. Отсортировать планеты" << '\n'
                  << "6. Добавить планету" << '\n' << "7. Удалить планету" << '\n'
                  << "8. Выйти" << '\n';
        int choice = 0;
        std::cin >> choice;
        return choice;
    }

    static void print_db(Planet* planets, int n_planet) {
        for (int i = 0; i < n_planet; i++) {
            std::cout << planets[i].getPlanet() << " " << planets[i].getDiameter() << " " << planets[i].getLife() << " " << planets[i].getSatellite() << '\n';
        }
    }

    static int write_db(char* file_name, Planet* planets, int n_planet) {
        std::ofstream file(file_name);
        if (file) {
            for (int i = 0; i < n_planet; i++) {
                file << planets[i].getPlanet() << " " << planets[i].getDiameter() << " " << planets[i].getLife() << " " << planets[i].getSatellite() << '\n';
            }
        }
        return 0;
    }

    static int find(Planet* planets, int n_planet) {
        std::cout << "Назовите какую планету вы хотите изменить: ";
        char name[100];
        std::cin >> name;
        for (int i = 0; i < n_planet; i++) {
            if (strcmp(name, planets[i].getPlanet()) == 0) {
                return i;
            }
        }
        return -1;
    }

    static void sort_db(Planet* planets, int n_planet) {
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
};

std::ostream& operator << (std::ostream &os, const Planet &planet)
{
    return os << planet.getPlanet() << " " << planet.getDiameter() << " " << planet.getLife() << " " << planet.getSatellite();
}
std::istream& operator >> (std::istream& in, Planet& planet)
{
    std::cout << "Введите измененные данные" << '\n';
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

};

int main() {
    const int MAX_PLANETS = 120;
    const int MAX_NAME_LENGTH = 100;
    char file_name[MAX_NAME_LENGTH];
    Planet planets[MAX_PLANETS];
    // Planet* planets = new Planet[20];
    int n_planet = 0;
    int ind;

    while (true) {
        switch (Planet::menu()) {
            case 1:
                std::cout << "Введите название файла" << '\n';
                std::cin >> file_name;
                n_planet = Planet::read_db(file_name, planets, MAX_PLANETS);
                break;
            case 2:
                std::cout << "Введите название файла" << '\n';
                std::cin >> file_name;
                Planet::write_db(file_name, planets, n_planet);
                break;
            case 3:
                if ((ind = Planet::find(planets, n_planet)) >= 0)
                    // planets[ind].edit();
                    std::cin >> planets[ind];
                else
                    std::cout << "Такой планеты нет" << std::endl;
                break;
            case 4:
                Planet::print_db(planets, n_planet);
                break;
            case 5:
                Planet::sort_db(planets, n_planet);
                break;
            case 6:
                Planet::add_planet(planets, n_planet);
                break;
            case 7:
                if ((ind = Planet::find(planets, n_planet)) >= 0)
                // planets[ind].edit();
                    Planet::delete_planet(planets, n_planet, ind);
                else
                    std::cout << "Такой планеты нет" << std::endl;
            case 8:
                return 0;
            default:
                std::cout << "Неправильный ввод" << std::endl;
                break;
        }
    }
    return 0;
}
