#include <iostream>
#include <string>

int main()
{
    enum visited
    {
        NOT_VISITED,
        VISITED
    };

    std::cout << NOT_VISITED << std::endl;
    std::cout << VISITED << std::endl;
    return 0;
}