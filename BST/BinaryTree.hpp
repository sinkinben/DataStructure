#include "TreeNode.hpp"
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <sstream>
#include <algorithm>
#include <cassert>
#ifndef BINARYTREE_H
#define BINARYTREE_H

template <typename T>
class BinaryTree
{
protected:
    const std::string NIL = "null";
    TreeNode<T> *root;

private:
    TreeNode<T> *generateNode(const std::string &s, TreeNode<T> *parent)
    {
        return s == NIL ? nullptr : new TreeNode<T>(std::stoi(s), parent);
    }
    TreeNode<T> *innerBuild(const std::vector<std::string> &v)
    {
        if (v.size() == 0)
            return nullptr;
        int idx = 0, len = v.size();
        TreeNode<T> *root = new TreeNode<T>(stoi(v[idx++]));
        assert(root != nullptr);
        std::queue<TreeNode<T> *> q;
        q.push(root);
        while (!q.empty())
        {
            auto node = q.front();
            q.pop();
            if (idx < len)
                node->left = generateNode(v[idx++], node);
            if (idx < len)
                node->right = generateNode(v[idx++], node);
            if (node->left != nullptr)
                q.push(node->left);
            if (node->right != nullptr)
                q.push(node->right);
        }
        return root;
    }

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
            if (p != nullptr)
                delete p;
        }
        root = nullptr;
    }

    TreeNode<T> *getRoot() { return this->root; }

    void buildTree(std::string str)
    {
        if (str.front() == '[' && str.back() == ']')
            str = str.substr(1, str.length() - 2);

        // replace "," with " "
        auto pos = str.find(",");
        while (pos != std::string::npos)
        {
            str.replace(pos, 1, " ");
            pos = str.find(",");
        }

        // make str into vector
        std::stringstream ss(str);
        std::string buf;
        std::vector<std::string> result;
        while (ss >> buf)
            result.emplace_back(buf);

        this->root = innerBuild(result);
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
                s.push(p);
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
        s.push(p);
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