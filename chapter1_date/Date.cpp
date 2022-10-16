#include <iostream>
#include <stdexcept>
#include "Date.hpp"

Date::Date(int d, int m, int y){
    day = d;
    month = m;
    year = y;
}

void Date::printDate() const
{
    std::cout << day << "/" << month << "/" << year << std::endl;
}

int Date::jumpYear(int c)
{    
    if(year+c > 1900 and year+c < 2100)
        year += c;
    
    return year;
}


void Date::setDate(int d, int m, int y)
{
    if (d > 0 && d < 32)
        day = d;
    if (m > 0 && m < 13)
        month = m;
    if (y > 1900 && y < 2100)
        year = y;
}


