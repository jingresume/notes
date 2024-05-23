#include <iostream>
#include <thread>

void hello()
{
    std::cout << "Hello Cocurrent World" << std::endl;
    std::cout << "Hardware Concurrency : " << std::thread::hardware_concurrency() << std::endl;
    std::cout << "thread id            : " << std::this_thread::get_id() << std::endl;
}

int main()
{
    std::thread t(hello);
    std::cout << "main thread id       : " << std::this_thread::get_id() << std::endl;
    // 等待子线程结束
    t.join();
    return 0;
}