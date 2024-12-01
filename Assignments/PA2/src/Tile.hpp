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

class Tile {
public:
    char m_suit;
    int m_number;

    // Default constructor
    Tile() : m_suit(' '), m_number(-1) {
        // Initialize m_suit with a default character (e.g., space)
        // and m_number with a default value (e.g., 0)
    }

    // Parameterized constructor
    Tile(char s, int n) : m_suit(s), m_number(n) {
        // Assign values to the member variables
    }

    // Comparison operator for equality
    bool operator==(const Tile& other) const {
        // Check if the suit and number of the tiles are initialized
        if (m_suit == ' ' || other.m_suit == ' ' || m_number == -1 || other.m_number == -1) {
            throw std::domain_error("Invalid suit: One or both tiles have an uninitialized suit.");
        }

        // Check if the suit and number of the tiles are equal
        if (m_suit == other.m_suit && m_number == other.m_number) {
            return true;
        }else{
            return false;
        }
    }
    // Overload less-than operator
    bool operator<(const Tile& other) const {
        // Check if the suit and number of the tiles are initialized
        if (m_suit == ' ' || other.m_suit == ' ' || m_number == -1 || other.m_number == -1) {
            throw std::domain_error("Invalid suit: One or both tiles have an uninitialized suit.");
        }

        // If suit of current tile is less than the suit of other tile, return true
        if (m_suit < other.m_suit) {
            return true;
        } 
        // If the suits are equal, check if the number of the current tile is less than the number of the other tile
        else if (m_suit == other.m_suit) {
            if (m_number < other.m_number) {
                return true;
            }
        } 
        // Neither of the conditions are met, this tile is not less than the other tile
        else{
            return false;
        }

    }

    // Overload greater-than operator
    bool operator>(const Tile& other) const {
        // Check if the suit and number of the tiles are initialized
        if (m_suit == ' ' || other.m_suit == ' ' || m_number == -1 || other.m_number == -1) {
            throw std::domain_error("Invalid suit: One or both tiles have an uninitialized suit.");
        }

        // If suit of current tile is greater than the suit of other tile, return true
        if (m_suit > other.m_suit) {
            return true;
        }
        // If the suits are equal, check if the number of the current tile is greater than the number of the other tile
        else if (m_suit == other.m_suit) {
            if (m_number > other.m_number) {
                return true;
            }
        }
        // Neither of the conditions are met, this tile is not greater than the other tile
        else{
            return false;
        }
    }

    bool operator<=(const Tile& other) const {
        // Check if the suit and number of the tiles are initialized
        if (m_suit == ' ' || other.m_suit == ' ' || m_number == -1 || other.m_number == -1) {
            throw std::domain_error("Invalid suit: One or both tiles have an uninitialized suit.");
        }

        // If suit of current tile is less than or equal to the suit of other tile, return true
        if (m_suit < other.m_suit) {
            return true;
        }
        // If the suits are equal, check if the number of the current tile is less than or equal to the number of the other tile
        else if (m_suit == other.m_suit) {
            if (m_number <= other.m_number) {
                return true;
            }
        }
        // Neither of the conditions are met, this tile is not less than or equal to the other tile
        else{
            return false;
        }       
    }

    bool operator>=(const Tile& other) const {
        // Check if the suit and number of the tiles are initialized
        if (m_suit == ' ' || other.m_suit == ' ' || m_number == -1 || other.m_number == -1) {
            throw std::domain_error("Invalid suit: One or both tiles have an uninitialized suit.");
        }

        // If suit of current tile is greater than or equal to the suit of other tile, return true
        if (m_suit > other.m_suit) {
            return true;
        }
        // If the suits are equal, check if the number of the current tile is greater than or equal to the number of the other tile
        else if (m_suit == other.m_suit) {
            if (m_number >= other.m_number) {
                return true;
            }
        }
        // Neither of the conditions are met, this tile is not greater than or equal to the other tile
        else{
            return false;
        }
    }

    bool operator!=(const Tile& other) const {
        // Check if the suit and number of the tiles are initialized
        if (m_suit == ' ' || other.m_suit == ' ' || m_number == -1 || other.m_number == -1) {
            throw std::domain_error("Invalid suit: One or both tiles have an uninitialized suit.");
        }

        // If the suit or number of the tiles are not equal, return true
        if (m_suit != other.m_suit || m_number != other.m_number) {
            return true;
        }else{
            return false;
        }
    }

    // Friend function to overload << operator for output
    friend std::ostream& operator<<(std::ostream& os, const Tile& tile) {
        os << tile.m_suit << tile.m_number;
        return os;
    }
};