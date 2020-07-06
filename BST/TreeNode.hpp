#ifndef TREENODE_H
#define TREENODE_H

template <typename T>
class TreeNode
{
public:
    T val;
    TreeNode<T> *left, *right;

public:
    TreeNode(T _val)
    {
        val = _val;
        left = right = nullptr;
    }
};

#endif