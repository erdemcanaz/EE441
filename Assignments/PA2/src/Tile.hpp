#pragma once
#include <iostream>
#include <stdexcept>

//------------------------------------------------------------
// suits   : Dots, Bamboos, Characters
// numbers : 1-9
// Example : Dots 1, Dots 2, ..., Dots 9
//           Bamboos 1, ..., Bamboos 9
//           Characters 1, ..., Characters 9
// Encoding: Dots-1 = D1, Bamboos-2 = B2, Characters-3 = C3
// Default encoding: suit = ' ', number = -1 (Not a valid tile)
//------------------------------------------------------------
// Bamboo (B) < Character (C) < Dot (D)
// ASCII values: B = 66, C = 67, D = 68

class Tile
{
public:
    char m_suit;
    int m_number;

    // Default constructor
    Tile() : m_suit(' '), m_number(-1) {
                 // Initialize m_suit with a default character (e.g., space)
                 // and m_number with a default value (e.g., -1)
             };

    // Parameterized constructor
    Tile(char s, int n) : m_suit(s), m_number(n) {
                              // Assign values to the member variables
                          };

    // Comparison operator for equality
    bool operator==(const Tile &other) const
    {
        // Check if the suit and number of the tiles are initialized
        if (m_suit == ' ' || other.m_suit == ' ' || m_number == -1 || other.m_number == -1)
        {
            throw std::domain_error("Invalid suit: One or both tiles have an uninitialized suit.");
        }

        // Check if the suit and number of the tiles are equal
        if (m_suit == other.m_suit && m_number == other.m_number)
        {
            return true;
        }
        // The tiles are not equal
        return false;
    };
    // Overload less-than operator
    bool operator<(const Tile &other) const
    {
        // Check if the suit and number of the tiles are initialized
        if (m_suit == ' ' || other.m_suit == ' ' || m_number == -1 || other.m_number == -1)
        {
            throw std::domain_error("Invalid suit: One or both tiles have an uninitialized suit.");
        }

        // If suit of current tile is less than the suit of other tile, return true
        if (m_suit < other.m_suit)
        {
            return true;
        }
        // If the suits are equal, check if the number of the current tile is less than the number of the other tile
        else if (m_suit == other.m_suit)
        {
            if (m_number < other.m_number)
            {
                return true;
            }
        }
        // Neither of the conditions are met, this tile is not less than the other tile
        return false;
    };

    // Overload greater-than operator
    bool operator>(const Tile &other) const
    {
        // Check if the suit and number of the tiles are initialized
        if (m_suit == ' ' || other.m_suit == ' ' || m_number == -1 || other.m_number == -1)
        {
            throw std::domain_error("Invalid suit: One or both tiles have an uninitialized suit.");
        }

        // If suit of current tile is greater than the suit of other tile, return true
        if (m_suit > other.m_suit)
        {
            return true;
        }
        // If the suits are equal, check if the number of the current tile is greater than the number of the other tile
        else if (m_suit == other.m_suit)
        {
            if (m_number > other.m_number)
            {
                return true;
            }
        }
        // Neither of the conditions are met, this tile is not greater than the other tile
        return false;
    };

    bool operator<=(const Tile &other) const
    {
        // Check if the suit and number of the tiles are initialized
        if (m_suit == ' ' || other.m_suit == ' ' || m_number == -1 || other.m_number == -1)
        {
            throw std::domain_error("Invalid suit: One or both tiles have an uninitialized suit.");
        }

        // If suit of current tile is less than or equal to the suit of other tile, return true
        if (m_suit < other.m_suit)
        {
            return true;
        }
        // If the suits are equal, check if the number of the current tile is less than or equal to the number of the other tile
        else if (m_suit == other.m_suit)
        {
            if (m_number <= other.m_number)
            {
                return true;
            }
        }
        // Neither of the conditions are met, this tile is not less than or equal to the other tile
        return false;
    };

    bool operator>=(const Tile &other) const
    {
        // Check if the suit and number of the tiles are initialized
        if (m_suit == ' ' || other.m_suit == ' ' || m_number == -1 || other.m_number == -1)
        {
            throw std::domain_error("Invalid suit: One or both tiles have an uninitialized suit.");
        }

        // If suit of current tile is greater than or equal to the suit of other tile, return true
        if (m_suit > other.m_suit)
        {
            return true;
        }
        // If the suits are equal, check if the number of the current tile is greater than or equal to the number of the other tile
        else if (m_suit == other.m_suit)
        {
            if (m_number >= other.m_number)
            {
                return true;
            }
        }
        // Neither of the conditions are met, this tile is not greater than or equal to the other tile
        return false;
    };

    bool operator!=(const Tile &other) const
    {
        // Check if the suit and number of the tiles are initialized
        if (m_suit == ' ' || other.m_suit == ' ' || m_number == -1 || other.m_number == -1)
        {
            throw std::domain_error("Invalid suit: One or both tiles have an uninitialized suit.");
        }

        // If the suit or number of the tiles are not equal, return true
        if (m_suit != other.m_suit || m_number != other.m_number)
        {
            return true;
        }
        return false;
    };

    // Friend function to overload << operator for output
    friend std::ostream &operator<<(std::ostream &os, const Tile &tile)
    {
        os << tile.m_suit << tile.m_number;
        return os;
    };
};

void __test_tile_class()
{
    std::cout << "\n\n--- Tile Class Tests ---" << std::endl;
    // Create tiles using parameterized constructor
    Tile tile_1('D', 1);
    Tile tile_2('D', 2);
    Tile tile_3('B', 3);
    Tile tile_4('C', 4); // Character tile
    Tile tile_5('C', 5); // Another Character tile

    // Create a tile using default constructor
    Tile default_tile;

    // Display tiles
    std::cout << "Tile 1: " << tile_1 << std::endl;
    std::cout << "Tile 2: " << tile_2 << std::endl;
    std::cout << "Tile 3: " << tile_3 << std::endl;
    std::cout << "Tile 4: " << tile_4 << std::endl;
    std::cout << "Tile 5: " << tile_5 << std::endl;
    std::cout << "Default Tile: " << default_tile.m_suit << default_tile.m_number << std::endl;

    // Test equality operator
    std::cout << "\n--- Equality Operator Tests ---" << std::endl;
    std::cout << "Tile 4 == Tile 5: " << (tile_4 == tile_5) << std::endl;
    std::cout << "Tile 4 == Tile 4: " << (tile_4 == tile_4) << std::endl;

    // Test inequality operator
    std::cout << "\n--- Inequality Operator Tests ---" << std::endl;
    std::cout << "Tile 1 != Tile 2: " << (tile_1 != tile_2) << std::endl;
    std::cout << "Tile 4 != Tile 5: " << (tile_4 != tile_5) << std::endl;

    // Test less-than operator
    std::cout << "\n--- Less-Than Operator Tests ---" << std::endl;
    std::cout << "Tile 3 < Tile 4: " << (tile_3 < tile_4) << std::endl; // B vs C
    std::cout << "Tile 4 < Tile 1: " << (tile_4 < tile_1) << std::endl; // C vs D

    // Test greater-than operator
    std::cout << "\n--- Greater-Than Operator Tests ---" << std::endl;
    std::cout << "Tile 4 > Tile 3: " << (tile_4 > tile_3) << std::endl;
    std::cout << "Tile 1 > Tile 4: " << (tile_1 > tile_4) << std::endl;

    // Test less-than-or-equal-to operator
    std::cout << "\n--- Less-Than-Or-Equal-To Operator Tests ---" << std::endl;
    std::cout << "Tile 4 <= Tile 5: " << (tile_4 <= tile_5) << std::endl;
    std::cout << "Tile 4 <= Tile 4: " << (tile_4 <= tile_4) << std::endl;

    // Test greater-than-or-equal-to operator
    std::cout << "\n--- Greater-Than-Or-Equal-To Operator Tests ---" << std::endl;
    std::cout << "Tile 5 >= Tile 4: " << (tile_5 >= tile_4) << std::endl;
    std::cout << "Tile 4 >= Tile 4: " << (tile_4 >= tile_4) << std::endl;

    // Test behavior with default-constructed tile
    std::cout << "\n--- Tests Involving Default-Constructed Tile ---" << std::endl;
    try
    {
        std::cout << "Default Tile == Tile 1: " << (default_tile == tile_1) << std::endl;
    }
    catch (const std::domain_error &e)
    {
        std::cout << "Error comparing Default Tile and Tile 1: " << e.what() << std::endl;
    }

    try
    {
        std::cout << "Default Tile < Tile 1: " << (default_tile < tile_1) << std::endl;
    }
    catch (const std::domain_error &e)
    {
        std::cout << "Error comparing Default Tile and Tile 1: " << e.what() << std::endl;
    }

    // Additional test: comparing default tile with itself
    try
    {
        std::cout << "Default Tile == Default Tile: " << (default_tile == default_tile) << std::endl;
    }
    catch (const std::domain_error &e)
    {
        std::cout << "Error comparing Default Tile with itself: " << e.what() << std::endl;
    }
};