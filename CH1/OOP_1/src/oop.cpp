#include <iostream>
#include <string>

class Person{
    //private by default
    private:
        std::string first;
        std::string last;

    public:
        void setFirstName(std::string first_name){
           first = first_name;
        }
        void setLastName(std::string last){
            this->last = last;
        }
        std::string getName(){
            return first+ " " + last;
        }
        void printFullName(){
            std::cout << first << " " << last << std::endl;
        }

};

int main(){
    Person p;
    p.setFirstName("Stephen");
    p.setLastName("Curry");   
    p.printFullName();

    Person p2;
    p2.setFirstName("John");
    p2.setLastName("Doe");
    p2.printFullName();

    std::cout << p2.getName() << std::endl;

    
    return 0;
}