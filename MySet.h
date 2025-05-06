// MySet.h
#ifndef MYSET_H
#define MYSET_H

#include <iostream>
#include <cstring>

template<typename INF>
class MyVector {
private:
    size_t max_size_;
    size_t size_;
    INF* pdata_;
public:
    MyVector(size_t max_size = 1);
    MyVector(const MyVector& other);
    MyVector& operator=(const MyVector& other);
    ~MyVector();

    void add_element(INF new_element);
    int delete_element(size_t index);
    int find(INF el);
    void resize();
    void sort();

    INF operator[](size_t num) const;
    size_t len() const;
};

template<>
int MyVector<char*>::find(char* el);

template<>
MyVector<char*>::~MyVector();

template<>
void MyVector<char*>::add_element(char* new_element);

template<>
int MyVector<char*>::delete_element(size_t index);

template<typename INF>
class MySet : public MyVector<INF> {
public:
    bool is_element(INF el);
    bool add_element(INF el);
    bool delete_element(INF el);

    void operator+=(const MySet& St);
    void operator-=(const MySet& St);
    void operator*=(const MySet& St);

    template<class I>
    friend std::ostream& operator<<(std::ostream& os, const MySet<I>& St);

    template<typename I>
    friend MySet<I> operator*(const MySet<I>& f_st, const MySet<I>& s_st);
    template<typename I>
    friend MySet<I> operator+(const MySet<I>& f_st, const MySet<I>& s_st);
    template<typename I>
    friend MySet<I> operator-(const MySet<I>& f_st, const MySet<I>& s_st);
    template<typename I>
    friend bool operator==(const MySet<I>& f_st, const MySet<I>& s_st);
};

template<typename INF>
std::ostream& operator<<(std::ostream& os, const MySet<INF>& St);

template<typename INF>
MyVector<INF>::MyVector(size_t max_size)
    : max_size_(max_size), size_(0), pdata_(new INF[max_size]) {}

template<typename INF>
MyVector<INF>::MyVector(const MyVector& other)
    : max_size_(other.max_size_), size_(other.size_), pdata_(new INF[other.max_size_]) {
    for (size_t i = 0; i < max_size_; ++i) {
        pdata_[i] = other.pdata_[i];
    }
}

template<typename INF>
MyVector<INF>& MyVector<INF>::operator=(const MyVector& other) {
    if (this != &other) {
        max_size_ = other.max_size_;
        size_ = other.size_;
        delete[] pdata_;
        pdata_ = new INF[max_size_];
        for (size_t i = 0; i < max_size_; ++i) {
            pdata_[i] = other.pdata_[i];
        }
    }
    return *this;
}

template<typename INF>
MyVector<INF>::~MyVector() {
    delete[] pdata_;
}

template<typename INF>
void MyVector<INF>::add_element(INF new_element) {
    ++size_;
    if (size_ >= max_size_ / 2) {
        resize();
    }
    pdata_[size_ - 1] = new_element;
}

template<typename INF>
int MyVector<INF>::delete_element(size_t index) {
    std::cout << '\n' << index << "index\n";
    if (index >= size_) {
        std::cout << "Индекс превосходит размер массива";
        return -1;
    }
    for (size_t i = index + 1; i < max_size_; ++i) {
        pdata_[i - 1] = pdata_[i];
    }
    pdata_[size_ - 1] = 0;
    --size_;
    resize();
    return 0;
}

template<typename INF>
int MyVector<INF>::find(INF el) {
    if (size_ == 0) return -1;
    int left_b = 0;
    int right_b = size_ - 1;
    int mid = (right_b - left_b) / 2 + left_b;
    while (pdata_[mid] != el) {
        if (pdata_[mid] > el)
            right_b = mid - 1;
        else
            left_b = mid + 1;
        mid = (right_b - left_b) / 2 + left_b;
        if (right_b == left_b) {
            if (pdata_[mid] == el) break;
            return -1;
        }
        if (right_b < 0 || left_b > static_cast<int>(size_) - 1) return -1;
    }
    return mid;
}

template<typename INF>
void MyVector<INF>::resize() {
    while (size_ > max_size_ / 2) {
        INF* new_pdata = new INF[max_size_ * 2];
        for (size_t i = 0; i < max_size_; ++i) new_pdata[i] = pdata_[i];
        delete[] pdata_;
        pdata_ = new_pdata;
        max_size_ *= 2;
    }
    while (size_ < max_size_ / 4) {
        INF* new_pdata = new INF[max_size_ / 2];
        for (size_t i = 0; i < max_size_; ++i) new_pdata[i] = pdata_[i];
        delete[] pdata_;
        pdata_ = new_pdata;
        max_size_ /= 2;
    }
}

template<typename INF>
void MyVector<INF>::sort() {
    for (size_t i = 0; i < size_ - 1; ++i) {
        for (size_t j = i + 1; j < size_; ++j) {
            if (pdata_[j] < pdata_[i]) {
                INF tmp = pdata_[i];
                pdata_[i] = pdata_[j];
                pdata_[j] = tmp;
            }
        }
    }
}

template<typename INF>
INF MyVector<INF>::operator[](size_t num) const {
    return pdata_[num];
}

template<typename INF>
size_t MyVector<INF>::len() const {
    return size_;
}

template<>
int MyVector<char*>::find(char* el) {
    for (size_t i = 0; i < size_; ++i) {
        if (std::strcmp(pdata_[i], el) == 0) return i;
    }
    return -1;
}

template<>
MyVector<char*>::~MyVector() {
    for (size_t i = 0; i < size_; ++i)
     delete[] pdata_[i];
    delete[] pdata_;
}

template<>
void MyVector<char*>::add_element(char* new_element) {
    ++size_;
    if (size_ >= max_size_ / 2) resize();
    delete[] pdata_[size_ - 1];
    pdata_[size_ - 1] = new char[std::strlen(new_element) + 1];
    std::strcpy(pdata_[size_ - 1], new_element);
}

template<>
int MyVector<char*>::delete_element(size_t index) {
    if (index >= size_) {
        std::cout << "Индекс превосходит размер массива";
        return -1;
    }
    delete[] pdata_[index];
    for (size_t i = index + 1; i < max_size_; ++i) {
        pdata_[i - 1] = pdata_[i];
    }
    --size_;
    resize();
    return 0;
}

template<typename INF>
bool MySet<INF>::is_element(INF el) {
    if (this->len() == 0) return false;
    return this->find(el) != -1;
}

template<typename INF>
bool MySet<INF>::add_element(INF el) {
    if (!is_element(el)) {
        this->MyVector<INF>::add_element(el);
        this->sort();
        return true;
    }
    return false;
}

template<typename INF>
bool MySet<INF>::delete_element(INF el) {
    if (is_element(el)) {
        this->MyVector<INF>::delete_element(this->find(el));
        return true;
    }
    return false;
}

template<typename INF>
void MySet<INF>::operator+=(const MySet& St) {
    for (size_t i = 0; i < St.len(); ++i) {
        if (!is_element(St[i])) add_element(St[i]);
    }
}

template<typename INF>
void MySet<INF>::operator-=(const MySet& St) {
    for (size_t i = 0; i < St.len(); ++i) {
        if (is_element(St[i])) delete_element(St[i]);
    }
}

template<typename INF>
void MySet<INF>::operator*=(const MySet& St) {
    for (size_t i = 0; i < this->len(); ++i) {
        if (!St.is_element(this->operator[](i))) delete_element(this->operator[](i));
    }
}

template<typename INF>
MySet<INF> operator*(const MySet<INF>& f_st, const MySet<INF>& s_st) {
    MySet<INF> new_v = f_st;
    new_v *= s_st;
    return new_v;
}

template<typename INF>
MySet<INF> operator+(const MySet<INF>& f_st, const MySet<INF>& s_st) {
    MySet<INF> new_v = f_st;
    new_v += s_st;
    return new_v;
}

template<typename INF>
MySet<INF> operator-(const MySet<INF>& f_st, const MySet<INF>& s_st) {
    MySet<INF> new_v = f_st;
    new_v -= s_st;
    return new_v;
}

template<typename INF>
bool operator==(const MySet<INF>& f_st, const MySet<INF>& s_st) {
    if (f_st.len() != s_st.len()) return false;
    for (size_t i = 0; i < f_st.len(); ++i) {
        if (f_st[i] != s_st[i]) return false;
    }
    return true;
}

template<>
bool operator==(const MySet<char *>& f_st, const MySet<char *>& s_st) {
    if (f_st.len() != s_st.len()) return false;
    for (size_t i = 0; i < f_st.len(); ++i) {
        if (std::strcmp(f_st[i], s_st[i]) != 0) return false;
    }
    return true;
}

template<typename INF>
std::ostream& operator<<(std::ostream& os, const MySet<INF>& St) {
    for (size_t i = 0; i < St.len(); ++i) {
        std::cout << St[i] << ' ';
    }
    std::cout << std::endl;
    return os;
}

#endif // MYSET_H
