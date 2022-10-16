#include <string>

class Company {
    //visible to the class and its derived classes
    protected:
    std::string firm_name;
    int money;
    int number_of_employee;

    public:
    Company();
    Company(std::string n, int m, int ne): firm_name(n), money(m), number_of_employee(ne) {};
    void print_company() const;
};

class Test: protected Company{
    private:
    int password;
    public: 
    Test(std::string n, int m, int ne, int psw);
    void print_company();
};

class OwnerCompany:protected Company{
    private:
        int number_of_subcompanies;
    public: 
    OwnerCompany(std::string n, int m, int ne,  int ns): Company(n,m,ne), number_of_subcompanies(ns) {};    
    void print_company() const;
};

class SubCompany: protected Company {
    private:
        int number_of_projects;
    public:
    SubCompany(std::string n, int m, int ne,  int np): Company(n,m,ne), number_of_projects(np) {};
    void print_company() const;
};

