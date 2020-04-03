#include "Hashing.h"
#include "HashFunc.h"
#include <cstring>
#ifndef LINEARHASHING_H
#define LINEARHASHING_H
template <typename KType, typename VType, typename HashFn = HASHFUNC::hash<KType>>
class LinearHashing : public Hashing<KType, VType>
{
private:
    int CAPACITY = 8;
    uint32_t size;
    Tuple<KType, VType> **table;
    HashFn hashFunc;

private:
    void resetTable()
    {
        for (int i = 0; i < CAPACITY; i++)
            table[i] = nullptr;
    }

    void freeElement(Tuple<KType, VType> **array, int len)
    {
        for (int i = 0; i < len; i++)
        {
            if (array[i] != nullptr)
                delete array[i];
        }
    }

    int getTargetPosition(KType key)
    {
        int idx = hashFunc(key) % CAPACITY;
        while (table[idx] != nullptr && table[idx]->getKey() != key)
            idx = (idx + 1) % CAPACITY;
        return idx;
    }

    void increaseCapacity()
    {
        int tempSize = CAPACITY;
        Tuple<KType, VType> **temp = table;
        CAPACITY *= 2;
        size = 0;
        table = new Tuple<KType, VType> *[CAPACITY];
        resetTable();
        for (int i = 0; i < tempSize; i++)
        {
            if (temp[i] != nullptr)
                set(temp[i]->getKey(), temp[i]->getVal());
        }
        freeElement(temp, tempSize);
        delete[] temp;
    }

public:
    LinearHashing()
    {
        table = new Tuple<KType, VType> *[CAPACITY];
        resetTable();
        size = 0;
    }
    LinearHashing(int capacity)
    {
        CAPACITY = capacity;
        table = new Tuple<KType, VType> *[CAPACITY];
        resetTable();
        size = 0;
    }
    ~LinearHashing()
    {
        freeElement(table, CAPACITY);
        if (table != nullptr)
            delete[] table;
    }
    Tuple<KType, VType> *get(KType key)
    {
        return table[getTargetPosition(key)];
    }
    void set(KType key, VType val)
    {
        int idx = getTargetPosition(key);
        if (table[idx] == nullptr)
        {
            table[idx] = new Tuple<KType, VType>(key, val), size++;
            if (size > CAPACITY / 2)
                increaseCapacity();
        }
        else
        {
            table[idx]->setVal(val);
        }
    }
    void remove(KType key)
    {
        int idx = getTargetPosition(key);
        if (table[idx] != nullptr)
        {
            delete table[idx];
            table[idx] = nullptr;
            size--;

            // adjust all elememts
            size = 0;
            Tuple<KType, VType> **temp = table;
            table = new Tuple<KType, VType> *[CAPACITY];
            resetTable();
            for (int i = 0; i < CAPACITY; i++)
            {
                if (temp[i] != nullptr)
                    set(temp[i]->getKey(), temp[i]->getVal());
            }
            freeElement(temp, CAPACITY);
            delete[] temp;
        }
    }
};
#endif