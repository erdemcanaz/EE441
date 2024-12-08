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

void basic_examples()
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
}

void Fun(int *a, int *b)
{
    // a[3]=3, b[5] = 105
    a = a + 5;
    // a[8]=8, b[5] = 105
    b = a - 2;
    // a[8]=8, b[5] = 105
};

void Fun_by_address(int **a, int **b)
{
    *a = *a - 3;
    *b = *b - 5;
};

void Fun_by_reference(int *&a, int *&b)
{
    a = a - 3;
    b = b - 5;
};

int main()
{
    // basic_examples();

    //_______________________________________________
    int a[50], b[50];

    for (int i = 0; i < 50; i++)
    {
        a[i] = i;
        b[i] = 100 + i;
    }
    int *p, *q;
    p = a + 3; // a[3] = 3;
    q = b + 5; // b[5] = 105
    Fun(p, q); // Line (X)

    Fun_by_reference(p, q);
    std::cout << "\n*p: " << *p << " *q: " << *q << std::endl;
    p = a + 3;
    q = b + 5;
    std::cout << "\n*p: " << *p << " *q: " << *q << std::endl;

    Fun_by_address(&p, &q);
    std::cout << "\n*p: " << *p << " *q: " << *q << std::endl;

    //_______________________________________________
    // What will be the output of the following piece of code? When contents of a memory location are not known,  indicate this.
    int i, j, M[3][4];
    int temp;
    for (i = 2; i >= 0; i = i - 1)
    {
        for (j = 3; j >= 0; j = j - 1)
        {
            if (i == j)
                M[i][j] = 10;
            else
                M[i][j] = i * j;
            std::cout << i << "," << j << ":" << M[i][j] << ";";
        }
        std::cout << std::endl;
    }
    temp = *(*(M + 2) + 3); // i.e fourth element of the third row
    std::cout << M[0][0] << " and " << temp << std::endl;

    return 0;
}