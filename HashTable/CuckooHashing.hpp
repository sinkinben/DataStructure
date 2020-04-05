#include "Hashing.h"
#include "HashFunc.h"
#ifndef CUCKOOHASHING_H
#define CUCKOOHASHING_H
template <typename KType, typename VType, typename HashFn = HASHFUNC::hash<KType>>
class CuckooHashing : public Hashing<KType, VType>
{
private:
    int CAPACITY = 8;
    Tuple<KType, VType> **leftTable;
    Tuple<KType, VType> **rightTable;
    HashFn hashFn;

private:
    void clearTables()
    {
        for (int i = 0; i < CAPACITY; i++)
            leftTable[i] = nullptr, rightTable[i] = nullptr;
    }

    uint32_t leftTableIndex(KType k)
    {
        return hashFn(k) % CAPACITY;
    }

    uint32_t rightTableIndex(KType k)
    {
        return (hashFn(k) / CAPACITY) % CAPACITY;
    }

    bool innerSet(Tuple<KType, VType> *tuple, bool isLeft, bool **visited)
    {
        Tuple<KType, VType> **table = isLeft ? leftTable : rightTable;
        uint32_t idx = isLeft ? leftTableIndex(tuple->getKey()) : rightTableIndex(tuple->getKey());
        if (visited[isLeft][idx])
            return false;
        visited[isLeft][idx] = true;
        if (table[idx] == nullptr)
        {
            table[idx] = tuple;
            return true;
        }
        else
        {
            Tuple<KType, VType> *t = table[idx];
            if (innerSet(t, !isLeft, visited))
            {
                table[idx] = tuple;
                return true;
            }
            return false;
        }
    }

    void freeElements(Tuple<KType, VType> **table1, Tuple<KType, VType> **table2, int len)
    {
        for (int i = 0; i < len; i++)
        {
            if (table1[i] != nullptr)
                delete table1[i];
            if (table2[i] != nullptr)
                delete table2[i];
        }
    }

    void increaseCapacity()
    {
        // std::puts("increase");
        int tableSize = CAPACITY;
        Tuple<KType, VType> **table1 = leftTable;
        Tuple<KType, VType> **table2 = rightTable;

        CAPACITY *= 2;
        leftTable = new Tuple<KType, VType> *[CAPACITY];
        rightTable = new Tuple<KType, VType> *[CAPACITY];
        clearTables();

        for (int i = 0; i < tableSize; i++)
            if (table1[i] != nullptr)
                set(table1[i]->getKey(), table1[i]->getVal());
        for (int i = 0; i < tableSize; i++)
            if (table2[i] != nullptr)
                set(table2[i]->getKey(), table2[i]->getVal());

        freeElements(table1, table2, tableSize);
        delete[] table1;
        delete[] table2;
    }

public:
    CuckooHashing()
    {
        leftTable = new Tuple<KType, VType> *[CAPACITY];
        rightTable = new Tuple<KType, VType> *[CAPACITY];
        clearTables();
    }
    ~CuckooHashing()
    {
        freeElements(leftTable, rightTable, CAPACITY);
        if (leftTable != nullptr)
            delete[] leftTable;
        if (rightTable != nullptr)
            delete[] rightTable;
    }

    void set(KType k, VType v)
    {
        Tuple<KType, VType> *tuple = get(k);
        // std::printf("tuple = %p\n", tuple);
        if (tuple == nullptr)
        {
            bool *visited[2] = {nullptr, nullptr};
            visited[0] = new bool[CAPACITY], std::memset(visited[0], 0, sizeof(bool) * CAPACITY);
            visited[1] = new bool[CAPACITY], std::memset(visited[1], 0, sizeof(bool) * CAPACITY);
            tuple = new Tuple<KType, VType>(k, v);
            if (!innerSet(tuple, true, visited))
            {
                // std::puts("inner set failed");
                increaseCapacity();
                bool *visited[2] = {nullptr, nullptr};
                visited[0] = new bool[CAPACITY], std::memset(visited[0], 0, sizeof(bool) * CAPACITY);
                visited[1] = new bool[CAPACITY], std::memset(visited[1], 0, sizeof(bool) * CAPACITY);
                innerSet(tuple, true, visited);
                delete[] visited[0], visited[0] = nullptr;
                delete[] visited[1], visited[0] = nullptr;
            }
            delete[] visited[0], visited[0] = nullptr;
            delete[] visited[1], visited[0] = nullptr;
        }
        else
        {
            tuple->setVal(v);
        }
    }

    Tuple<KType, VType> *get(KType k)
    {
        Tuple<KType, VType> *tuple1 = leftTable[leftTableIndex(k)];
        Tuple<KType, VType> *tuple2 = rightTable[rightTableIndex(k)];
        if (tuple1 != nullptr && tuple1->getKey() == k)
            return tuple1;
        if (tuple2 != nullptr && tuple2->getKey() == k)
            return tuple2;
        return nullptr;
    }

    void remove(KType k)
    {
        int idx1 = leftTableIndex(k);
        int idx2 = rightTableIndex(k);
        if (leftTable[idx1] != nullptr && leftTable[idx1]->getKey() == k)
        {
            delete leftTable[idx1];
            leftTable[idx1] = nullptr;
        }
        if (rightTable[idx2] != nullptr && rightTable[idx2]->getKey() == k)
        {
            delete rightTable[idx2];
            rightTable[idx2] = nullptr;
        }
    }
};

#endif