# Guideline

[TOC]

## 自己习惯C++

### item2 尽量以const/enum/inline替换#define

+ 对于单纯的常量，使用const对象或enum替换#define
+ 对于函数宏，使用inline替换#define

### item3 尽可能使用const

+ const关键字出现在*左边，表示被指物是常量
+ const关键字出现在*右边，表示指针是常量
+ const成员函数要求不能修改非static等成员，可以在成员变量前加上**mutable**声明，解除这种限制
+ const成员函数不能调用non const成员函数

### item4 确定对象使用前已经被初始化

+ 确保每一个构造函数都将对象的每一个成员初始化
+ 为内置类型执行手工初始化，C++不保证初始化他们
+ 构造函数最好使用成员初始化列表，而不是在构造函数中赋值
+ 为免除跨编译单元的初始化次序问题，请使用local static对象 代替non-local static对象

## 构造/析构/赋值

### item5 了解C++默默编写并调用哪些函数

+ default构造函数
+ copy构造函数
+ 拷贝赋值函数
+ 析构函数
+ 只有在用户调用时，才会生成
+ 在用户有任意自定义构造函数时，编译器不会生成默认构造函数
+ 类中包含引用、const对象时，编译器不会生成拷贝构造和赋值函数
+ 基类的拷贝构造或赋值函数被声明为private时，编译器不会生成拷贝构造或赋值函数

### item6 若不想使用编译器生成的默认函数，就该明确拒绝

+ 可以将不想要编译器生成的函数，声明为private，并且不实现
+ 可以继承一个成员函数为private的base类
+ C++11可以使用=delete

```C++
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
```

### item7 为多态基类声明virtual析构函数

+ 带多态性质的base类应该声明一个virtual析构函数，因为当使用基类指针指向子类时，如果基类没有声明virtual析构函数，delete基类指针时，就不会执行子类的析构函数，从而造成泄漏。
+ 不具备多态性质的base类，不应该声明virtual析构函数，因为virtual会引入虚函数表，导致类体积增加。
