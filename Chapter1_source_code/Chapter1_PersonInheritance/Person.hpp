#include <iostream>

enum Gender{male, female};

class Person{
    protected: //new access control level used for inheritance
        Gender gender; // either male or female
        int age; // Age of the person
    public:
        Person (int a = 0, Gender g = male); // Constructor
        void Info() const; // Print info about person
};

class Parent:public Person{//Derived Class
    private:
        int children;
    public:
        Parent(int a = 20, Gender g = female, int c = 0);
        void Info() const;
        void update();
};
