// 面试题2：实现Singleton模式
// 题目：设计一个类，我们只能生成该类的一个实例。

#include <iostream>

class Singleton
{
public:
    static Singleton& getInstance()
    {
        static Singleton instance;
        return instance;
    }
private:
    Singleton(){}
    Singleton(const Singleton& sin) = delete;
    Singleton& operator= (const Singleton& sin) = delete;
};

void Test()
{
    Singleton& instance1 = Singleton::getInstance();
    Singleton& instance2 = Singleton::getInstance();

    if (&instance1 == &instance2)
        std::cout << "instance1 is same with instance2" << std::endl;
}

int main()
{
    Test();
    return 0;
}