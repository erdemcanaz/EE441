#include <iostream>

const char* recommendMeAFood(char first_letter);
 
int main()
{
    std::cout<< recommendMeAFood('b') << std::endl;
}


const char* recommendMeAFood(char first_letter)
{
    if(first_letter == 'a'){
        return "apple";
    }
    else if(first_letter == 'b'){
        return "banana";
    }
    else{
        return "candy";
    }
}