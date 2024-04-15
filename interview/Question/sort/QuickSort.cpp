#include <iostream>
#include <vector>

#include "sort.h"
#include "../utils/log.h"

void Test(std::function<void(std::vector<int>&)> func, const std::string str)
{
    std::vector<std::vector<int>> vv{{1, 3, 2, 5, 4, 0, 8, 7},
                                     {1, 1, 1},
                                    };
    std::vector<std::vector<int>> sortedvv;
    for (const auto& v : vv)
    {
        sortedvv.push_back(v);
        std::sort(sortedvv.back().begin(), sortedvv.back().end());
    }

    std::cout << str << std::endl;
    for (int i = 0; i < vv.size(); i++)
    {
        auto& v       = vv[i];
        auto& sortedV = sortedvv[i];
        bool  ret     = true;

        printVector(v, "input ");
        func(v);
        for (int j = 0; j < v.size(); j++)
        {
            if (v[j] != sortedV[j]) ret = false;
        }
        printVector(v, "output");
        std::cout << str << ": " << (ret ? "Pass" : "Fail") << std::endl;
    }
    std::cout << std::endl;
}

void Test1()
{
    Test(bubbleSort<int>, "bubbleSort");
}

void Test2()
{
    std::vector<int> v1{1, 3, 2, 5, 4, 0, 8, 7};
    std::vector<int> v2{1, 1, 1};
    quickSort(v1, 0, 7);
    quickSort(v2, 0, 2);
    printVector(v1, "quickSort");
    printVector(v2, "quickSort");
}

void Test3()
{
    Test(insertionSort<int>, "insertionSort");
}

int main()
{
    Test1();
    Test3();
    return 0;
}