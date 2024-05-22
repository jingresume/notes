#include <iostream>
#include "utils/tree.h"

bool isSymmetricalTree(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
    if (pRoot1 == nullptr && pRoot2 == nullptr)
        return true;
    
    if (pRoot1 == nullptr || pRoot2 == nullptr)
        return false;

    if (pRoot1->m_nValue != pRoot2->m_nValue)
        return false;

    return isSymmetricalTree(pRoot1->m_pLeft, pRoot2->m_pRight) 
           && isSymmetricalTree(pRoot1->m_pRight, pRoot2->m_pLeft);
}

bool isSymmetricalTree(BinaryTreeNode* root)
{
    isSymmetricalTree(root, root);
}