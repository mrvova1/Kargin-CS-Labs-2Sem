#include <iostream>
#include "MyStack.h"

using namespace std;

void Multipliers(int n, MyStack<int> &stack) {
    if(n <= 1)
        return;
    int divisor = 2;
    while(n > 1) {
        while(n % divisor == 0) {
            stack.push(divisor);
            n /= divisor;
        }
        divisor++;
        if(divisor * divisor > n && n > 1) {
            stack.push(n);
            break;
        }
    }
}

int main() {
    int n = 3960;
    std::cin >> n;
    MyStack<int> stack;

    char abs[100];
    std::cin >> abs;
    MyStack<char> absSt;
    for (char i: abs){
        absSt.push(i);
    }
    std::cout << absSt;


    Multipliers(n, stack);

    MyStack<int> copyStack = stack;
    MyStack<int> factors;
    factors = copyStack;
    // while(!copyStack.empty()) {
    //     factors.push(copyStack.top_inf());
    //     copyStack.pop();
    // }

    cout << n << "=";
    for (size_t i = 0; i < factors.len(); i++) {
        cout << factors[i];
        if(i < factors.len() - 1)
            cout << " * ";
    }
    cout << endl;

    // cout << n << "=";
    // for (int i = factors.len() - 1; i >= 0; i--) {
    //     cout << factors[i];
    //     if(i > 0)
    //         cout << " * ";
    // }
    // cout << endl;

    // factors.inverted();
    cout << n << "=";
    cout << copyStack;


    return 0;
}
