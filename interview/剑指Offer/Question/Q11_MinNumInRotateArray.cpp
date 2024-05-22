/*
* 将一个递增的有序数组，末尾任意个元素移动到数组起始处，这样的数组称为旋转数组
* 例如 [1 2 3 4 5] 的任意一个旋转数组可能是 [4 5 1 2 3]
* 如何快速找到旋转数组的最小值？
*/
#include <iostream>
#include <vector>

int MinInOrder(const std::vector<int>& nums, int start, int end);

int Min(const std::vector<int>& nums)
{
    int start = 0, end = nums.size() - 1;
    int mid = start;
    
    while (start < end)
    {
        if (end - start == 1)
        {
            mid = end;
            break;
        }

        mid = (start + end) >> 1;
        
        // special case，无法二分查找
        if (nums[mid] == nums[start] && nums[start] == nums[end])
            return MinInOrder(nums, start, end);
        
        if (nums[mid] >= nums[start])
            start = mid;
        else if ( nums[mid] <= nums[end])
            end = mid;
    }

    return nums[mid];
}

int MinInOrder(const std::vector<int>& nums, int start, int end)
{
    int ret = nums[start];
    for (int i = start; i <= end; i++)
        ret = std::min(ret, nums[i]);
    return ret;
}

// ====================测试代码====================
void Test(const std::vector<int>& numbers ,int expected)
{
    int result = 0;
    result = Min(numbers);

    for(int i = 0; i < numbers.size(); ++i)
        printf("%d ", numbers[i]);

    if(result == expected)
        printf("\tpassed\n");
    else
        printf("\tfailed\n");
}

int main(int argc, char* argv[])
{
    // 典型输入，单调升序的数组的一个旋转
    std::vector<int> array1{ 3, 4, 5, 1, 2 };
    Test(array1, 1);

    // 有重复数字，并且重复的数字刚好的最小的数字
    std::vector<int> array2 { 3, 4, 5, 1, 1, 2 };
    Test(array2, 1);

    // 有重复数字，但重复的数字不是第一个数字和最后一个数字
    std::vector<int> array3{ 3, 4, 5, 1, 2, 2 };
    Test(array3, 1);

    // 有重复的数字，并且重复的数字刚好是第一个数字和最后一个数字
    std::vector<int> array4{1, 0, 1, 1, 1 };
    Test(array4, 0);

    // 单调升序数组，旋转0个元素，也就是单调升序数组本身
    std::vector<int> array5{ 1, 2, 3, 4, 5 };
    Test(array5, 1);

    // 数组中只有一个数字
    std::vector<int> array6{ 2 };
    Test(array6, 2);

    return 0;
}