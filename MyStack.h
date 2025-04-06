#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>

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

    ~ListNode() { delete next; }

    friend FRIEND;
};

template<class INF>
class MyStack {
    typedef ListNode<INF, MyStack<INF>> Node;
    Node *top;
public:
    MyStack() : top(nullptr) {}

    MyStack(const MyStack &other) : top(nullptr) {
        if(other.top)
            top = new Node(*other.top);
    }

    MyStack& operator=(const MyStack &other) {
        if(this != &other) {
            // this->empty();
            // other.empty();
            while(!empty()) {
                pop();
            }
            for (size_t i=0; i < other.len(); i++){
                push(other[i]);
            }
            // while (!other.empty())
            // {
            //    push(other.pop());
            // }

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
        if(empty())
            return false;
        Node* temp = top;
        top = top->next;
        temp->next = nullptr;
        delete temp;
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

    int operator [] (int num) const {
        Node *temp = top;
        for (int i=0; i<num; i++){
            temp = temp->next;
        }
        return temp->d;
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
#endif // MYSTACK_H
