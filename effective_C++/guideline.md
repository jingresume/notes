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

### item19 设计class犹如type

### item20 用pass-by-reference-to-const替换pass-by-value

+ 尽量以pass-by-reference-to-const替换pass-by-value，前者通常比较高效，并且避免切割问题
+ 切割问题：当派生类按值传递给一个用基类做参数的函数时，传值过程中只会复制基类部分
+ 以上规则不适用于内置类型、迭代器、函数指针，习惯上他们都被设计为pass-by-value，且体积较小

### item21 必须返回对象时，别妄想返回其reference

+ 绝不要返回pointer或reference指向的一个local对象、或者heap对象
+ 带来的麻烦会比收益小，且一般编译器会有返回值优化

### item22 将成员变量声明为private

+ 将成员变量声明为private，这赋予了用户访问数据的一致性、可细微划分访问控制、允许约束条件获得保证、提供给class的作者充分的实现弹性，为后期的维护升级提供方便。
+ protected并不比public更具封装性，一个是对子类开放，一个是对用户开放，都没有封装数据。

### item23 以no-member/no-friend替换member函数

+ 当一个功能，既可以用no-member函数实现，又可以用member函数实现时，倾向于选择no-member函数
+ 因为no-member函数有更好的封装性 -- no member不可访问成员变量，所以封装性更好
+ 一个类可能拥有大量的便利函数，而用户可能只对其中某一部分感兴趣，如果这些便利函数时使用no-member的形式，那么我们可以将它们分为多个头文件。降低编译依赖性。在class内的member函数是无法分离的。

### item24 如果所有函数参数都需要类型转换，请为此采用no-member函数

+ 主要针对操作法重载  
如果操作法重载使用member函数，则只有乘法*右边的参数可以进行隐式类型转换  

```C++
class Ration
{
public:
    Ration(int a);
    const Ration operator* (const Ration& rhs)
    {
        return Ration(this->a * rhs->getA());
    }
private:
    int a;
}

```

```C++
Ration a(1);
Ration b = a * 1; // a.*(1)
Ration b = 1 * a; // 1.*(a)无法通过编译，因为1在*左边，不在操作符重载的参数列表中，所以无法隐式类型转换
```

此时我们就需要将操作符重载用non-member实现

```C++
const Ration operation* (const Ration& lhs, const Ration& rhs)
{
    return Ration(lhs->getA() * rhs->getA());
}
```

+ 如果不需要访问私有成员，我们也不必将non-member声明为friend

### item25 考虑写出一个不抛出异常的swap函数

+ 当std::swap的默认实现，对于自定义的class效率不高时，提供一个swap成员函数，并确定这个函数不抛出异常
+ 如果你提供一个member swap函数，也该提供一个non member swap函数来调用他；对于class（非template）请特化std::swap，并在特化版本中调用member swap
+ 调用swap时，应该针对std::swap使用using声明式，然后调用swap时，不使用任何namespace，这样编译器才能找到正确的版本
+ swap的一个重要应用是，帮助class提供强烈的异常安全性保障，所以要求swap成员函数不抛出异常

```C++
using std::swap
swap(obj1, obj2);
```

## 实现

### item26 尽量延后变量定义式的出现时间

+ 应该尽量延后变量的定义式，这样做可以增加程序运行效率，也可以改善代码清晰度

### item27 尽量少做转型动作

+ const_cast 常量性转除
+ dynamic_cast 安全的向下转型（基类->子类）
+ reinterpret_cast 低级转型，一般不用
+ static_cast 强迫隐式转换
+ dynamic_cast的实现通常效率较低，如果连续的执行dynamic_cast来调用子类函数，可以将子类函数变成基类的virtual函数
+ 尽量使用C++ style转型，不要使用旧式转型，前者更容易识别，且分工更明确
+ 类型转换并不只是告诉编译器将某种类型视为另一种类型，往往会令编译器编译出更多的代码，例如将子类转换为基类，转换后的基类指针可能是在子类指针基础上增加了偏移。（多重继承）

### item28 避免返回handles指向对象内部成分

+ 这里的handles指的是reference/指针/迭代器等
+ 返回handles会破坏封装性
+ 返回handles容易导致指针空悬
+ 有时返回handles是必要的，例如 operator[]

### item29 为异常安全而努力是值得的

+ 异常安全函数：即使发生异常，也不会造成资源泄露或者任何数据结构的损坏。
+ 异常安全函数分为三个等级：基本型、强烈型、不抛任何异常型。  
    1 基本承诺：如果异常抛出，程序内任何事物仍保持在有效状态下，但不保证是何种状态  
    2 强烈保证：如果异常抛出，程序状态不改变（保持调用之前的状态）  
    3 不抛保证：承诺永远不抛出异常，作用于内置类型的所有操作都提供nothrow保证  
+ copy and swap  
    1 为你打算修改的对象创建一个副本  
    2 然后在副本上进行修改，如果修改过程中抛出异常，原对象保持不变  
    3 当所有修改成功后，将副本与原对象在一个不抛出异常的操作中置换（swap）
+ 强烈保证往往可以通过copy-and-swap实现

### item30 透彻了解inlining的里里外外

+ inline会导致代码膨胀，进而导致额外的换页行为、降低指令高速缓存命中率，进而带来效率损失
+ inline只是对编译器的建议，不是强制命令，有两种方式表明函数是inline  
    1 在class声明中定义函数  
    2 在函数的定义式前加上inline关键字，通常inline函数位于头文件中  
+ 构造/析构函数不适合被声明为inline，因为当继承发生时，base类的构造函数会在子类中展开，导致子类无法inline
+ inline函数无法随着程序库升级，必须客户重新编译代码
+ 大部分调试器对inline无法调试
+ 所以我们应该只将inline限制在小型、被频繁调用的函数上

### item31 将文件间的依存关系降至最低

+ C++没有将接口与实现相分离做的很好，class的定义中，不仅包含接口，还包含成员变量等。这会导致仅修改实现代码时，仍然会编译道调用接口的代码
+ PIMPL：pointer to implemention，指在class中只声明接口和一个指向实现类的指针，这样就可以解耦接口与实现
+ 如果使用reference或指针可以完成任务，就不要使用对象，因为使用对象需要其定义，而使用指针只需要其声明，这样可以减少编译依赖
+ 尽量用class的声明式，代替class的定义式。
+ 当你在声明函数时使用道class作为参数或返回值，此时只需要class的声明，不需要定义式。
+ 为声明式和定义式提供不同的头文件
+ 将接口部分单独声明为一个虚基类，实现部分继承这个虚基类也是一种接口和实现分离的方法。
+ 程序库的头文件应该以完全且仅有声明式的形式存在

## 继承与面向对象设计

### item32 确定你的public继承塑膜出is-a的关系

+ 最重要的一个规则：public继承，意味着一种is-a（是一种）的关系

```C++
class Person {};
class Student : public Person {};
```

意味着Student is a Person。  

+ 适用于base class身上的每一件事情，也一定适用于derived class，因为dervied class也是一种base class

### item33 避免遮掩继承而来的名称

+ derived class内的名称会遮掩base class内的名称（同名函数），在public继承下，没有人希望如此。

```C++
class Base
{
    void f1(int);
    void f2();
};

class Derived : public Base
{
    void f1(); //Derived将无法调用到Base中的f1，因为名称遮掩
    void f3();
}
```

+ 为了让被遮掩的名称重新暴露，可以使用using声明，或者转交函数

```C++
class Derived : public Base
{
    using f1;
    void f1();
    void f3();
}
```

### item34 区分接口继承和实现继承

+ 成员函数的接口总是会被继承
+ 声明non-virtual函数的目的是：为了让devired class继承函数的接口和一份强制实现（不应该在子类中重新定义）
+ 声明非纯虚函数的目的是：为了让devired class继承函数的接口和default实现
+ 声明纯虚函数的目的是：为了让devired class只继承函数的接口
+ 基类也可以为纯虚函数提供一份default实现，但是必须在子类中显式调用Base::f1()

### item35 考虑virtual函数以外的其他选择

+ NVI: Non-Virtual Interface，用public non-virtual包裹低访问性的virtual函数。  
    1 将接口声明为non-Virtual函数  
    2 在接口中调用private virtual函数  
    3 这是template method设计模式的一种表现
+ 使用函数指针替换virtual函数  
    1 对象不同的实例可以拥有不同的计算函数  
    2 可在运行期间改变计算函数  
    3 必须降低对象的封装性（函数指针需要访问内部变量）
    4 这是策略模式的一种表现

### item36 绝不重新定义继承而来的non-virtual函数

+ non-virtual函数是静态绑定、virtual函数是动态绑定
+ 如果重写了继承来的non-virtual函数，则通过基类指针调用这个函数和通过子类指针调用会有不一样的结果

### item37 绝不重新定义继承而来的缺省参数值

+ virtual函数是动态绑定，但是缺省参数是静态绑定
+ 如果重新定义继承而来的缺省参数值，在使用基类指针调用时，重新定义的缺省参数无效

### item38 通过复合塑膜出has-a或“根据某物实现出“

+ 复合是类型之间的一种关系，当某种对象内含它种对象时，就是这种关系
+ 在应用域，复合意味着has-a
+ 在实现域，复合意味着根据某物实现出

### item39 明智而审慎的使用private继承

+ private继承，从base class继承来的所有成员，都会变成private成员
+ 编译器不会自动将derived class自动转换为base class
+ private继承，意味着根据某物实现，只有实现部分被继承，接口应略去
+ 如果D private继承B，意味着D对象根据B对象实现而得
+ C++裁定，凡是独立对象，都必须有非零大小

```C++
class empty {} // sizeof(empty) != 0
```

+ private继承意味着根据某物实现，复合也表示同样的意思，优先选择复合；但是当derived class需要访问protected base class成员、或者要重新定义virtual函数时，使用private继承是合理的。
+ private继承可以造成empty class最优化，因为被继承得empty class不再是一个独立的对象。

### item40 明智而审慎的使用多重继承

+ 多重继承容易导致歧义：多个基类中拥有同样的函数
+ 棱形继承：使用virtual继承来避免成员变量重复
+ 多重继承有正当用途，例如需要同时实现两个接口

## 模板与范型编程

### item41 了解隐式接口和编译期多态

```C++
template <typename T>
void doProcessing(T& w)
{
    if (w.size() > 10)
    {
        T temp(w);
        temp.normalize();
        temp.swap(w);
    }
}
```

+ 上述模板中的w的类型，必须支持normalize、size、swap等接口，这便是T必须支持的**隐式接口**
+ 以不同的模板参数实例化函数模板，会导致调用不同的函数，这便是**编译期多态**
