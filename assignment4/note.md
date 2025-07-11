# Template Functions
## min函数
```c++
// 这是一个简单的函数，用于返回两个值中较小的那个。
// 注意它通过值传递参数，并假设两个参数是相同的类型。
template <typename T>
T min_basic(T a, T b) {
  return a < b ? a : b;
}
// 显式实例化
int int_min = min_basic<int>(106, 107);
// 隐式实例化
int int_min = min_ref(106, 107);
```
