#include "Person.hpp"

int main(){
    Parent p;
    Person q;
    std::cout << "parent info:" << std::endl;
    p.Info();
    std::cout << "person info:" << std::endl;
    q.Info();
    std::cout << "change:" << std::endl;
    p.update();
    p.Info();
    return 0;
}
