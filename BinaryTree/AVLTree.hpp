#include "BinaryTree.hpp"
#include <cassert>
#include <iostream>
#ifndef AVLTREE_H
#define AVLTREE_H
template <typename T>
class AVLTree : public BinaryTree<T>
{
private:
    void selfCheck()
    {
        auto v = this->inorder();
        int len = v.size();
        for (int i = 1; i < len; i++)
            assert(v[i] > v[i - 1]);
    }

public:
    void rightRotate(TreeNode<T> *p)
    {
        if (p == nullptr)
            return;
        auto lc = p->left;

        assert(lc != nullptr);

        p->left = lc->right;
        if (p->left)
            p->left->parent = p;

        if (p->parent == nullptr)
            this->root = lc;
        else if (p->parent->left == p)
            p->parent->left = lc;
        else
            p->parent->right = lc;

        lc->parent = p->parent;

        lc->right = p, p->parent = lc;

        // p = lc;
    }

    void leftRotate(TreeNode<T> *p)
    {
        // std::cout << "00";
        if (p == nullptr)
            return;
        auto rc = p->right;

        assert(rc != nullptr);

        p->right = rc->left;
        if (p->right)
            p->right->parent = p;

        if (p->parent == nullptr)
            this->root = rc;
        else if (p->parent->left == p)
            p->parent->left = rc;
        else
        {
            // std::cout << "11";
            p->parent->right = rc;
        }

        rc->parent = p->parent;

        rc->left = p, p->parent = rc;

        // p = rc;
    }
    bool insert(int val)
    {
        bool taller;
        insert(this->root, val, taller, nullptr);
        // std::cout << "111";
    }
    bool insert(TreeNode<T> *&subtree, T val, bool &taller, TreeNode<T> *parent)
    {
        if (subtree == nullptr)
        {
            subtree = new TreeNode<T>(val, AVLFactor::EH, parent);
            taller = true;
        }
        else if (val == subtree->val)
        {
            taller = false;
            return false;
        }
        else if (val < subtree->val)
        {
            if (!insert(subtree->left, val, taller, subtree))
                return false;
            if (taller)
            {
                switch (subtree->factor)
                {
                case AVLFactor::LH:
                    leftBalance(subtree);
                    taller = false;
                    break;
                case AVLFactor::EH:
                    subtree->factor = AVLFactor::LH;
                    taller = true;
                    break;
                case AVLFactor::RH:
                    subtree->factor = AVLFactor::EH;
                    taller = false;
                    break;
                default:
                    assert(0);
                    break;
                }
            }
        }
        else if (val > subtree->val)
        {
            if (!insert(subtree->right, val, taller, subtree))
                return false;
            if (taller)
            {
                switch (subtree->factor)
                {
                case AVLFactor::LH:
                    subtree->factor = AVLFactor::EH;
                    taller = false;
                    break;
                case AVLFactor::EH:
                    subtree->factor = AVLFactor::RH;
                    taller = true;
                    break;
                case AVLFactor::RH:
                    rightBalance(subtree);
                    taller = false;
                    break;
                default:
                    break;
                }
            }
        }
        else
        {
            assert(0);
        }
        return true;
    }

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

    bool remove(T val)
    {
        return remove(this->root, val);
    }

    bool remove(TreeNode<T> *&subtree, T val)
    {
    }

    void leftBalance(TreeNode<T> *p)
    {
        // lc means left child
        // lcr means leftChild->right
        TreeNode<T> *l = p->left, *lr = nullptr;
        switch (l->factor)
        {
        case AVLFactor::LH:
            p->factor = AVLFactor::EH;
            l->factor = AVLFactor::EH;
            rightRotate(p);
            break;
        case AVLFactor::RH:
            // here lcr must be not nullptr
            lr = l->right;
            switch (lr->factor)
            {
            case AVLFactor::LH:
                l->factor = AVLFactor::EH;
                lr->factor = AVLFactor::EH;
                p->factor = AVLFactor::RH;
                break;
            case AVLFactor::EH:
                l->factor = AVLFactor::EH;
                lr->factor = AVLFactor::EH;
                p->factor = AVLFactor::EH;
                break;
            case AVLFactor::RH:
                l->factor = AVLFactor::LH;
                lr->factor = AVLFactor::EH;
                p->factor = AVLFactor::EH;
                break;
            default:
                break;
            }
            leftRotate(p->left);
            rightRotate(p);
            break;
        case AVLFactor::EH:
            assert(0);
        default:
            break;
        }
    }

    void rightBalance(TreeNode<T> *p)
    {
        TreeNode<T> *r, *rl;
        r = p->right;
        switch (r->factor)
        {
        case AVLFactor::RH:
            r->factor = p->factor = AVLFactor::EH;
            leftRotate(p);
            break;
        case AVLFactor::LH:
            rl = r->left;
            switch (rl->factor)
            {
            case AVLFactor::LH:
                p->factor = AVLFactor::EH;
                r->factor = AVLFactor::RH;
                break;
            case AVLFactor::EH:
                p->factor = r->factor = AVLFactor::EH;
                break;
            case AVLFactor::RH:
                p->factor = AVLFactor::EH;
                r->factor = AVLFactor::LH;
                break;
            default:
                break;
            }
            rl->factor = AVLFactor::EH;
            rightRotate(p->right);
            leftRotate(p);
            break;
        default:
            break;
        }
    }
};

#endif