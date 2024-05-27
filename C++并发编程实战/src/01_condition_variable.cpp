#include <iostream>
#include <thread>
#include <queue>
#include <condition_variable>
#include <chrono>

std::mutex mut;
std::condition_variable cv;
std::queue<int> q;

void data_prepare_thread()
{
    int k = 10;
    while (k >= 0)
    {
        {
            std::lock_guard<std::mutex> lk(mut);
            q.push(k);
        }
        // 解锁后再通知，避免data_process_thread线程被唤醒后，还需要等待mut解锁
        cv.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        k--;
    }
}

void data_process_thread()
{
    while (true)
    {
        std::unique_lock<std::mutex> lk(mut);
        cv.wait(lk, [](){
            return !q.empty();
        });
        int data = q.front();
        q.pop();
        // 离开临界区后立刻解锁
        lk.unlock();
        std::cout << data << std::endl;
        if (data == 0) break;
    }
}

int main()
{
    std::thread t1(data_process_thread);
    std::thread t2(data_prepare_thread);
    t1.join();
    t2.join();
    return 0;
}