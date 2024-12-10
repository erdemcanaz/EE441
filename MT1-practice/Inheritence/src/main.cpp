#include <iostream>
#include <string>

// Person class
class Person
{
protected:
    std::string m_name;
    int m_age;

public:
    Person();                          // default constructor
    Person(std::string name, int age); // Parametric consturctor
    Person(const Person &other);       // Copy Constructor
    ~Person();                         // Deconstructor
    void Info() const;
};

Person::Person() : m_name("NO-NAME"), m_age(-1) {};
Person::Person(std::string name, int age) : m_name(name), m_age(age) {};
Person::Person(const Person &other)
{
    m_name = other.m_name;
    m_age = other.m_age;
}
Person::~Person()
{
    std::cout << "Person deconstructor is called" << std::endl;
};
void Person::Info() const
{
    std::cout << "Person | " << m_name << " (" << m_age << ")" << std::endl;
}

// Parent class
class Parent : public Person
{
private:
    int m_number_of_kids;

public:
    Parent();
    Parent(std::string name, int age, int number_of_kids);
    ~Parent();
    void Info() const;
};

Parent::Parent() : Person(), m_number_of_kids(-1) {};
Parent::Parent(std::string name, int age, int number_of_kids) : Person(name, age), m_number_of_kids(number_of_kids) {};
Parent::~Parent()
{
    std::cout << "Parent deconstructor is called" << std::endl;
};
void Parent::Info() const
{
    std::cout << "Person | " << m_name << " (" << m_age << "), " << m_number_of_kids << " kids" << std::endl;
}

int main()
{
    Person *p_person;
    p_person = new Person("Erdem", 24);
    p_person->Info();

    Parent *p_parent;
    p_parent = new Parent("Neslihan", 50, 2);
    p_parent->Info();

    const int NUMBER_OF_PERSONS = 10;
    Person *p_persons;
    p_persons = new Person[NUMBER_OF_PERSONS];

    for (uint8_t i = 0; i < NUMBER_OF_PERSONS; i++)
    {
        (p_persons + i)->Info();
    }

    delete p_person;
    delete p_parent;
    delete[] p_persons;
    return 0;
}