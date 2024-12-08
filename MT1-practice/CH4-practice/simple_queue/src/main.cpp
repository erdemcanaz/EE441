#include <iostream>
#include <string>

//-------------------------------------------------------
template <class T>
T getMax(T a, T b)
{
    T result;
    result = (a > b) ? a : b;
    return result;
}
void template_function_test()
{
    int a = 5;
    int b = 10;
    int c = getMax<int>(a, b);
    std::cout << c << std::endl;
}

//-------------------------------------------------------
const int MaxStackSize = 50;
template <class T>
class Stack
{
private:
    T stacklist[MaxStackSize];
    int top; // Index of the top item. -1 for empty array.

public:
    Stack()
    {
        top = -1;
    };

    void Push(const T &item)
    {
        if (top == MaxStackSize - 1)
        {
            throw std::logic_error("Stack is full");
        }
        top++;
        stacklist[top] = item;
    };

    T Pop()
    {
        if (top == -1)
        {
            throw std::logic_error("Nothing to pop");
        }
        T temp;
        temp = stacklist[top];
        top--;
        return temp;
    };

    void ClearStack()
    {
        top = -1;
    };

    T Peek() const
    {
        T temp;
        if (top == -1)
        {
            throw std::logic_error("Nothing to peek");
        }
        temp = stacklist[top];
        return temp;
    };

    int IsStackEmpty() const
    {
        if (top == -1)
        {
            return 1;
        }
        return 0;
    };
    int IsStackFull() const
    {
        if (top == MaxStackSize - 1)
        {
            return 1;
        }
        return 0;
    };
};

void CheckIfPalindrome(std::string &s)
{
    std::cout << "\n\nChecking for palindrome..." << std::endl;
    Stack<char> stack = Stack<char>();
    for (uint8_t i = 0; i < 255; i++)
    {
        if (s[i] == '\0')
            break;
        stack.Push(s[i]);
    };

    for (uint8_t i = 0; i < 255; i++)
    {
        if (stack.IsStackEmpty())
        {
            std::cout << s << " is a palindrome";
            break;
        };

        if (stack.Pop() == s[i])
        {
            std::cout << (int)i << " : " << s[i] << std::endl;
        }
        else
        {
            std::cout << s << " is not a palindrome";
            break;
        }
    };
}

int main()
{
    // template_function_test();

    std::string palindrome = "kabak";
    std::string not_palindrome = "erdem";

    CheckIfPalindrome(palindrome);
    CheckIfPalindrome(not_palindrome);

    Stack<char> *sp;
    Stack<char> char_stack = Stack<char>();
    sp = &char_stack;
    return 0;
}