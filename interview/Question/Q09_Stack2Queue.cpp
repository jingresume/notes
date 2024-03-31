/*
* 两个栈实现队列
*/

#include <iostream>
#include <stack>

template <typename T>
class CQueue
{
public:
    CQueue();
    ~CQueue();

    void push(const T& val);
    T pop();

private:
    std::stack<T> st1, st2;
};

template <typename T>
CQueue<T>::CQueue()
{

}

template <typename T>
CQueue<T>::~CQueue()
{

}

template <typename T>
void CQueue<T>::push(const T& val)
{
    st1.push(val);
}

template <typename T>
T CQueue<T>::pop()
{
    if (st2.empty())
    {
        while (!st1.empty())
        {
            st2.push(st1.top());
            st1.pop();
        }
    }

    T head = st2.top();
    st2.pop();
    return head;
}

// ====================测试代码====================
void Test(char actual, char expected)
{
    if(actual == expected)
        printf("Test passed.\n");
    else
        printf("Test failed.\n");
}

int main(int argc, char* argv[])
{
    CQueue<char> queue;

    queue.push('a');
    queue.push('b');
    queue.push('c');

    char head = queue.pop();
    Test(head, 'a');

    head = queue.pop();
    Test(head, 'b');

    queue.push('d');
    head = queue.pop();
    Test(head, 'c');

    queue.push('e');
    head = queue.pop();
    Test(head, 'd');

    head = queue.pop();
    Test(head, 'e');

    return 0;
}