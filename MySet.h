#pragma once
#include <cstring>
#include <iostream>

template<class INF>
class MyVector {
 protected:
    int max_size_;
    int size_;
    INF* pdata_;
    void resize();

 public:
    MyVector(INF el = NULL, int max_size = 1);
    MyVector(const MyVector& other);
    ~MyVector();

    void add_element(INF el);
    bool delete_element(int index);
    void sort();
    int find(INF el);

    MyVector<INF>& operator=(const MyVector<INF>& other);
    const INF& operator[](int index) const;
    template <class I>
    friend std::ostream& operator<<(std::ostream& out, MyVector<I>& other);
};

template<class INF>
void MyVector<INF>::resize() {
    max_size_ *= 2;
    INF* newSize = new INF[max_size_];
    for (int i = 0; i < size_; ++i) {
        newSize[i] = pdata_[i];
    }
    delete[] pdata_;
    pdata_ = newSize;
}

template<class INF>
MyVector<INF>::MyVector(INF el , int max_size) {
    max_size_ = max_size;
    size_ = 0;
    pdata_ = new INF[max_size_];
    if (el) {
        add_element(el);
    }
}

template<class INF>
MyVector<INF>::MyVector(const MyVector& other) {
    max_size_ = other.max_size_;
    size_ = other.size_;
    pdata_ = new INF[max_size_];
    for (int i = 0; i < size_; ++i) {
        pdata_[i] = other.pdata_[i];
    }
}

template<>
MyVector<char*>::MyVector(const MyVector& other) {
    max_size_ = other.max_size_;
    size_ = other.size_;
    pdata_ = new char*[max_size_];
    for (int i = 0; i < size_; ++i) {
        pdata_[i]=new char[strlen(other[i])+1];
        strcpy(pdata_[i],other[i]);
    }
}

template<class INF>
MyVector<INF>::~MyVector() {
    delete[] pdata_;
}

template<>
MyVector<char*>::~MyVector() {
    for(int i =0;i<max_size_;++i){
        delete[] pdata_[i];
    }
    delete[] pdata_;
}

template<class INF>
void MyVector<INF>::add_element(INF el) {
    if (size_ >= max_size_) {
        resize();
    }
    pdata_[size_] = el;
    ++size_;
}

template<>
void MyVector<char*>::add_element(char* el) {
    if (size_ >= max_size_) {
        resize();
    }
    pdata_[size_]=new char[strlen(el)+1];
    strcpy(pdata_[size_],el);
    ++size_;
}

template<class INF>
bool MyVector<INF>::delete_element(int i) {
    if (size_ == 0 || i < 0 || i >= size_) {
        return false;
    }
    for (int j = 0; j < size_ - 1; ++j) {
        if(j>=i) {
            pdata_[j] = pdata_[j + 1];
        }
    }
    --size_;
    if (size_ < max_size_ / 4) {
        max_size_ = max_size_ / 2;
    }
    return true;
}

template<>
bool MyVector<char*>::delete_element(int i) {
    if (size_ == 0 or i < 0 or i >= size_) {
        return false;
    }
    for (int j = i; j < size_ - 1; ++j) {
        delete[] pdata_[j];
        pdata_[j] = pdata_[j+1];
    }
    --size_;
    if (size_ < max_size_ / 4) {
        max_size_ = max_size_ / 2;
    }
    return true;
}

template<class INF>
void MyVector<INF>::sort() {
    if (!pdata_) {
        return;
    }
    for (int i = 0; i < size_; ++i) {
        for (int j = 0; j < size_ - i - 1; ++j) {
            if (pdata_[j] > pdata_[j + 1]) {
                std::swap(pdata_[j], pdata_[j + 1]);
            }
        }
    }
}

template<>
void MyVector<char*>::sort() {
    if (!pdata_) {
        return;
    }
    for (int i = 0; i < size_; ++i) {
        for (int j = 0; j < size_ - i - 1; ++j) {
            if (strcmp(pdata_[j + 1], pdata_[j]) < 0) {
                std::swap(pdata_[j], pdata_[j + 1]);
            }
        }
    }
}

template<class INF>
int MyVector<INF>::find(INF el) {
    int index = -1;
    for (int i = 0; i < this->size_; ++i) {
        if (pdata_[i] == el) {
            index = i;
        }
    }
    return index;
}

template<>
int MyVector<char*>::find(char* el) {
    int index = -1;
    for (int i = 0; i < this->size_; ++i) {
        if (!strcmp(pdata_[i], el)) {
            index =  i;
        }
    }
    return index;
}

template<class INF>
MyVector<INF>& MyVector<INF>::operator=(const MyVector<INF>& other) {
    if(this==&other){
        return *this;
    }
    delete[] pdata_;
    this->max_size_ = other.max_size_;
    this->size_ = other.size_;
    this->pdata_ = new INF[max_size_];
    for (int i = 0; i < size_; ++i) {
        this->pdata_[i] = other[i];
    }
    return *this;
}

template<>
MyVector<char*>& MyVector<char*>::operator=(const MyVector<char*>& other) {
    if(this==&other){
        return *this;
    }
    delete[] pdata_;
    this->max_size_ = other.max_size_;
    this->size_ = other.size_;
    this->pdata_ = new char*[max_size_];
    for (int i = 0; i < size_; ++i) {
        delete[] this->pdata_[i];
        this->pdata_[i]=new char[strlen(other[i])+1];
        strcpy(this->pdata_[i],other[i]);
    }
    return *this;
}

template<class INF>
const INF& MyVector<INF>::operator[](int i) const {
    if (i < 0 || i >= size_) {
        std::cout<<"Введены некорректные данные";
        return pdata_[max_size_];
    }
    return pdata_[i];
}

template<class I>
std::ostream& operator<<(std::ostream& out, MyVector<I>& other) {
    for (int i = 0; i < other.size_; ++i) {
        out << other[i] << ' ';
    }
    return out;
}

template<class INF=const char*>
class MySet : public MyVector<INF> {
 public:
    MySet(INF el = NULL) : MyVector<INF>(el) {}

    void add_element(INF el);
    void delete_element(INF el);
    bool is_element(INF el) const;

    template <class I>
    friend std::ostream& operator<<(std::ostream& out, const MySet<I>& Set);
    template <class I>
    friend bool operator==(const MySet<I>& f_st,const MySet<I>& s_st);
    template <class I>
    friend MySet<I>& operator+=( MySet<I>& f_st,const MySet<I>& s_st);
    template <class I>
    friend MySet<I>& operator-=( MySet<I>& f_st,const MySet<I>& s_st);
    template <class I>
    friend MySet<I>& operator*=( MySet<I>& f_st,const MySet<I>& s_st);
    template <class I>
    friend MySet<I> operator+(const MySet<I>& f_st, const MySet<I>& s_st);
    template <class I>
    friend MySet<I> operator-(const MySet<I>& f_st, const MySet<I>& s_st);
    template <class I>
    friend MySet<I> operator*(const MySet<I>& f_st, const MySet<I>& s_st);
};

template<class INF>
void MySet<INF>::add_element(INF el) {
    if (!this->is_element(el)) {
        MyVector<INF>::add_element(el);
        this->sort();
    }
    return;
}

template<class INF>
void MySet<INF>::delete_element(INF el) {
    int index = this->find(el);
    if (index != -1) {
        MyVector<INF>::delete_element(index);
    }
    return;
}

template<class INF>
bool MySet<INF>::is_element(INF el)const  {
    for (int i = 0; i < this->size_; ++i) {
        if ((*this)[i] == el) {
            return true;
        }
    }
    return false;
}

template<>
bool MySet<char*>::is_element(char* el) const{
    for (int i = 0; i < this->size_; ++i) {
        if (!strcmp((*this)[i], el)) {
            return true;
        }
    }
    return false;
}

template<class I>
std::ostream& operator<<(std::ostream& out, const MySet<I>& Set) {
    std::cout << "{";
    for (int i = 0; i < Set.size_; ++i) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << Set[i];
    }
    std::cout << "}";
    return out;
}

template<class I>
bool operator==(const MySet<I>& f_st,const MySet<I>& s_st){
    if (f_st.size_ != s_st.size_) {
        return false;
    }
    for (int i = 0; i < f_st.size_; ++i) {
        if (!(s_st.is_element(f_st[i]))) {
            return false;
        }
    }
    return true;
}

template<class I>
MySet<I>& operator+=(MySet<I>& f_st,const MySet<I>& s_st) {
    for (int i = 0; i < s_st.size_; ++i) {
        f_st.add_element(s_st[i]);
    }
    return f_st;
}

template<class I>
MySet<I>& operator-=( MySet<I>& f_st,const MySet<I>& s_st) {
    for (int i = 0; i < f_st.size_; ++i) {
        if (s_st.is_element((f_st[i]))) {
            f_st.delete_element(f_st[i--]);
        }
    }
    return f_st;
}

template<class I>
MySet<I>& operator*=( MySet<I>& f_st,const MySet<I>& s_st) {
    for (int i = 0; i < f_st.size_; ++i) {
        if (!(s_st.is_element(f_st[i]))) {
            f_st.delete_element(f_st[i--]);
        }
    }
    return f_st;
}

template<class I>
MySet<I> operator+(const MySet<I>& f_st, const MySet<I>& s_st) {
    MySet<I> result = f_st;
    result += s_st;
    return result;
}

template<class I>
MySet<I> operator-(const MySet<I>& f_st, const MySet<I>& s_st) {
    MySet<I> result = f_st;
    result -= s_st;
    return result;
}

template<class I>
MySet<I> operator*(const MySet<I>& f_st, const MySet<I>& s_st) {
    MySet<I> result = f_st;
    result *= s_st;
    return result;
}
