#include "Food.hpp"

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