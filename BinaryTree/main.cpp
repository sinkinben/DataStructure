#include <iostream>
#include <sstream>
#include "BST.hpp"
#include "BinaryTree.hpp"
BSTree<int> tree;
auto vprint = [](std::vector<int> v) {for (int x: v) std::cout<<x<<' '; std::cout<<std::endl; };
void dispatchCmd(const std::string &cmd)
{
    std::stringstream ss(cmd);
    std::string name;
    ss >> name;
    //update
    if (name == "u")
    {
        int oldval, newval;
        ss >> oldval >> newval;
        tree.update(oldval, newval);
    }
    //insert
    else if (name == "i")
    {
        int val;
        while (ss >> val)
            tree.insert(val);
    }
    //remove
    else if (name == "r")
    {
        int val;
        ss >> val;
        tree.remove(val);
    }
    //sucessor
    else if (name == "s")
    {
        int val;
        ss >> val;
        auto p = tree.successor(val);
        if (p != nullptr)
            std::cout << val << "\'s sucessor is " << p->val << std::endl;
        else
            std::cout << val << " is not in the tree or has no successor\n";
    }
    // precedessor
    else if (name == "p")
    {
        int val;
        ss >> val;
        auto p = tree.predecessor(val);
        if (p != nullptr)
            std::cout << val << "\'s precedessor is " << p->val << std::endl;
        else
            std::cout << val << "is not in the tree or has no precedessor\n";
    }
    else if (name == "preorder")
    {
        vprint(tree.preorder());
    }
    else if (name == "inorder")
    {
        vprint(tree.inorder());
    }
    else if (name == "postorder")
    {
        vprint(tree.postorder());
    }
    else if (name == "show")
    {
        tree.draw();
    }
    else if (name == "cls")
    {
        system("cls");
    }
    else
    {
        throw "Unknown command\n";
    }
    tree.selfCheck();
}

int main()
{

    std::string prompt = "> ";
    std::string cmd;
    std::cout << prompt;
    while (true)
    {
        getline(std::cin, cmd);
        if (cmd == "exit" || cmd == "q")
            break;
        try
        {
            dispatchCmd(cmd);
        }
        catch (const char *msg)
        {
            std::cout << msg << std::endl;
        }
        std::cout << prompt;
    }
}
