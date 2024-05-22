/*
* 请实现一个函数，将字符串中的空格都替换成20%，在原字符串上操作
*/

#include <iostream>

void replaceSpace(char str[], int len)
{
    if (str == nullptr || len <= 0)
        return;
    
    int oriLen = 0, spaceCnt = 0;
    while (str[oriLen] != '\0')
    {
        if (str[oriLen] == ' ') spaceCnt++;
        oriLen++;
    }

    int newLen = oriLen + spaceCnt * 2;

    if (newLen > len) return;

    int firstIdx = oriLen, lastIdx = newLen;
    while (firstIdx >= 0 && firstIdx < lastIdx)
    {
        if (str[firstIdx] == ' ')
        {
            str[lastIdx--] = '0';
            str[lastIdx--] = '2';
            str[lastIdx--] = '%';
        }
        else
        {
            str[lastIdx--] = str[firstIdx];
        }
        firstIdx--;
    }
}

// ====================测试代码====================
void Test(const char* testName, char str[], int length, const char expected[])
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    replaceSpace(str, length);

    if(expected == nullptr && str == nullptr)
        printf("passed.\n");
    else if(expected == nullptr && str != nullptr)
        printf("failed.\n");
    else if(strcmp(str, expected) == 0)
        printf("passed.\n");
    else
        printf("failed.\n");
}

// 空格在句子中间
void Test1()
{
    const int length = 100;

    char str[length] = "hello world";
    Test("Test1", str, length, "hello%20world");
}

// 空格在句子开头
void Test2()
{
    const int length = 100;

    char str[length] = " helloworld";
    Test("Test2", str, length, "%20helloworld");
}

// 空格在句子末尾
void Test3()
{
    const int length = 100;

    char str[length] = "helloworld ";
    Test("Test3", str, length, "helloworld%20");
}

// 连续有两个空格
void Test4()
{
    const int length = 100;

    char str[length] = "hello  world";
    Test("Test4", str, length, "hello%20%20world");
}

// 传入nullptr
void Test5()
{
    Test("Test5", nullptr, 0, nullptr);
}

// 传入内容为空的字符串
void Test6()
{
    const int length = 100;

    char str[length] = "";
    Test("Test6", str, length, "");
}

//传入内容为一个空格的字符串
void Test7()
{
    const int length = 100;

    char str[length] = " ";
    Test("Test7", str, length, "%20");
}

// 传入的字符串没有空格
void Test8()
{
    const int length = 100;

    char str[length] = "helloworld";
    Test("Test8", str, length, "helloworld");
}

// 传入的字符串全是空格
void Test9()
{
    const int length = 100;

    char str[length] = "   ";
    Test("Test9", str, length, "%20%20%20");
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
    Test8();
    Test9();

    return 0;
}