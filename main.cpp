#include "engine.h"


int main() {
    Vector<Engine*> container;

    container.push_back(new InternalCombustionEngine(2.5, 180));
    container.push_back(new DieselEngine(3.0, 220, 17.5));
    container.push_back(new TurbojetEngine(150.0));

    std::cout << "\n--- print() ---" << std::endl;
    container.print();

    std::cout << "\n--- removeAt index 1 ---" << std::endl;
    container.remove(1);
    container.print();

    std::cout << "\n--- clearAll() ---" << std::endl;
    container.clear();
    std::cout << "Container size after clear: " << container.size() << std::endl;

    return 0;
}
