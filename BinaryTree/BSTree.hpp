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

    // remove helper
    // replace subtree-u with subtree-v
    void transplant(TreeNode<T> *u, TreeNode<T> *v)
    {
        if (u == nullptr)
            return;
        // u is the root
        if (u->parent == nullptr)
            this->root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        if (v != nullptr)
            v->parent = u->parent;
    }

public:
    BSTree()
    {
        this->root = nullptr;
    }

    BSTree(TreeNode<T> *root)
    {
        this->root = root;
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
    // return nullptr means 'val' is already in BST
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
        // case '!l' include (!l && !r) and (!l && r)
        if (!l)
            transplant(node, node->right);
        else if (l && !r)
            transplant(node, node->left);
        else
        {
            auto y = minval(node->right);
            if (y->parent != node)
            {
                transplant(y, y->right);
                y->right = node->right;
                y->right->parent = y;
            }
            transplant(node, y);
            y->left = node->left;
            y->left->parent = y;
        }

        delete node;
        return true;
    }

    // update oldval to newval if oldval is in the BST, otherwise do nothing
    TreeNode<T> *update(T oldval, T newval)
    {
        if (!remove(oldval))
            return nullptr;
        return insert(newval);
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
    TreeNode<T> *maxval(TreeNode<T> *p)
    {
        if (p == nullptr)
            return nullptr;
        while (p->right != nullptr)
            p = p->right;
        return p;
    }
    TreeNode<T> *maxval() { return maxval(this->root); }

    // get min val in the BST
    TreeNode<T> *minval(TreeNode<T> *p)
    {
        if (p == nullptr)
            return nullptr;
        while (p->left != nullptr)
            p = p->left;
        return p;
    }
    TreeNode<T> *minval() { return minval(this->root); }

    /* get the node's successor, whose value is 'val'
     * if the right subtree of a node x in T is empty and x has a successor y, 
     * then y is the lowest ancestor of x whose left child is also an ancestor of x. 
     * (Recall that every node is its own ancestor.)
     */
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
        auto y = x->parent;
        while (y != nullptr && y->left == x)
            x = y, y = y->parent;
        return y;
    }
};
#endif