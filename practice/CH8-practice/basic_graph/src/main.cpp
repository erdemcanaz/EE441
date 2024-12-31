#include <iostream>
#include <string>
#include "graph.hpp"

void test()
{
    Graph graph_0;
    std::cout << "Address of the graph_0 is:" << &graph_0 << std::endl;
    Graph graph_1 = Graph(1, 5);
    std::cout << "Address of the graph_1 is:" << &graph_1 << std::endl;
    graph_1.printAdjacencyMatrix();
    graph_0 = Graph(3, 2);
    std::cout << "Address of the graph_0 is:" << &graph_0 << std::endl;
    graph_1 = graph_0;

    graph_0.printAdjacencyMatrix();
    graph_0.printMarkMatrix();
    graph_1.printAdjacencyMatrix();
}
int main()
{
    enum visited
    {
        NOT_VISITED,
        VISITED
    };

    std::cout << NOT_VISITED << std::endl;
    std::cout << VISITED << std::endl;

    test();

    return 0;
}