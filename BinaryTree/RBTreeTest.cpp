#include "RBTree.hpp"
using namespace std;
// test left rotate
void test1()
{
    string s = "[1,2,3,null,null,4,5]";
    RBTree<int> rbtree;
    rbtree.buildTree(s);
    rbtree.draw();
    rbtree.leftRotate(rbtree.getRoot());
    rbtree.draw();
}

// test right rotate
void test2()
{
    string s = "[1,2,3,4,5]";
    RBTree<int> tree;
    tree.buildTree(s);
    tree.draw();
    tree.rightRoate(tree.getRoot());
    tree.draw();
}

// test build tree
void test3()
{
    RBTree<int> tree;
    string s = "[111,22,333,444,533]";
    tree.buildTree(s);
    tree.draw();
}

int main()
{
    // test1();
    // test2();
    test3();
}