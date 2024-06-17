#include <thread>
#include <future>
#include <string>
#include <iostream>
#include <latch>
#include <barrier>
#include <sstream>
/*
#include <experimental/algorithm>
#include <experimental/filesystem>
#include <experimental/future>


std::experimental::future<int> find_the_answer();
std::string find_the_question(std::experimental::future<int> ans);

int main()
{
    auto fut  = find_the_answer();
    auto fut2 = fut.then(find_the_question);
    return 0;
}

*/

void latchTest()
{
    unsigned int threadCnt = 10;
    std::latch done(threadCnt);
    std::vector<std::string> data(10);
    std::vector<std::future<void>> threads;

    for (int i = 0; i < threadCnt; i++)
    {
        threads.push_back(std::async(std::launch::async, [&, i]{
            std::ostringstream oss;
            oss << "new data: " << i;
            data[i] = oss.str();
            done.count_down();
            std::cout << "thread" << i << " process done" << std::endl;
        }));
    }

    done.wait();
    for (int i = 0; i < threadCnt; i++)
    {
        std::cout << data[i] << std::endl;
    }
}

void barrierTest()
{
    const unsigned int threadCnt = 10;
    std::barrier sync(threadCnt);
    std::vector<std::string> data(threadCnt);
    std::vector<std::future<void>> threads;
    int cnt = 10;
    for (int i = 0; i < threadCnt; i++)
    {
        threads.push_back(std::async(std::launch::async, [&, i]{
            int cnt = 2;
            while (cnt--)
            {
                std::ostringstream oss;
                oss << "new data: " << i + cnt;
                data[i] = oss.str();
                // 等待所有数据准备好
                sync.arrive_and_wait();
                // 串形区域
                if (i == 0)
                {
                    std::cout << "==========loop" << cnt << "==========" << std::endl;
                    for (int j = 0; j < threadCnt; j++)
                    {
                        std::cout << data[j] << std::endl;
                    }
                }
                // 所有线程等待串形区域执行完成
                sync.arrive_and_wait();
            }
        }));
    }
}
 
int main() {
    std::cout << "C++ compiler version is " << __cplusplus << std::endl;
    std::cout << "========latch test start=========" << std::endl;
    latchTest();
    std::cout << "========barrier test start=======" << std::endl;
    barrierTest();
    return 0;
}
