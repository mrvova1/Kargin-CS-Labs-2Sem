#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int s_count(std::string &first_s, std::string &second_s){
    int count = 0;
    char last_s = second_s[second_s.length()-1];
    for (size_t i = 0; i < first_s.length(); i++){
        if (first_s[i] == last_s) {
            count++;
        }
    }
    return count;
}

int first(){
    std::string first_s;
    std::string second_s;
    std::getline(std::cin, first_s);
    std::getline(std::cin, second_s);
    return s_count(first_s, second_s);
}

std::string s_info(std::string &first_s){
    std::string info;
    bool start = false;
    bool end = false;
    char c;
    for (size_t i = 0; i < first_s.length(); i++){
        c = first_s[i];
        if (c == ',') {
            end = true;
        }
        if (end) {break;}
        if (start) {info.push_back(c);}
        if (c == ' ') {
            start = true;
        }
    }
    return info;
}

std::string second(){
    std::string first_s;
    std::getline(std::cin, first_s);
    return s_info(first_s);
}

void file_numerate(std::string &filename){
    std::ifstream in(filename);
    std::ofstream out("numerated_" + filename);
    if (not out.is_open() or not in.is_open()){
        return;
    }
    std::string line;
    int count = 0;
    while (std::getline(in, line))
    {
        out << count << ". " << line << std::endl;
        count++;
    }
    out.close();
    in.close();
}

void third(){
    std::string first_s;
    std::getline(std::cin, first_s);
    file_numerate(first_s);
}

std::vector<float> vector_summ(std::vector<float> &first_v, std::vector<float> &second_v){
    std::vector<float> third_v;
    for (size_t i=0; i<std::min(first_v.size(), second_v.size()); i++) {
        third_v.push_back(first_v[i]+second_v[i]);
    }
    return third_v;
}

void fourth_print(std::vector<float> vector){
    for (size_t i=0; i < vector.size(); i++){
        std::cout << vector[i] << ' ';
    }
    std::cout << '\n';
}

void fourth(){
    std::vector<float> first_v;
    std::vector<float> second_v;
    std::vector<float> third_v;
    float number = 1.0;
    for (int i=0; i < 25; i++){
        number *= static_cast<float>(i) + 0.1;
        first_v.push_back(number);
        second_v.push_back(number*0.52);
    }
    third_v = vector_summ(first_v, second_v);
    fourth_print(first_v);
    fourth_print(second_v);
    fourth_print(third_v);
}

class Planet {
public:
    std::string name_;
    int satelites_;

    Planet(std::string name="", int satelites = 0): name_(name), satelites_(satelites) {};
};

void fivth_print(std::vector<Planet> vector){
    for (size_t i=0; i < vector.size(); i++){
        std::cout << vector[i].name_ << ' ' << vector[i].satelites_ << '\n';
    }
}

int main(){
    // std::cout << first();
    // std::cout << second() << '\n';
    // third();
    // fourth();

    // std::vector<Planet> planets;
    // planets.push_back(Planet("Меркурий", 0));
    // planets.push_back(Planet("Венера", 0));
    // planets.push_back(Planet("Земля", 1));
    // planets.push_back(Planet("Марс", 2));
    // planets.push_back(Planet("Юпитер", 69));
    // planets.push_back(Planet("Сатурн", 62));
    // planets.push_back(Planet("Уран", 27));
    // planets.push_back(Planet("Нептун", 14));
    // planets.push_back(Planet("Плутон", 10));
    // fivth_print(planets);
    // std::cout << '\n';
    // int max_sat = -1;
    // Planet max_plan = Planet();
    // for (size_t i=0; i < planets.size(); i++){
    //     if (planets[i].satelites_) {
    //         max_sat = planets[i].satelites_;
    //         max_plan = planets[i];
    //     }
    // }
    // std::cout << max_plan.name_ << max_plan.satelites_ <<  '\n';



    return 0;
}

#endif // ENGINE_H
