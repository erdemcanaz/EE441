#pragma once

#include <stdexcept>
#include "memory.hpp"

template <class T>
class List
{
    // A doubly linked list allowing bidirectional traversal.
    // null < N_0 <> N_1 <> N_2 <>... <> N_i >null
    // Nodes are dynamically allocated as needed.
private:
    struct Node
    {
        T m_data;
        Node *m_prev;
        Node *m_next;

        Node(T data) : m_data(data), m_prev(nullptr), m_next(nullptr) {}
    };

    Node *m_head;
    Node *m_tail;
    size_t m_size;

public:
    // DEFAULT CONSTRUCTOR: Initialize an empty list
    List() : m_head(nullptr), m_tail(nullptr), m_size(0) {}

    // DESTRUCTOR: Delete all nodes to avoid memory leaks.
    ~List()
    {
        Node *current = m_head;
        while (current)
        {
            Node *next = current->m_next;
            delete current;
            current = next;
        }
        // Not strictly necessary, but makes it clear everything is gone:
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;
    }

    // COPY CONSTRUCTOR: Initialize this list as an empty list, then copy every node from `other`
    List(const List &other) : m_head(nullptr), m_tail(nullptr), m_size(0)
    {
        Node *temp = other.m_head;
        while (temp != nullptr)
        {
            push_back(temp->m_data);
            temp = temp->m_next;
        }
    }

    // MOVE CONSTRUCTOR: "Steals" the head, tail, and size from `other`, leaving `other` in an empty state.
    List(List &&other) : m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size)
    {
        // Leave `other` in an empty (but destructible) state
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;
    }

    // COPY ASSIGNMENT: Deep-Copy every node from `other` to this list. ( Guard against self-assignment.)
    List &operator=(const List &other)
    {
        // Guard against self-assignment
        if (this == &other)
            return *this;

        // First, free the existing list
        Node *current = m_head;
        while (current)
        {
            Node *next = current->m_next;
            delete current;
            current = next;
        }
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;

        // Then, copy from `other`
        Node *temp = other.m_head;
        while (temp != nullptr)
        {
            push_back(temp->m_data);
            temp = temp->m_next;
        }
        return *this;
    }

    // MOVE ASSIGNMENT: Other list entities are referenced by this list. Used if the other list is temporary and will be destroyed.
    List &operator=(List &&other)
    {
        if (this == &other)
            return *this; // self-assignment, do nothing

        // SWAP-AND-ROLLBACK LOGIC -- swap pointers with `other`
        // Swap m_head
        Node *tempHead = m_head;
        m_head = other.m_head;
        other.m_head = tempHead;

        // Swap m_tail
        Node *tempTail = m_tail;
        m_tail = other.m_tail;
        other.m_tail = tempTail;

        // Swap m_size
        size_t tempSize = m_size;
        m_size = other.m_size;
        other.m_size = tempSize;

        // When `other` goes out of scope, it will destroy
        // what used to be our old list (if any).

        return *this;
    }

    // Return the number of elements in the list (i.e len(list) in Python)
    size_t size() const
    {
        return m_size;
    }

private:
    // Helper function for inserting for the first time
    // Should only be called when m_head == nullptr
    inline void initiate(T data)
    {
        Node *node = new Node(data);
        m_head = node;
        m_tail = node;
        m_size = 1;
    }

    // Helper function for removing the only element in a list with size 1.
    // Should only be called when m_head == m_tail
    inline T deplete()
    {
        // Let's assume we pop the single element
        if (!m_head)
            throw std::runtime_error("deplete called on empty list");

        T ret = m_head->m_data;
        delete m_head;
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;
        return ret;
    }

    // Helper function to connect two nodes in a doubly linked list
    static inline void hook(Node *prev, Node *next)
    {
        if (prev)
            prev->m_next = next;
        if (next)
            next->m_prev = prev;
    }

public:
    // Add a new node to the end of the list
    void push_back(T data)
    {
        if (!m_head)
        {
            // If list is empty, initiate
            initiate(data);
        }
        else
        {
            Node *node = new Node(data);
            // Connect the new node to the last node
            hook(m_tail, node);
            m_tail = node;
            ++m_size;
        }
    }

    // Add a new node to the front of the list
    void push_front(T data)
    {
        if (!m_head)
        {
            // If list is empty, initiate
            initiate(data);
        }
        else
        {
            Node *node = new Node(data);
            hook(node, m_head);
            m_head = node;
            ++m_size;
        }
    }

    // Remove the last node from the list
    T pop_back()
    {
        // If the list is empty, throw an error
        if (!m_head)
            throw std::runtime_error("pop_back on empty list");

        // If the list has only one element, deplete the list
        if (m_head == m_tail)
            return deplete();

        // Otherwise, remove the last element
        Node *oldTail = m_tail;
        T ret = oldTail->m_data;
        m_tail = m_tail->m_prev;
        // Unhook oldTail
        m_tail->m_next = nullptr;
        delete oldTail;
        --m_size;
        return ret;
    }

    // Remove the first node from the list
    T pop_front()
    {
        // If the list is empty, throw an error
        if (!m_head)
            throw std::runtime_error("pop_front on empty list");

        // If the list has only one element, deplete the list
        if (m_head == m_tail)
            return deplete();

        // Otherwise, remove the first element
        Node *oldHead = m_head;
        T ret = oldHead->m_data;
        m_head = m_head->m_next;
        // Unhook oldHead
        m_head->m_prev = nullptr;
        delete oldHead;
        --m_size;
        return ret;
    }

    class Iterator
    {
    private:
        Node *m_node;

        Iterator(Node *node) : m_node(node) {}

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

        T &operator*()
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
        const Node *m_node;

        ConstIterator(const Node *node) : m_node(node) {}

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

        const T &operator*() const
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
