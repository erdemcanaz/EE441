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
            return *this;
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
    std::cout << *p << std::endl;

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

template <class T>
class DynamicClass
{
private:
    T m1;
    T *m2; // dangling

public:
    DynamicClass(const T &member_1, const T &member_2);           // Constructor       -> to initilize with parameters
    DynamicClass(const DynamicClass<T> &item);                    // Copy constructor  -> Initilize object with another object of the same class
    DynamicClass<T> &operator=(const DynamicClass<T> &other_item) // Operator override -> Both objects are already existing. Copy values of other class to this one.
    {
        std::cout << "Equality override " << m1 << "/" << *m2 << std::endl;

        m1 = other_item.m1;
        *m2 = *other_item.m2;
        return *this;
    };
    ~DynamicClass(); // Deconstructor     -> to deallocate memory
    DynamicClass<T> *getObjectPointer() const;
    void displayClass() const;
};

template <class T>
DynamicClass<T>::DynamicClass(const T &member_1, const T &member_2)
{
    // Constructor
    m1 = member_1;
    m2 = new T(member_2);

    std::cout << "Constructor " << m1 << "/" << *m2 << std::endl;
}

template <class T>
DynamicClass<T>::DynamicClass(const DynamicClass<T> &item)
{
    // Copy consturctor
    m1 = item.m1;
    m2 = new T;
    *m2 = *item.m2;
    std::cout << "Copy consturctor " << m1 << "/" << *m2 << std::endl;
}

template <class T>
DynamicClass<T>::~DynamicClass()
{
    // Deconstructor
    std::cout << "Deconstructor is called for " << m1 << "/" << *m2 << std::endl;
    delete m2;
}

template <class T>
DynamicClass<T> *DynamicClass<T>::getObjectPointer() const
{
    return this;
}

template <class T>
void DynamicClass<T>::displayClass() const
{
    std::cout << "Object info\n " << m1 << "/" << *m2 << "\n"
              << &m1 << "/" << m2 << std::endl;
}

template <class T>
void _print(T value)
{
    //  _print<std::string>("test print");
    std::cout << value << std::endl;
}

int main()
{
    DynamicClass<int> obj_1 = DynamicClass<int>(5, 500);
    DynamicClass<int> obj_2 = obj_1;
    DynamicClass<int> obj_3 = DynamicClass<int>(3, 300);
    obj_3 = obj_2;

    obj_1.displayClass();
    obj_2.displayClass();
    obj_3.displayClass();

    return 0;
}