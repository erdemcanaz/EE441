#include <iostream>
#include <string>

void simple_test_1()
{
    int *p_1, *p_2;

    p_1 = new int[5];
    p_2 = new int;

    *p_2 = 25;

    for (uint8_t i = 0; i < 5; i++)
    {
        *(p_1 + i) = i;
        std::cout << *(p_1 + i) << std::endl;
    }

    std::cout << *p_2 << std::endl;

    delete p_1;
    delete p_2;
}

void simple_test_2()
{
    class Person
    {
    private:
        int mId;

    public:
        Person() : mId(-1) {};
        Person(int id) : mId(id) {};
        ~Person()
        {
            std::cout << "Destructor is called: " << mId << std::endl;
        };
        Person(const Person &other_person)
        {
            // Copy constructor. Called when an object is initiliazed with other object -> Person A = B;
            std::cout << "Copy constructor is called" << std::endl;
            mId = other_person.mId;
        };
        Person &operator=(const Person &other_person)
        {
            // Overriding equality operator. Called when already initiliazed object is overwritten by other object
            std::cout << "Equality override is called" << std::endl;
            mId = other_person.mId;
        }
        void setId(int id)
        {
            mId = id;
            std::cout << "Id is set to: " << id << std::endl;
        };
        void printId() const
        {
            std::cout << mId << std::endl;
        }
    };

    double *p = new double(5.3);


    const int NUMBER_OF_PERSONS = 20;
    Person *persons = new Person[NUMBER_OF_PERSONS];
    for (uint8_t i = 0; i < NUMBER_OF_PERSONS; i++)
    {
        (persons + i)->setId(i);
    }

    persons[0] = persons[NUMBER_OF_PERSONS - 1];
    persons[0].printId();
    delete[] persons;
}


int main()
{
    return 0;
}