# 剑指Offer

## 第三章 高质量的代码

### 代码的规范性

+ 清晰的布局：缩进
+ 合理的命名：命名能够看出函数和变量的意图

### 代码的完整性

从三个方面保证代码的完整性：  

1. 功能测试：是否完成基本功能
2. 边界测试：输入边界值（最大值、最小值等）是否能得到正确输出
3. 负面测试：是否对非法输入，做出合理的错误处理

三种错误处理的方式：  

1. 返回值：通过返回值判断函数处理是否出错，最大的问题是使用不便，无法将函数计算结果通过返回值返回。
2. 当错误发生时，设置一个全局变量：调用者很容易忘记检查全局变量。
3. 抛出异常：与旧代码不兼容，对性能有负面影响。

+ Q16 数值的整数次方
`double Power(double base, int exp)`  
a. 需要注意指数是零或负数的情况
b. 输入无效时如何处理(0, -1)
c. 效率上考虑使用[快速幂](https://oi-wiki.org/math/binary-exponentiation/)  
例如：`3^13 = 3^(1101) = 3^8 * 3^4 * 3^1`

```C++
long long binPow(long long a, long long b)
{
    long long res = 1;
    while (b > 0)
    {
        if (b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}
```

+ Q17 打印从1到最大n位数

> 例如`n = 3`，则打印从1到999  

a. 考虑n的取值范围，如果n很大，那么无法用整型直接表示，需要使用字符串or数组来表示大数。  

+ Q18 删除链表的节点

> `void DeleteNode(ListNode** pListHead, ListNode* pToBeDeleted);`  
> O(1)时间内完成

a. 一般情况下删除链表中的node，我们需要遍历链表，并找到该node的前一个节点，所以需要O(n)的时间  
b. 但是这里直接给出了要删除的node：`pToBeDeleted`，所以可以将其下一个节点的内容复制到该节点，然后删除下一个节点。  
c. **需要额外考虑删除头节点和尾节点的情况**，对于尾节点，我们仍然需要采用遍历到方式找到上一个节点进行删除，对于只有一个节点的链表的头节点，我们需要在删除后，将头节点设置为nullptr
d. 如果头节点有可能被修改，那头节点的参数就要被设置为指针的指针

+ Q19 正则表达式匹配

> 检查一个模式串和字符串的正则匹配  
  模式串中包含两种模式字符：`.`表示匹配一个任意字符，`*`表示它前面的字符可以出现任意次（包括0次）  
  `bool match(char* str, char* pattern)`

重点是`*`的匹配，分为两种情况：  
a. 当*前面的字符与字符串中的字符不匹配时，我们直接跳过。
b. 当*前面的字符与字符串中的字符匹配时，我们可以选择跳过、匹配一次、匹配n次，只要这些选择中后续的匹配有一种能匹配成功就可以，所以这里是一个dfs搜索的过程。

+ Q20 表示数值的字符串

> 判断字符串是否表示一个数值

a. 将字符串分为整数部分、小数部分、指数部分  
b. 整数部分可以是正数、负数、或者空，整数和小数的分界为小数点  
c. 小数部分只能是正数或者空，小数和指数的分界点为`e`  
d. 指数部分可以是正数、或者负数，但是不能只有指数部分  
逐个部分检查即可.

+ Q21 调整数组顺序使奇数位于偶数前面

a. 双指针，指针a指向数组开头，指针b指向数组结尾 b. 移动指针a，直到a指向一个偶数。  
c. 移动指针b，直到b指向一个奇数。  
d. 交换指针a\b的内容，并重复上述操作直到两个指针相遇  

### 代码的鲁棒性

程序能够判断输入是否合乎规范，并对不符合要求的输入做合理的处理。

+ Q22 链表中倒数第K个节点

快慢指针：  
a. 定义两个指针，第一个指针先走k-1步
b. 然后两个指针同时走，当第一个指针走到尾节点时，第二个指针刚好指向倒数第k个节点

考虑不合法的输入：  
a. 输入链表为空  
b. 链表中没有k个节点  
c. k = 0时，倒数第0个节点是没有意义的，最后一个节点是倒数第一个节点  

举一反三：  
> 求链表的中间节点  

同样可以使用快慢指针，a指针一次走两步，b指针一次走一步，当a指针指向尾节点时，b指针刚好指向中间节点

+ Q23 链表中环的入口节点

a. 如何确定链表中有环：  
快慢指针：快指针一次走两步，慢指针一次走一步，如果快指针追上了慢指针，说明链表中有环  

b. 如何确定环包含的节点数：  
当快慢指针相遇时，相遇的节点一定是在环中的，从这个节点开始计数，继续遍历，当再一次回到相遇节点时，我们就能得到环中的节点数  

c. 如何找到环的入口：  
考虑两个指针a、b，a先走n步，n等于环中的节点数，当a、b相遇时，即为环的入口。

+ [Q24 反转链表](./Question/Q24_ReverseList.cpp)

由于反转的过程中，链表需要将当前节点的next指针指向前一个节点，所以这里我们需要三个指针记录：  
pPrev : 前一个节点，pNode : 当前节点，pNext : 下一个节点  
当pNext为空时，说明时最后一个节点，也就是反转后的头节点  

```C++
ListNode* ReverseList(ListNode* pHead)
{
    ListNode* res = nullptr;
    ListNode* pNode = pHead;
    ListNode* pPrev = nullptr;

    while (pNode != nullptr)
    {
        ListNode* pNext = pNode->m_pNext;
        
        if (pNext == nullptr) res = pNode;

        pNode->m_pNext = pPrev;
        pPrev          = pNode;
        pNode          = pNext;
    }

    return res;
}
```

+ [Q25 合并两个排序链表](./Question/Q25_MergeList.cpp)

a. 递归处理更简洁  
b. 考虑空指针情况  

```C++
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
```

+ Q26 树的子结构

> 输入两棵二叉树A、B，判断B是不是A的子结构

a. 在A中寻找节点值与B的根节点值相等的节点k  
b. 比较节点k的子树和B是否完全相等  
c. 涉及数的遍历，大多使用递归  
d. 指针操作记得判空

## 第四章 解决面试题的思路

通常，我们在编码前，需要先理清思路。  
针对一些抽象的数据结构，我们通常可以通过画图来理清思路。

+ [Q27 二叉树镜像](./Question/Q27_MirrorBinaryTree.cpp)

递归交换左右子树

+ [Q28 对称的二叉树](./Question/Q28_SymmetricalTree.cpp)

> 如果一棵树和它的镜像一样，那么就说它是对称的，请判断一棵树是不是对称

定义一种与前序遍历对称的遍历，判断两次遍历的结果是否相等：
a. 前序遍历：根、左、右
b. 对称遍历：根、右、左
c. 遍历时需要考虑空指针，如果空指针在树中的位置不一致也不对称

+ Q29 顺时针打印矩阵

a. 每次打印最外层的一个圈，打印的起点时左上角(x, x)
b. 循环结束的条件
