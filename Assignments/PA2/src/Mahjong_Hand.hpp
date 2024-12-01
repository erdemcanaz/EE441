#pragma once
#include <algorithm>
#include "Tile.hpp"

#define MAX_HAND_SIZE 14
class Hand
{
private:
    Tile *m_tiles[MAX_HAND_SIZE]; // default:  Array of pointers to Tile objects
    size_t m_handSize;            // Current hand size

    void insert_before(size_t index, Tile *new_tile)
    {
        //  This function adds a new Tile to the tiles before the given index. This function throws std::out_of_range error if the m_handSize exceeds MAX_HAND_SIZE macro with the insertion. Example: Hand: B1,B2,B4,C2,C5, nullptr, … -> insert_before (3, C1) -> B1,B2,B4,C1,C2,C5, nullptr, …
        if (m_handSize >= MAX_HAND_SIZE)
        {
            throw std::out_of_range("Invalid operation: Cannot insert into a full hand.");
        };

        // Shift the elements to the right starting from the index
        for (size_t i = m_handSize; i > index; --i)
        {
            m_tiles[i] = m_tiles[i - 1];
        };

        // Insert the new_tile at the index
        m_tiles[index] = new_tile;
        m_handSize++;
    };

    Tile *pop(size_t index)
    {
        // This function pops the Tile pointer with a given index from the m_tiles array. Hand: B1 B2 B4 C1 C2 C5 nullptr … -> pop (3, C1) -> B1 B2 B4 C2 C5 nullptr …
        if (index >= m_handSize)
        {
            throw std::out_of_range("Invalid operation: Cannot pop the tile at the given index since it exceeds the hand size.");
        };

        Tile *popped_tile = m_tiles[index]; // Get the pointer to the tile to be popped

        // Shift the elements to the left starting from the index
        for (size_t i = index; i < m_handSize - 1; ++i)
        {
            m_tiles[i] = m_tiles[i + 1];
        };
    };

public:
    // Constructors and Destructor
    Hand() : m_handSize(0) {
                 // Initialize the hand size with a default value (e.g., 0)
             };
    ~Hand()
    {
        for (size_t i = 0; i < m_handSize; ++i)
        {
            delete m_tiles[i];    // Free the heap pointed by the pointer
            m_tiles[i] = nullptr; // Set the pointer to nullptr to avoid dangling pointers
        }
    };

    // Member Functions
    void clear()
    {
        throw std::logic_error("Function \"clear\" is not implemented!");
        ;
    };

    void add_tile(Tile *tile)
    {
        // This function adds a new tile into the hand such that the tiles held are ordered after the insertion

        // Find the index to insert the new tile. Assume the tiles are sorted in ascending order (e.g., B1, B2, B4, C2, C5, …)
        size_t index_to_insert = m_handSize;
        for (size_t i = 0; i < m_handSize; i++)
        {
            bool is_tile_less = *tile < *m_tiles[i];
            if (*tile < *m_tiles[i])
            {
                index_to_insert = i;
                break;
            }
        }
        insert_before(index_to_insert, tile);
    };

    Tile *discard_tile(void)
    {
        throw std::logic_error("Function \"discard_tile\" is not implemented!");
    };

    bool check_win_condition() const
    {
        throw std::logic_error("Function \"check_win_condition\" is not implemented!");
    };

    // Display Function
    void display_hand() const
    {
        for (size_t i = 0; i < m_handSize; i++)
        {
            std::cout << *m_tiles[i] << ' ';
        }
    };
};

void __test_hand_class()
{
    std::cout << "\n\n--- Hand Class Tests ---" << std::endl;

    // Create Tile objects

    Tile tile_1('B', 1);
    Tile tile_2('C', 2);
    Tile tile_3('C', 3);
    Tile tile_4('B', 9);

    // Create a Hand of Tile objects
    Hand hand;
    std::cout << "Created an empty Hand. (Default)" << std::endl;
    hand.display_hand();

    // Add Tile objects to the hand
    hand.add_tile(&tile_1);
    std::cout << "\nAdded Tile 1 to the hand." << std::endl;
    hand.display_hand();

    hand.add_tile(&tile_2);
    std::cout << "\nAdded Tile 2 to the hand." << std::endl;
    hand.display_hand();

    hand.add_tile(&tile_3);
    std::cout << "\nAdded Tile 3 to the hand." << std::endl;
    hand.display_hand();

    hand.add_tile(&tile_4);
    std::cout << "\nAdded Tile 4 to the hand." << std::endl;
    hand.display_hand();
}