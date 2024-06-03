#include <chrono>
#include <iostream>

using namespace std::chrono_literals;
int main()
{
    // 10ms
    std::chrono::duration<double, std::ratio<1, 1000>> ms1(10);
    // 20ms
    std::chrono::milliseconds ms2(20);

    auto one_min = 1min;

    return 0;
}