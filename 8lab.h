#ifndef LAB8_H
#define LAB8_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <map>
#include <random>

int s_count(std::string &first_s, std::string &second_s){
    int count = 0;
    char last_s = second_s[second_s.length()-1];
    int last_i = 0;
    while (first_s.find(last_s, last_i) != std::string::npos)
    {
        last_i = first_s.find(last_s, last_i)+1;
        count++;
        // std::cout <<
    }

    // for (size_t i = 0; i < first_s.length(); i++){
    //     if (first_s[i] == last_s) {
    //         count++;
    //     }
    // }
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
    size_t space = first_s.find(' ');
    size_t comma = first_s.find(',');

    if (space == std::string::npos){ std::cout << "Нет пробела\n"; return "";}
    if (comma == std::string::npos){ std::cout << "Нет запятой\n"; return "";}
    if (space >= comma){ return "";}


    return first_s.substr(space+1, comma-space-1);

    // bool start = false;
    // bool end = false;
    // char c;


    // for (size_t i = 0; i < first_s.length(); i++){
    //     c = first_s[i];
    //     if (c == ',') {
    //         end = true;
    //     }
    //     if (end) {break;}
    //     if (start) {info.push_back(c);}
    //     if (c == ' ') {
    //         start = true;
    //     }
    // }
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
    for (float i : vector){
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

void fourth(){
    std::vector<float> first_v;
    std::vector<float> second_v;
    std::vector<float> third_v;
    float randomNum;
    for (int i=0; i < 25; i++){
        randomNum = (rand() % 10001) / 100;
        first_v.push_back(randomNum);
        randomNum = (rand() % 10001) / 100;
        second_v.push_back(randomNum);
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

int plus_count(std::list<int> list_n){
    std::list<int>::iterator iter;
    int count = 0;
    for (iter = list_n.begin(); iter != list_n.end(); iter++) {
        if (*iter > 0) {count++;};
    }
    return count;
}

void sixth(){
    std::list<int> list_n;
    std::list<int>::iterator iter;
    int randomNum;
    for (int i=0; i<10; i++){
        randomNum = rand() % 1000 - 500;
        list_n.push_back(randomNum);
    }
    for (iter = list_n.begin(); iter != list_n.end(); iter++) {
        std::cout << *iter << ' ';
    }
    std::cout << '\n';
    std::cout << plus_count(list_n) << '\n';
}

class Card {
  std::string title;   // заглавие книги
  std::string author;  // автор
  int number;     // количество имеющихся экземпляров
 public:
  Card() : title(""), author(""), number(0) {}
  Card(std::string t, std::string a, int n) : title(t), author(a), number(n) {}
  std::string get_title(){return title;}
  std::string get_author(){return author;}
  int get_number(){return number;}
};

void seventh() {
    std::list<Card> list_cards;
    list_cards.push_back(Card("Невероятные приключения ДжоДжо часть 1", "Хирохико Араки", 9));
    list_cards.push_back(Card("Невероятные приключения ДжоДжо часть 2", "Хирохико Араки", 9));
    list_cards.push_back(Card("Невероятные приключения ДжоДжо часть 3", "Хирохико Араки", 9));
    list_cards.push_back(Card("Магическая битва", "Геге Акутами", 3));
    list_cards.push_back(Card("Что-то", "Кто-то", 100));
    list_cards.push_back(Card("Яблоки", "Никита", 54321));
    list_cards.push_back(Card("Почему", "Зачем", 1));
    std::list<Card>::iterator iter;
    for (iter = list_cards.begin(); iter != list_cards.end(); iter++) {
      std::cout << iter->get_title() << " - " << iter->get_author() << ' ' << iter->get_number() << "шт" << std::endl;
    }
    std::string author;
    std::cout << "Введите автора" << std::endl;
    std::getline(std::cin, author);
    bool in_l = false;
    for (iter = list_cards.begin(); iter != list_cards.end(); iter++) {
        // std::cout << iter->get_author();
        if (iter->get_author().compare(author) == 0){ std::cout << iter->get_title() << ' ' << iter->get_number() << "шт" << std::endl; in_l=true;}
    }
    if (not in_l){
        std::cout << "Книги данного автора отсутствуют" << std::endl;
    }
}

void eighth() {
    std::map<int, double> m;
    std::map<int, double>::iterator i;
    for (int j=0; j<10; j++){
        m[j] = static_cast<float>(j) + static_cast<float>(j)/10;
    }
    for (i = m.begin(); i != m.end(); i++){
        std::cout << i->first << " -> " << i->second << "; \n";
    }

    for (i = m.begin(); i != m.end();){
        if (i->first % 2 == 0) {
            auto j = i++;
            m.erase(j->first);
        }
        else {
            i++;
        }
    }
    std::cout << '\n';
    for (i = m.begin(); i != m.end(); i++){
        std::cout << i->first << " -> " << i->second << "; \n";
    }
}

void ninth(){
    std::map<std::string, std::string> m;
    std::map<std::string, std::string>::iterator i;
    std::string number;
    std::string name;
    std::cout << "Справочник номеров\n";
    while (true)
    {
        std::cout << "Введите номер (чтобы выйти введите 0)\n";
        std::getline(std::cin, number);
        if (number.compare("0") == 0) {break;}
        std::cout << "Введите фамилию\n";
        std::getline(std::cin, name);
        m[number] = name;
    }

    // m["5671234"] = "Ivanov";
    // m["3214567"] = "Petrov";
    // m["9871234"] = "Sidorov";

    // std::string mas[4] = { "1112233", "9871234", "5671234", "5556688" };

    std::string mas[100];
    size_t mas_i= 0;
    std::cout << "Введите номера людей\n";
    while (true)
    {
        std::cout << "Введите номер (чтобы выйти введите 0)\n";
        std::getline(std::cin, number);
        if (number.compare("0") == 0) {break;}
        // mas->append(number);
        mas[mas_i] = number;
        mas_i++;
    }
    // std::cout << mas->size() << ";;;; \n";
    for (size_t j=0; j<mas_i;j++){
        for (i = m.begin(); i != m.end(); i++){
            // std::cout << i->first << " -> " << i->second << "; \n";
            // std::cout << i->first << '\n';
            if (i->first.compare(mas[j]) == 0) std::cout << i->second << "\n";
        }
        // std::cout << mas[j] << "\n\n";
    }

}

int main(){
    std::cout << "\nЗадача 1\n";
    std::cout << "Введите 2 слова\n";
    std::cout << first();

    std::cout << "\nЗадача 2\n";
    std::cout << "Введите слово\n";
    std::cout << second() << '\n';

    std::cout << "\nЗадача 3\n";
    third();

    std::cout << "\nЗадача 4\n";
    fourth();

    std::cout << "\nЗадача 5\n";
    std::vector<Planet> planets;
    planets.emplace_back("Меркурий", 0);
    planets.emplace_back("Венера", 0);
    planets.emplace_back("Земля", 1);
    planets.emplace_back("Марс", 2);
    planets.emplace_back("Юпитер", 69);
    planets.emplace_back("Сатурн", 62);
    planets.emplace_back("Уран", 27);
    planets.emplace_back("Нептун", 14);
    planets.emplace_back("Плутон", 10);
    fivth_print(planets);
    std::cout << '\n';
    int max_sat = -1;
    Planet max_plan = Planet();
    for (size_t i=0; i < planets.size(); i++){
        if (planets[i].satelites_ > max_sat) {
            max_sat = planets[i].satelites_;
            max_plan = planets[i];
        }
    }
    std::cout << max_plan.name_ << max_plan.satelites_ <<  '\n';

    std::cout << "\nЗадача 6\n";
    sixth();

    std::cout << "\nЗадача 7\n";
    seventh();

    std::cout << "\nЗадача 8\n";
    eighth();

    std::cout << "\nЗадача 9\n";
    ninth();

    return 0;
}

#endif // LAB8_H
