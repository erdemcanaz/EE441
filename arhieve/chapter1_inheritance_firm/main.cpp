#include "Firms.hpp"
#include <iostream>

int main(){
    Company company_1("Company1", 1000, 10);
    Test test_1("Test1", 520, 22, 123321);
    OwnerCompany owner_company_1("owner_company1", 2000, 20, 5);
    SubCompany sub_company("sub_company1", 3000, 30, 10);

    company_1.print_company();
    std::cout << std::endl;
    
    test_1.print_company();
    std::cout << std::endl;
    
    owner_company_1.print_company();
    std::cout << std::endl;

    sub_company.print_company();
    
    return 0;
}