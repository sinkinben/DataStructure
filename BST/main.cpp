#include <iostream>
#include "BST.hpp"
#include "BinaryTree.hpp"

int main()
{
    auto print = [](std::vector<int> v) { for (int x : v) std::cout<<x<<' '; std::cout<<std::endl; };
    BinaryTree<int> tree;
    tree.buildTree("[10,5,-3,3,2,null,11,3,-2,null,1]");
    print(tree.preorder());
    print(tree.inorder());
    print(tree.postorder());
}
