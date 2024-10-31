#include <iostream>
#include <string>

class Person{
    //private by default
    protected:
        std::string first;
        std::string last;

    public:
        Person(std::string first, std::string last):first(first), last(last){
            //Constructor should have the same name as the class
        }
        Person() = default;

        void setFirstName(std::string first_name){
           first = first_name;
        }
        void setLastName(std::string last){
            this->last = last;
        }
        std::string getName() const{
            return first+ " " + last;
        }
        void printFullName(){
            std::cout << first << " " << last << std::endl;
        }
        virtual void printInfo() const {
            std::cout << "name: " + getName() << std::endl;
        }

};


class Employee : public Person{
    private:
        std::string department;
    public:
        Employee(std::string first_name, std::string last_name, std::string department): Person(first_name, last_name), department(department){
            //Constructor should have the same name as the class
        }
        std::string getDepartment() const{
            return department;
        }
        void setDepartment(std::string department){
            this->department = department;
        }
        void printInfo() const override{
            std::cout << "name: "  + getName() << std::endl;
            std::cout << "department: "+ getDepartment() << std::endl;            
        }
        void printInfoProtected() const{
            std::cout << first << " " << last << " " << department << std::endl;
        }
};


int main(){
    Employee e("Stephen", "Curry", "Basketball");
    std::cout << e.getDepartment() << std::endl;

    std::cout << "----" << std::endl;

    e.printInfo();

    std::cout << "----" << std::endl;

    e.printInfoProtected();


    return 0;
}