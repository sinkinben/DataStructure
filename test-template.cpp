#include <iostream>
using namespace std;

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

template <typename T>
template <typename innerType>
class Dummy<T>::AnotherClass
{
public:
    T func() { return sizeof(innerType); }
};

int main()
{
    Dummy<double> dummy;
    printf("%lf\n", dummy.add<double, float>(1.1, 2.2));
    printf("%lf\n", dummy.another.func());
}