#ifndef HASHING_H
#define HASHING_H
template <typename KType, typename VType>
class Tuple
{
private:
    KType key;
    VType val;

public:
    Tuple(KType k, VType v) { key = k, val = v; }
    KType getKey() { return key; }
    VType getVal() { return val; }
    void setVal(VType v) { val = v; }
};

template <typename KeyType, typename ValType>
class Hashing
{
private:
public:
    virtual Tuple<KeyType, ValType> *get(KeyType key) = 0;
    virtual void set(KeyType key, ValType val) = 0;
    virtual void remove(KeyType key) = 0;
};

#endif