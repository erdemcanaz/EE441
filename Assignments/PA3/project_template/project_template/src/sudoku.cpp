#include <iostream>
#include <stdexcept>
#include "sudoku.hpp"
#include "memory.hpp"

Sudoku::Sudoku() : Graph(create("data/sudoku.txt"))
{
    // Nothing else needed here since the base class is initialized
}

Sudoku::~Sudoku()
{
    // Nothing special to do, as the Graph base destructor
    // takes care of cleaning up dynamic memory for the vertices.
}

bool Sudoku::solve()
{
    // For Sudoku, the Graph::color() method tries to color all vertices
    // from 1..max_color() in a backtracking manner.
    // If it succeeds, we have a solution; otherwise, no solution.
    return this->color();
}

void Sudoku::print()
{
    // Print the Sudoku board in 9 rows x 9 columns
    // Each vertex ID from 1..81 corresponds to row,col as:
    //   row = (id-1) / 9
    //   col = (id-1) % 9
    //
    // We add some spacing/lines to mimic a Sudoku layout.

    for (int row = 0; row < 9; ++row)
    {
        // Horizontal line every 3 rows (except the top might be omitted or customized)
        if (row % 3 == 0 && row != 0)
        {
            std::cout << "------+-------+------" << std::endl;
        }

        for (int col = 0; col < 9; ++col)
        {
            // Vertical line every 3 columns (except the leftmost can be omitted or customized)
            if (col % 3 == 0 && col != 0)
            {
                std::cout << " |";
            }

            // Compute the cell ID in [1..81]
            int id = row * 9 + col + 1;
            int c = (*this)[id]->color();

            // If color == 0, that means uncolored
            if (c == 0)
                std::cout << " .";
            else
                std::cout << " " << c;
        }
        std::cout << std::endl;
    }
}

int Sudoku::max_color() const
{
    // For a standard Sudoku, we always want digits 1..9
    // regardless of what the underlying graph says about "maximum degree + 1".
    // So we override the base class method to forcibly return 9.
    return 9;
}