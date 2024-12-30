#include "graph.hpp"
#include "memory.hpp"

Graph::Vertex::Vertex(size_t id) : m_id(id), m_color(0) {}

size_t Graph::Vertex::id() const
{
    return m_id;
}

int Graph::Vertex::color() const
{
    return m_color;
}

bool Graph::Vertex::color(int color)
{
    // If the input color is zero, always allow the update
    if (color == 0)
    {
        m_color = color;
        return true;
    }

    // Use the iterator to traverse through neighbors
    for (List<Vertex *>::Iterator it = m_neighbors.begin(); it != m_neighbors.end(); ++it)
    {
        if ((*it)->m_color == color)
        {
            return false; // Conflict found, cannot update color
        }
    }

    // No conflicts, update the color
    m_color = color;
    return true;
}

void Graph::Vertex::add_neighbor(Vertex *other)
{
    // Do nothing if the input is nullptr
    if (!other)
    {
        return;
    }

    // Check if the vertex is already a neighbor using an iterator
    for (List<Vertex *>::Iterator it = m_neighbors.begin(); it != m_neighbors.end(); ++it)
    {
        if (*it == other)
        {
            return; // Already a neighbor, do nothing
        }
    }

    // Add the vertex to the neighbor list
    m_neighbors.push_back(other);

    // Add this vertex to the other vertex's neighbor list
    other->m_neighbors.push_back(this);
}

void Graph::Vertex::remove_neighbor(Vertex *other)
{
    throw std::logic_error("Function \"Graph Vertex remove_neighbor\" is not implemented!");
}

Graph::Graph() {}

Graph::~Graph()
{
    throw std::logic_error("Function \"Graph destructor\" is not implemented!");
}

Graph::Graph(const Graph &other)
{
    throw std::logic_error("Function \"Graph copy constructor\" is not implemented!");
}

Graph::Graph(Graph &&other)
{
    throw std::logic_error("Function \"Graph move constructor\" is not implemented!");
}

Graph &Graph::operator=(const Graph &other)
{
    throw std::logic_error("Function \"Graph copy assignment\" is not implemented!");
}

Graph &Graph::operator=(Graph &&other)
{
    throw std::logic_error("Function \"Graph move assignment\" is not implemented!");
}

size_t Graph::add_vertex()
{
    throw std::logic_error("Function \"Graph add_vertex\" is not implemented!");
}

Graph::Vertex *Graph::operator[](size_t id)
{
    throw std::logic_error("Function \"Graph operator[]\" is not implemented!");
}

void Graph::connect(size_t id1, size_t id2)
{
    throw std::logic_error("Function \"Graph connect\" is not implemented!");
}

int Graph::max_color() const
{
    throw std::logic_error("Function \"Graph max_color\" is not implemented!");
}

bool Graph::color_helper(List<Vertex *>::Iterator vertex)
{
    throw std::logic_error("Function \"Graph color_helper\" is not implemented!");
}

bool Graph::color()
{
    throw std::logic_error("Function \"Graph color\" is not implemented!");
}
