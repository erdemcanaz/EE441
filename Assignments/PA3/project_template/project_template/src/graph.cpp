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
    // NOTE: there is a huge performance issue with this implementation
    //       one can implement remove(Node* other) in the List class to make this operation more efficient
    //       However, this is not required for this assignment and is not implemented here

    //  Do nothing if the input is nullptr
    if (!other)
    {
        return;
    }

    // Create a temporary list for this vertex's neighbors
    List<Vertex *> temp_neighbors;
    for (List<Vertex *>::Iterator it = m_neighbors.begin(); it != m_neighbors.end(); ++it)
    {
        if (*it != other)
        {
            temp_neighbors.push_back(*it);
        }
    }

    // Use SWAP-AND-ROLLBACK LOGIC to prevent memory leak
    m_neighbors = std::move(temp_neighbors);

    // Create a temporary list for the other vertex's neighbors
    List<Vertex *> temp_other_neighbors;
    for (List<Vertex *>::Iterator it = other->m_neighbors.begin(); it != other->m_neighbors.end(); ++it)
    {
        if (*it != this)
        {
            temp_other_neighbors.push_back(*it);
        }
    }

    // Use SWAP-AND-ROLLBACK LOGIC to prevent memory leak
    other->m_neighbors = std::move(temp_other_neighbors);
}

Graph::Graph() {}

// Destructor: clean up all Vertex* in m_vertices
Graph::~Graph()
{
    // Delete all Vertex* in m_vertices
    //  Graph ->  List<Vertex*> m_vertices;
    for (List<Vertex *>::Iterator it = m_vertices.begin(); it != m_vertices.end(); ++it)
    {
        delete *it; // each *it is a 'Vertex*'
        //*it -> List<Vertex*> m_neighbors;
        // The List destructor will handle clearing up its nodes(i.e neighbors)
    }
}

// Copy constructor: deep copy all vertices from 'other'
Graph::Graph(const Graph &other)
{
    // We need to do a "deep copy" so that each Vertex* in the new graph
    // is distinct from the Vertex* in 'other'.

    // First, make two parallel lists to map old pointers -> new pointers
    List<Vertex *> oldPtrs;
    List<Vertex *> newPtrs;

    // --- 1) Create new Vertex objects with the same ID (and color),
    //         but do not yet wire up neighbors
    for (auto it = other.m_vertices.begin(); it != other.m_vertices.end(); ++it)
    {
        Vertex *oldV = *it;
        Vertex *newV = new Vertex(oldV->id());
        newV->m_color = oldV->m_color;
        oldPtrs.push_back(oldV);
        newPtrs.push_back(newV);
    }

    // --- 2) Wire up neighbors
    // We iterate oldPtrs and newPtrs in parallel
    auto oldIt = oldPtrs.begin();
    auto newIt = newPtrs.begin();
    while (oldIt != oldPtrs.end() && newIt != newPtrs.end())
    {
        Vertex *oldV = *oldIt;
        Vertex *newV = *newIt;

        // For each neighbor in oldV, find the matching new vertex
        // (based on pointer location in oldPtrs/newPtrs) and add it as neighbor.
        for (auto nit = oldV->m_neighbors.begin(); nit != oldV->m_neighbors.end(); ++nit)
        {
            Vertex *oldNeighbor = *nit;

            // We find oldNeighbor in oldPtrs (linear search),
            // then pick the same index in newPtrs
            Vertex *newNeighbor = nullptr;
            {
                auto o2 = oldPtrs.begin();
                auto n2 = newPtrs.begin();
                while (o2 != oldPtrs.end() && n2 != newPtrs.end())
                {
                    if (*o2 == oldNeighbor)
                    {
                        newNeighbor = *n2;
                        break;
                    }
                    ++o2;
                    ++n2;
                }
            }
            // Now wire them up
            if (newNeighbor)
            {
                newV->add_neighbor(newNeighbor);
            }
        }
        ++oldIt;
        ++newIt;
    }

    // --- 3) Finally, add all the newly created Vertex pointers into this->m_vertices
    for (auto it = newPtrs.begin(); it != newPtrs.end(); ++it)
    {
        m_vertices.push_back(*it);
    }
}

// Move constructor: steal the list of vertices from 'other'
Graph::Graph(Graph &&other)
{
    // Steal the list of vertices
    m_vertices = std::move(other.m_vertices);

    // 'other' no longer owns these vertices; it has effectively given them away
    // We do not delete anything in 'other', its destructor won't delete transferred vertices
    // because the list is now empty, and the pointers have moved here.
}

// Copy assignment: deep copy all vertices from 'other'
Graph &Graph::operator=(const Graph &other)
{
    if (this == &other)
    {
        return *this; // self-assignment guard
    }

    // 1) Destroy all existing vertices in *this
    for (auto it = m_vertices.begin(); it != m_vertices.end(); ++it)
    {
        delete *it;
    }
    m_vertices = List<Vertex *>(); // clear

    // 2) Same deep-copy logic as copy constructor
    List<Vertex *> oldPtrs;
    List<Vertex *> newPtrs;

    // --- Create new vertices
    for (auto it = other.m_vertices.begin(); it != other.m_vertices.end(); ++it)
    {
        Vertex *oldV = *it;
        Vertex *newV = new Vertex(oldV->id());
        newV->m_color = oldV->m_color;
        oldPtrs.push_back(oldV);
        newPtrs.push_back(newV);
    }

    // --- Wire up neighbors
    auto oldIt = oldPtrs.begin();
    auto newIt = newPtrs.begin();
    while (oldIt != oldPtrs.end() && newIt != newPtrs.end())
    {
        Vertex *oldV = *oldIt;
        Vertex *newV = *newIt;

        for (auto nit = oldV->m_neighbors.begin(); nit != oldV->m_neighbors.end(); ++nit)
        {
            Vertex *oldNeighbor = *nit;
            Vertex *newNeighbor = nullptr;

            // find oldNeighbor in oldPtrs
            auto o2 = oldPtrs.begin();
            auto n2 = newPtrs.begin();
            while (o2 != oldPtrs.end() && n2 != newPtrs.end())
            {
                if (*o2 == oldNeighbor)
                {
                    newNeighbor = *n2;
                    break;
                }
                ++o2;
                ++n2;
            }
            // wire up
            if (newNeighbor)
            {
                newV->add_neighbor(newNeighbor);
            }
        }
        ++oldIt;
        ++newIt;
    }

    // --- Put the new vertices in our list
    for (auto it = newPtrs.begin(); it != newPtrs.end(); ++it)
    {
        m_vertices.push_back(*it);
    }

    return *this;
}

// Move assignment: steal the list of vertices from 'other'
Graph &Graph::operator=(Graph &&other)
{
    if (this == &other)
    {
        return *this; // self-assignment guard
    }

    // 1) Destroy old data in *this
    for (auto it = m_vertices.begin(); it != m_vertices.end(); ++it)
    {
        delete *it;
        //*it -> List<Vertex*> m_neighbors;
        // The List destructor will handle clearing up its nodes(i.e neighbors)
    }
    m_vertices = List<Vertex *>();

    // 2) Steal other's data
    m_vertices = std::move(other.m_vertices);

    return *this;
}

size_t Graph::add_vertex()
{
    // Create a new vertex with an ID equal to the current size of m_vertices
    Vertex *v = new Vertex(m_vertices.size());
    m_vertices.push_back(v);
    return v->id();
}

Graph::Vertex *Graph::operator[](size_t id)
{
    // Iterate through m_vertices to find the vertex with the given ID
    for (List<Vertex *>::Iterator it = m_vertices.begin(); it != m_vertices.end(); ++it)
    {
        if ((*it)->id() == id)
        {
            return *it;
        }
    }
    throw std::domain_error("Vertex with the given ID does not exist");
}

void Graph::connect(size_t id1, size_t id2)
{
    // Check if the IDs are the same
    if (id1 == id2)
    {
        throw std::invalid_argument("Cannot connect a vertex to itself");
    }

    // Find the vertices with the given IDs, assumes IDs are unique
    Vertex *v1 = nullptr;
    Vertex *v2 = nullptr;

    for (List<Vertex *>::Iterator it = m_vertices.begin(); it != m_vertices.end(); ++it)
    {
        if ((*it)->id() == id1)
        {
            v1 = *it;
        }
        if ((*it)->id() == id2)
        {
            v2 = *it;
        }
    }

    // Check if the vertices were found
    if (v1 == nullptr || v2 == nullptr)
    {
        throw std::domain_error("One or both vertices do not exist with the given ID(s)");
    }

    // Add each vertex as a neighbor of the other, call only for one vertex since it is also added to other's neighbors within the function
    v1->add_neighbor(v2);
}

int Graph::max_color() const
{
    // Implement the function Graph::max_color which gives the maximum possible color. Please note that this value is equal to the maximum degree in the graph plus one.

    // Initialize the maximum degree to zero
    int max_degree = 0;

    // Iterate through all vertices in the graph
    for (auto it = m_vertices.begin(); it != m_vertices.end(); ++it)
    {
        // Get the current vertex
        Vertex *v = *it;

        // Get the number of neighbors of the current vertex
        int degree = v->m_neighbors.size();

        // Update the maximum degree if the current vertex has a higher degree
        if (degree > max_degree)
        {
            max_degree = degree;
        }
    }

    // Return the maximum degree plus one
    return max_degree + 1;
}

// Private helper (recursive) function to color vertices of the graph.
bool Graph::color_helper(List<Vertex *>::Iterator vertexIt)
{
    // (a) If the vertices are depleted, return true
    if (vertexIt == m_vertices.end())
        return true;

    Vertex *v = *vertexIt; // Dereference the iterator to get the Vertex*

    // (b) If this vertex is already colored, move on to the next one
    if (v->color() != 0)
    {
        // Just recurse on the next vertex
        ++vertexIt;
        return color_helper(vertexIt);
    }

    // (c) If the vertex is not colored, we will try assigning possible colors
    //     up to max_color() (you can change the logic if you prefer fewer colors).
    int maxC = max_color(); // e.g., could be # of vertices or some other bound
    for (int c = 1; c <= maxC; ++c)
    {
        // Check if color 'c' is valid (i.e., no neighbor has that color)
        bool canUseThisColor = true;
        for (auto nbIt = v->m_neighbors.begin(); nbIt != v->m_neighbors.end(); ++nbIt)
        {
            if ((*nbIt)->color() == c)
            {
                canUseThisColor = false;
                break;
            }
        }

        if (canUseThisColor)
        {
            // Temporarily color this vertex
            v->color(c);

            // Recurse on the next vertex
            List<Vertex *>::Iterator nextIt = vertexIt;
            ++nextIt;
            if (color_helper(nextIt))
                return true;

            // (d) Backtrack: reset the color if it didn't lead to a solution
            v->color(0);
        }
    }

    // If no color assignment worked, return false
    return false;
}

/**
 * Public function to color the entire graph.
 * For disconnected graphs, we attempt coloring from each vertex to ensure
 * that each connected component is colored.
 */
bool Graph::color()
{
    // Call color_helper for each vertex in the graph.
    // If any vertex fails to color properly (returns false),
    // the entire coloring process fails.
    for (auto it = m_vertices.begin(); it != m_vertices.end(); ++it)
    {
        // If color_helper cannot complete coloring starting from this vertex, return false
        if (!color_helper(it))
            return false;
    }

    // If we never failed, we have a consistent coloring
    return true;
}

// Return the number of vertices in the graph
int Graph::__size() const
{
    return m_vertices.size();
}