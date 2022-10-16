#include "Person.hpp"

Person::Person (int a, Gender g): age(a), gender(g){
}

//same as:
//Person::Person(int a, Gender g){
//  age=a;
//  gender= g;
//}

void Person::Info() const{
    std::cout << "Age: " << age;
	std::cout << ", Gender: ";
	if(gender == male)
        std::cout << "male";
    else
        std::cout << "female";
    std::cout << std::endl;
}

Parent::Parent (int a, Gender g, int c):Person(a,g),children(c){//ADD-ON
}


void Parent::Info() const{//OVERWRITE
    Person::Info();
    std::cout << "Number of Children: " << children << std::endl;
}

void Parent::update( ){//BRAND NEW
	std::cout << "Age: ";
	std::cin >> age;
	int gender_input;
	std::cout << "Gender (male=0, female=1): ";
	std::cin >> gender_input;
	if(gender_input == 0)
        gender = male;
    else
        gender = female;
	std::cout << "Number of Children: ";
	std::cin >> children;
}
