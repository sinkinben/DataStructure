#include <stdint.h>
#ifndef HASHFUNC_H
#define HASHFUNC_H

namespace HASHFUNC
{
typedef uint32_t hash_t;

template <typename KType>
struct hash
{
};

template <>
struct hash<uint32_t>
{
    hash_t operator()(uint32_t x) const { return x; }
};

template <>
struct hash<int>
{
    hash_t operator()(int x) const { return x; }
};

template <>
struct hash<char>
{
    hash_t operator()(char x) const { return x; }
};

template <>
struct hash<unsigned char>
{
    hash_t operator()(unsigned char x) const { return x; }
};

template <>
struct hash<short>
{
    hash_t operator()(short x) const { return x; }
};

template <>
struct hash<unsigned short>
{
    hash_t operator()(unsigned short x) const { return x; }
};

template <>
struct hash<long>
{
    hash_t operator()(long x) const { return x; }
};

template <>
struct hash<unsigned long>
{
    hash_t operator()(unsigned long x) const { return x; }
};
} // namespace HASHFUNC
#endif