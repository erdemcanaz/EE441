#pragma once

#include <stdexcept>
#include "memory.hpp"

template <class T>
class List
{
private:
    struct Node
    {
        T m_data;
        Node* m_prev;
        Node* m_next;

        Node(T data) : m_data(data), m_prev(nullptr), m_next(nullptr) { }
    };

    Node* m_head;
    Node* m_tail;
    size_t m_size;

public:
    List() : m_head(nullptr), m_tail(nullptr), m_size(0) { }
    ~List()
    {
        throw std::logic_error("Function \"List destructor\" is not implemented!");
    }

    size_t size() const {
        return m_size;
    }


    List(const List& other)
    {
        throw std::logic_error("Function \"List copy constructor\" is not implemented!");
    }

    List(List&& other)
    {
        throw std::logic_error("Function \"List move constructor\" is not implemented!");
    }

    List& operator=(const List& other)
    {
        throw std::logic_error("Function \"List copy assignment\" is not implemented!");
    }

    List& operator=(List&& other)
    {
        throw std::logic_error("Function \"List move assignment\" is not implemented!");
    }

private:
    // Helper function for inserting for the first time
    // Should only be called when m_head == nullptr
    inline void initiate(T data)
    {
        throw std::logic_error("Function \"List initate\" is not implemented!");
    }

    // Helper function for removing the only element in a list with size 1.
    // Should only be called when m_head == m_tail
    inline T deplete()
    {
        throw std::logic_error("Function \"List deplete\" is not implemented!");
    }

    // Helper function to connect two nodes in a doubly linked list
    static inline void hook(Node* prev, Node* next)
    {
        throw std::logic_error("Function \"List hook\" is not implemented!");
    }

public:
    void push_back(T data)
    {
        throw std::logic_error("Function \"List push_back\" is not implemented!");
    }

    void push_front(T data)
    {
        throw std::logic_error("Function \"List push_front\" is not implemented!");
    }

    T pop_back()
    {
        throw std::logic_error("Function \"List pop_back\" is not implemented!");
    }

    T pop_front()
    {
        throw std::logic_error("Function \"List pop_front\" is not implemented!");
    }

    class Iterator
    {
    private:
        Node* m_node;

        Iterator(Node* node) : m_node(node) { }

        friend class List;

    public:
        bool operator==(Iterator other) const
        {
            throw std::logic_error("Function \"List Iterator operator==\" is not implemented!");
        }

        bool operator!=(Iterator other) const
        {
            throw std::logic_error("Function \"List Iterator operator!=\" is not implemented!");
        }

        T& operator*()
        {
            throw std::logic_error("Function \"List Iterator operator*\" is not implemented!");
        }

        Iterator next()
        {
            throw std::logic_error("Function \"List Iterator next\" is not implemented!");
        }

        // prefix increment
        Iterator operator++()
        {
            throw std::logic_error("Function \"List Iterator prefix increment\" is not implemented!");
        }

        // postfix increment
        Iterator operator++(int)
        {
            throw std::logic_error("Function \"List Iterator postfix increment\" is not implemented!");
        }
    };

    class ConstIterator
    {
    private:
        const Node* m_node;

        ConstIterator(const Node* node) : m_node(node) { }

        friend class List;

    public:
        bool operator==(ConstIterator other) const
        {
            throw std::logic_error("Function \"List ConstIterator operator==\" is not implemented!");
        }

        bool operator!=(ConstIterator other) const
        {
            throw std::logic_error("Function \"List ConstIterator operator!=\" is not implemented!");
        }

        const T& operator*() const
        {
            throw std::logic_error("Function \"List ConstIterator operator*\" is not implemented!");
        }

        ConstIterator next()
        {
            throw std::logic_error("Function \"List ConstIterator next\" is not implemented!");
        }

        // prefix increment
        ConstIterator operator++()
        {
            throw std::logic_error("Function \"List ConstIterator prefix increment\" is not implemented!");
        }

        // postfix increment
        ConstIterator operator++(int)
        {
            throw std::logic_error("Function \"List ConstIterator postfix increment\" is not implemented!");
        }
    };

    Iterator begin()
    {
        return Iterator(m_head);
    }

    Iterator end()
    {
        return Iterator(nullptr);
    }

    ConstIterator begin() const
    {
        return ConstIterator(m_head);
    }

    ConstIterator end() const
    {
        return ConstIterator(nullptr);
    }

    Iterator insert(Iterator iter, T data)
    {
        throw std::logic_error("Function \"List insert\" is not implemented!");
    }

    Iterator remove(Iterator iter)
    {
        throw std::logic_error("Function \"List remove\" is not implemented!");
    }
};
