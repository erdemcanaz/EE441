#include <iostream>
#include <string>

const int MAX_Q_SIZE = 50;
template <class T>
class Queue
{
private:
    int front; // Index of the next item to be delivered
    int rear;  // Index where next item will be added
    int count; // Number of items in the queue
    T qlist[MAX_Q_SIZE];

public:
    Queue();
    void Qinsert(const T &item);
    T Qdelete();         // Get and delete next item
    T Qpeek() const;     // Get next item
    void ClearQueue();   // Reset queue
    int Qlength() const; // Get the number of items
    int Qempty() const;  // Check if queue is empty
    int Qfull() const;   //  Check if queue is full
};

template <class T>
Queue<T>::Queue() : front(0), rear(0), count(0){};

template <class T>
void Queue<T>::Qinsert(const T &item)
{
    if (count == MAX_Q_SIZE - 1)
    {
        throw std::logic_error("Queue is full");
    }
    qlist[rear] = item;
    count++;
    rear = (rear + 1) % MAX_Q_SIZE;
}

template <class T>
T Queue<T>::Qdelete()
{
    if (count == 0)
    {
        throw std::logic_error("Queue is empty");
    }
    T temp = qlist[front];
    front = (front + 1) % MAX_Q_SIZE;
    count--;
    return temp;
}

template <class T>
T Queue<T>::Qpeek() const
{
    T temp;
    if (count == 0)
    {
        throw std::logic_error("No item in the queue");
    }
    temp = qlist[front];
    return temp;
}

template <class T>
void Queue<T>::ClearQueue()
{
    front = 0;
    rear = 0;
    count = 0;
}

template <class T>
int Queue<T>::Qlength() const
{
    return count;
}

template <class T>
int Queue<T>::Qempty() const
{
    if (count == 0)
    {
        return 1;
    }
    return 0;
}

template <class T>
int Queue<T>::Qfull() const
{
    if (count == MAX_Q_SIZE - 1)
    {
        return 1;
    }
    return 0;
}
int main()
{
    Queue<char> test_queue = Queue<char>();
    std::string test_string = "Erdem Buraya Gel";
    for (uint8_t i = 0; i < 255; i++)
    {
        if (test_string[i] == '\0')
        {
            break;
        }
        test_queue.Qinsert(test_string[i]);
    }

    while (test_queue.Qempty() != 1)
    {
        std::cout << test_queue.Qdelete() << std::endl;
    }
    return 0;
}