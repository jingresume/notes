# Guideline

[TOC]

## item2 尽量以const/enum/inline替换#define

+ 对于单纯的常量，使用const对象或enum替换#define
+ 对于函数宏，使用inline替换#define

## item3 尽可能使用const

+ const关键字出现在*左边，表示被指物是常量
+ const关键字出现在*右边，表示指针是常量
