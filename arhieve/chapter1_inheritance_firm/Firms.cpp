#include <iostream>
#include "Firms.hpp"

// Test::Test(std::string n, int m, int ne): Company(n,m,ne){    
//     std::cout << "Test constructor" << std::endl;
// }

Test::Test( std::string n, int m, int ne, int psw): Company(n,m,ne), password(psw){}

void Test::print_company(){
    std::cout << "Firm name: " << firm_name << std::endl;
    std::cout << "Password: " << password << std::endl;
    std::cout << "Money: " << money << std::endl;
    std::cout << "Number of employees: " << number_of_employee << std::endl;
}

void Company::print_company() const {
    std::cout << "Company name: " << firm_name << std::endl;
    std::cout << "Money: " << money << std::endl;
    std::cout << "Number of employees: " << number_of_employee << std::endl;
}

void OwnerCompany::print_company() const{
    std::cout << "Owner company name: " << firm_name << std::endl;
    std::cout << "Money: " << money << std::endl;
    std::cout << "Number of employees: " << number_of_employee << std::endl;
    std::cout << "Number of subcompanies: " << number_of_subcompanies << std::endl;
}

void SubCompany::print_company() const{
    std::cout << "Subcompany name: " << firm_name << std::endl;
    std::cout << "Money: " << money << std::endl;
    std::cout << "Number of employees: " << number_of_employee << std::endl;
    std::cout << "Number of projects: " << number_of_projects << std::endl;
}


