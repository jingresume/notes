#ifndef __INC_UTILS_H
#define __INC_UTILS_H

#include <thread>

class thread_guard
{
public:
    explicit thread_guard(std::thread& _t) : t(_t) {}

    ~thread_guard()
    {
        if (t.joinable())
        {
            t.join();
        }
    }

    thread_guard(const thread_guard&) = delete;
    thread_guard& operator=(const thread_guard&) = delete;

private:
    std::thread& t;
};

#endif