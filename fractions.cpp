#include <iostream>
#include <fstream>
#include <cstring>
# include <cmath>

class Fractions {
    private:
        int Integer_part_ = 0;
        int Numerator_ = 0;
        int Denominator_ = 0;
        bool Positive_ = true;
    public:
    Fractions() : Integer_part_(0), Numerator_(0), Denominator_(0), Positive_(true) {};
    Fractions(const Fractions&) = default;

    Fractions(int Integer_part, int Numerator=0, int Denominator=1) : Integer_part_(abs(Integer_part)), Numerator_(Numerator), Denominator_(Denominator), Positive_(Integer_part>=0) {};

    Fractions(double fraction) {
        Positive_ = (fraction >= 0);
        double abs_value = std::fabs(fraction);

        Integer_part_ = static_cast<int>(abs_value);
        double fractional = abs_value - Integer_part_;

        const double precision = pow(10, 6);
        Numerator_ = static_cast<int>(std::round(fractional * precision));
        Denominator_ = precision;
        Reducing();

    };

    Fractions(char *fraction){
        int start_of_Numerator_part = 0;
        int start_of_Integer_part = 0;
        int upper = 0;
        // std::cout << fraction << '\n';
        for (int i=strlen(fraction)-1; i > -1; i--){
            char element = fraction[i];
            // std::cout << element << '\n';
            if (element == '-') {
                Positive_ = not Positive_;
            } else if (element != '/' and element != '\\'){
                Denominator_ += (static_cast<int>(element)-static_cast<int>('0')) * pow(10, upper);
                upper++;
            } else {
                start_of_Numerator_part = i-1;
                upper = 0;
                break;
            }

        }
        // std::cout << Denominator_ << '\n';

        if (upper == 0){
        for (int i=start_of_Numerator_part; i > -1; i--){
            char element = fraction[i];
            // std::cout << element << '\n';
            if (element == '-') {
                Positive_ = not Positive_;
            } else if (element != ' ') {
            Numerator_ += (static_cast<int>(element)-static_cast<int>('0')) * pow(10, upper);
            upper++;
            } else {
                start_of_Integer_part = i-1;
                upper = 0;
                break;
            }
        }

        if (upper == 0){
        for (int i=start_of_Integer_part; i > -1; i--){
            char element = fraction[i];
            // std::cout << element << '\n';
            if (element == '-') {
                Positive_ = not Positive_;
            } else {
                Integer_part_ += (static_cast<int>(element)-static_cast<int>('0')) * pow(10, upper);
                upper++;
            }
        }
    }
        // std::cout << Numerator_ << '\n';

        Reducing();
        Find_Integer_part();
    }else{
        Integer_part_ = Denominator_;
        Numerator_ = 0;
        Denominator_ = 1;
    }
    }

    ~Fractions(){};

    Fractions& operator=(const Fractions &other){
        if (this != &other) {
            Integer_part_ = other.Integer_part_;
            Numerator_ = other.Numerator_;
            Denominator_ = other.Denominator_;
            Positive_ = other.Positive_;
        }
        return *this;
    }

    Fractions& operator-=(const Fractions &other){
        // std::cout << "||||||||||||||||||||||||||||||\n";

        // std::cout << *this;
        // std::cout << Integer_part_ << ' ' << Numerator_ << ' ' <<Denominator_ << '\n';

        // std::cout << other;

        if (other.Positive_) {
            Numerator_ = (Integer_part_ * Denominator_ + Numerator_) * other.Denominator_ - (other.Integer_part_ * other.Denominator_ + other.Numerator_) * Denominator_;
        } else {
            Numerator_ = (Integer_part_ * Denominator_ + Numerator_) * other.Denominator_ + (other.Integer_part_ * other.Denominator_ + other.Numerator_) * Denominator_;
        }
        Integer_part_ = 0;


        // std::cout << "asd " <<  (Integer_part_ * Denominator_ + Numerator_) * other.Denominator_ << '\n';
        // std::cout << "dsa " << (other.Integer_part_ * other.Denominator_ + other.Numerator_) * Denominator_ << '\n';

        // std::cout << "Нум " << Numerator_ << '\n';
        Denominator_ = other.Denominator_ * Denominator_;
        // std::cout << "Den " << Denominator_ << '\n';

        if (Numerator_ > 0) {
            Positive_ = true;
        } else {
            Positive_ = false;
            Numerator_ = -Numerator_;
        }
        Reducing();
        Find_Integer_part();
        return *this;
    }

    Fractions& operator+=(const Fractions &other){
        if (other.Positive_) {
            Numerator_ = (Integer_part_ * Denominator_ + Numerator_) * other.Denominator_ + (other.Integer_part_ * other.Denominator_ + other.Numerator_) * Denominator_;
        } else {
            Numerator_ = (Integer_part_ * Denominator_ + Numerator_) * other.Denominator_ - (other.Integer_part_ * other.Denominator_ + other.Numerator_) * Denominator_;
        }
        Integer_part_ = 0;

        Denominator_ = other.Denominator_ * Denominator_;
        if (Numerator_ > 0) {
            Positive_ = true;
        } else {
            Positive_ = false;
            Numerator_ = -Numerator_;
        }
        Reducing();
        Find_Integer_part();
        return *this;
    }

    Fractions operator-(const Fractions &other) const {
        Fractions difference = *this;
        difference -= other;
        return difference;
    }

    Fractions operator+(const Fractions &other) const {
        Fractions difference = *this;
        difference += other;
        return difference;
    }

    Fractions& operator*=(const Fractions &other){
        Numerator_ = (Integer_part_ * Denominator_ + Numerator_) * (other.Integer_part_ * other.Denominator_ + other.Numerator_);
        Denominator_ *= other.Denominator_;
        Reducing();
        Find_Integer_part();
        return *this;
    }

    Fractions& operator/=(const Fractions &other){
        Numerator_ = (Integer_part_ * Denominator_ + Numerator_) * other.Denominator_;
        Denominator_ *= (other.Integer_part_ * other.Denominator_ + other.Numerator_);
        Reducing();
        Find_Integer_part();
        return *this;
    }

    Fractions operator*(const Fractions &other) const {
        Fractions difference = *this;
        difference *= other;
        return difference;
    }

    Fractions operator/(const Fractions &other) const {
        Fractions difference = *this;
        difference /= other;
        return difference;
    }

    bool operator<(const Fractions &other) const {
        if (Positive_ < other.Positive_){
            return true;
        } else if (Positive_ < other.Positive_){
            return false;
        }

        if (Integer_part_ < other.Integer_part_) {
            return true;
        } else if (Integer_part_ > other.Integer_part_){
            return false;
        }

        if (Numerator_ * other.Denominator_ < other.Numerator_ * Denominator_) {
            return true;
        } else {
            return false;
        }
    }

    bool operator > (const Fractions &other) const {
        return (other < *this);
    }

    bool operator == (const Fractions &other) const {
        if (
            Positive_ == other.Positive_ and
            Integer_part_ == other.Integer_part_ and
            Numerator_ == other.Numerator_ and
            Denominator_ == other.Denominator_
        ) {
            return true;
        } else {
            return false;
        }
    }

    bool operator <= (const Fractions &other) const {
        return not (other < *this);
    }

    bool operator >= (const Fractions &other) const {
        return not (*this < other);
    }

    void Reducing(){
        for (int i = Denominator_ / 2 + 2; i > 2; i--){
            if (Numerator_ % i == 0 and Denominator_ % i == 0){
                Numerator_ /= i;
                Denominator_ /= i;
            }
        }
        if (Numerator_ % Denominator_ == 0){
            Numerator_ /= Denominator_;
            Denominator_ = 1;
        }
    }

    void Find_Integer_part() {
        Integer_part_ += Numerator_ / Denominator_;
        Numerator_ = Numerator_ % Denominator_;
    }

    friend std::ostream& operator << (std::ostream &os, const Fractions &fractions);
    friend std::istream& operator >> (std::istream& in, Fractions& fractions);


};

std::ostream& operator << (std::ostream &os, const Fractions &fractions)
{
    if (not fractions.Positive_){
        os << '-';
    }
    os << fractions.Integer_part_ << " ";
    if (fractions.Numerator_ != 0){
        os << fractions.Numerator_ << "/"
        << fractions.Denominator_ << "\n";
    } else {
        os << '\n';
    }
    return os;
}

std::istream& operator >> (std::istream& in, Fractions& fractions)
{
    char frac[100];
    in.getline(frac, 100);

    fractions = Fractions(frac);
    return in;
}

// int interactive();

// int demo();

// int main(int argc, char *argv[]) {
//     bool isInteractive = false;    // по умолчанию демо-режим.

//     // Если i передается в качестве аргумента, то программу
//     // необходимо запустить в интерактивном режиме
//     if ((argc == 2) && strcmp(argv[1], "i") == 0) {
//         isInteractive = true;
//     }

//     if (isInteractive) {
//         return interactive();

//     } else {
//         return demo();
//     }
// }

int main() {
    setlocale(LC_ALL, "Russian");

    // ввод дроби с клавиатуры
    std::cout << "Введите дробь: \n";
    Fractions z;
    std::cin >> z;
    std::cout << "z=" << z << std::endl;
    // проверка конструкторов
    Fractions fr1(10, 14), fr2;
    std::cout << "fr2=" << fr2 << std::endl;
    std::cout << "fr1=" << fr1 << std::endl;
    Fractions fr = "-1 4/8";
    std::cout << "fr=" << fr << std::endl;
    Fractions x(z), y;
    std::cout << "x=" << x << std::endl;
    double dbl = -1.25;
    Fractions f = dbl;
    std::cout << "f=" << f << std::endl;
    // проверка перегруженной операции "+"
    y = x + z;
    std::cout << "y=" << y << std::endl;
    y += x;
    f += dbl / 2;
    std::cout << "f=" << f << std::endl;
    y = x + dbl;
    std::cout << "y=" << y << std::endl;
    y = dbl + y;
    std::cout << "y=" << y << std::endl;
    y += dbl;
    std::cout << "y=" << y << std::endl;
    int i = 5;
    y += i;
    std::cout << "y=" << y << std::endl;
    y = i + x;
    std::cout << "y=" << y << std::endl;
    y = x + i;
    std::cout << "y=" << y << std::endl;
    y += dbl + i + x;
    std::cout << "y=" << y << std::endl;
    return 0;
}
