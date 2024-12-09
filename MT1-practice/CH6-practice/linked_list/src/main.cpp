#include <iostream>
#include <string>

template <class T>
class Node
{
private:
    Node<T> *m_previous;
    Node<T> *m_next;

public:
    T m_data;
    Node(const T &data, Node<T> *previous = nullptr, Node<T> *next = nullptr); // constructor
    Node(const Node<T> &other_node);                                           // copy constructor
    ~Node();                                                                   // deconstructor
    Node &operator=(const Node<T> &other_node)
    {
        m_data = other_node.m_data;
        m_previous = other_node.m_previous;
        m_next = other_node.m_next;
        return *this;
    };
    void displayNode() const;
    void printAddress() const;

    void insertAfter(Node<T> &inserted_node)
    {
        if (inserted_node.m_previous != nullptr || inserted_node.m_next != nullptr)
        {
            throw std::logic_error("Inserted Node should not be connected to any list");
        }
        Node<T> *temp_next = m_next;
        // Update current node
        m_next = &inserted_node;

        // Update older next_node if exists
        if (temp_next != nullptr)
        {
            (*temp_next).m_previous = &inserted_node;
        }

        // Update inserted node
        inserted_node.m_previous = this;
        inserted_node.m_next = temp_next;
    }
};

template <class T>
Node<T>::Node(const T &data, Node<T> *previous, Node<T> *next) : m_previous(previous), m_next(next), m_data(data){};

template <class T>
Node<T>::~Node(){};

template <class T>
void Node<T>::displayNode() const
{
    std::cout << this << " | " << m_previous << " <" << m_data << "> " << m_next << std::endl;
}

template <class T>
void Node<T>::printAddress() const
{
    std::cout << "Address of the node: " << this << std::endl;
}

void test_code_1()
{
    Node<char> *node_1, *node_2, *node_3;
    node_1 = new Node<char>('B');
    node_2 = new Node<char>('C');
    node_3 = new Node<char>('E');

    node_1->insertAfter(*node_2);
    node_1->insertAfter(*node_3);

    node_1->displayNode();
    node_2->displayNode();
    node_3->displayNode();
    // node_1.printAddress();
}
int main()
{
    test_code_1();
    return 0;
}