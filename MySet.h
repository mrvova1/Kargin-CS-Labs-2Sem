#ifndef MYSET_H
#define MYSET_H

#include <iostream>
#include <cstring>

template<typename INF>
class MyVector {
private:
    size_t max_size_;
    size_t size_;
    INF* pdata_ = nullptr;
public:
    MyVector(size_t max_size=1) : max_size_(max_size), size_(0) {pdata_= new INF[max_size_];}

    MyVector(const MyVector &other) : max_size_(other.max_size_), size_(other.size_) {
        pdata_ = new INF[max_size_];
        for (size_t i = 0; i<max_size_; i++){
            pdata_[i] = other.pdata_[i];
        }
    }

    MyVector& operator=(const MyVector &other) {
        if(this != &other) {
            max_size_ = other.max_size_;
            size_ = other.size_;
            pdata_ = new INF[max_size_];
            for (size_t i = 0; i<max_size_; i++){
                pdata_[i] = other.pdata_[i];
            }
            }
        return *this;
    }

    ~MyVector() { delete[] pdata_; }

    void add_element(INF new_element){
        size_+=1;
        if (size_ >= max_size_/2){
            resize();
        }
        pdata_[size_-1] = new_element;
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
        if (size_ == 0){
            return -1;
        }
        int left_b = 0;
        int right_b = size_-1;
        int mid = (right_b-left_b)/2+left_b;
        while (pdata_[mid] != el){
            if (pdata_[mid] > el){
                right_b = mid-1;
            } else {
                left_b = mid+1;
            }
            mid = (right_b-left_b)/2+left_b;
            if (right_b == left_b){
                if (pdata_[mid] == el){
                    break;
                }
                return -1;
            }
            if (right_b < 0 or left_b > static_cast<int>(size_)-1){
                return -1;
            }
        }
        return mid;
    }

    // int find(INF el) {
    //     if (size_ == 0){
    //         return -1;
    //     }
    //     size_t find_e = size_/2;
    //     const size_t min_find_zone = 1;
    //     size_t find_zone = std::max(size_/4, min_find_zone);
    //     bool end = false;
    //     // std::cout << find_e << '\n';
    //     // std::cout << find_zone << '\n';

    //     // // std::cout << find_e << '\n';
    //     // std::cout << pdata_[find_e] << '\n';
    //     // std::cout << el << '\n';
    //     // // std::cout << "el" << '\n';
    //     // // std::cout << el << '\n';
    //     // // std::cout << pdata_[find_e] != el << '\n';
    //     // std::cout << "/////////////////////////" << '\n';

    //     while (pdata_[find_e] != el){
    //         // std::cout << "pdata_[find_e]" << '\n';
    //         // std::cout << pdata_[find_e] << '\n';
    //         // std::cout << find_zone << '\n';
    //         if (find_zone <= 1){
    //             end = true;
    //         }
    //         if (pdata_[find_e] < el){
    //             find_e += find_zone;
    //             find_zone /= 2;
    //         } else {
    //             find_e -= find_zone;
    //             find_zone /= 2;
    //         }
    //         if (end){
    //             if (pdata_[find_e] == el){
    //                 return find_e;
    //             }
    //             if (pdata_[find_e-1] == el){
    //                 return find_e-1;
    //             }
    //             if (pdata_[find_e+1] == el) {
    //                 return find_e+1;
    //             }
    //             return -1;
    //         }
    //     }
    //     // std::cout << "]]]]]]]]]]]]]" << '\n';
    //     // std::cout << find_e << '\n';


    //     return find_e;
    // }

    void resize() {
        while (size_ > max_size_/2) {
            INF* new_pdata_ = new INF[max_size_*2];
            for (size_t i=0; i<max_size_; i++){
                new_pdata_[i] = pdata_[i];
            }
            delete[] pdata_;
            pdata_ = new_pdata_;
            max_size_*=2;
        }
        while (size_ < max_size_/4) {
            INF* new_pdata_ = new INF[max_size_/2];
            for (size_t i=0; i<max_size_; i++){
                new_pdata_[i] = pdata_[i];
            }
            delete[] pdata_;
            pdata_ = new_pdata_;
            max_size_/=2;
        }
    }

    void sort(){
        for (size_t i = 0; i<size_-1; i++){
            for (size_t j = i+1; j<size_; j++){
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
};

template<>
int MyVector<char*>::find(char* el) {
    for (size_t i=0; i<size_; i++){
        if (std::strcmp(pdata_[i], el) == 0){
            return i;
        }
    }
    return -1;
}

template<>
MyVector<char*>::~MyVector() {
    for (size_t i=0; i<size_; i++){
        delete[] pdata_[i];
    }
    delete[] pdata_;
}

template<>
void MyVector<char*>::add_element(char* new_element){
    size_+=1;
    if (size_ >= max_size_/2){
        resize();
    }
    delete[] pdata_[size_-1];
    pdata_[size_-1] = new char[std::strlen(new_element)+1];
    std::strcpy(pdata_[size_-1], new_element);
}

template<>
int MyVector<char*>::delete_element(size_t index){
    if (index >= size_-1){
        std::cout << "Индекс превосходит размер массива";
        return -1;
    }
    for (size_t i=index+1; i < max_size_; i++){
        pdata_[i-1] = pdata_[i];
    }
    delete[] pdata_[size_-1]; //возможны будующие ошибки
    size_ -= 1;
    resize();
    return 0;
}
// };
//     private:
//         size_t max_size_;
//         size_t size_;
//         INF* pdata_ = nullptr;
//     public:
//     MyVector(size_t max_size=1) : max_size_(max_size), size_(0) {pdata_= new INF[max_size_];}

//     MyVector(const MyVector &other) : max_size_(other.max_size_), size_(other.size_) {
//         pdata_ = new INF[max_size_];
//         for (size_t i = 0; i<max_size_; i++){
//             pdata_[i] = other.pdata_[i];
//         }
//     }

//     MyVector& operator=(const MyVector &other) {
//         if(this != &other) {
//             max_size_ = other.max_size_;
//             size_ = other.size_;
//             pdata_ = new INF[max_size_];
//             for (size_t i = 0; i<max_size_; i++){
//                 pdata_[i] = other.pdata_[i];
//             }
//             }
//         return *this;
//     }

//     ~MyVector() { delete[] pdata_; }
// };

template<typename INF>
class MySet: public MyVector<INF> {
public:
    bool is_element(INF el){
        if (this->len() == 0){
            return false;
        }
        // std::cout << this->find(el) << '\n';
        if (this->find(el) != -1) {
            return true;
        }
        return false;
    }

    bool add_element(INF el){
        // std::cout << el << '\n';
        // std::cout << is_element(el) << '\n';
        // std::cout << "||||||||||||||" << '\n';
        if (not is_element(el)){
            this->MyVector<INF>::add_element(el);
            this->sort();
            return true;
        }
        return false;
    }

    bool delete_element(INF el){
        if (is_element(el)){
            this->MyVector<INF>::delete_element(this->find(el));
            return true;
        }
        return false;
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

template<typename INF>
std::ostream& operator<<(std::ostream &os, const MySet<INF>& St){
    for (size_t i = 0; i < St.len(); i++) {
        std::cout << St[i] << ' ';
    }
    std::cout << std::endl;
    return os;
}

#endif // MYSET_H
