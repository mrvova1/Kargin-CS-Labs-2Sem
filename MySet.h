#ifndef MYSET_H
#define MYSET_H

#include <iostream>
#include <cstring>

class Term {
private:
    int k_;
    int n_;
public:
    Term();
    Term(int k, int n=0);
    Term(char* cterm);
    int degree() const;
    int coeff() const;
    Term& operator+=(const Term& other);
    friend Term operator+(const Term& a, const Term& b);
    friend std::istream& operator>>(std::istream& is, Term& term);
    friend std::ostream& operator<<(std::ostream& os, const Term& term);
};

Term::Term(char* cterm) {
    std::cout << cterm << '\n';
    int pk = 1;
    int k = 0;
    int pn = 1;
    int n = 0;
    int j = 0;
    bool is_k = false;

    while (cterm[j] == ' ')
    {
        j += 1;
    }
    if (cterm[j] == '-'){
        pk = -1;
        j+=1;
    }
    if (cterm[j] == '+'){
        j+=1;
    }
    while (cterm[j] == ' ')
    {
        j += 1;
    }

    for (int i = j; true; i++){
        if (cterm[i] == ' '){
            break;
        }
        if (cterm[i] == 'x'){
            break;
        }
        if (not isdigit(cterm[i])){
            k_ = 0;
            n_ = 0;
            return;
        }
        k *= 10;
        k += (static_cast<int>(cterm[i]) - static_cast<int>('0'));
        j+=1;
        is_k = true;

    }

    j+=1;

    while (cterm[j] == ' ' or cterm[j] == '^' or cterm[j] == 'x')
    {
        j += 1;
    }
    if (cterm[j] == '-'){
        pn = -1;
        j+=1;
    }
    while (cterm[j] == ' ')
    {
        j += 1;
    }
    for (int i = j; i < static_cast<int>(std::strlen(cterm)); i++){
        if (cterm[i] == ' '){
            break;
        }

        if (not isdigit(cterm[i])){
            k_ = 0;
            n_ = 0;
            return;
        }
        n *= 10;
        n += (static_cast<int>(cterm[i]) - static_cast<int>('0'));
        j+=1;
    }

    // term = Term(k * pk, n * pn);
    k_ = k * pk;
    n_ = n * pn;
    if (not is_k) {
        k_ = pk;
    }
    return;
}

class Polynomial {
private:
    Term* terms_;
    int size_;
    int capacity_;
    void ensure_capacity();
    void sort_desc();
public:
    Polynomial();
    Polynomial(const Polynomial& other);
    Polynomial& operator=(const Polynomial& other);
    ~Polynomial();
    void add_term(const Term& t);
    friend Polynomial operator+(const Polynomial& a, const Polynomial& b);
    friend Polynomial operator*(const Polynomial& a, const Polynomial& b);
    friend std::istream& operator>>(std::istream& is, Polynomial& poly);
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
};

Term::Term(): k_(0), n_(0) {}
Term::Term(int k, int n): k_(k), n_(n) {}
int Term::degree() const { return n_; }
int Term::coeff() const { return k_; }
Term& Term::operator+=(const Term& other) {
    if (n_ == other.n_) k_ += other.k_;
    return *this;
}
Term operator+(const Term& a, const Term& b) {
    Term r = a;
    r += b;
    return r;
}

std::istream& operator>>(std::istream& is, Term& term) {
    char cterm[1000];
    is.getline(cterm, 1000);
    term = Term(cterm);
    return is;
}
// std::istream& operator>>(std::istream& is, Term& term) {
//     char c;
//     while (is.peek() == ' ' || is.peek() == '\t' || is.peek() == '\n') {
//         is.get();
//     }
//     if (!is.good()) return is;
//     int sign = 1;
//     if (is.peek() == '+' || is.peek() == '-') {
//         is.get(c);
//         if (c == '-') sign = -1;
//     }
//     int k = 0;
//     bool haveDigit = false;
//     while (std::isdigit(is.peek())) {
//         is.get(c);
//         haveDigit = true;
//         k = k * 10 + (c - '0');
//     }
//     if (!haveDigit) k = 1;
//     k *= sign;
//     int n = 0;
//     if (is.peek() == 'x') {
//         is.get();
//         n = 1;
//         if (is.peek() == '^') {
//             is.get();
//             n = 0;
//             while (std::isdigit(is.peek())) {
//                 is.get(c);
//                 n = n * 10 + (c - '0');
//             }
//         }
//     }
//     term = Term(k, n);
//     return is;
// }


std::ostream& operator<<(std::ostream& os, const Term& term) {
    int k = term.k_;
    int n = term.n_;
    if (k == 0) {
        os << '0';
        return os;
    }
    if (n == 0) {
        os << k << 'x';
        return os;
    }
    if (k <= -1) os << '-';
    else if (k != 1) os << k;
    os << 'x';
    if (n != 1) os << '^' << n;
    return os;
}

Polynomial::Polynomial(): terms_(new Term[4]), size_(0), capacity_(4) {}
Polynomial::Polynomial(const Polynomial& other): terms_(new Term[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
    for (int i = 0; i < size_; ++i) terms_[i] = other.terms_[i];
}
Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        delete[] terms_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        terms_ = new Term[capacity_];
        for (int i = 0; i < size_; ++i) terms_[i] = other.terms_[i];
    }
    return *this;
}
Polynomial::~Polynomial() { delete[] terms_; }
void Polynomial::ensure_capacity() {
    if (size_ < capacity_) return;
    int newCap = capacity_ * 2;
    Term* tmp = new Term[newCap];
    for (int i = 0; i < size_; ++i) tmp[i] = terms_[i];
    delete[] terms_;
    terms_ = tmp;
    capacity_ = newCap;
}
void Polynomial::add_term(const Term& t) {
    for (int i = 0; i < size_; ++i) {
        if (terms_[i].degree() == t.degree()) {
            terms_[i] += t;
            if (terms_[i].coeff() == 0) {
                for (int j = i; j < size_ - 1; ++j) terms_[j] = terms_[j+1];
                size_--;
            }
            return;
        }
    }
    ensure_capacity();
    terms_[size_++] = t;
    sort_desc();
}
void Polynomial::sort_desc() {
    for (int i = 0; i < size_ - 1; ++i)
        for (int j = i + 1; j < size_; ++j)
            if (terms_[j].degree() > terms_[i].degree()) {
                Term tmp = terms_[i];
                terms_[i] = terms_[j];
                terms_[j] = tmp;
            }
}
// std::istream& operator>>(std::istream& is, Polynomial& poly) {
//     poly.size_ = 0;
//     char c;
//     while (true) {
//         while (is.peek() == ' ' || is.peek() == '\t') is.get();
//         if (!is.good() || is.peek() == '\n') {
//             if (is.peek() == '\n') is.get();
//             break;
//         }
//         int sign = 1;
//         if (is.peek() == '+' || is.peek() == '-') {
//             is.get(c);
//             if (c == '-') sign = -1;
//         }
//         int k = 0; bool have = false;
//         while (std::isdigit(is.peek())) { is.get(c); have = true; k = k*10 + (c - '0'); }
//         if (!have) k = 1;
//         k *= sign;
//         int n = 0;
//         if (is.peek() == 'x') {
//             is.get(); n = 1;
//             if (is.peek() == '^') {
//                 is.get(); n = 0;
//                 while (std::isdigit(is.peek())) { is.get(c); n = n*10 + (c - '0'); }
//             }
//         }
//         poly.add_term(Term(k,n));
//     }
//     poly.sort_desc();
//     return is;
// }

char* slice(char* s, int from, int to)
{
    char copy_s[1000];
    strcpy(copy_s, s);
    copy_s[to+1] = 0;
    return copy_s+from;
};

bool end(char cpol[1000], int j){
    return j > static_cast<int>(std::strlen(cpol));
}

std::istream& operator>>(std::istream& is, Polynomial& poly) {
    char cpol[1000];
    is.getline(cpol, 1000);
    int i = 0;
    // int ij = 0;
    int j = 0;
    bool short_T;
    char slice_cpol[1000];
    bool is_number = false;
    // bool number = false;
    while (true)
    {
        is_number = false;
        // number = false;
        while (cpol[j] != 'x'){
            j+=1;
            if (end(cpol, j)) {break;};
            if (cpol[j] == '-' or cpol[j] == '+') {
                if (is_number) {
                    poly.add_term(Term(slice(cpol, i, j-1)));
                    i=j;
                    continue;
                };
                is_number = true;
            }
        }
        if (end(cpol, j)) {poly.add_term(Term(slice(cpol, i, j-1))); break;}
        j+=1;
        // ij = j;
        short_T = false;
        while (cpol[j] != '^'){j+=1; if (cpol[j] == '-' or cpol[j] == '+') {j-=1; short_T = true; break;} }
        j+=1;
        if (short_T) { poly.add_term(Term(slice(cpol, i, j+1))); i=j+1; continue; }
        while (cpol[j] == ' '){ j+=1; }
        while (isdigit(cpol[j])){ j+=1; }
        std::strcpy(slice_cpol, cpol);
        Term s = Term(slice(slice_cpol, i, j+1));
        poly.add_term(s); i=j+1; continue;
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
    if (poly.size_ == 0) { os << '0'; return os; }
    for (int i = 0; i < poly.size_; ++i) {
        // std::cout << poly.terms_[i] << '\n';

        int k = poly.terms_[i].coeff();
        int n = poly.terms_[i].degree();
        if (i > 0) os << (k >= 0 ? " + " : " - ");
        else if (k < 0) os << '-';
        int absK = k < 0 ? -k : k;
        if (n == 0) os << absK;
        else {
            if (absK != 1) os << absK;
            if (n != 0){
            os << 'x';
            if (n != 1) os << '^' << n;
            }
        }
        // os << '\n';
    }
    return os;
}

Polynomial operator+(const Polynomial& a, const Polynomial& b) {
    Polynomial r = a;
    for (int i = 0; i < b.size_; ++i) r.add_term(b.terms_[i]);
    r.sort_desc();
    return r;
}
Polynomial operator*(const Polynomial& a, const Polynomial& b) {
    Polynomial r;
    for (int i = 0; i < a.size_; ++i)
        for (int j = 0; j < b.size_; ++j)
            r.add_term(Term(a.terms_[i].coeff() * b.terms_[j].coeff(),
                           a.terms_[i].degree() + b.terms_[j].degree()));
    r.sort_desc();
    return r;
}

#endif // MYSET_H
