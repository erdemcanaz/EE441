#include <iostream>

class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date(int d = 1, int m = 1, int y = 1900);
    int JumpYear(int j) const;
    void PrintDate() const;
    void SetDate(int d, int m, int y);
};

Date::Date(int d, int m, int y)
{
    day = d;
    month = m;
    year = y;
}

void Date::PrintDate() const
{
    std::cout << "Day: " << day << " Month: " << month << " Year: " << year << std::endl;
}

int main(){
    Date Today(3,10,2022); // Construct object initialized with today's date
    Today.PrintDate(); // Print today's date using member method
}







