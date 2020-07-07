/* 
 *  BST meas Binary Search Tree
 */
#include "BinaryTree.hpp"
#include <cassert>
#ifndef BST_H
#define BST_H

template <typename T>
class BSTree : public BinaryTree<T>
{
private:
    // search val by recursion
    TreeNode<T> *innerSearch(TreeNode<T> *p, T val)
    {
        if (p == nullptr || p->val == val)
            return p;
        if (val < p->val)
            return innerSearch(p->left, val);
        else
            return innerSearch(p->right, val);
    }

public:
    BSTree()
    {
        this->root = nullptr;
    }

    void selfCheck()
    {
        auto v = this->inorder();
        int n = v.size();
        for (int i = 1; i < n; i++)
            assert(v[i] > v[i - 1]);
    }

    // insert a new node into the BST, whose value is 'val'
    // each node in BST is unique
    TreeNode<T> *insert(T val)
    {
        if (this->root == nullptr)
            return this->root = new TreeNode<T>(val);
        auto x = this->root;
        auto y = x->parent; // nullptr actually
        while (x != nullptr)
        {
            y = x;
            if (val < x->val)
                x = x->left;
            else if (val > x->val)
                x = x->right;
            else
                return nullptr;
        }
        auto node = new TreeNode<T>(val);
        node->parent = y;
        return val < y->val ? (y->left = node) : (y->right = node);
    }

    // remove node from the BST, whose value is 'val'
    bool remove(T val)
    {
        auto node = search(val);
        if (node == nullptr)
            return false;
        bool l = (node->left != nullptr);
        bool r = (node->right != nullptr);
        // TODO
        assert(0);
    }

    // update oldval to newval if oldval is in the BST, otherwise do nothing
    bool update(T oldval, T newval)
    {
        auto p = search(oldval);
        if (p != nullptr)
        {
            p->val = newval;
            return true;
        }
        return false;
    }

    // search val by non-recursion
    TreeNode<T> *search(T val)
    {
        auto p = this->root;
        while (p != nullptr && p->val != val)
        {
            if (val < p->val)
                p = p->left;
            else
                p = p->right;
        }
        return p;
    }

    // get max val in the BST
    TreeNode<T> *maxval()
    {
        auto p = this->root;
        if (p == nullptr)
            return nullptr;
        while (p->right != nullptr)
            p = p->right;
        return p;
    }

    // get min val in the BST
    TreeNode<T> *minval()
    {
        auto p = this->root;
        if (p == nullptr)
            return nullptr;
        while (p->left != nullptr)
            p = p->left;
        return p;
    }

    // get the node's successor, whose value is 'val'
    TreeNode<T> *successor(T val)
    {
        auto x = search(val);
        if (x == nullptr)
            return nullptr;
        if (x->right != nullptr)
            return minval(x->right);
        auto y = x->parent;
        while (y != nullptr && y->right == x)
            x = y, y = y->parent;
        return y;
    }

    // get the node's predecessor, whose value is 'val'
    TreeNode<T> *predecessor(T val)
    {
        auto x = search(val);
        if (x == nullptr)
            return nullptr;
        if (x->left != nullptr)
            return maxval(x->left);
        return x->parent;
    }
};
#endif