#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>


class Engine {
protected:
    Engine() { std::cout << "Engine()" << std::endl; }
public:
    virtual ~Engine() { std::cout << "~Engine()" << std::endl; }
    virtual void show() const = 0;
};


class InternalCombustionEngine : public Engine {
protected:
    double displacement;
    double power;
public:
    InternalCombustionEngine(double d, double p)
        : displacement(d), power(p) {
        std::cout << "InternalCombustionEngine()" << std::endl;
    }
    ~InternalCombustionEngine() override {
        std::cout << "~InternalCombustionEngine()" << std::endl;
    }
    void show() const override {
        std::cout << "ICE: " << displacement << "L, " << power << "hp" << std::endl;
    }
};

class DieselEngine : public InternalCombustionEngine {
protected:
    double compressionRatio;
public:
    DieselEngine(double d, double p, double cr)
        : InternalCombustionEngine(d, p), compressionRatio(cr) {
        std::cout << "DieselEngine()" << std::endl;
    }
    ~DieselEngine() override {
        std::cout << "~DieselEngine()" << std::endl;
    }
    void show() const override {
        std::cout << "Diesel: "
                  << displacement << "L, " << power << "hp, CR="
                  << compressionRatio << std::endl;
    }
};

class TurbojetEngine : public Engine {
protected:
    double thrust;
public:
    TurbojetEngine(double t)
        : thrust(t) {
        std::cout << "TurbojetEngine()" << std::endl;
    }
    ~TurbojetEngine() override {
        std::cout << "~TurbojetEngine()" << std::endl;
    }
    void show() const override {
        std::cout << "Turbojet: " << thrust << " kN thrust" << std::endl;
    }
};

template<typename T>
class Vector {
private:
    T* data;
    size_t sz;
    size_t cap;
    void resize(size_t newCap) {
        T* newData = new T[newCap];
        for (size_t i = 0; i < sz; ++i) newData[i] = data[i];
        delete[] data;
        data = newData;
        cap = newCap;
    }
public:
    Vector() : data(nullptr), sz(0), cap(0) {}
    ~Vector() {
        clear();
        delete[] data;
    }
    void print() {
        for (size_t i = 0; i < size(); ++i) {
            std::cout << "[" << i << "] ";
            data[i]->show();
        }
    }
    void push_back(const T& v) {
        if (sz == cap)
            resize(cap == 0 ? 1 : cap * 2);
        data[sz++] = v;
    }
    void remove(size_t index) {
        if (index >= sz) return;
        delete data[index];
        for (size_t i = index; i + 1 < sz; ++i)
            data[i] = data[i + 1];
        --sz;
    }
    void clear() {
        for (size_t i = 0; i < sz; ++i)
            delete data[i];
        sz = 0;
    }
    size_t size() const { return sz; }
    T& operator[](size_t i) { return data[i]; }
};

#endif // ENGINE_H
