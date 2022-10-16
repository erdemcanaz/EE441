#include <iostream>
#include "Date.hpp"


int main(){
    std::cout << "date 1 is created" << std::endl;
    Date date_1 = Date(1, 1, 1900);
    date_1.printDate();

    std::cout << "date 2 is created" << std::endl;
    Date date_2(27,3,2000);
    date_2.printDate();
    
    std::cout << "date 2 is jumped 20 years" << std::endl;
    date_2.jumpYear(20);
    date_2.printDate();
    
    std::cout <<"date 1 is set to 1/1/2000" << std::endl;
    date_1.setDate(1,1,2000);
    date_1.printDate();

    return 0;
}