#include <atomic>
#include <iostream>

using std::cout;
using std::endl;

void atomic_flag_test()
{
    std::atomic_flag f = ATOMIC_FLAG_INIT;
    f.clear(std::memory_order_release);
    bool x = f.test_and_set();
    cout << x << endl;
}

int main()
{
    atomic_flag_test();
    return 0;
}