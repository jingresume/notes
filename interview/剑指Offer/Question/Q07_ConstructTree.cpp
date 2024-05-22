/*
* 输入某二叉树等前序遍历和中序遍历，请重建该二叉树
* 假设树中没有重复的数字
*/

#include <iostream>

struct BinaryTreeNode
{
    int value;
    BinaryTreeNode* pLeft;
    BinaryTreeNode* pRight;
};

BinaryTreeNode* ConstructTree(int preOrder[], int inOrder[], int len)
{
    if (preOrder == nullptr || inOrder == nullptr || len <= 0)
        return nullptr;
    
    BinaryTreeNode* root = new BinaryTreeNode();
    root->value = preOrder[0];

    if (len != 1)
    {
        int rootIdx = 0;
        while(rootIdx < len && inOrder[rootIdx] != root->value)
            rootIdx++;
        
        int leftLen = rootIdx, rightLen = len - rootIdx - 1;
        if (leftLen) root->pLeft = ConstructTree(preOrder + 1, inOrder, leftLen);
        if (rightLen) root->pRight = ConstructTree(preOrder + leftLen + 1, inOrder + leftLen + 1, rightLen);
    }

    return root;
}

void PrintTreeNode(const BinaryTreeNode* pNode)
{
    if(pNode != nullptr)
    {
        printf("value of this node is: %d\n", pNode->value);

        if(pNode->pLeft != nullptr)
            printf("value of its left child is: %d.\n", pNode->pLeft->value);
        else
            printf("left child is nullptr.\n");

        if(pNode->pRight != nullptr)
            printf("value of its right child is: %d.\n", pNode->pRight->value);
        else
            printf("right child is nullptr.\n");
    }
    else
    {
        printf("this node is nullptr.\n");
    }

    printf("\n");
}

void PrintTree(const BinaryTreeNode* pRoot)
{
    PrintTreeNode(pRoot);

    if(pRoot != nullptr)
    {
        if(pRoot->pLeft != nullptr)
            PrintTree(pRoot->pLeft);

        if(pRoot->pRight != nullptr)
            PrintTree(pRoot->pRight);
    }
}

// ====================测试代码====================
void Test(const char* testName, int* preorder, int* inorder, int length)
{
    if(testName != nullptr)
        printf("%s begins:\n", testName);

    printf("The preorder sequence is: ");
    for(int i = 0; i < length; ++ i)
        printf("%d ", preorder[i]);
    printf("\n");

    printf("The inorder sequence is: ");
    for(int i = 0; i < length; ++ i)
        printf("%d ", inorder[i]);
    printf("\n");


    BinaryTreeNode* root = ConstructTree(preorder, inorder, length);
    PrintTree(root);
    //DestroyTree(root);
}

// 普通二叉树
//              1
//           /     \
//          2       3  
//         /       / \
//        4       5   6
//         \         /
//          7       8
void Test1()
{
    const int length = 8;
    int preorder[length] = {1, 2, 4, 7, 3, 5, 6, 8};
    int inorder[length] = {4, 7, 2, 1, 5, 3, 8, 6};

    Test("Test1", preorder, inorder, length);
}

// 所有结点都没有右子结点
//            1
//           / 
//          2   
//         / 
//        3 
//       /
//      4
//     /
//    5
void Test2()
{
    const int length = 5;
    int preorder[length] = {1, 2, 3, 4, 5};
    int inorder[length] = {5, 4, 3, 2, 1};

    Test("Test2", preorder, inorder, length);
}

// 所有结点都没有左子结点
//            1
//             \ 
//              2   
//               \ 
//                3 
//                 \
//                  4
//                   \
//                    5
void Test3()
{
    const int length = 5;
    int preorder[length] = {1, 2, 3, 4, 5};
    int inorder[length] = {1, 2, 3, 4, 5};

    Test("Test3", preorder, inorder, length);
}

// 树中只有一个结点
void Test4()
{
    const int length = 1;
    int preorder[length] = {1};
    int inorder[length] = {1};

    Test("Test4", preorder, inorder, length);
}

// 完全二叉树
//              1
//           /     \
//          2       3  
//         / \     / \
//        4   5   6   7
void Test5()
{
    const int length = 7;
    int preorder[length] = {1, 2, 4, 5, 3, 6, 7};
    int inorder[length] = {4, 2, 5, 1, 6, 3, 7};

    Test("Test5", preorder, inorder, length);
}

// 输入空指针
void Test6()
{
    Test("Test6", nullptr, nullptr, 0);
}

// 输入的两个序列不匹配
void Test7()
{
    const int length = 7;
    int preorder[length] = {1, 2, 4, 5, 3, 6, 7};
    int inorder[length] = {4, 2, 8, 1, 6, 3, 7};

    Test("Test7: for unmatched input", preorder, inorder, length);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
    
    return 0;
}