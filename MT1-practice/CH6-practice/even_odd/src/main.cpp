#include <iostream>
#include <string>

template <class T>
class Node
{
private:
    Node<T> *m_next;

public:
    T m_data;
    Node(T data = T(), Node<T> *next = nullptr); // default constructor
    void insertAfter(Node<T> *inserted_node);
    Node<T> *deleteAfter();
    Node<T> *breakAfterChain();
    void connectAfterChain(Node<T> *after_chain_header_node);
    Node<T> *getNextNode() const;
    void displayNode() const;
};

template <class T>
Node<T>::Node(T data, Node<T> *next) : m_next(next), m_data(data){};

template <class T>
void Node<T>::insertAfter(Node<T> *inserted_node)
{
    Node<T> *temp_next = m_next;
    m_next = inserted_node;
    inserted_node->m_next = temp_next;
}

template <class T>
Node<T> *Node<T>::deleteAfter()
{
    // no node found after this node
    if (m_next == nullptr)
    {
        return nullptr;
    }

    // update node
    Node<T> *deleted_node = m_next;
    m_next = deleted_node->m_next;
    return deleted_node;
}

template <class T>
Node<T> *Node<T>::breakAfterChain()
{
    // no chain afterwards
    Node<T> *temp_next = m_next;
    if (temp_next == nullptr)
    {
        return nullptr;
    }

    m_next = nullptr;
    return temp_next;
}

template <class T>
void Node<T>::connectAfterChain(Node<T> *after_chain_header_node)
{
    if (m_next != nullptr)
    {
        throw std::logic_error("This node is not the rear of the link");
    }

    m_next = after_chain_header_node;
}
template <class T>
Node<T> *Node<T>::getNextNode() const
{
    return m_next;
}

template <class T>
void print_linked_list(Node<T> *&head)
{
    // assumes header is valid
    size_t counter = 0;
    Node<T> *next_node = head;
    while (true)
    {
        std::cout << "Node: " << counter << " Data:" << next_node->m_data << std::endl;
        if (next_node->getNextNode() == nullptr)
        {
            break;
        }
        counter++;
        next_node = next_node->getNextNode();
    }
    std::cout << std::endl;
}

template <class T>
void Node<T>::displayNode() const
{
    std::cout << m_data << "|" << m_next << std::endl;
}
template <class T>
void arrange_2(Node<T> *&header)
{
    Node<T> *even_list_header_node = nullptr;
    Node<T> *even_list_rear_node = nullptr;
    Node<T> *odd_list_header_node = nullptr;
    Node<T> *odd_list_rear_node = nullptr;

    // iterate list and append even & odd nodes to corresponding linked-lists
    Node<T> *current_node = header;

    while (true)
    {
        Node<T> *temp_next_node = current_node->getNextNode();

        int is_even = (current_node->m_data % 2 == 0) ? 1 : 0;
        if (is_even)
        {
            std::cout << "Even: " << current_node->m_data << std::endl;
            if (even_list_header_node == nullptr)
            {
                even_list_header_node = current_node;
                even_list_rear_node = current_node;
            }
            else
            {
                even_list_rear_node->insertAfter(current_node);
                even_list_rear_node = current_node;
            }
        }
        else
        {
            std::cout << "Odd: " << current_node->m_data << std::endl;
            if (odd_list_header_node == nullptr)
            {
                odd_list_header_node = current_node;
                odd_list_rear_node = current_node;
            }
            else
            {
                odd_list_rear_node->insertAfter(current_node);
                odd_list_rear_node = current_node;
            }
        }

        if (temp_next_node == nullptr)
        {
            break;
        }
        current_node = temp_next_node;
    }

    // disconnect rear nodes and get two seperate lists
    even_list_rear_node->breakAfterChain();
    odd_list_rear_node->breakAfterChain();

    // connet odd and even chains
    even_list_rear_node->connectAfterChain(odd_list_header_node);

    print_linked_list(even_list_header_node);
}

int main()
{
    Node<int> node_1 = Node<int>(12);
    Node<int> node_2 = Node<int>(43);
    Node<int> node_3 = Node<int>(36);
    Node<int> node_4 = Node<int>(3);
    Node<int> node_5 = Node<int>(90);
    Node<int> node_6 = Node<int>(14);
    Node<int> node_7 = Node<int>(2);
    Node<int> node_8 = Node<int>(67);

    node_1.insertAfter(&node_2);
    node_2.insertAfter(&node_3);
    node_3.insertAfter(&node_4);
    node_4.insertAfter(&node_5);
    node_5.insertAfter(&node_6);
    node_6.insertAfter(&node_7);
    node_7.insertAfter(&node_8);

    node_8.displayNode();
    std::cout << "Before arranging the linked list" << std::endl;
    Node<int> *head = &node_1;
    print_linked_list<int>(head);

    arrange_2(head);
    return 0;
}