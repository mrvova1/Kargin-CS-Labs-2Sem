// MySet.h
#ifndef MYSET_H
#define MYSET_H

#include <iostream>
#include <cstring>

class Term {
private:
    int k_ = 0;
    int n_ = 0;
public:
    Term();
    Term(int k) : k_(k) {}
    Term(int k, int n) : k_(k), n_(n) {}
    Term(const Term& other);
    Term& operator=(const Term& other);
    ~Term();

    Term& operator+=(const Term& other){
        if (n_ != other.n_){
            std::cout<< "Нельзя складывать термы разной степени\n";
            return *this;
        }
        k_ += other.k_;
        return *this;
    }

    Term& operator*=(const Term& other){
        n_ += other.n_;
        k_ *= other.k_;
        return *this;
    }

    Term operator+(const Term& other) {
        Term new_term = *this;
        new_term += other;
        return new_term;
    }

    Term operator*(const Term& other) {
        Term new_term = *this;
        new_term *= other;
        return new_term;
    }

    friend class Polynomial;
};


class Polynomial {
private:
    size_t max_size_;
    size_t size_;
    Term* poly_;
    int degree_;
    bool order_;
public:
    Polynomial(size_t max_size = 1);
    Polynomial(const Polynomial& other);
    Polynomial& operator=(const Polynomial& other);

    Polynomial() : max_size_(1), size_(0), degree_(0), order_(false), poly_(new Term[1]) {}

    Polynomial(int k, bool order=false) : max_size_(1), size_(0), degree_(0), order_(order){
        poly_ = new Term[1];
        poly_[0] = Term(k);
    }

    Polynomial(Term new_Term, bool order=false) : max_size_(1), size_(0), degree_(0), order_(order){
        poly_ = new Term[1];
        poly_[0] = new_Term;
    }

    ~Polynomial();

    void add_element(Term new_element);
    Term delete_element(size_t index);
    void resize();
    void sort();

    Polynomial operator+=(const Polynomial& other) {
        bool have;
        for (size_t i=0; i < other.len(); i++) {
            have = false;
            for (size_t j=0; j < len(); j++) {
                if (poly_[j].n_ == other[i].n_) {
                    poly_[j] += other[i];
                    have = true;
                    break;
                }
            }
            if (not have){
                add_element(other[i]);
            }
        }
        return *this;
    }

    Polynomial operator*=(const Polynomial& other) {
        for (size_t i=0; i < other.len(); i++) {
            for (size_t j=0; j < len()-1; j++) {
                add_element(poly_[j] * other[i]);
            }
            poly_[len()] *= other[i];
        }
        return *this;
    }

    friend Polynomial operator+(const Polynomial& first, const Polynomial& second);
    friend Polynomial operator*(const Polynomial& first, const Polynomial& second);

    Term operator[](size_t num) const;
    size_t len() const;
};

Polynomial operator+(const Polynomial& first, const Polynomial& second) {
    Polynomial new_Polynomial = first;
    new_Polynomial += second;
    return new_Polynomial;
}

Polynomial operator*(const Polynomial& first, const Polynomial& second) {
    Polynomial new_Polynomial = first;
    new_Polynomial *= second;
    return new_Polynomial;
}

Polynomial::Polynomial(const Polynomial& other) {
    order_ = other.order_;
    max_size_ = other.max_size_;
    size_ = other.size_;
    poly_ = new Term[max_size_];
    for (size_t i = 0; i < max_size_; ++i) {
        poly_[i] = other.poly_[i];
    }
    degree_ = other.degree_;
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        order_ = other.order_;
        max_size_ = other.max_size_;
        size_ = other.size_;
        delete[] poly_;
        poly_ = new Term[max_size_];
        for (size_t i = 0; i < max_size_; ++i) {
            poly_[i] = other.poly_[i];
        }
        degree_ = other.degree_;
    }
    return *this;
}


Polynomial::~Polynomial() {
    delete[] poly_;
}


void Polynomial::add_element(Term new_element) {
    ++size_;
    if (size_ >= max_size_ / 2) {
        resize();
    }
    poly_[size_ - 1] = new_element;
    sort();
}


Term Polynomial::delete_element(size_t index) {
    if (index >= size_ - 1) {
        std::cout << "Индекс превосходит размер массива";
        return -1;
    }
    for (size_t i = index + 1; i < max_size_; ++i) {
        poly_[i - 1] = poly_[i];
    }
    poly_[size_ - 1] = 0;
    --size_;
    resize();
    return 0;
}


void Polynomial::resize() {
    while (size_ > max_size_ / 2) {
        Term* new_pdata = new Term[max_size_ * 2];
        for (size_t i = 0; i < max_size_; ++i) new_pdata[i] = poly_[i];
        delete[] poly_;
        poly_ = new_pdata;
        max_size_ *= 2;
    }
    while (size_ < max_size_ / 4) {
        Term* new_pdata = new Term[max_size_ / 2];
        for (size_t i = 0; i < max_size_; ++i) new_pdata[i] = poly_[i];
        delete[] poly_;
        poly_ = new_pdata;
        max_size_ /= 2;
    }
}


void Polynomial::sort() {
    for (size_t i = 0; i < size_ - 1; ++i) {
        for (size_t j = i + 1; j < size_; ++j) {
            if (order_ == (poly_[j].n_ < poly_[i].n_)) {
                Term tmp = poly_[i];
                poly_[i] = poly_[j];
                poly_[j] = tmp;
            }
        }
    }
}


Term Polynomial::operator[](size_t num) const {
    return poly_[num];
}


size_t Polynomial::len() const {
    return size_;
}

#endif // MYSET_H
