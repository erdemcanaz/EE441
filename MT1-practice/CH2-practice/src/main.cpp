#include <iostream>
#include <string>

void swap_integers_pass_by_address(int *p1, int *p2)
{
    int dummy = *p1;
    *p1 = *p2;
    *p2 = dummy;
}

void swap_integers_by_reference(int &v1, int &v2)
{
    int dummy = v1;
    v1 = v2;
    v2 = dummy;
}

int main()
{
    // Array examples
    char C[5];
    double grades[3] = {2.31, 35.2, 52.42};
    char letters[] = {'M', 'E', 'T', 'U'};

    double table[2][3] = {{0, 0, 0},
                          {0, 0, 0}};

    // Pointer examples
    char *p_char = &letters[0];
    for (uint8_t i = 0; i < 4; i++)
    {
        std::cout << *(p_char + i) << std::endl;
    }

    char *p_char_allias = &letters[0];
    std::cout << "&p_char: " << &p_char << " &p_char_allias: " << &p_char_allias << std::endl;
    std::cout << "*p_char: " << *p_char << " *p_char_allias: " << *p_char_allias << std::endl;

    char *p_char_allias_2 = p_char_allias;
    std::cout << "\n&p_char_allias: " << &p_char_allias << " &p_char_allias_2: " << &p_char_allias_2 << std::endl;
    std::cout << "*p_char_allias: " << *p_char_allias << " *p_char_allias_2: " << *p_char_allias_2 << std::endl;

    // Function value passing
    int integer_1 = 10;
    int integer_2 = 20;

    std::cout << "\nInteger 1: " << integer_1 << " Integer 2: " << integer_2 << std::endl;
    swap_integers_pass_by_address(&integer_1, &integer_2);
    std::cout << "Integer 1: " << integer_1 << " Integer 2: " << integer_2 << std::endl;
    swap_integers_pass_by_address(&integer_1, &integer_2);

    std::cout << "\nInteger 1: " << integer_1 << " Integer 2: " << integer_2 << std::endl;
    swap_integers_by_reference(integer_1, integer_2);
    std::cout << "Integer 1: " << integer_1 << " Integer 2: " << integer_2 << std::endl;
    swap_integers_by_reference(integer_1, integer_2);

    return 0;
}