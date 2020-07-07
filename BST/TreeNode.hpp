#ifndef TREENODE_H
#define TREENODE_H

template <typename T>
class TreeNode
{
private:
    int x, y;

public:
    T val;
    TreeNode<T> *left, *right, *parent;

public:
    TreeNode(T _val)
    {
        val = _val;
        left = right = parent = nullptr;
        x = y = -1;
    }

    void setPosition(int _x, int _y)
    {
        x = _x, y = _y;
    }
};

#endif