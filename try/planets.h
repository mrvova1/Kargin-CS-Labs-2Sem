#include <cstring>

class Planet {
    private:
        int diameter_, life_, satellite_;
        char* planet_;
    public:
        Planet() : planet_(nullptr), diameter_(0), life_(0), satellite_(0) {}

        Planet(char* planet, int diameter, int life, int satellite) {
            this->planet_ = new char[strlen(planet) + 1];
            strcpy(planet_, planet);
            this->diameter_ = diameter;
            this->life_ = life;
            this->satellite_ = satellite;
        }

        ~Planet() {
            delete[] planet_;
        }


void edit();

static int menu();

static int read_db(char *file_name, Planet *planets, const int Size);

static void print_db(Planet* planets, int n_planet);

static int write_db(char *file_name, Planet *planets, int n_planet);

static int find(Planet *planets, int n_planet);

static void sort_db(Planet *planets, int n_planet);

char* getPlanet() const;

int getDiameter() const;

int getLife() const;

int getSatellite() const;
    };
