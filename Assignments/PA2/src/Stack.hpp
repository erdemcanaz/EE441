#pragma once

#include <iostream>

template <class T>
class Stack
{
private:
    size_t m_capacity; // Default:0        | Stacks current capacity
    size_t m_size;     // Default:0          | Number of elements in the stack currently
    T *m_data;         // Default:nullptr    | Pointer to the allocated memory for the stack of templated type

public:
    // Default constructor
    Stack() : m_capacity(0), m_size(0), m_data(nullptr)
    {
        // Initialize m_capacity with a default value (e.g., 0)
        // Initialize m_size with a default value (e.g., 0)
        // Initialize m_data with a default value (e.g., nullptr)
    }
    // Parameterized constructor
    Stack(size_t capacity) : m_capacity(capacity), m_size(0), m_data(new T[capacity])
    {
        // Initialize m_capacity with the given capacity
        // Initialize m_size with a default value (e.g., 0) since the stack is empty
        // Allocate memory for m_data with the given capacity
    }
    // Destructor
    ~Stack()
    {
        delete[] m_data;  //  deallocate memory for m_data
        m_data = nullptr; // set m_data to nullptr to avoid dangling pointers
    }

    bool is_empty() const
    {
        //(OPTIONAL) Check if memory is allocated for the stack, if not throw an error
        // if (m_data == nullptr)
        // {
        //     throw std::logic_error("Invalid stack: One cannot check if an uninitialized stack is empty.");
        // };

        // Check if the stack is empty
        return m_size == 0;
    }

    void clear()
    {
        // Deallocate memory for m_data
        delete[] m_data;

        // Reset the member variables
        m_capacity = 0;
        m_size = 0;
        m_data = nullptr;
    }

    void reserve(size_t new_capacity)
    {
        // Claim new memory from the heap of the size_of(T) * new_capacity
        T *new_data = new T[new_capacity];

        // if the new capacity is less than the current number of elements, only copy the elements that fit
        size_t number_of_elements_to_copy = (new_capacity < m_size) ? new_capacity : m_size;

        // Copy the elements from the old memory to the new memory
        for (size_t i = 0; i < number_of_elements_to_copy; ++i)
        {
            new_data[i] = m_data[i]; // Deep copy the elements where values are the same but memory addresses are different
        };

        // Deallocate the old memory
        delete[] m_data;

        // Update the member variables
        m_data = new_data;
        m_capacity = new_capacity;
        m_size = number_of_elements_to_copy;
    }

    void push_back(const T &value)
    {
        // check if the stack is full
        if (m_size == m_capacity)
        {
            // if the stack is full, double the capacity
            size_t new_doubled_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
            reserve(new_doubled_capacity); // Keep the old elements and double the capacity
        };

        // Add the value as the last element of the stack, and increment the element count
        m_data[m_size] = value;
        m_size++;
    }

    T pop_back()
    {
        if (is_empty())
        {
            throw std::out_of_range("Invalid operation: Cannot pop from an empty stack.");
        };

        T popped_value = m_data[m_size - 1]; // Get the last element of the stack and deep copy it to popped_value (pass by value)
        m_size--;                            // Decrement the element count
        return popped_value;                 // Return the popped value
    }

    // Friend function to overload << operator for output
    friend std::ostream &operator<<(std::ostream &os, const Stack &stack)
    {
        os << "[ ";
        for (size_t i = 0; i < stack.m_size; ++i)
        {
            os << stack.m_data[i] << ' ';
        }
        os << ']';
        return os;
    }
};

void __test_stack_class()
{
    std::cout << "\n\n--- Stack Class Tests ---" << std::endl;

    // Create Tile objects
    Tile tile_1('B', 1);
    Tile tile_2('C', 2);
    Tile tile_3('D', 3);

    // Create a Stack of Tile objects
    Stack<Tile> tile_stack;
    std::cout << "Created an empty Stack<Tile>. (Default)" << std::endl;

    // Test is_empty on empty stack
    std::cout << "Tile stack is empty: " << (tile_stack.is_empty() ? "Yes" : "No") << std::endl;

    // Push Tile objects onto the stack
    tile_stack.push_back(tile_1);
    tile_stack.push_back(tile_2);
    tile_stack.push_back(tile_3);
    std::cout << "After pushing tile_1, tile_2, tile_3: " << tile_stack << std::endl;

    // Test is_empty on non-empty stack
    std::cout << "Tile stack is empty: " << (tile_stack.is_empty() ? "Yes" : "No") << std::endl;

    // Pop a Tile object from the stack
    Tile popped_tile = tile_stack.pop_back();
    std::cout << "Popped tile: " << popped_tile << std::endl;
    std::cout << "Tile stack after pop_back: " << tile_stack << std::endl;

    // Reserve additional capacity
    tile_stack.reserve(5);
    std::cout << "After reserving capacity of 5: " << tile_stack << std::endl;

    // Push more Tile objects
    Tile tile_4('B', 4);
    Tile tile_5('C', 2);
    tile_stack.push_back(tile_4);
    tile_stack.push_back(tile_5);
    std::cout << "After pushing tile_4, tile_5: " << tile_stack << std::endl;

    // Clear the stack
    tile_stack.clear();
    std::cout << "After clearing the tile stack: " << tile_stack << std::endl;

    // Test exception handling for pop_back on empty stack
    try
    {
        tile_stack.pop_back();
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception caught (as expected): " << e.what() << std::endl;
    };
}