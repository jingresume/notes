#include <atomic>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <assert.h>

using std::cout;
using std::endl;

std::atomic<bool> x, y;
std::atomic<int> z;

void write_x()
{
    x.store(true, std::memory_order_seq_cst);
}

void write_y()
{
    y.store(true, std::memory_order_seq_cst);
}

void read_x_then_y()
{
    while (!x.load(std::memory_order_seq_cst));
    if (y.load(std::memory_order_seq_cst))
        ++z;
}

void read_y_then_x()
{
    while (!y.load(std::memory_order_seq_cst));
    if (x.load(std::memory_order_seq_cst))
        ++z;
}

void cst_order_test()
{
    x = false;
    y = false;
    z = 0;
    std::thread a(read_x_then_y);
    std::thread b(read_y_then_x);
    std::thread c(write_x);
    std::thread d(write_y);
    a.join(), b.join(), c.join(), d.join();
    cout << "[cst order]z: " << z << endl;
    assert(z.load() != 0);
}

void write_x_then_y_relaxed()
{
    x.store(true, std::memory_order_relaxed);
    y.store(true, std::memory_order_relaxed);
}

void read_y_then_x_relaxed()
{
    while (!y.load(std::memory_order_relaxed));
    if (x.load(std::memory_order_relaxed))
        ++z;
}

void relaxed_order_test()
{
    x = false;
    y = false;
    z = 0;

    std::thread a(read_y_then_x_relaxed);
    std::thread b(write_x_then_y_relaxed);
    a.join(), b.join();
    cout << "[relaxed order]z: " << z << endl;
    assert(z.load() != 0);
}

void atomic_flag_test()
{
    std::atomic_flag f = ATOMIC_FLAG_INIT;
    f.clear(std::memory_order_release);
    bool x = f.test_and_set();
    cout << x << endl;
}

void atomic_bool_test()
{
    std::atomic<bool> b(false);
    cout << "atomic<bool> is lock free :" << b.is_lock_free() << endl;
    std::atomic<int*> pi(nullptr);
    cout << "atomic<int*> is lock free :" << pi.is_lock_free() << endl;
    // 不支持string、vector，因为其不具备trivailly copy
    /*
    std::atomic<std::string> str;
    cout << "atomic<string> is lock free :" << str.is_lock_free() << endl;
    */
}

int main()
{
    cout << "==========atomic flag test==========" << endl;
    atomic_flag_test();
    cout << "==========atomic bool test==========" << endl;
    atomic_bool_test();
    cout << "==========memory order test=========" << endl;
    int cnt = 1;
    while (cnt--) cst_order_test();
    cnt = 10000;
    while (cnt--) relaxed_order_test();
    return 0;
}