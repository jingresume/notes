#ifndef __QUESTION_SORT_SORT_H
#define __QUESTION_SORT_SORT_H

#include <vector>

template <typename T>
void bubbleSort(std::vector<T>& nums)
{
    int n = nums.size();
    for (int i = 0; i < n - 1; i++)
    {
        bool bSwapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (nums[j] > nums[j + 1])
            {
                std::swap(nums[j], nums[j + 1]);
                bSwapped = true;
            }
        }
        if (!bSwapped) break;
    }
    return;
}

template <typename T>
void quickSort(std::vector<T>& q, int l, int r)
{
    if (l >= r) return;

    int x = q[(l + r) >> 1];
    int i = l - 1, j = r + 1;
    while (i < j)
    {
        // do while 而不是 while do
        // 考虑全部相等的数组
        do i++; while (q[i] < x);
        do j--; while (q[j] > x);
        if (i < j) std::swap(q[i], q[j]);
    }

    quickSort(q, l, j);
    quickSort(q, j + 1, r);
}

template <typename T>
void insertionSort(std::vector<T>& nums)
{
    int n = nums.size();
    for (int i = 1; i < n; i++)
    {
        T key = nums[i];
        int j = i - 1;
        while (j >= 0 && nums[j] > key)
        {
            nums[j + 1] = nums[j];
            j--;
        }
        nums[j + 1] = key;
    }
}

#endif
