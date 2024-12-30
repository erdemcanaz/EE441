#pragma once

#include "list.hpp"
#include "memory.hpp"

class Graph
{
public:
    class Vertex
    {
    private:
        size_t m_id;
        int m_color;

        List<Vertex *> m_neighbors;

        friend class Graph;

    public:
        //  Return how many neighbors this vertex has. added for testing
        size_t __neighbor_count() const
        {
            return m_neighbors.size();
        }

        //  Check if 'other' is a neighbor. added for testing
        bool __has_neighbor(const Vertex *other) const
        {
            for (auto it = m_neighbors.begin(); it != m_neighbors.end(); ++it)
            {
                if (*it == other)
                    return true;
            }
            return false;
        }

        // Return the neighbor at a given index (for testing or iteration).
        Vertex *__neighbor_at(size_t index) const
        {
            auto it = m_neighbors.begin();
            for (size_t i = 0; i < index; i++)
            {
                ++it; // no bounds checking in this simple snippet
            }
            return *it;
        }

        Vertex(size_t id);

        size_t id() const;
        int color() const;
        bool color(int color);

        void add_neighbor(Vertex *other);
        void remove_neighbor(Vertex *other);
    };

private:
    List<Vertex *> m_vertices;

public:
    Graph();
    virtual ~Graph();

    Graph(const Graph &other);
    Graph(Graph &&other);
    Graph &operator=(const Graph &other);
    Graph &operator=(Graph &&other);

    size_t add_vertex();

    Vertex *operator[](size_t id);

    void connect(size_t id1, size_t id2);

    virtual int max_color() const;

    //  Return the number of vertices in the graph. added for testing
    int __size() const;

private:
    bool color_helper(List<Vertex *>::Iterator vertex);

public:
    bool color();
};

Graph create(const char *filename);
