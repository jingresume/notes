# 数位DP

+ 为了不重不漏地统计所有不超过上限的答案，要从高到低枚举每一位，再考虑每一位都可以填哪些数字，最后利用通用答案数组统计答案。

将数字转换成二进制字符串s, 定义 $f(i,isLimit,isNum)$ 表示构造从左往右第i位及其之后数位的合法方案数，其余参数的含义为：

+ isLimit: 表示当前是否受到了 n 的约束。若为真，则第 i 位填入的数字至多为 s[i]，否则可以是 1。如果在受到约束的情况下填了 s[i]，那么后续填入的数字仍会受到 n 的约束。
+ isNum: 表示 i 前面的数位是否填了数字。若为假，则当前位可以跳过（不填数字），或者要填入的数字至少为 1；若为真，则要填入的数字可以从 0 开始。
+ 记忆化搜索是可以只记忆重要参数，对于`isLimit == true or isNum == false`的少数情况可以不进行记忆化，以减少记忆化数组大小。

题目  
[600](https://leetcode.cn/problems/non-negative-integers-without-consecutive-ones/solutions/1750941/by-endlesscheng-1egu/?envType=daily-question&envId=2024-08-05)
