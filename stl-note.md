## 模板的使用

在初学者看来，模板声明有 2 个方式。

```cpp
template <class T>
template <typename T>
```

大部分情况下可以混用，具体差异参考 [这篇文章](https://www.cnblogs.com/cthon/p/9201649.html) 。

### 模板函数

非常 simple，且 naive 。

```cpp
template <typename T>
T add(T a, T b)
{
    return a + b;
}
int main()
{
    cout << add<int>(1, 2) << endl;
}
```

### 模板类

Too simple.

```cpp
template <typename T>
class Calculator
{
public:
    T add(T a, T b) { return a + b; }
    T sub(T a, T b) { return a - b; }
    T mul(T a, T b) { return a * b; }
    T div(T a, T b) { return a / b; }
};
int main()
{
    int a = 1, b = 2;
    Calculator<int> cal;
    printf("%d %d %d %d", cal.add(a, b), cal.sub(a, b), cal.mul(a, b), cal.div(a, b));
}
```

### 成员模板

`Dummy` 类的声明：

```cpp
template <typename T>
class Dummy
{
private:
    T dummyVal;

public:
    template <typename t1, typename t2>
    void dummyFunc(t1 a, t2 b);
};
```

`dummyFunc` 方法的实现：

```cpp
template <typename T>
template <typename t1, typename t2>
void Dummy<T>::dummyFunc(t1 a, t2 b)
{
    printf("%d %d\n", sizeof(a), sizeof(b));
}
```

调用方法：

```cpp
int main()
{
    Dummy<float> dummy;
    dummy.dummyFunc<float, double>(0, 0);
}
```

### 嵌套模板

在模板类中再定义一个模板类，体会了一把「语言律师」的感觉。
首先定义一个模板类 `Dummy` ，然后在该类中再次声明一个新的类 `AnotherClass` :

```cpp
template <typename T>
class Dummy
{
public:
    template <typename T1, typename T2>
    T add(T1 a, T2 b) { return (T)(a + b); }

    // This is a declaration, not implementa.
    template <typename T3>
    class AnotherClass;

    // Define a variable, whose type is 'AnotherClass'
    AnotherClass<T> another;
};
```

在 `Dummy` 外定义这个新的类 `AnotherClass` :

```cpp
template <typename T>
template <typename innerType>
class Dummy<T>::AnotherClass
{
public:
    T func() { return sizeof(innerType); }
};
```

调用方法：

```cpp
int main()
{
    Dummy<double> dummy;
    // print 3.300000
    printf("%lf\n", dummy.add<double, float>(1.1, 2.2));
    // print 8.000000, which is equal to sizeof(double)
    printf("%lf\n", dummy.another.func());
}
```



