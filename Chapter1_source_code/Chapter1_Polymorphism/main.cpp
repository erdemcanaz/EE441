#include "Polygon.hpp"


int main(){
    Rectangle r(4,5);
    Triangle t(7,8);
    std::cout << "Rectangle Area: " << r.Area() << std::endl;
    std::cout << "Triangle Area: " << t.Area() << std::endl;
    // Make use of polymorphism
    Polygon *p_poly; // Pointer to object of Polygon class
    p_poly = &r; // Assign address of r to p_polygon
    std::cout << "Access member method Area from Base class" << std::endl;
    // Access member method Area from Base class
    std::cout << "Rectangle Area: " << p_poly->Area() << std::endl;
    p_poly = &t; // Assign address of t to p_polygon
    // Access member method Area from Base class
    std::cout << "Triangle Area: " << p_poly->Area() << std::endl;
    return 0;
}

