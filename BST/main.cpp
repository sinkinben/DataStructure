#include <iostream>
#include "BST.hpp"
#include "BinaryTree.hpp"

int main()
{
    auto print = [](std::vector<int> v) { for (int x : v) std::cout<<x<<' '; std::cout<<std::endl; };
    BinaryTree<int> tree;
    std::string s1 = "[10,5,-3,3,2,null,11,3,-2,null,1]";
    std::string s2 = "[1,2,3,null,null,4,5]";
    std::string s3 = "[700,-1,800,-2,1,null,null,null,null,null,5,3,null,2,4]";
    std::string s4 = "[700,-1,800,-2,6,null,null,null,null,5,null,3,null,2,4]";
    tree.buildTree(s4);
    print(tree.preorder());
    print(tree.inorder());
    print(tree.postorder());

    BSTree<int> bstree(tree.getRoot());
    bstree.selfCheck();
    auto p = bstree.successor(5);
    std::cout << p->val << std::endl;
}
