#include <iostream>
#include "utils/tree.h"

// pLastNode表示链表当前最末端的节点
// covert(pRoot, nullptr);
void convert(BinaryTreeNode* pRoot, BinaryTreeNode** pLastNode)
{
    if (pRoot == nullptr) return;

    BinaryTreeNode* pCurrentNode = pRoot;

    if (pRoot->m_pLeft != nullptr) convert(pRoot->m_pLeft, pLastNode);

    pCurrentNode->m_pLeft = *pLastNode;

    if (*pLastNode != nullptr) (*pLastNode)->m_pLeft = pCurrentNode;

    *pLastNode = pCurrentNode;

    if (pRoot->m_pRight != nullptr) convert(pRoot->m_pRight, pLastNode);
}