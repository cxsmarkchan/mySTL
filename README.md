# mySTL
C++标准模板库：cxsmarkchan的实现
调试环境：win10 + VS2010, 暂未在linux环境下调试

## 库结构
- lib/xxx.h 为xxx结构的声明部分
- lib/xxx_impl.h 为xxx结构的实现部分
- test/Testxxx.cpp 为xxx结构的单元测试部分
- 实际使用时引用xxx.h即可，注意命名空间为cxs

## 目前已完成

- allocator
- algorithm: swap
- functional: less, greater
- vector

## 目前正在进行
- list
