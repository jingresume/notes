/*
* 找出数组中重复的数字
* 在一个长度为n的数组中，所有数字大小都在0～n-1的范围内，
* 数组中有些数字是重复的，请找出数组中任意重复的数字。
*/

#include <iostream>

bool findDupNum(int nums[], int len, int& res)
{
    if (nums == nullptr) return false;

    for (int i = 0; i < len; i++)
        if (nums[i] < 0 || nums[i] >= len) return false;

    for (int i = 0; i < len; i++)
    {
        while (nums[i] != i)
        {
            if (nums[i] == nums[nums[i]])
            {
                res = nums[i];
                return true;
            }
            else
            {
                std::swap(nums[i], nums[nums[i]]);
            }
        }
    }

    return false;
}

void Test()
{
    int test1[5] = {0, 1, 2, 2, 3};
    int test2[8] = {2, 3, 1, 1, 0, 7, 5, 6};
    int res = -1;
    bool bFind = findDupNum(test1, 5, res);
    printf("find1(%d) dup number %d\n", bFind, res);
    res = -1;
    bFind = findDupNum(test2, 8, res);
    printf("find2(%d) dup number %d\n", bFind, res);
}

int main()
{
    Test();
    return 0;
}