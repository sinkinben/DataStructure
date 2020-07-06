#include "TreeNode.hpp"
#include <vector>
#include <stack>
#include <algorithm>
#ifndef BINARYTREE_H
#define BINARYTREE_H

template <typename T>
class BinaryTree
{
protected:
    TreeNode<T> *root;

public:
    BinaryTree()
    {
        root = nullptr;
    }
    ~BinaryTree()
    {
        if (root == nullptr)
            return;
        std::stack<TreeNode<T> *> result;
        auto p = root;
        std::stack<TreeNode<T> *> s;
        s.push(p);
        while (!s.empty())
        {
            p = s.top(), s.pop();
            result.push(p);
            if (p->left != nullptr)
                s.push(p->left);
            if (p->right != nullptr)
                s.push(p->right);
        }
        while (!result.empty())
        {
            p = result.top(), result.pop();
            delete p;
        }
    }

    std::vector<T> inorder()
    {
        std::vector<T> v;
        if (root == nullptr)
            return v;
        std::stack<TreeNode<T> *> s;
        auto p = root;
        while (!s.empty() || p != nullptr)
        {
            if (p != nullptr)
            {
                s.push(p->left);
                p = p->left;
            }
            else
            {
                p = s.top(), s.pop();
                v.push_back(p->val);
                p = p->right;
            }
        }
        return v;
    }

    std::vector<T> preorder()
    {
        std::vector<T> v;
        if (root == nullptr)
            return v;
        std::stack<TreeNode<T> *> s;
        auto p = root;
        s.push(p);
        while (!s.empty())
        {
            p = s.top(), s.pop();
            v.emplace_back(p->val);
            if (p->right != nullptr)
                s.push(p->right);
            if (p->left != nullptr)
                s.push(p->left);
        }
        return v;
    }

    std::vector<T> postorder()
    {
        std::vector<T> v;
        if (root == nullptr)
            return v;
        auto p = root;
        std::stack<TreeNode<T> *> s;
        while (!s.empty())
        {
            p = s.top(), s.pop();
            v.push_back(p->val);
            if (p->left != nullptr)
                s.push(p->left);
            if (p->right != nullptr)
                s.push(p->right);
        }
        std::reverse(v.begin(), v.end());
        return v;
    }
};
#endif