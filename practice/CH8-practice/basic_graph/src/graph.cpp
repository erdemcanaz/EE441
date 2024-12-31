#include <stdio.h>
#include <iostream>

#include "graph.hpp"

// Default constructor (not usefull, for the sake of completeness)
Graph::Graph() : id(0), num_vertex(0), num_edge(0)
{
    adjacency_matrix = nullptr;
    mark = nullptr;
};

// Constructor
Graph::Graph(int i, int n) : id(i), num_vertex(n), num_edge(0)
{
    // Allocate memory for adjacency matrix (2D nxn array) and initialize it to 0
    adjacency_matrix = new int *[num_vertex];
    for (size_t i = 0; i < n; i++)
    {
        adjacency_matrix[i] = new int[num_vertex];
        for (size_t j = 0; j < n; j++)
        {
            adjacency_matrix[i][j] = 0;
        }
    }

    // Allocate memory for mark array (1D n array) and initialize it.
    mark = new int[n];
    for (size_t i = 0; i < n; i++)
    {
        mark[i] = UNVISITED;
    }
};

// Assignment operator
Graph &Graph::operator=(const Graph &other)
{
    // ### Ensure that other is not this
    if (this == &other)
    {
        return *this;
    }

    // ### Free previous data
    //  Deallocate adjacency matrix
    for (size_t i = 0; i < num_vertex; i++)
    {
        delete[] adjacency_matrix[i];
    }
    delete[] adjacency_matrix;

    // Deallocate mark array
    delete[] mark;

    adjacency_matrix = nullptr;
    mark = nullptr;

    // ### Deepcopy data
    id = other.id;
    num_vertex = other.num_vertex;
    num_edge = other.num_edge;

    adjacency_matrix = new int *[num_vertex];
    for (size_t i = 0; i < num_vertex; i++)
    {
        adjacency_matrix[i] = new int[num_vertex];
        for (size_t j = 0; j < num_vertex; j++)
        {
            adjacency_matrix[i][j] = other.adjacency_matrix[i][j];
        }
    }

    // Allocate memory for mark array (1D n array) and initialize it.
    mark = new int[num_vertex];
    for (size_t i = 0; i < num_vertex; i++)
    {
        mark[i] = other.mark[i];
    }
};

// Destructor
Graph::~Graph()
{
    // Deallocate adjacency matrix
    for (size_t i = 0; i < num_vertex; i++)
    {
        delete[] adjacency_matrix[i];
    }
    delete[] adjacency_matrix;

    // Deallocate mark array
    delete[] mark;

    adjacency_matrix = nullptr;
    mark = nullptr;

    std::cout << "Destructor is called for graph (" << id << ")" << std::endl;
}

void Graph::printAdjacencyMatrix() const
{
    std::cout << "\n\nPrinting Graph (" << id << ")" << std::endl;
    for (size_t row = 0; row < num_vertex; row++)
    {
        for (size_t column = 0; column < num_vertex; column++)
        {
            std::cout << adjacency_matrix[row][column] << " ";
        }
        std::cout << "\n";
    }
};

void Graph::printMarkMatrix() const
{
    for (size_t i = 0; i < num_vertex; i++)
    {
        std::cout << "Vertex (" << i << ") :" << mark[i] << std::endl;
    }
}