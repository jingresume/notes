#ifndef __QUESTION_UTILS_LIST_H
#define __QUESTION_UTILS_LIST_H

#include <iostream>

struct ListNode
{
    int m_nKey;
    ListNode* m_pNext;
};

void PrintList(ListNode* pHead)
{
    while (pHead != nullptr)
    {
        std::cout << pHead->m_nKey << (pHead->m_pNext ? "->" : "\n");
        pHead = pHead->m_pNext;
    }  
}

ListNode* CreateListNode(int val)
{
    ListNode* pNode = new ListNode();
    pNode->m_nKey  = val;
    pNode->m_pNext = nullptr;
    return pNode;
}

void ConnectListNodes(ListNode* pCur, ListNode* pNext)
{
    if (pCur == nullptr)
    {
        std::cout << "Connect Error, pCur is nullptr" << std::endl;
        return;
    }
    pCur->m_pNext = pNext;
}

void DestroyList(ListNode* pHead)
{
    while (pHead != nullptr)
    {
        ListNode* pNext = pHead->m_pNext;
        delete pHead;
        pHead = pNext;
    }
    
}

#endif