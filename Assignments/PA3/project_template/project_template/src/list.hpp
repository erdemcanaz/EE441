#pragma once

#include <stdexcept>
#include "memory.hpp"
#include <iostream>

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

    // COPY CONSTRUCTOR: Initialize this list as an empty list, then copy every node from 'other'
    List(const List &other) : m_head(nullptr), m_tail(nullptr), m_size(0)
    {
        Node *temp = other.m_head;
        while (temp != nullptr)
        {
            push_back(temp->m_data);
            temp = temp->m_next;
        }
    }

    // MOVE CONSTRUCTOR: "Steals" the head, tail, and size from 'other', leaving 'other' in an empty state.
    List(List &&other) : m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size)
    {
        // Leave 'other' in an empty (but destructible) state
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;
    }

    // COPY ASSIGNMENT: Deep-Copy every node from 'other' to this list. ( Guard against self-assignment.)
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

        // Then, copy from 'other'
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

        // 1. Clean up any existing nodes in *this
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

        // 2. Steal the data from 'other'
        m_head = other.m_head;
        m_tail = other.m_tail;
        m_size = other.m_size;

        // 3. Leave 'other' in an empty state
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;

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
        // Constructor is private so only List can create Iterators
        Iterator(Node *node) : m_node(node) {}
        friend class List;

    public:
        // Compare if two iterators point to the same node
        bool operator==(Iterator other) const
        {
            return m_node == other.m_node;
        }

        // Compare if two iterators point to different nodes
        bool operator!=(Iterator other) const
        {
            return m_node != other.m_node;
        }

        // Dereference operator: returns a reference to the data stored in the node
        T &operator*()
        {
            if (!m_node)
            {
                throw std::runtime_error("Dereferencing end() iterator or nullptr");
            }
            return m_node->m_data;
        }

        // Return an iterator to the *next* element (without changing the current iterator)
        Iterator next()
        {
            if (m_node)
            {
                return Iterator(m_node->m_next);
            }
            return Iterator(nullptr);
        }

        // Prefix increment: ++it
        Iterator operator++()
        {
            if (m_node)
            {
                m_node = m_node->m_next;
            }
            return *this;
        }

        // Postfix increment: it++
        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++(*this); // reuse prefix
            return temp;
        }
    };

    class ConstIterator
    {
    private:
        const Node *m_node;
        // Constructor is private so only List can create ConstIterators
        ConstIterator(const Node *node) : m_node(node) {}
        friend class List;

    public:
        bool operator==(ConstIterator other) const
        {
            return m_node == other.m_node;
        }

        bool operator!=(ConstIterator other) const
        {
            return m_node != other.m_node;
        }

        // Dereference operator (const): returns a const reference to the data
        const T &operator*() const
        {
            if (!m_node)
            {
                throw std::runtime_error("Dereferencing end() const iterator or nullptr");
            }
            return m_node->m_data;
        }

        ConstIterator next()
        {
            if (m_node)
            {
                return ConstIterator(m_node->m_next);
            }
            return ConstIterator(nullptr);
        }

        // prefix increment: ++it
        ConstIterator operator++()
        {
            if (m_node)
            {
                m_node = m_node->m_next;
            }
            return *this;
        }

        // postfix increment: it++
        ConstIterator operator++(int)
        {
            ConstIterator temp = *this;
            ++(*this); // reuse prefix
            return temp;
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
        /*
            insert:
            Inserts a new node before the node pointed to by 'iter'.
            If 'iter' == begin(), it's equivalent to push_front.
            If 'iter' == end(),   it's equivalent to push_back.
        */

        // Special case: if the iterator is end() => push_back
        if (iter.m_node == nullptr)
        {
            push_back(data);
            // The new tail node is the inserted node
            return Iterator(m_tail);
        }

        // Special case: if iter == begin() => push_front
        if (iter.m_node == m_head)
        {
            push_front(data);
            // The new head node is the inserted node
            return Iterator(m_head);
        }

        // Otherwise, we need to insert before iter.m_node
        Node *current = iter.m_node;
        Node *prevNode = current->m_prev;

        Node *newNode = new Node(data);
        hook(prevNode, newNode);
        hook(newNode, current);

        ++m_size;
        return Iterator(newNode);
    }

    Iterator remove(Iterator iter)
    {
        /*
            remove:
            Removes the node at 'iter'. Returns an iterator to the element after the one removed.
            - If the list is empty or iter is end(), we throw an exception.
            - If removing the head or tail, update pointers accordingly.
        */
        if (m_size == 0)
            throw std::logic_error("Cannot remove from an empty list");

        if (iter.m_node == nullptr)
            throw std::logic_error("Cannot remove end() iterator");

        Node *nodeToRemove = iter.m_node;
        Node *prevNode = nodeToRemove->m_prev;
        Node *nextNode = nodeToRemove->m_next;

        // If removing the head
        if (nodeToRemove == m_head)
        {
            m_head = nodeToRemove->m_next;
            if (m_head)
                m_head->m_prev = nullptr;
        }
        else
        {
            prevNode->m_next = nextNode;
        }

        // If removing the tail
        if (nodeToRemove == m_tail)
        {
            m_tail = nodeToRemove->m_prev;
            if (m_tail)
                m_tail->m_next = nullptr;
        }
        else
        {
            if (nextNode)
                nextNode->m_prev = prevNode;
        }

        delete nodeToRemove;
        --m_size;

        // Return iterator pointing to the next node in the list (which might be nullptr if we removed the last element)
        return Iterator(nextNode);
    }
};
