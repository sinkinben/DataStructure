#include "TreeNode.hpp"
#include <vector>
#include <stack>
#include <string>
#include <sstream>
#include <algorithm>
#ifndef BINARYTREE_H
#define BINARYTREE_H

template <typename T>
class BinaryTree
{
protected:
    const std::string nullNode = "null";
    TreeNode<T> *root;

private:
    TreeNode<T> *innerBuild(const std::vector<std::string> &data, int idx)
    {
        if (idx >= (int)data.size() || idx < 0 || data[idx] == nullNode)
            return nullptr;
        auto ptr = new TreeNode<T>(std::stoi(data[idx]));
        ptr->left = innerBuild(data, 2 * idx + 1);
        ptr->right = innerBuild(data, 2 * idx + 2);
        return ptr;
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
    }

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

        this->root = innerBuild(result, 0);
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