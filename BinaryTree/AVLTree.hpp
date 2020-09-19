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
            p->parent->right = rc;

        rc->parent = p->parent;

        rc->left = p, p->parent = rc;

        // p = rc;
    }
    bool insert(int val)
    {
        bool taller;
        insert(this->root, val, taller);
        // std::cout << "111";
    }
    bool insert(TreeNode<T> *&subtree, T val, bool &taller)
    {
        if (subtree == nullptr)
        {
            subtree = new TreeNode<T>(val, AVLFactor::EH);
            taller = true;
        }
        else if (val == subtree->val)
        {
            taller = false;
            return false;
        }
        else if (val < subtree->val)
        {
            if (!insert(subtree->left, val, taller))
                return false;
            if (taller)
            {
                switch (subtree->factor)
                {
                case AVLFactor::LH:
                    leftBalance(subtree);
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
            if (!insert(subtree->right, val, taller))
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
    }

    void leftBalance(TreeNode<T> *p)
    {
        // lc means left child
        // lcr means leftChild->right
        TreeNode<T> *lc = p->left, *lcr = nullptr;
        switch (lc->factor)
        {
        case AVLFactor::LH:
            p->factor = AVLFactor::EH;
            lc->factor = AVLFactor::EH;
            rightRotate(p);
            break;
        case AVLFactor::RH:
            // here lcr must be not nullptr
            lcr = lc->right;
            switch (lcr->factor)
            {
            case AVLFactor::LH:
                lc->factor = AVLFactor::EH;
                lcr->factor = AVLFactor::EH;
                p->factor = AVLFactor::RH;
                break;
            case AVLFactor::EH:
                lc->factor = AVLFactor::EH;
                lcr->factor = AVLFactor::EH;
                p->factor = AVLFactor::EH;
                break;
            case AVLFactor::RH:
                lc->factor = AVLFactor::LH;
                lcr->factor = AVLFactor::EH;
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
        TreeNode<T> *lc, *lcr;
        lc = p->right;
        switch (lc->factor)
        {
        case AVLFactor::RH:
            lc->factor = p->factor = AVLFactor::EH;
            leftRotate(p);
            break;
        case AVLFactor::LH:
            lcr = lc->left;
            switch (lcr->factor)
            {
            case AVLFactor::LH:
                p->factor = AVLFactor::EH;
                lc->factor = AVLFactor::RH;
                break;
            case AVLFactor::EH:
                p->factor = lc->factor = AVLFactor::EH;
                break;
            case AVLFactor::RH:
                p->factor = AVLFactor::EH;
                lc->factor = AVLFactor::LH;
                break;
            default:
                lcr->factor = AVLFactor::EH;
                rightRotate(p->right);
                leftRotate(p);
                break;
            }
            break;
        default:
            break;
        }
    }
};

#endif