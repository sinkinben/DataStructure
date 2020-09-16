#ifndef TREENODE_H
#define TREENODE_H

template <typename T>
class TreeNode
{
private:
    // (x, y) is used to draw the binary tree in the console
    // which is the node's coordinate on the screen
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

    TreeNode(T _val, TreeNode<T> *_parent)
    {
        val = _val;
        parent = _parent;
        left = right = nullptr;
    }
    int getx() { return x; }
    int gety() { return y; }
    void setx(int _x) { x = _x; }
    void sety(int _y) { y = _y; }
};

#endif