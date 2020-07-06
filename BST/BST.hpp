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
    void selfCheck()
    {
        std::vector<T> v;
        inorder(this->root, v);
        int n = v.size();
        for (int i = 1; i < n; i++)
            assert(v[i] > v[i - 1]);
    }

    void inorder(TreeNode<T> *p, std::vector<T> &v)
    {
        if (p == nullptr)
            return;
        inorder(p->left);
        v.emplace_back(p->val);
        inorder(p->right);
    }

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

    TreeNode<T> *insert(T val)
    {
        if (this->root == nullptr)
            return this->root = new TreeNode<T>(val);

        return nullptr;
    }

    bool remove(T val)
    {
        return false;
    }

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

    TreeNode<T> *search(T val)
    {
        return innerSearch(this->root, val);
    }

    TreeNode<T> *maxval()
    {
        auto p = this->root;
        if (p == nullptr)
            return nullptr;
        while (p->right != nullptr)
            p = p->right;
        return p;
    }

    TreeNode<T> *minval()
    {
        auto p = this->root;
        if (p == nullptr)
            return nullptr;
        while (p->left != nullptr)
            p = p->left;
        return p;
    }
};
#endif