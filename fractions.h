#ifndef FRACTIONS_H
#define FRACTIONS_H

#include <iostream>

enum MenuOption {
    INPUT_FRACTION = 1,
    ADD_FRACTIONS,
    SUBTRACT_FRACTIONS,
    MULTIPLY_FRACTIONS,
    DIVIDE_FRACTIONS,
    EXIT_PROGRAM
};

class Fractions {
private:
    int Integer_part_;
    int Numerator_;
    int Denominator_;
    bool Positive_;
    void Reducing();
    void Find_Integer_part();
public:
   // Fractions();
    Fractions(const Fractions& other);
    Fractions(int Integer_part=0, int Numerator = 0, int Denominator = 1);
    Fractions(double fraction);
    Fractions(const char* fraction);
    ~Fractions();
    Fractions& operator=(const Fractions &other);
    Fractions& operator-=(const Fractions &other);
    Fractions& operator+=(const Fractions &other);
    //Fractions operator-(const Fractions &other) const;
    Fractions operator+(const Fractions &other) const;
    Fractions& operator*=(const Fractions &other);
    Fractions& operator/=(const Fractions &other);
    Fractions operator*(const Fractions &other) const;
    Fractions operator/(const Fractions &other) const;
    bool operator<(const Fractions &other) const;
    bool operator>(const Fractions &other) const;
    bool operator==(const Fractions &other) const;
    bool operator<=(const Fractions &other) const;
    bool operator>=(const Fractions &other) const;

    friend std::ostream& operator<<(std::ostream &os, const Fractions &fractions);
    friend std::istream& operator>>(std::istream &in, Fractions &fractions);
    friend Fractions operator-(const Fractions &self, const Fractions &other);

    static int menu();
};

// Перегрузки операторов для работы с типами double и int в качестве левого операнда.
Fractions operator+(double lhs, const Fractions &rhs);
Fractions operator+(int lhs, const Fractions &rhs);

#endif // FRACTIONS_H
