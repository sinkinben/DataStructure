#include "TreeNode.hpp"
#include <string>
#include <stack>
#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#ifndef RBTREE_H
#define RBTREE_H
template <typename T>
class RBTree
{
public:
    TreeNode<T> *const NIL = new TreeNode<T>();
    const std::string SEPARATOR = ",";
    TreeNode<T> *root;
    void leftRotate(TreeNode<T> *x)
    {
        auto y = x->right;

        // move y.left to x.right
        x->right = y->left;
        if (x->right != NIL)
            x->right->parent = x;

        // move y to x's position
        y->parent = x->parent;
        if (x->parent == NIL)
            this->root = y;
        else if (x->parent->left == x)
            x->parent->left = y;
        else
            x->parent->right = y;

        // let x to be y.left
        y->left = x;
        x->parent = y;
    }

    void rightRoate(TreeNode<T> *y)
    {

        auto x = y->left;

        // move x.right to y.left
        y->left = x->right;
        if (y->left != NIL)
            y->left->parent = y;

        // move x to y's position
        x->parent = y->parent;
        if (y->parent == NIL)
            this->root = x;
        else if (y->parent->left == y)
            y->parent->left = x;
        else
            y->parent->right = x;

        // let y to be x.right
        x->right = y;
        y->parent = x;
    }

public:
    RBTree()
    {
        NIL->color = RBColor::Black;
        this->root = NIL;
    }
    ~RBTree()
    {
        delete NIL;
    }

    TreeNode<T> *insert(T val)
    {
        auto y = NIL, x = this->root;
        while (x != NIL)
        {
            y = x;
            if (val < x->val)
                x = x->left;
            else
                x = x->right;
        }
        auto z = new TreeNode<T>(val, y, NIL, NIL, RBColor::Red);
        if (y == NIL)
            this->root = z;
        else if (val < y->val)
            y->left = z;
        else
            y->right = z;
        insertFixup(z);
    }

    void insertFixup(TreeNode<T> *z)
    {
        while (z->parent->color == RBColor::Red)
        {
            if (z->parent == z->parent->parent->left)
            {
                auto y = z->parent->parent->right;
                if (y->color == RBColor::Red)
                {
                    z->parent->color = RBColor::Black;
                    y->color = RBColor::Black;
                    z->parent->parent->color = RBColor::Red;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = RBColor::Black;
                    z->parent->parent->color = RBColor::Red;
                    rightRoate(z->parent->parent);
                }
            }
            else
            {
                auto y = z->parent->parent->left;
                if (y->color == RBColor::Red)
                {
                    z->parent->color = RBColor::Black;
                    y->color = RBColor::Black;
                    z->parent->parent->color = RBColor::Red;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        rightRoate(z);
                    }
                    z->parent->color = RBColor::Black;
                    z->parent->parent->color = RBColor::Red;
                    leftRotate(z->parent->parent);
                }
            }
        }
        this->root->color = RBColor::Black;
    }

    std::vector<T> inorder()
    {
        std::vector<T> v;
        if (root == NIL)
            return v;
        std::stack<TreeNode<T> *> s;
        auto p = root;
        while (!s.empty() || p != NIL)
        {
            if (p != NIL)
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

    TreeNode<T> *getRoot() { return root; }

    void buildTree(std::string str)
    {
        if (str.front() == '[' & str.back() == ']')
            str = str.substr(1, str.length() - 2);
        std::vector<std::string> list;
        size_t l = 0, r = str.find(SEPARATOR, l);
        while (r != std::string::npos)
        {
            list.emplace_back(str.substr(l, r - l));
            l = r + SEPARATOR.length();
            r = str.find(SEPARATOR, l);
        }
        if (l < str.length())
            list.emplace_back(str.substr(l));
        for (std::string &x : list)
            insert(std::stoi(x));
    }

    void initx(TreeNode<T> *p, int &x)
    {
        if (p == NIL)
            return;
        initx(p->left, x);
        p->setx(x++);
        initx(p->right, x);
    }

    void inity()
    {
        if (root == NIL)
            return;
        int level = 1;
        std::queue<TreeNode<T> *> q;
        q.push(root);
        while (!q.empty())
        {
            std::queue<TreeNode<T> *> next;
            while (!q.empty())
            {
                auto p = q.front();
                q.pop();
                p->sety(level);
                if (p->left != NIL)
                    next.push(p->left);
                if (p->right != NIL)
                    next.push(p->right);
            }
            q = next;
            level++;
        }
    }

    void draw(int widthzoom = 3)
    {
        typedef std::pair<int, int> Pair;
        auto printNode = [](RBColor color, T val) {
            if (color == RBColor::Red)
                std::cout << "\033[41m" << val << "\033[0m";
            else if (color == RBColor::Black)
                std::cout << "\033[40m" << val << "\033[0m";
        };
        auto printChars = [](char c, int n) {for(;n>0;n--) std::cout << c; };
        int x = 0;
        initx(root, x);
        inity();

        std::queue<TreeNode<T> *> q;
        int y, val;
        std::string sval;
        RBColor color;

        q.push(root);

        while (!q.empty())
        {
            std::queue<TreeNode<T> *> next;
            std::vector<Pair> pairs;
            int idx = 0;
            while (!q.empty())
            {
                auto p = q.front();
                q.pop();
                color = p->color;
                x = p->getx() * widthzoom, y = p->gety(), val = p->val, sval = std::to_string(val);
                printChars(' ', x - idx), printNode(color, val);
                idx += (x + sval.length());
                if (p->left != NIL)
                {
                    next.push(p->left);
                    pairs.push_back(Pair(p->left->getx() * widthzoom, x + sval.length() / 2));
                }
                if (p->right != NIL)
                {
                    next.push(p->right);
                    pairs.push_back(Pair(x + sval.length() / 2 + 1,
                                         p->right->getx() * widthzoom + std::to_string(p->right->val).length()));
                }
            }
            std::cout << '\n';
            idx = 0;
            if (!pairs.empty())
            {
                std::string line;
                for (auto &p : pairs)
                {
                    line.append(p.first - line.length(), ' ');
                    line.append(p.second - p.first, '_');
                    line.append(1, '|');
                }
                line.pop_back();
                std::cout << line << '\n';
            }
            q = next;
        }
    }
};
#endif