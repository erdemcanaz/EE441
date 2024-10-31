#include "Date.hpp"


/* Class implementation */
// constructor */
Date::Date(int d, int m, int y )
{
	day = d;
	month = m;
	year = y;
}

int Date::JumpYear(int j) const
{
     return  year+j;
}

void Date::PrintDate() const
{
	std::cout << "Day: " << day  << " Month: " << month << " Year: " << year << std::endl;
}

void Date::SetDate(int d, int m, int y){
    day = d;
    month = m;
    year = y;
}
