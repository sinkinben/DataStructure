#ifndef TREENODE_H
#define TREENODE_H
enum RBColor
{
    Red,
    Black
};

enum AVLFactor
{
    LH = 1,
    EH = 0,
    RH = -1
};

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
    // 'color' variable is due to the implementation of the red and black tree.
    RBColor color;
    // 'factor variable is due to the implementation of the AVLTree.
    AVLFactor factor;

public:
    TreeNode() { left = right = parent = this; }
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

    // This construct function is used for RBTree.hpp
    TreeNode(T _val, TreeNode<T> *_parent, TreeNode<T> *_left, TreeNode<T> *_right, RBColor _color)
    {
        val = _val, parent = _parent, left = _left, right = _right;
        color = _color;
    }

    // This construct function is uedf for AVLTree.hpp
    TreeNode(T _val, AVLFactor _factor, TreeNode<T> *_parent)
    {
        val = _val, factor = _factor;
        left = right = nullptr;
        parent = _parent;
    }

    int getx() { return x; }
    int gety() { return y; }
    void setx(int _x) { x = _x; }
    void sety(int _y) { y = _y; }
};

#endif