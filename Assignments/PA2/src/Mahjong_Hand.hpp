#pragma once
#include <algorithm>
#include "Tile.hpp"

#define MAX_HAND_SIZE 14
class Hand {
private:
    Tile* m_tiles[MAX_HAND_SIZE];        // Array of pointers to Tile objects
    size_t m_handSize;       // Current hand size

    void insert_before(size_t index, Tile* new_tile) {
        throw std::logic_error("Function \"insert_before\" is not implemented!");
    };

    Tile * pop(size_t index) {
        throw std::logic_error("Function \"pop\" is not implemented!");
    };
public:
    // Constructors and Destructor
    Hand() {
        throw std::logic_error("Function \"default constructor\" is not implemented!");
    };
    ~Hand() {
        throw std::logic_error("Function \"destructor\" is not implemented!");
    };

    // Member Functions
    void clear() {
        throw std::logic_error("Function \"clear\" is not implemented!");;
    };

    void add_tile(Tile* tile) {
        throw std::logic_error("Function \"add_tile\" is not implemented!");     
    };

    Tile* discard_tile(void) {
        throw std::logic_error("Function \"discard_tile\" is not implemented!");
    };

    bool check_win_condition() const {
        throw std::logic_error("Function \"check_win_condition\" is not implemented!");
    };

    // Display Function
    void display_hand() const {
        throw std::logic_error("Function \"display_hand\" is not implemented!");    
    };
};
