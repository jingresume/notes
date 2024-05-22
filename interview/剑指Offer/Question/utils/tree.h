#ifndef __QUESTION_UTILS_TREE_H
#define __QUESTION_UTILS_TREE_H

#include <iostream>

struct BinaryTreeNode
{
    int m_nValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
};

BinaryTreeNode* CreateBinaryTreeNode(int val)
{
    BinaryTreeNode* pNode = new BinaryTreeNode();
    pNode->m_nValue = val;
    pNode->m_pLeft  = nullptr;
    pNode->m_pRight = nullptr;

    return pNode;
}

void ConnectTreeNodes(BinaryTreeNode* pParent, BinaryTreeNode* pLeft, BinaryTreeNode* pRight)
{
    if (pParent == nullptr)
    {
        std::cout << "Connect Error pParent is nullptr" << std::endl;
        return;
    }
    pParent->m_pLeft  = pLeft;
    pParent->m_pRight = pRight;
}

void DestroyTree(BinaryTreeNode* pRoot)
{
    if (pRoot != nullptr)
    {
        DestroyTree(pRoot->m_pLeft);
        DestroyTree(pRoot->m_pRight);

        delete pRoot;
        pRoot = nullptr;
    }
}

void PrintTreeNode(BinaryTreeNode* pNode)
{
    if (pNode != nullptr)
    {
        printf("value of this node is: %d\n", pNode->m_nValue);

        if (pNode->m_pLeft != nullptr)
            printf("value of its left child is: %d\n", pNode->m_pLeft->m_nValue);
        else
            printf("left child is nullptr\n");
        
        if (pNode->m_pRight != nullptr)
            printf("value of its right child is: %d\n", pNode->m_pRight->m_nValue);
        else
            printf("right child is nullptr\n");
    }
    else
    {
        printf("this node is nullptr\n");
    }
}

void PrintTree(BinaryTreeNode* pRoot)
{
    PrintTreeNode(pRoot);
    if (pRoot != nullptr)
    {
        if (pRoot->m_pLeft != nullptr) PrintTree(pRoot->m_pLeft);
        if (pRoot->m_pRight != nullptr) PrintTree(pRoot->m_pRight);
    }
}

#endif