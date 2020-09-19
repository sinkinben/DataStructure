#include "AVLTree.hpp"
#include <iostream>
#include <string>
using namespace std;

void test1()
{

    AVLTree<int> avl;
    string s = "[1,2,null,3,null,4]";
    avl.buildTree(s);
    avl.draw();
    avl.rightRotate(avl.getRoot()->left);
    avl.draw();
}

void test2()
{
    AVLTree<int> avl;
    string s = "[1,null,2,null,3,null,4]";
    avl.buildTree(s);
    avl.draw();
    avl.leftRotate(avl.getRoot()->right);
    avl.draw();
}

int main()
{
    string s;
    AVLTree<int> avl;
    while (getline(cin, s))
    {
        stringstream ss(s);
        int val;
        while (ss >> val)
        {
            // cout << val << endl;
            avl.insert(val);
        }
        // cout << "222";
        avl.draw();
    }
}