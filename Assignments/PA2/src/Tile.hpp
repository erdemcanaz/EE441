#pragma once
#include <iostream>

// Define your Tile struct
class Tile {
public:
    char m_suit;
    int m_number;

    // Default constructor
    Tile() {
		throw std::logic_error("Function \"default constructor\" is not implemented!");
	}

    // Parameterized constructor
    Tile(char s, int n) {
		throw std::logic_error("Function \"destructor\" is not implemented!");
	}

    // Comparison operator for equality
    bool operator==(const Tile& other) const {
        throw std::logic_error("Function \"==\" is not implemented!");
    }
    // Overload less-than operator
    bool operator<(const Tile& other) const {
        throw std::logic_error("Function \"<\" is not implemented!");
    }

    // Overload greater-than operator
    bool operator>(const Tile& other) const {
        throw std::logic_error("Function \">\" is not implemented!");
    }

    bool operator<=(const Tile& other) const {
        throw std::logic_error("Function \"<=\" is not implemented!");
    }

    bool operator>=(const Tile& other) const {
        throw std::logic_error("Function \">=\" is not implemented!");
    }

    bool operator!=(const Tile& other) const {
        throw std::logic_error("Function \"!=\" is not implemented!");
    }

    // Friend function to overload << operator for output
    friend std::ostream& operator<<(std::ostream& os, const Tile& tile) {
        os << tile.m_suit << tile.m_number;
        return os;
    }
};