#include <iostream>
#include <thread>

void hello()
{
    std::cout << "Hello Cocurrent World" << std::endl;
}

int main()
{
    std::thread t(hello);
    // 等待子线程结束
    t.join();
    return 0;
}