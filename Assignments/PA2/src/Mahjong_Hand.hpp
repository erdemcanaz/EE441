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

        m_handSize--; // Decrement the hand size
        return popped_tile;
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
        for (size_t i = 0; i < m_handSize; ++i)
        {
            delete m_tiles[i];    // Free the heap pointed by the pointer
            m_tiles[i] = nullptr; // Set the pointer to nullptr to avoid dangling pointers
        }
        m_handSize = 0;
    };

    void add_tile(Tile *tile)
    {
        // This function adds a new tile into the hand such that the tiles held are ordered after the insertion

        // Find the index to insert the new tile. Assume the tiles are sorted in ascending order (e.g., B1, B2, B4, C2, C5, …)
        size_t index_to_insert = m_handSize;
        for (size_t i = 0; i < m_handSize; i++)
        {
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
        // The hand is ordered. To better readbility, considering the computational expense is fairly low, we can use brute force to find the tile to discard.

        // (I) Look for quadruplets in the hand. If a quadruplet exists the function will discard one of the tiles from the quadruplet.
        for (size_t i = 0; i < m_handSize; i++)
        {
            if (((i + 3 < m_handSize) && (*m_tiles[i] == *m_tiles[i + 1]) && (*m_tiles[i] == *m_tiles[i + 2]) && (*m_tiles[i] == *m_tiles[i + 3])))
            {
                // Quadruplet starting at index i
                return pop(i);
            }
        }

        // (II)  | Look for single tiles in the hand, which are tiles with no duplicates in your hand. If a single tile exists the function will discard it.
        for (size_t i = 0; i < m_handSize; i++)
        {

            if (i == 0 && *m_tiles[i] != *m_tiles[i + 1])
            {
                // first tile
                return pop(i);
            }
            else if (i == m_handSize - 1 && *m_tiles[i] != *m_tiles[i - 1])
            {
                // last tile
                return pop(i);
            }
            else if (i != 0 && i!= m_handSize &&*m_tiles[i] != *m_tiles[i - 1] && *m_tiles[i] != *m_tiles[i + 1])
            {
                // in between
                return pop(i);
            }
        }
        // (III) | Look for pairs in the hand. If the previous two steps did not find anything the hand will have at least 3 pairs and the function will discard a tile from one of them.
        for (size_t i = 0; i < m_handSize; i++)
        {
            if ((i + 1 < m_handSize) && *m_tiles[i] == *m_tiles[i + 1])
            {
                // Check if not part of a triplet
                bool is_triplet = false;

                if ((i > 0) && *m_tiles[i] == *m_tiles[i - 1])
                    is_triplet = true;
                if ((i + 2 < m_handSize) && *m_tiles[i] == *m_tiles[i + 2])
                    is_triplet = true;

                if (!is_triplet)
                {
                    // Found a pair not part of a triplet, discard one tile
                    return pop(i);
                }
            }
        }
    };

    bool check_win_condition() const
    {
        // Implement the check_win_condition function.This function will return true if the hand has 4 triplets and a pair indicating a game win.
        size_t keys[MAX_HAND_SIZE];   // key mapping is -> (suit - 'B') * 10 + number
        size_t counts[MAX_HAND_SIZE]; // counts of each tile exist in the hand
        size_t unique_tile_count = 0; // how many unique tiles exist in the hand

        for (size_t i = 0; i < MAX_HAND_SIZE; i++)
        {
            keys[i] = 0;
            counts[i] = 0;
        }

        // calculate the counts of each tile type incrementally
        for (size_t i = 0; i < m_handSize; i++)
        {
            size_t key = (m_tiles[i]->m_suit - 'B') * 10 + (m_tiles[i]->m_number);

            size_t key_index = unique_tile_count;
            for (size_t j = 0; j < unique_tile_count; j++)
            {
                if (keys[j] == key)
                {
                    key_index = j;
                    break;
                }
            }
            if (key_index == unique_tile_count)
            {
                unique_tile_count++;
                keys[key_index] = key;
            }
            counts[key_index]++;
        }

        // check the number of group types
        size_t pair_count = 0;
        size_t triplet_count = 0;

        for (size_t i = 0; i < unique_tile_count; i++)
        {
            if (counts[i] == 2)
            {
                pair_count++;
            }
            else if (counts[i] == 3)
            {
                triplet_count++;
            }
        }

        if (triplet_count == 4 && pair_count == 1)
        {
            return true;
        }
        return false;
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
    Tile tile_5('B', 5);
    Tile tile_6('B', 5);
    Tile tile_7('B', 5);
    Tile tile_8('B', 5);
    Tile tile_9('C', 2);

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

    hand.add_tile(&tile_5);
    std::cout << "\nAdded Tile 5 to the hand." << std::endl;
    hand.display_hand();

    hand.add_tile(&tile_6);
    std::cout << "\nAdded Tile 6 to the hand." << std::endl;
    hand.display_hand();

    hand.add_tile(&tile_7);
    std::cout << "\nAdded Tile 7 to the hand." << std::endl;
    hand.display_hand();

    hand.add_tile(&tile_8);
    std::cout << "\nAdded Tile 8 to the hand." << std::endl;
    hand.display_hand();

    hand.add_tile(&tile_9);
    std::cout << "\nAdded Tile 9 to the hand." << std::endl;
    hand.display_hand();

    hand.check_win_condition();

    // Discard Tile objects from the hand
    Tile *discarded_tile = hand.discard_tile();
    std::cout << "\nDiscarded Tile: " << *discarded_tile << std::endl;
    hand.display_hand();

    Tile *discarded_tile2 = hand.discard_tile();
    std::cout << "\nDiscarded Tile: " << *discarded_tile2 << std::endl;
    hand.display_hand();

    Tile *discarded_tile3 = hand.discard_tile();
    std::cout << "\nDiscarded Tile: " << *discarded_tile3 << std::endl;
    hand.display_hand();

    Tile *discarded_tile4 = hand.discard_tile();
    std::cout << "\nDiscarded Tile: " << *discarded_tile4 << std::endl;
    hand.display_hand();

    Tile *discarded_tile5 = hand.discard_tile();
    std::cout << "\nDiscarded Tile: " << *discarded_tile5 << std::endl;
    hand.display_hand();

    hand.check_win_condition();
}
