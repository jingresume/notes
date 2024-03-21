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

### item8 别让异常逃离析构函数

+ 如果析构函数在调用某个函数时抛出异常，析构函数应该捕捉异常，不向外传播
+ 如果一个对象的析构函数抛出异常，那么包含该对象容器可能发生未定义行为

### item9 绝不在构造/析构函数中调用virtual方法

+ 在基类构造函数中调用virtual方法，将无法调用到派生类的virtual方法
+ 因为此时派生类还没有进行构造，编译器认为对象是基类
+ 析构函数同理，在派生类析构函数执行之后，编译器认为对象是基类，从而无法调用到派生类的virtual方法

### item10 令`operator=`返回一个reference to *this

+ 连环赋值`a = b = c`

```C++
Widget& operator=(const Widget& rhs)
{
    ...
    return *this;
}
```

+ 包括所有的赋值符 = +=等

### item11 在operator=中处理自我赋值

+ 即对象自己赋值给自己
+ 可以通过比较两个对象的地址进行处理
+ 也可以通过语句顺序、copy-and-swap技术等避免异常安全问题

### item12 复制对象时，勿忘其每一个成分

+ 确保复制所有local成员变量
+ 调用base class的拷贝函数

## 资源管理

### item13 以对象管理资源

+ 把资源放入对象内，利用C++自动调用析构函数，来释放资源
+ RAII：资源取得时机便是初始化时机，以对象管理资源的常用语
+ 资源在构造期间获得，析构期间释放
+ 智能指针就是常见的RAII对象

### item14 在资源管理类中小心copy行为

+ 复制RAII对象，必须一一复制它所管理的资源，所以资源的copy行为决定了RAII对象的copy行为

### item15 在资源管理类中，提供对原始资源的访问

+ API往往要求访问原始资源，而不是资源管理类，所以RAII类需要提供访问原始资源的接口
+ 对原始资源的访问可以使用显式转化、隐式转换，一般而言，显示转化较安全，隐式转化较方便

### item16 成对使用new delete时，要采用相同的形式

+ new/delete new[]/delete[]
+ 数组的内存布局存在一个头部，用来记录数组中有多少个对象，delete时需要读取这个头部，而[]就是告诉delete指针指向的是数组；而非数组是没有这个头部的。

### item17 以独立语句，将newed对象放入智能指针

+ 以独立的语句将newed对象存储与智能指针中，如果不这样做，一旦异常抛出，可能导致内存泄漏
非独立的语句：

```C++
    process(shared_ptr(new Widget), priority());
```

非独立的语句，可能执行顺序被编译器重排，导致

1) new Widget
2) priority()
3) shared_ptr()
如果2）抛出异常，那么1）new的资源就会泄漏；

独立的语句：

```C++
    shared_ptr<Widget> pw(new Widget);
    process(Widget, priority());
```

## 设计与声明

### item18 让接口容易被正确使用，不容易被误用

+ 必须考虑客户可能会做出什么错误
+ 尽量让自定义的types行为与内置types行为一致
+ 促进正确使用的办法包括：接口一致性、与内置类型行为兼用等
+ 防止误用的办法包括：建立新的类型、限制类型上的操作、束缚对象值、以及消除对象的资源管理责任
+ 以const修饰operator*的返回类型
