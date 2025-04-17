#ifndef MYSET_H
#define MYSET_H

#include <iostream>

template<class INF, class FRIEND>
class MyVector {
private:
    size_t max_size_;
    size_t size_;
    INF* pdata_ = nullptr;
public:
    MyVector(size_t max_size=1) : max_size_(max_size), size_(0) {pdata_= new INF(max_size_);}

    MyVector(const MyVector &other) : max_size_(other.max_size_), size_(other.size_) {
        pdata_ = new INF(max_size_);
        for (size_t i = 0; i<max_size_; i++){
            pdata_[i] = other.pdata_[i];
        }
    }

    MyVector& operator=(const MyVector &other) {
        if(this != &other) {
            max_size_ = other.max_size_;
            size_ = other.size_;
            pdata_ = new INF(max_size_);
            for (size_t i = 0; i<max_size_; i++){
                pdata_[i] = other.pdata_[i];
            }
            }
        return *this;
    }

    ~MyVector() { delete[] pdata_; }

    void add_element(INF new_element){
        std::cout << max_size_ << '\n';
        if (size_+1 >= max_size_/2){
            resize();
        }
        std::cout << max_size_ << '\n';
        pdata_[size_] = new_element;
        size_+=1;
        std::cout << max_size_ << '\n';

    }

    int delete_element(size_t index){
        if (index >= size_-1){
            std::cout << "Индекс превосходит размер массива";
            return -1;
        }
        for (size_t i=index+1; i < max_size_; i++){
            pdata_[i-1] = pdata_[i];
        }
        pdata_[size_-1] = 0; //возможны будующие ошибки
        size_ -= 1;
        resize();
        return 0;
    }

    int find(INF el) {
        size_t find_e = size_/2;
        size_t find_zone = size_/4;
        bool end = false;
        std::cout << find_e << '\n';
        std::cout << pdata_[find_e] << '\n';
        std::cout << "el" << '\n';
        std::cout << el << '\n';
        while (pdata_[find_e] != el){
            std::cout << "pdata_[find_e]" << '\n';
            std::cout << pdata_[find_e] << '\n';
            if (find_zone == 1){
                end = true;
            }
            if (pdata_[find_e] < el){
                find_e += find_zone;
                find_zone /= 2;
            } else {
                find_e -= find_zone;
                find_zone /= 2;
            }
            if (end){
                return -1;
            }
        }
        std::cout << "]]]]]]]]]]]]]" << '\n';
        std::cout << find_e << '\n';


        return find_e;
    }

    void resize() {
        if (size_ > max_size_/2) {
            INF* new_pdata_ = new INF(max_size_*2);
            for (size_t i=0; i<max_size_; i++){
                new_pdata_[i] = pdata_[i];
            }
            delete[] pdata_;
            pdata_ = new_pdata_;
        } else if (size_ < max_size_/4) {
            INF* new_pdata_ = new INF(max_size_/2);
            for (size_t i=0; i<max_size_; i++){
                new_pdata_[i] = pdata_[i];
            }
            delete[] pdata_;
            pdata_ = new_pdata_;
        }
    }

    void sort(){
        for (size_t i = 0; i<max_size_-1; i++){
            for (size_t j = i+1; j<max_size_; j++){
                if (pdata_[j] < pdata_[i]){
                    INF move_el = pdata_[i];
                    pdata_[i] = pdata_[j];
                    pdata_[j] = move_el;
                }
            }
        }
    }


    INF operator [] (size_t num) const {
        return pdata_[num];
    }

    size_t len() const{
        return size_;
    }


    friend FRIEND;
};

template<class INF>
class MySet: public MyVector<INF, MySet<INF>> {
public:
    bool is_element(INF el){
        std::cout << this->find(el) << '\n';
        if (this->find(el) != -1) {
            return true;
        }
        return false;
    }

    void add_element(INF el){
        if (not is_element(el)){
            this->MyVector<INF, MySet<INF>>::add_element(el);
            this->sort();
        }
    }

    void delete_element(INF el){
        if (is_element(el)){
            this->MyVector<INF, MySet<INF>>::delete_element(this->find(el));
        }
    }

    void operator+=(const MySet& St){
        for (size_t i = 0; i < St.len(); i++){
            if (not is_element(St[i])) {
                add_element(St[i]);
            }
        }
    }
    void operator-=(const MySet& St){
        for (size_t i = 0; i < St.len(); i++){
            if (is_element(St[i])) {
                delete_element(St[i]);
            }
        }
    }
    void operator*=(const MySet& St){
        for (size_t i = 0; i < this->len(); i++){
            if (not St.is_element(this[i])) {
                delete_element(this[i]);
            }
        }
    }

    friend MySet operator*(const MySet& f_st, const MySet& s_st){
        MySet new_v = f_st;
        new_v *= s_st;
        return new_v;
    }
    friend MySet operator+(const MySet& f_st, const MySet& s_st){
        MySet new_v = f_st;
        new_v += s_st;
        return new_v;
    }
    friend MySet operator-(const MySet& f_st, const MySet& s_st){
        MySet new_v = f_st;
        new_v -= s_st;
        return new_v;
    }
    friend MySet operator==(const MySet& f_st, const MySet& s_st){
        if (f_st.len() != s_st.len()){
            return false;
        }
        for (size_t i = 0; i < f_st.len(); i++){
            if (f_st[i] != s_st[i]){
                return false;
            }
        }
        return true;
    }

    template<class I>
    friend std::ostream& operator<<(std::ostream &os, const MySet<I>& St);

};

template<class INF>
std::ostream& operator<<(std::ostream &os, const MySet<INF>& St){
    for (size_t i = 0; i < St.len(); i++) {
        std::cout << St[i] << ' ';
    }
    std::cout << std::endl;
    return os;
}

#endif // MYSET_H
