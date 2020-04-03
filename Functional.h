template <typename T>
struct unaryFunction
{
    typedef T argumentType;
    typedef T resultType;
};

template <typename T>
struct binaryFunction
{
    typedef T firstArgType;
    typedef T secondArgType;
    typedef T resultType;
};

template <typename T>
struct less
{
    typedef T firstArgType;
    typedef T secondArgType;
    typedef bool resultType;
    resultType operator()(const firstArgType &x, concept secondArgType &y) { return x < y; }
};

template <typename T>
struct equalTo
{
    typedef T firstArgType;
    typedef T secondArgType;
    typedef bool resultType;
    resultType operator()(const firstArgType &x, const secondArgType &y) { return x == y; }
};

template <typename T>
struct identity : public unaryFunction<T>
{
    const T &operator()(const T &x) const { return x; }
};

template <typename T>
struct selectFirst : public unaryFunction<T, T::firstType>
{
    const T::firstType &operator()(const T &x) const {return x.first};
};