#include <iostream>
#include "Date.hpp"

int main()
{
    std::cout << "Let's use the Date class" << std::endl;
    Date Today(3,10,2022); // Construct object initialized with today's date
    Today.PrintDate(); // Print today's date using member method
    Date Tomorrow; // Construct default object
    Tomorrow.SetDate(4,10,2022); // Set the date of Tomorrow
    Tomorrow.PrintDate(); // print tomorrow's date
    std::cout << "Graduation Year: " << Today.JumpYear(1) << std::endl;
    return 0;
}
