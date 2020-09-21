#include <string>
#include <iostream>
#include "BinaryTree.hpp"
using namespace std;
int main()
{
    BinaryTree<int> tree;
    string input = "[6,2,8,0,4,7,9,null,null,3,5]";
    string cmd, buf;
    const string prompt = "> ";

    auto vprint = [](vector<int> v) {for (int x: v) cout<<x<<' '; cout<<'\n'; };

    tree.buildTree(input);
    cout << "Built tree by \'" << input << "\'" << endl;

    while (true)
    {
        cout << prompt;
        getline(cin, buf);
        stringstream ss(buf);
        ss >> cmd;
        if (cmd == "q" || cmd == "exit")
            break;
        if (cmd == "preorder")
            vprint(tree.preorder());
        else if (cmd == "inorder")
            vprint(tree.inorder());
        else if (cmd == "postorder")
            vprint(tree.postorder());
        else if (cmd == "show")
            tree.draw();
        else if (cmd == "build")
        {
            tree.destroy();
            input = buf.substr(cmd.length() + 1);
            tree.buildTree(input);
            cout << "Rebuilt tree successfully." << endl;
        }
    }
}