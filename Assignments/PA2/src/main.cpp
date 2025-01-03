// Simple_mahjongv2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Tile.hpp"
#include "Stack.hpp"
#include "Mahjong_Hand.hpp"
#include "Parser.hpp"
#include <algorithm>

#define NUMBER_OF_TURNS 3
#define IS_TESTING 0 // 0: Run the game, 1: Run the tests
int main()
{

    if (IS_TESTING)
    {
        __test_tile_class();
        __test_stack_class();
        __test_hand_class();
        return 0;
    }

    Stack<Tile> wall;
    Hand my_hand;

    for (int turn = 0; turn < NUMBER_OF_TURNS; turn++)
    {
        std::cout << "******************* GAME " << turn << " ***********************";
        std::cin.get();
        int turn_count = 0;
        parseFile("mahjong_tiles", turn, &wall);

        // Print the stack of parsed tiles
        std::cout << "Parsed Tiles: " << wall << std::endl;
        Tile *temp_tile;
        for (int i = 0; i < 14; i++)
        {
            temp_tile = new Tile(wall.pop_back());
            my_hand.add_tile(temp_tile);
        }

        while (!my_hand.check_win_condition() && !wall.is_empty())
        {
            turn_count++;
            std::cout << "Turn " << turn_count << "\n";
            my_hand.display_hand();
            temp_tile = my_hand.discard_tile();

            std::cout << *temp_tile << "\n";
            delete temp_tile;
            temp_tile = new Tile(wall.pop_back());
            my_hand.add_tile(temp_tile);
        }
        my_hand.display_hand();
        std::cout << "I won in turn " << turn_count << "!!!!! \n";
        wall.clear();
        my_hand.clear();
    }
    return 0;
}