/*
* 从尾到头打印链表
*/

#include <stack>
#include <vector>

struct ListNode
{
    int value;
    ListNode* pNext;
};

void ReversePrint(ListNode* pHead)
{
    if (pHead == nullptr) return;

    std::stack<ListNode*> st;
    while (pHead != nullptr)
    {
        st.push(pHead);
        pHead = pHead->pNext;
    }

    while (!st.empty())
    {
        printf("%d ", st.top()->value);
        st.pop();
    }
    printf("\n");
}

void AddToTail(ListNode** pHead, int value)
{
    if (pHead == nullptr) return;

    ListNode* node = new ListNode();
    node->pNext = nullptr;
    node->value = value;

    if (*pHead == nullptr)
    {
        *pHead = node;
    }
    else
    {
        ListNode* curNode = *pHead;
        while (curNode->pNext != nullptr)
            curNode = curNode->pNext;
        curNode->pNext = node;
    }
}

void RemoveNode(ListNode** pHead, int value)
{
    if (pHead == nullptr || *pHead == nullptr)
        return;
    
    ListNode* pToBeDelete = nullptr;

    if ((*pHead)->value == value)
    {
        pToBeDelete = *pHead;
        *pHead = (*pHead)->pNext;
    }
    else
    {
        ListNode* curNode = *pHead;
        while (curNode->pNext != nullptr && curNode->pNext->value == value)
        {
            pToBeDelete = curNode->pNext;
            curNode->pNext = curNode->pNext->pNext;
        }
    }

    if (pToBeDelete != nullptr)
    {
        delete pToBeDelete;
        pToBeDelete = nullptr;
    }
}

//==================测试代码==================

void Test(std::vector<int> nums)
{
    ListNode* pHead = nullptr;
    printf("Input: \n");
    for (int i = 0; i < nums.size(); i++)
    {
        printf("%d ", nums[i]);
        AddToTail(&pHead, nums[i]);
    }
    printf("\nReverse: \n");
    ReversePrint(pHead);
}

void Test1()
{
    std::vector<int> nums{1, 2, 3, 4, 5};
    Test(nums);
}

void Test2()
{
    std::vector<int> nums;
    Test(nums);
}

void Test3()
{
    std::vector<int> nums{1};
    Test(nums);
}

int main()
{
    Test1();
    Test2();
    Test3();
}