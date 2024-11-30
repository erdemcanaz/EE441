#pragma once

#include <iostream>

template <class T>
class Stack
{
private:
    size_t m_capacity;
    size_t m_size;
    T* m_data;

public:
    Stack() {
		throw std::logic_error("Function \"default constructor\" is not implemented!");
	}
    Stack(size_t capacity)
    {
       throw std::logic_error("Function \"constructor\" is not implemented!");
    }
    ~Stack()
    {
        throw std::logic_error("Function \"destructor\" is not implemented!");
    }

    bool is_empty() const {
        throw std::logic_error("Function \"is_empty\" is not implemented!");
    }

    void clear() {
        throw std::logic_error("Function \"clear\" is not implemented!");
    }

    void reserve(size_t new_capacity)
    {
        throw std::logic_error("Function \"reserve\" is not implemented!");
    }

    void push_back(const T& value)
    {
        throw std::logic_error("Function \"push_back\" is not implemented!");
    }

    T pop_back()
    {   
        throw std::logic_error("Function \"pop_back\" is not implemented!");
    }

    // Friend function to overload << operator for output
    friend std::ostream& operator<<(std::ostream& os, const Stack& stack)
    {
        os << "[ ";
        for (size_t i = 0; i < stack.m_size; ++i) {
            os << stack.m_data[i] << ' ';
        }
        os << ']';
        return os;
    }
};
