/*
* 在一个长度为n + 1的数组里，所有数字都在1～n的范围，所以数组中至少有一个数字是重复的  
*  请找出数组中的任意一个重复数字，但不能修改数组
*/

#include <iostream>

int countRange(int left, int right, int nums[], int len)
{
    if (nums == nullptr) return 0;
    int ret = 0;
    for (int i = 0; i < len; i++)
        if (nums[i] >= left && nums[i] <= right) ret++;
    return ret;
}

// 这是一种时间O(nlogn)，空间O(1)的做法
// 实际上使用hash表更简单快速，但是O(n)
bool findDupNum(int nums[], int len, int& res)
{
    if (nums == nullptr) return false;
    
    for (int i = 0; i < len; i++)
        if (nums[i] < 1 || nums[i] > (len - 1)) return false;
    
    // 二分
    int left = 1, right = len - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        int cnt = countRange(left, mid, nums, len);
        if (left == right)
        {
            if (cnt > 1)
            {
                res = left;
                return true;
            }
            else
            {
                break;
            }
        }
        if (cnt > (mid - left + 1))
        {
            right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }
    return false;
}

void Test()
{
    int test1[5] = {1, 2, 2, 3, 4};
    int test2[8] = {3, 4, 7, 2, 5, 1, 3, 6};
    bool bFind = false;
    int  res   = -1;
    bFind = findDupNum(test1, 5, res);
    printf("find(%d) res = %d\n", bFind, res);
    res = -1;
    bFind = findDupNum(test2, 8, res);
    printf("find(%d) res = %d\n", bFind, res);
}

int main()
{
    Test();
    return 0;
}