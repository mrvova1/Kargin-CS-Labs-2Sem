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
    InternalCombustionEngine(double d=0, double p=0)
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
    DieselEngine(double d=0, double p=0, double cr=0)
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
    TurbojetEngine(double t=0)
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


template<class INF, class FRIEND>
class ListNode {
private:
    INF d;
    ListNode *next;

    ListNode() : next(nullptr) {}

    ListNode(const ListNode &other) : d(other.d), next(nullptr) {
        if(other.next)
            next = new ListNode(*other.next);
    }

    ListNode& operator=(const ListNode &other) {
        if(this != &other) {
            d = other.d;
            if(next) {
                delete next;
                next = nullptr;
            }
            if(other.next)
                next = new ListNode(*other.next);
        }
        return *this;
    }

    ~ListNode() {
        delete d;
        delete next;
     }

    friend FRIEND;
};

template<class INF>
class MyStack {
    typedef ListNode<INF, MyStack<INF>> Node;
    Node *top;
public:
    MyStack() : top(nullptr) {}

    MyStack(const MyStack &other) : top(nullptr) {
        for (size_t i=0; i < other.len(); i++){
            push(other[i]);
        }
    }

    MyStack& operator=(MyStack &other) {
        if(this != &other) {
            // this->empty();
            // other.empty();

            while(!empty()) {
                pop();
            }
            // for (size_t i=0; i < other.len(); i++){
            //     push(other[i]);
            // }
            while (!other.empty())
            {
               push(other.top());
               other.pop();
            //    std::cout << this;
            }
            inverted();
            // Node copy_node = other;
            // if (!copy_node){
            //     top = nullptr;
            // } else {
            // while (copy_node) {
            //     push(copy_node);
            //     top = copy_node;
            //     copy_node = copy_node->next;
                // top = new Node(*other.top);
            // }
        }
        return *this;
    // }
}

    ~MyStack() {
        while(top != nullptr) {
            Node *temp = top;
            top = top->next;
            temp->next = nullptr;
            delete temp;
        }
    }

    bool empty() const {
        return (top == nullptr);
    }

    bool push(INF n) {
        Node* newNode = new Node;
        newNode->d = n;
        newNode->next = top;
        top = newNode;
        return true;
    }

    bool pop() {
        // std::cout << "\\\\\\" << '\n';
        if(empty()){
            return false;
        }
        Node* temp = top;
        top = top->next;
        temp->next = nullptr;
        delete temp;
        // std::cout << n << '\n';
        return true;
    }

    INF top_inf() const {
        if(empty())
            throw "Stack is empty";
        return top->d;
    }

    size_t len() const {
        size_t len = 0;
        Node *temp = top;
        while(temp != nullptr) {
            temp = temp->next;
            len++;
        }
        return len;
    }

    void inverted() {
        Node *temp = top;
        Node *temp_now = top;
        Node *back = nullptr;
        while (temp != nullptr){
            temp_now = temp;
            temp = temp->next;
            temp_now->next = back;
            back = temp_now;
        }
        top = back;
    }

    INF operator [] (int num) const {
        Node *temp = top;
        for (int i=0; i<num; i++){
            temp = temp->next;
        }
        return temp->d;
    }

    void delete_el(size_t index){
        Node *temp = top;
        Node *now_temp = top;
        for (size_t i=0; i<index; i++){
            now_temp = temp;
            temp = temp->next;
        }
        now_temp->next = temp->next;
        temp->next = nullptr;
        delete temp;
    }

    template<class I>
    friend std::ostream& operator<<(std::ostream &os, const MyStack<I>& St);

};

template<class INF>
std::ostream& operator<<(std::ostream &os, const MyStack<INF>& St){
    for (size_t i = 0; i < St.len(); i++) {
        std::cout << St[i] << ' ';
    }
    std::cout << std::endl;
    return os;
}
#endif // engine
