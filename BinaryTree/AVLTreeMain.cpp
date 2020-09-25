#include "AVLTree.hpp"
#include <sstream>
#include <functional>
using namespace std;
AVLTree<int> tree;
auto printv = [](vector<int> v) {for (int x: v) cout<<x<<' '; cout<<endl; };
void dispatch(string &cmd)
{
    stringstream ss(cmd);
    string name;
    ss >> name;
    if (name == "i")
    {
        int val;
        while (ss >> val)
            tree.insert(val);
    }
    else if (name == "r")
    {
        int val;
        ss >> val;
        tree.remove(val);
    }
    else if (name == "preorder")
    {
        printv(tree.preorder());
    }
    else if (name == "inorder")
    {
        printv(tree.inorder());
    }
    else if (name == "postorder")
    {
        printv(tree.postorder());
    }
    else if (name == "show")
    {
        tree.draw();
    }
    else
    {
        throw "Unknown command: " + name;
    }
}

int main()
{
    string cmd;
    const string prompt = "> ";
    cout << prompt;
    while (true)
    {
        getline(cin, cmd);
        if (cmd == "exit" || cmd == "q")
            break;
        try
        {
            dispatch(cmd);
        }
        catch (const string msg)
        {
            std::cerr << msg << '\n';
        }
        cout << prompt;
    }
}