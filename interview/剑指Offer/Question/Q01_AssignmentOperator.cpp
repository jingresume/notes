/*
* 题目1: 如下类型为CMyString的声明，请为该类型添加赋值运算符
*/
#include <iostream>

class CMyString
{
public:
    CMyString(const char* pData = nullptr);
    CMyString(const CMyString& str);
    ~CMyString();

public:
    CMyString& operator= (const CMyString& str);
    void print() const;

private:
    char* m_pData;
};

CMyString::CMyString(const char* pData)
{
    if (pData == nullptr)
    {
        m_pData = new char[1];
        m_pData[0] = '\0';
    }
    else
    {
        int len = strlen(pData);
        m_pData = new char[len + 1];
        strcpy(m_pData, pData);
    }
}

CMyString::CMyString(const CMyString& str)
{
    int len = strlen(str.m_pData);
    m_pData = new char[len + 1];
    strcpy(m_pData, str.m_pData);
}

CMyString::~CMyString()
{
    delete[] m_pData;
}

/*
// 非异常安全版本
CMyString& CMyString::operator= (const CMyString& str)
{
    if (this == &str) return *this;

    delete[] m_pData;
    int len = strlen(str.m_pData);
    m_pData = new char[len + 1];

    strcpy(m_pData, str.m_pData);
    return *this;
}
*/

// 异常安全版本
CMyString& CMyString::operator= (const CMyString& str)
{
    if (this != &str)
    {
        CMyString newStr = str;
        char* tempStr  = newStr.m_pData;
        newStr.m_pData = this->m_pData;
        this->m_pData  = tempStr;
    }
    return *this;
}

void CMyString::print() const
{
    printf("%s\n", m_pData);
}

// =============Test==============

// 赋值
void Test1()
{
    const char* str = "Hello World";
    CMyString str1(str);
    str1.print();   

    CMyString str2(str1);
    str2.print();
    CMyString str3;
    
    str3 = str2;
    str3.print();
}

// 赋值给自己
void Test2()
{
    CMyString str("Hello World");
    str = str;
    str.print();
}

//连续赋值

void Test3()
{
    CMyString str1, str2;
    CMyString str3("Hello World");
    str1 = str2 = str3;
    str1.print();
    str2.print();
    str3.print();
}

int main()
{
    Test1();
    Test2();
    Test3();
    
    return 0;
}
