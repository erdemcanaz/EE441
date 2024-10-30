#include <iostream>
#include <string>

class Person{
    public:
        std::string first;
        std::string last;

        void printFullName(){
            std::cout << first << " " << last << std::endl;
        }
};

int main(){
    Person p;
    p.first = "Caleb";
    p.last = "Curry";
   
    p.printFullName();
    return 0;
}