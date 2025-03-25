#include "fractions.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <stdexcept>

//Fractions::Fractions() : Integer_part_(0), Numerator_(0), Denominator_(1), Positive_(true) {}

 Fractions::Fractions(const Fractions &other) = default;

Fractions::Fractions(int Integer_part, int Numerator, int Denominator)
    : Integer_part_(std::abs(Integer_part)), Numerator_(Numerator), Denominator_(Denominator), Positive_(Integer_part >= 0) {
        Reducing();
        Find_Integer_part();
    }

Fractions::Fractions(double fraction) {
    Positive_ = (fraction >= 0);
    double abs_value = std::fabs(fraction);
    Integer_part_ = static_cast<int>(abs_value);
    double fractional = abs_value - Integer_part_;
    const double precision = std::pow(10, 6);
    Numerator_ = static_cast<int>(std::round(fractional * precision));
    Denominator_ = static_cast<int>(precision);
    Reducing();
    Find_Integer_part();
}

Fractions::Fractions(const char *fraction)
    : Integer_part_(0), Numerator_(0), Denominator_(0), Positive_(true) {
    int start_of_Numerator_part = 0;
    int start_of_Integer_part = 0;
    int upper = 0;
    for (int i = std::strlen(fraction) - 1; i > -1; i--) {
        char element = fraction[i];
        if (element == '-') {
            Positive_ = !Positive_;
        } else if (element != '/' && element != '\\') {
            if (not isdigit(element)){
                throw std::invalid_argument("Введены не числа");
            }
            Denominator_ += (static_cast<int>(element) - static_cast<int>('0')) * std::pow(10, upper);
            upper++;
        } else {
            start_of_Numerator_part = i - 1;
            upper = 0;
            break;
        }
    }
    if (upper == 0) {
        for (int i = start_of_Numerator_part; i > -1; i--) {
            char element = fraction[i];
            if (element == '-') {
                Positive_ = !Positive_;
            } else if (element != ' ') {
                if (not isdigit(element)){
                    throw std::invalid_argument("Введены не числа");
                }
                Numerator_ += (static_cast<int>(element) - static_cast<int>('0')) * std::pow(10, upper);
                upper++;
            } else {
                start_of_Integer_part = i - 1;
                upper = 0;
                break;
            }
        }
        if (upper == 0) {
            for (int i = start_of_Integer_part; i > -1; i--) {
                char element = fraction[i];
                if (element == '-') {
                    Positive_ = !Positive_;
                } else {
                    if (not isdigit(element)){
                        throw std::invalid_argument("Введены не числа");
                    }
                    Integer_part_ += (static_cast<int>(element) - static_cast<int>('0')) * std::pow(10, upper);
                    upper++;
                }
            }
        }
        Reducing();
        Find_Integer_part();
    } else {
        Integer_part_ = Denominator_;
        Numerator_ = 0;
        Denominator_ = 1;
    }
}

Fractions::~Fractions() {}

Fractions& Fractions::operator=(const Fractions &other) {
    if (this != &other) {
        Integer_part_ = other.Integer_part_;
        Numerator_ = other.Numerator_;
        Denominator_ = other.Denominator_;
        Positive_ = other.Positive_;
    }
    return *this;
}

Fractions& Fractions::operator-=(const Fractions &other) {
    int left_total = Integer_part_ * Denominator_ + Numerator_;
    int right_total = other.Integer_part_ * other.Denominator_ + other.Numerator_;
    if (other.Positive_ == Positive_) {
        Numerator_ = left_total * other.Denominator_ - right_total * Denominator_;
    } else {
        Numerator_ = left_total * other.Denominator_ + right_total * Denominator_;
    }
    Integer_part_ = 0;
    Denominator_ *= other.Denominator_;
    if (Numerator_ < 0) {
        Positive_ = false;
        Numerator_ = -Numerator_;
    } else {
        Positive_ = true;
    }
    Reducing();
    Find_Integer_part();
    return *this;
}

Fractions& Fractions::operator+=(const Fractions &other) {
    // std::cout << "l====================" << *this << std::endl;
    // std::cout << "r====================" << other << std::endl;
    int left_total = Integer_part_ * Denominator_ + Numerator_;
    int right_total = other.Integer_part_ * other.Denominator_ + other.Numerator_;
    if (other.Positive_ == Positive_) {
        Numerator_ = left_total * other.Denominator_ + right_total * Denominator_;
    } else {
        Numerator_ = left_total * other.Denominator_ - right_total * Denominator_;
    }


    // std::cout << "l======" << left_total << std::endl;
    // std::cout << "r======" << right_total << std::endl;
    // std::cout << "s======" << Numerator_ << std::endl;

    Integer_part_ = 0;
    Denominator_ *= other.Denominator_;
    if (Numerator_ < 0) {
        Positive_ = not Positive_;
        Numerator_ = -Numerator_;
    }
    Reducing();
    Find_Integer_part();
    return *this;
}

Fractions operator-(const Fractions &self, const Fractions &other){
    Fractions result = self;
    result -= other;
    return result;
}


Fractions Fractions::operator+(const Fractions &other) const {
    Fractions result = *this;
    result += other;
    return result;
}

// Оператор *=
Fractions& Fractions::operator*=(const Fractions &other) {
    int left_total = Integer_part_ * Denominator_ + Numerator_;
    int right_total = other.Integer_part_ * other.Denominator_ + other.Numerator_;
    Numerator_ = left_total * right_total;
    Denominator_ *= other.Denominator_;
    Reducing();
    Find_Integer_part();
    return *this;
}

// Оператор /=
Fractions& Fractions::operator/=(const Fractions &other) {
    int left_total = Integer_part_ * Denominator_ + Numerator_;
    int right_total = other.Integer_part_ * other.Denominator_ + other.Numerator_;
    Numerator_ = left_total * other.Denominator_;
    Denominator_ *= right_total;
    Reducing();
    Find_Integer_part();
    return *this;
}

// Оператор *
Fractions Fractions::operator*(const Fractions &other) const {
    Fractions result = *this;
    result *= other;
    return result;
}

// Оператор /
Fractions Fractions::operator/(const Fractions &other) const {
    Fractions result = *this;
    // std::cout << "t||||||||||||||||||" << result << std::endl;
    // std::cout << "o||||||||||||||||||" << other << std::endl;

    result /= other;
    return result;
}

// Сравнение
bool Fractions::operator<(const Fractions &other) const {
    if (Positive_ != other.Positive_) {
        return !Positive_;
    }
    if (Integer_part_ != other.Integer_part_) {
        return Integer_part_ < other.Integer_part_;
    }
    return (Numerator_ * other.Denominator_) < (other.Numerator_ * Denominator_);
}

bool Fractions::operator>(const Fractions &other) const {
    return other < *this;
}

bool Fractions::operator==(const Fractions &other) const {
    return (Positive_ == other.Positive_ &&
            Integer_part_ == other.Integer_part_ &&
            Numerator_ == other.Numerator_ &&
            Denominator_ == other.Denominator_);
}

bool Fractions::operator<=(const Fractions &other) const {
    return !(*this > other);
}

bool Fractions::operator>=(const Fractions &other) const {
    return !(*this < other);
}

// Функция сокращения дроби
void Fractions::Reducing() {
    for (int i = Denominator_ / 2 + 2; i >= 2; i--) {
        if (Numerator_ % i == 0 && Denominator_ % i == 0) {
            Numerator_ /= i;
            Denominator_ /= i;
        }
    }
    if (Denominator_ != 0 && Numerator_ % Denominator_ == 0) {
        Numerator_ /= Denominator_;
        Denominator_ = 1;
    }
}

// Вычисление целой части
void Fractions::Find_Integer_part() {
    if (Denominator_ != 0) {
        Integer_part_ += Numerator_ / Denominator_;
        Numerator_ = Numerator_ % Denominator_;
    } else {
        throw std::invalid_argument("Деление на 0");
    }
}

// Перегрузка оператора <<
std::ostream& operator<<(std::ostream &os, const Fractions &fractions) {
    if (!fractions.Positive_) {
        os << '-';
    }
    if (fractions.Integer_part_ != 0) {
        os << fractions.Integer_part_ << " ";
    }
    if (fractions.Numerator_ != 0) {
        os << fractions.Numerator_ << "/" << fractions.Denominator_;
    }
    if (fractions.Integer_part_ == 0 and fractions.Numerator_ == 0){
        os << '0' << '\n';
    }
    return os;
}

// Перегрузка оператора >>
std::istream& operator>>(std::istream &in, Fractions &fractions) {
    char frac[100];
    in.getline(frac, 100);
    fractions = Fractions(frac);
    return in;
}

Fractions operator+(double lhs, const Fractions &rhs) {
    return Fractions(lhs) + rhs;
}

Fractions operator+(int lhs, const Fractions &rhs) {
    return Fractions(lhs) + rhs;
}

int Fractions::menu() {
    std::cout << "\nВведите, что бы вы хотели сделать:" << std::endl
              << "1. Ввести дробь" << std::endl
              << "2. Сложить две дроби" << std::endl
              << "3. Вычесть две дроби" << std::endl
              << "4. Умножить две дроби" << std::endl
              << "5. Разделить две дроби" << std::endl
              << "6. Выйти" << std::endl;
    int choice;
    std::cin >> choice;
    return choice;
}
