/*
* 合并两个排序链表，要求合并后仍然有序
*/

#include <iostream>
#include <utils/list.h>

ListNode* MergeList(ListNode* pHead1, ListNode* pHead2)
{
    if (pHead1 == nullptr) return pHead2;
    if (pHead2 == nullptr) return pHead1;

    ListNode* pMergeNode = nullptr;
    if (pHead1->m_nKey <= pHead2->m_nKey)
    {
        pMergeNode = pHead1;
        pMergeNode->m_pNext = MergeList(pHead1->m_pNext, pHead2);
    }
    else
    {
        pMergeNode = pHead2;
        pMergeNode->m_pNext = MergeList(pHead1, pHead2->m_pNext);
    }

    return pMergeNode;
}